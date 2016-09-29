#ifndef DSE_PROCESS_WRAPPER_UTILS_H
#define DSE_PROCESS_WRAPPER_UTILS_H

/**
 * Waits for a single value in a pipe. Success is assumed iff the value is
 * read and it is 1.
 * @param pipe pipe descriptors array as returned from pipe method
 * @return 0 for success, -1 for failure
 */
int read_status(int *pipe);

/**
 * Writes a value 1 into a give pipe.
 * @param pipe pipe descriptors arrays as returned from pipe method
 * @return 0 for success, -1 for failure
 */
int write_status(int *pipe);

/**
 * Closes a descriptor for reading in a given pipe.
 * @param pipe pipe descriptors arrays as returned from pipe method
 */
void close_input(int *pipe);

/**
 * Closes a descriptor for writing in a given pipe.
 * @param pipe pipe descriptors arrays as returned from pipe method
 */
void close_output(int *pipe);

/**
 * Prints a message into stderr, including a resolved error string if errno
 * denotes an error.
 */
void log_error(const char *fmt, ...);

/**
 * Waits for the child process to die. An exit status is written into status
 * param.
 * @return 0 for success, -1 for failure
 */
int wait_for_child(int pid, int &status);

#endif //DSE_PROCESS_WRAPPER_UTILS_H
