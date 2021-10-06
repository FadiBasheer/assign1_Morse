/*
 * This file is part of dc_dump.
 *
 *  dc_dump is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Foobar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with dc_dump.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <dc_posix/dc_unistd.h>
#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define BUF_SIZE 1024

void print_binary(int *binary, int str_len) {
    printf("\n\nBinary Converter: \n");
    for (int i = 1; i <= 8 * str_len; i++) {
        printf("%d", binary[i - 1]);
        if (i % 8 == 0) {
            printf(" ");
        }
    }
}


void addingHam(int location, int *a, int *binary, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (binary[a[i] - 1] == 1) {
            count++;
        }
        // printf("---- %d", binary[a[i] - 1]);
    }
    if ((count % 2) != 0) {
        binary[location - 1] = 1;
    }
}

int main(void) {
    struct dc_error err;
    struct dc_posix_env env;
    char chars[BUF_SIZE];
    ssize_t nread;
    int ret_val;

    dc_error_init(&err, NULL);
    dc_posix_env_init(&env, NULL);
    ret_val = EXIT_SUCCESS;

    /*
    while ((nread = dc_read(&env, &err, STDIN_FILENO, chars, BUF_SIZE)) > 0) {
        if (dc_error_has_error(&err)) {
            ret_val = 1;
        }


        for (int i = 0; i < strlen(chars); i++) {
            chars[i] = toupper(chars[i]);
        }
        dc_write(&env, &err, STDOUT_FILENO, chars, (size_t) nread);

        if (dc_error_has_error(&err)) {
            ret_val = 2;
        }
    }
*/


    //reading from keyboard
    nread = dc_read(&env, &err, STDIN_FILENO, chars, BUF_SIZE);
    int str_len = strlen(chars) - 1;

    printf("strlen(chars): %d\n", str_len);
    int i, j, k = 8, num;
    int binary[8 * str_len];

    //filling binary array with zeros
    for (i = 0; i < 8 * str_len; i++) {
        binary[i] = 0;
    }

    //converting each char and filling the binary array
    for (i = 0; i < str_len; i++) {
        j = k - 1;
        num = chars[i];
        printf("num: %d\n", num);
        while (num != 0) {
            binary[j--] = num % 2;
            num /= 2;
        }
        k += 8; // because the next position of second character is at index of (7+8)=15
    }


// Convert from 8 to 12
    int testbinary[12];
    for (i = 0; i < 12; i++) {
        testbinary[i] = 0;
    }
    int bin = 0;
    int one[5] = {3, 5, 7, 9, 11};
    int tow[5] = {3, 6, 7, 10, 11};
    int four[4] = {5, 6, 7, 12};
    int eight[4] = {9, 10, 11, 12};

    // and open the files at the same time
    FILE *f1;
    f1 = fopen("program1.txt", "w");
    FILE *f2;
    f2 = fopen("program2.txt", "w");
    FILE *f3;
    f3 = fopen("program3.txt", "w");
    FILE *f4;
    f4 = fopen("program4.txt", "w");
    if (f1 == NULL | f2 == NULL | f3 == NULL | f4 == NULL) {
        printf("Error!");
        exit(1);
    }


    for (int ou = 1; ou <= (8 * str_len); ou += 8) {
        for (i = 1; i <= 12; i++) {
            double rem = remainder(log(i), log(2));
            double newRem;
            if (rem < 0) { newRem = -(rem); }
            else { newRem = rem; }

            if (newRem < 0.0000001) {
                testbinary[i - 1] = 0;
            } else {
                testbinary[i - 1] = binary[bin++];
            }
        }
        addingHam(1, one, testbinary, 5);
        addingHam(2, tow, testbinary, 5);
        addingHam(4, four, testbinary, 4);
        addingHam(8, eight, testbinary, 4);
        printf("\n");

        fprintf(f1, "%d", testbinary[0]);
        fprintf(f2, "%d", testbinary[1]);
        fprintf(f3, "%d", testbinary[2]);
        fprintf(f4, "%d", testbinary[3]);
        for (int p = 0; p < 12; p++) {
            printf("%d", testbinary[p]);
        }
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);

    printf("\n");

    return ret_val;
}

