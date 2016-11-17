#include <cstdio>
#include <unistd.h>

int main(int argc, char *argv[])
{
    FILE *fp;

    if ((fp = fopen("sample.result", "w")) == NULL)
    {
        return -1;
    }

    uid_t uid = getuid();
    uid_t euid = geteuid();
    gid_t gid = getgid();
    gid_t egid = getegid();
    fprintf(fp, "UID %d\n", uid);
    fprintf(fp, "EUID %d\n", euid);
    fprintf(fp, "GID %d\n", gid);
    fprintf(fp, "EGID %d\n", egid);

    fprintf(fp, "ARGUMENTS %d\n", argc);
    for (int i = 0; i < argc; i++)
    {
        fprintf(fp, "%s\n", argv[i]);
    }

    int envc = -1;
    while (environ[++envc] != NULL);
    fprintf(fp, "ENVIRONMENT %d\n", envc);
    for (int i = 0; i < envc; i++)
    {
        fprintf(fp, "%s\n", environ[i]);
    }

    fclose(fp);

    return 0;
}
