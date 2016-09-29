#ifndef SIMPLE_WRAPPER_NS_UTILS_H
#define SIMPLE_WRAPPER_NS_UTILS_H

#include <sys/types.h>

/**
 * Set UID mapping with newuidmap command.
 * @return 0 for success, -1 for failure
 */
int new_uid_map(int pid, int child_uid, int parent_uid, int range);

/**
 * Set GID mapping with newuidmap command.
 * @return 0 for success, -1 for failure
 */
int new_gid_map(int pid, int child_uid, int parent_uid, int range);

/**
 * Combined setting UID and GID mapping with newuidmap and newgidmap
 * commands respectively. It assumes UID == GID therefore just a single
 * value for id in child process, id in parent process and range.
 * @return 0 for success, -1 for failure
 */
int new_id_map(int pid, int child_id, int parent_id, int range);

/**
 * Combined setting UID, GID and additional groups.
 * @return 0 for success, -1 for failure
 */
int set_id(uid_t uid, gid_t gid, size_t groups_cnt, gid_t *groups);

/**
 * Recursively set propagation for a given mount point.
 * @param target mount point
 * @param propagation one of allowed propagation values
 * @return 0 for success, -1 for failure
 */
int set_propagation(const char *target, unsigned long propagation);

/**
 * Unmounts and the mounts a file system. Failure during unmounting doesn't
 * cause the method to fail - it is silently ignored.
 * @return 0 for success, -1 for failure
 */
int mount_fs(const char *source, const char *target,
             const char *type, unsigned long flags);

#endif //SIMPLE_WRAPPER_NS_UTILS_H
