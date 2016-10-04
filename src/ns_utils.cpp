#include <utils.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mount.h>
#include <cstring>
#include <grp.h>

static int _new_map(const char *id_type, int pid,
                    int child_id, int parent_id, int range)
{
    char cmd[100];

    memset(cmd, '\0', sizeof(cmd));
    int ret = snprintf(cmd, sizeof(cmd), "new%smap %u %u %u %u", id_type,
                       pid, child_id, parent_id, range);

    if (ret >= sizeof(cmd) && ret < 1)
        log_error("Cannot format command for setting ID map: %d.", ret);
    else if (system(cmd) != 0)
        log_error("Failed to setup %s map", id_type);
    else
        return 0;

    return -1;
}

int new_uid_map(int pid, int child_uid, int parent_uid, int range)
{
    return _new_map("uid", pid, child_uid, parent_uid, range);
}

int new_gid_map(int pid, int child_uid, int parent_uid, int range)
{
    return _new_map("gid", pid, child_uid, parent_uid, range);
}

int new_id_map(int pid, int child_id, int parent_id, int range)
{
    if (new_uid_map(pid, child_id, parent_id, range) ||
        new_gid_map(pid, child_id, parent_id, range))
        return -1;

    return 0;
}

int set_id(uid_t uid, gid_t gid, size_t groups_cnt, gid_t *groups)
{
    if (setgid(gid))
        log_error("Failed to set GID to %u", gid);
    else if (setuid(uid))
        log_error("Failed to set UID to %u", uid);
    else if (setgroups(groups_cnt, groups))
        log_error("Failed to set additional groups");
    else
        return 0;

    return -1;
}

int set_propagation(const char *target, unsigned long propagation)
{
    const unsigned long valid_propagation =
            MS_SHARED | MS_SLAVE | MS_PRIVATE | MS_UNBINDABLE;
    if (propagation & valid_propagation != propagation)
        log_error("Invalid propagation was specified %u", propagation);
    else if (mount(NULL, target, NULL, propagation | MS_REC, NULL))
        log_error("Failed to set propagation of %s to %u",
                  target, propagation);
    else
        return 0;

    return -1;

}

int mount_fs(const char *source, const char *target,
             const char *type, unsigned long flags)
{
    // may fail, especially if the mount point does not exist
    // but we don't care about that, because the purpose of this method
    // is to mount/remount
    umount(target);

    if (mount(source, target, type, flags, NULL))
        log_error("Failed to mount %s", source);
    else
        return 0;

    return -1;
}
