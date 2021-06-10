#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 0x200
#define ERRMSG "Can't open "
#define ERRMSG_LEN 11

int main(int argc, char **argv) {
    if (argc < 2) {
        char buf[BUFFER_SIZE] = {0};
        ssize_t len;
        
        while ((len = read(STDIN_FILENO, buf, BUFFER_SIZE)) > 0) {
            write(STDOUT_FILENO, buf, len);
        }
    } else {
        for (int i = 1; i < argc; i++) {
            char *path = argv[i];
            char buf[BUFFER_SIZE] = {0};

            int fd = open(path, O_RDONLY);
            if (fd < 0) {
                int path_len = strlen(path);
                write(STDOUT_FILENO, ERRMSG, ERRMSG_LEN);
                write(STDOUT_FILENO, path, path_len);
                write(STDOUT_FILENO, "\n", 1);
                return 1;
            }

            ssize_t len;

            while ((len = read(fd, buf, BUFFER_SIZE)) > 0) {
                write(STDOUT_FILENO, buf, len);
            }
        }
    }
}
