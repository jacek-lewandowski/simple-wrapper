#include <iostream>
#include <unistd.h>
#include <ns_utils.h>
#include <sys/mount.h>

#include "utils.h"

int run_application()
{
    system("id");
    system("ps aux");
    return 0;
}

int mount_filesystems()
{
    // inability to remount /proc is important because if it failed the child
    // process would see the full processes list with their command line args
    if (set_propagation("/proc", MS_PRIVATE) ||
        mount_fs("proc", "/proc", "proc", MS_NOSUID | MS_NOEXEC | MS_NODEV))
        return -1;

    return 0;
}

static int child_process(void *arg)
{
    int *from_parent = (int *) arg;

    // we don't need those endpoints in the child process
    close_output(from_parent);

    int ret = -1;
    if (read_status(from_parent))
        log_error("Failed waiting for parent to setup mappings");
    else if (mount_filesystems())
        log_error("Failed to mount file systems");
    else if (set_id(0, 0, 0, NULL));
    else if (set_propagation("/", MS_PRIVATE));
    else ret = 0;

    close_input(from_parent);

    // now, assuming the setup phase passed, we can run the wrapped app
    return ret || run_application();
}

int main(int argc, char *argv[])
{
    // create and setup pipe
    int to_child[2];

    if (pipe(to_child) < 0)
    {
        log_error("Failed to create a pipe");
        return -1;
    }

    size_t stack_size = (size_t) sysconf(_SC_PAGESIZE);
    void *stack = alloca(stack_size);

    int flags = CLONE_NEWUSER | CLONE_NEWNS | CLONE_NEWPID | CLONE_NEWIPC;
    int pid = clone(child_process, stack + stack_size, flags, &to_child);
    if (pid > 0)
    {
        // we don't need this endpoint in the parent process
        close_input(to_child);

        // we will send a notification to the client only if new_id_map
        // succeeded
        if (new_id_map(pid, 0, 100000, 10));
        else if (write_status(to_child))
            log_error("Failed to notify child that mappings are set");

        // regardless of the result of setup_parent we want to close
        // the remaining pipe endpoints
        close_output(to_child);

        // if parent failed at some point, the child process will not
        // receive any notification and therefore it will die with error
        // status, thus we do not need to check the result of setup_parent
        int ret, status;
        if ((ret = wait_for_child(pid, status))) return ret;
        else if (!WIFEXITED(status))
            log_error("The process %u exited with non-zero exit code %d",
                      pid, status);

        return status;
    }
    else
    {
        log_error("Failed to create a child process: %d\n", pid);
        return 1;
    }
}
