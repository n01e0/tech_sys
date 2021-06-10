#include <stdio.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        char buf[0x200] = {0};

        while ((fgets(buf, 0x200, stdin)) != NULL) {
            for (int i = 0; i < 0x200; i++) {
                putchar(buf[i]);
                if (buf[i] == '\n') 
                    break;
            }
        }
    } else {
        for (int i = 1; i < argc; i++) {
            char *path = argv[i];

            FILE *fp = fopen(path, "r");

            if (fp == NULL) {
                printf("Can't open %s\n", path);
                return 1;
            }

            char buf[0x200] = {0};
            size_t len;

            while ((len = fread(buf, sizeof(char), 0x200, fp)) != 0) {
                fwrite(buf, sizeof(char), len, stdout);
            }
        }
    }
}

