#include <ctype.h> 
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char* DEFAULT_BUFFER_VALUE = "--";

#define DIGITS_IN_LETTERS_SIZE 9
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

int get_lower_positive_element_i(int *arr, int len) {
    int min = INT_MAX;
    int out = -1;
    for(int i = 0; i < len; i++) {
        if(arr[i] >= 0 && arr[i] < min) {
            min = arr[i];
            out = i;
        }
    }
   
    return out;
}

void replace_digits(char *str) {
    char *digit_pointers[DIGITS_IN_LETTERS_SIZE];
    memset(digit_pointers, NULL, sizeof(digit_pointers));
    int digit_positions[DIGITS_IN_LETTERS_SIZE];
    memset(digit_positions, -1, sizeof(digit_positions));
    for(int i = 0; i < DIGITS_IN_LETTERS_SIZE; i++) {
        char *digit_in_str = strstr(str, DIGITS_IN_LETTERS[i]);
        if(digit_in_str != NULL) {
            digit_pointers[i] = digit_in_str; 
            digit_positions[i] = digit_in_str - str; 
        }
    }

    for(int i = 0; i < DIGITS_IN_LETTERS_SIZE; i++) {
        printf("%d; %s\n", digit_positions[i], digit_pointers[i]);
    }

    print_separators(1);
    int first_digit_i = get_lower_positive_element_i(digit_positions, DIGITS_IN_LETTERS_SIZE);
    printf("first digit i: %d\n", first_digit_i);

    if(first_digit_i == -1) {
        return;
    }

    // TODO replace all chars of digits in letter with corresponding digit
    *digit_pointers[first_digit_i] = (first_digit_i + 1) + '0';
    replace_digits(str);
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
    }

    printf("output: %d\n", output);

    free(line);
    exit(EXIT_SUCCESS);
}
