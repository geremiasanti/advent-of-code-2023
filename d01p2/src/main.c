#include <ctype.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* DEFAULT_BUFFER_VALUE = "--";

const int DIGITS_IN_LETTERS_SIZE = 9;
const char* DIGITS_IN_LETTERS[] = { 
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

void print_separators(size_t rows) {
    for(int i = 0; i < rows; i++) {
        printf("----------------------------------------------------------\n");
    }
}

void replace_digits(char *str) {
    int digits_i;
    const char *digit_char;
    for(char *str_char = str; *str_char != '\0'; str_char++) {
        if(!isalpha(*str_char)) 
            continue;

        printf("str_char: %c\n", *str_char);

        for(digits_i = 0; digits_i < DIGITS_IN_LETTERS_SIZE; digits_i++) {
            for(digit_char = DIGITS_IN_LETTERS[digits_i]; *digit_char != '\0'; digit_char++) {
                printf("digit_char: %c\n", *digit_char); 
            }
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
        print_separators(1);
        printf("replaced: %s", line);
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

        break;
    }

    printf("output: %d\n", output);

    free(line);
    exit(EXIT_SUCCESS);
}
