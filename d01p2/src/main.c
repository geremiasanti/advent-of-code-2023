#include <ctype.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* DEFAULT_BUFFER_VALUE = "--";

const int DIGITS_IN_LETTERS_SIZE = 10;
const char* DIGITS_IN_LETTERS[] = { 
    "zero", 
    "one", 
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
};

void print_separators(int rows) {
    for(int i = 0; i < rows; i++) {
        printf("----------------------------------------------------------\n");
    }
}

void replace_digits(char *str) {
    char *found_digit_in_letters = NULL;
    for(int i = 0; i < DIGITS_IN_LETTERS_SIZE; i++) {
        while((found_digit_in_letters = strstr(str, DIGITS_IN_LETTERS[i])) != NULL) {
            // convert i to corresponding char
            found_digit_in_letters[0] = i + '0';
        }
    }
}

int main(int argc, char *argv[]) {
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
        print_separators(1);

        replace_digits(line);
        printf("translated: %s", line);
        print_separators(1);

        strcpy(buffer, DEFAULT_BUFFER_VALUE);
        for(int i = 0; i < len; i++) {
            if(isdigit(line[i])) {
                if(buffer[0] == '-')
                    buffer[0] = line[i];

                buffer[1] = line[i];
            }
        } 

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
