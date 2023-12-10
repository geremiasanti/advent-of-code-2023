#include <stdio.h>
#include <stdlib.h>

void print_separators(int rows) {
    for(int i = 0; i < rows; i++) {
        printf("----------------------------------------------------------\n");
    }
}

int main(int argc, char* argv []) {
    FILE *fp;
    char *line = NULL;
    size_t allocated_size = 0;
    ssize_t len;

    if(argc < 2) {
        printf("Missing first argument (input file)\n");
        exit(EXIT_FAILURE);
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Can't read input file (%s)\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    printf("reading file %s\n", argv[1]);
    print_separators(2);
    while ((len = getline(&line, &allocated_size, fp)) != -1) {
        printf("Retrieved line of length %zu:\n", len);
        printf("%s", line);

        // make shit happen

        print_separators(2);
    }

    free(line);
    exit(EXIT_SUCCESS);
}
