#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFF_SIZE 32
#define MAX_ENV_LEN 1024*1024
#define MAX_ENV_NUM 1024

int main (int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <pid|environ-file> [cmd [arg]...]\n", argv[0]);
        exit(1);
    }

    char filename[BUFF_SIZE] = {0};
    char *pname = filename;
    if (argv[1][0] == '/') {
        pname = argv[1];
    } else {
        snprintf(filename, BUFF_SIZE, "/proc/%s/environ", argv[1]);
    }

    int fd = open(pname, O_RDONLY);
    if (fd == -1) {
        perror(pname);
        exit(1);
    }

    char environ[MAX_ENV_LEN+2] = {0};
    int len = read(fd, environ, MAX_ENV_LEN);
    if (len == -1) {
        perror(pname);
        exit(1);
    }

    if (len == MAX_ENV_LEN) {
        fprintf(stderr, "environ more than %d bytes, may be truncated.\n", MAX_ENV_LEN);
    }

    char* envp[MAX_ENV_NUM] = {0};
    int count = 0;
    char *p = environ;
    for (; count < MAX_ENV_NUM && *p; count++) {
        envp[count] = p;
        p += strlen(p) + 1;
    }

    if (count == MAX_ENV_NUM) {
        fprintf(stderr, "vars more than %d, some have been discarded.\n", MAX_ENV_NUM);
    }

    if (argc <= 2) {
        int i;
        for (i = 0; i < count; i++) {
            printf("%s\n", envp[i]);
        }
        exit(0);
    }

    if (-1 == execvpe(argv[2], argv + 2, envp)) {
        perror("exec");
        exit(1);
    }

    exit(9);
}
