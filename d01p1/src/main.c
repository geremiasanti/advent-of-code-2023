#include <ctype.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_separators(int rows) {
    for(int i = 0; i < rows; i++) {
        printf("----------------------------------------------------------\n");
    }
}

int main(int argc, char* argv []) {
    // file
    FILE *fp;

    // reading
    char *line = NULL;
    size_t allocated_size = 0;
    ssize_t len;

    // digits
    char buffer[3];
    int calibration_value;

    // output
    int output;

    if(argc < 2) {
        printf("Missing first argument (input file)\n");
        exit(EXIT_FAILURE);
    }

    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Can't read input file (%s)\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    printf("reading file %s\n", argv[1]);
    print_separators(2);

    output = 0;
    while((len = getline(&line, &allocated_size, fp)) != -1) {
        printf("Retrieved line of length %zu:\n", len);
        printf("%s", line);

        strcpy(buffer, "--");
        for(int i = 0; i < len; i++) {
            if(isdigit(line[i])) {
                if(buffer[0] == '-')
                    buffer[0] = line[i];

                buffer[1] = line[i];
            }
        } 

        print_separators(1);

        calibration_value = atoi(buffer);
        output += calibration_value;
        printf("calibration_value: %d\naccumulated: %d\n", 
               calibration_value,
               output);

        print_separators(2);
    }

    printf("output: %d\n", output);

    free(line);
    exit(EXIT_SUCCESS);
}
