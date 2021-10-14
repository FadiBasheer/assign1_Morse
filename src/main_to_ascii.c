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
#include <bits/stdint-uintn.h>

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

    printf("num: %d\n", 'A');


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

    //reading from keyboard afdfiourfkaljgv
    nread = dc_read(&env, &err, STDIN_FILENO, chars, BUF_SIZE);
    size_t str_len = strlen(chars) - 1;

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
        while (num != 0) {
            binary[j--] = num % 2;
            num /= 2;
        }
        k += 8; // because the next position of second character is at index of (7+8)=15
    }


// Convert from 8 to 12
    uint8_t testbinary[12];
    for (i = 0; i < 12; i++) {
        testbinary[i] = 0;
    }
    int bin = 0;
    int one[5] = {3, 5, 7, 9, 11};
    int tow[5] = {3, 6, 7, 10, 11};
    int four[4] = {5, 6, 7, 12};
    int eight[4] = {9, 10, 11, 12};

    // and open the files at the same time
    FILE *f0;
    f0 = fopen("program0.hamming", "w");
    FILE *f1;
    f1 = fopen("program1.hamming", "w");
    FILE *f2;
    f2 = fopen("program2.hamming", "w");
    FILE *f3;
    f3 = fopen("program3.hamming", "w");
    FILE *f4;
    f4 = fopen("program4.hamming", "w");
    FILE *f5;
    f5 = fopen("program5.hamming", "w");
    FILE *f6;
    f6 = fopen("program6.hamming", "w");
    FILE *f7;
    f7 = fopen("program7.hamming", "w");
    FILE *f8;
    f8 = fopen("program8.hamming", "w");
    FILE *f9;
    f9 = fopen("program9.hamming", "w");
    FILE *f10;
    f10 = fopen("program10.hamming", "w");
    FILE *f11;
    f11 = fopen("program11.hamming", "w");

    if (f1 == NULL | f2 == NULL | f3 == NULL | f4 == NULL) {
        printf("Error!");
        exit(1);
    }

    uint8_t byte0 = 0, byte1 = 0, byte2 = 0, byte3 = 0, byte4 = 0, byte5 = 0, byte6 = 0, byte7 = 0, byte8 = 0, byte9 = 0, byte10 = 0, byte11 = 0;
    int looop = 0;

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

        //Writing one bit to each file, we just need to do it 12 times
//        fprintf(f1, "%d", testbinary[0]);
//        fprintf(f2, "%d", testbinary[1]);
//        fprintf(f3, "%d", testbinary[2]);
//        fprintf(f4, "%d", testbinary[3]);

        printf("\n");

        for (int p = 0; p < 12; p++) {
            printf("%d", testbinary[p]);
        }
        printf("\n");

        if (looop == 8) {
            fprintf(f0, "%d", byte0);
            fprintf(f1, "%d", byte1);
            fprintf(f2, "%d", byte2);
            fprintf(f3, "%d", byte3);
            fprintf(f4, "%d", byte4);
            fprintf(f5, "%d", byte5);
            fprintf(f6, "%d", byte6);
            fprintf(f7, "%d", byte7);
            fprintf(f8, "%d", byte8);
            fprintf(f9, "%d", byte9);
            fprintf(f10, "%d", byte10);
            fprintf(f11, "%d", byte11);

            byte0 = 0, byte1 = 0, byte2 = 0, byte3 = 0, byte4 = 0, byte5 = 0, byte6 = 0, byte7 = 0, byte8 = 0, byte9 = 0, byte10 = 0, byte11 = 0;
            looop = 0;
        }
        looop++;

        //shifting by one
        byte0 = (uint8_t) (byte0 << 1);
        byte1 = (uint8_t) (byte1 << 1);
        byte2 = (uint8_t) (byte2 << 1);
        byte3 = (uint8_t) (byte3 << 1);
        byte4 = (uint8_t) (byte4 << 1);
        byte5 = (uint8_t) (byte5 << 1);
        byte6 = (uint8_t) (byte6 << 1);
        byte7 = (uint8_t) (byte7 << 1);
        byte8 = (uint8_t) (byte8 << 1);
        byte9 = (uint8_t) (byte9 << 1);
        byte10 = (uint8_t) (byte10 << 1);
        byte11 = (uint8_t) (byte11 << 1);

        printf("bit0: %d", (testbinary[0] >> 0) & 0x01);
        printf("  bit1: %d", (testbinary[1] >> 0) & 0x01);
        printf("  bit2: %d", (testbinary[2] >> 0) & 0x01);
        printf("  bit3: %d", (testbinary[3] >> 0) & 0x01);
        printf("  bit4: %d", (testbinary[4] >> 0) & 0x01);
        printf("  bit5: %d", (testbinary[5] >> 0) & 0x01);
        printf("  bit6: %d", (testbinary[6] >> 0) & 0x01);
        printf("  bit7: %d", (testbinary[7] >> 0) & 0x01);
        printf("  bit8: %d", (testbinary[8] >> 0) & 0x01);
        printf("  bit9: %d", (testbinary[9] >> 0) & 0x01);
        printf("  bit10: %d", (testbinary[10] >> 0) & 0x01);
        printf("  bit11: %d\n", (testbinary[11] >> 0) & 0x01);

        //adding the first bit
        byte0 = (uint8_t) (byte0 | (testbinary[0] >> 0));
        byte1 = (uint8_t) (byte1 | (testbinary[1] >> 0));
        byte2 = (uint8_t) (byte2 | (testbinary[2] >> 0));
        byte3 = (uint8_t) (byte3 | (testbinary[3] >> 0));
        byte4 = (uint8_t) (byte4 | (testbinary[4] >> 0));
        byte5 = (uint8_t) (byte5 | (testbinary[5] >> 0));
        byte6 = (uint8_t) (byte6 | (testbinary[6] >> 0));
        byte7 = (uint8_t) (byte7 | (testbinary[7] >> 0));
        byte8 = (uint8_t) (byte8 | (testbinary[8] >> 0));
        byte9 = (uint8_t) (byte9 | (testbinary[9] >> 0));
        byte10 = (uint8_t) (byte10 | (testbinary[10] >> 0));
        byte11 = (uint8_t) (byte11 | (testbinary[11] >> 0));


        //printf("byte0: = %d\n", byte0);

        //printing the byte
        for (int l = 7; l >= 0; --l) { printf("%d", (byte0 >> l) & 0x01); }
        printf(" ");
        for (int l = 7; l >= 0; --l) { printf("%d", (byte1 >> l) & 0x01); }
        printf(" ");
        for (int l = 7; l >= 0; --l) { printf("%d", (byte2 >> l) & 0x01); }
        printf(" ");
        for (int l = 7; l >= 0; --l) { printf("%d", (byte3 >> l) & 0x01); }
        printf(" ");
        for (int l = 7; l >= 0; --l) { printf("%d", (byte4 >> l) & 0x01); }
        printf(" ");
        for (int l = 7; l >= 0; --l) { printf("%d", (byte5 >> l) & 0x01); }
        printf(" ");
        for (int l = 7; l >= 0; --l) { printf("%d", (byte6 >> l) & 0x01); }
        printf(" ");
        for (int l = 7; l >= 0; --l) { printf("%d", (byte7 >> l) & 0x01); }
        printf(" ");
        for (int l = 7; l >= 0; --l) { printf("%d", (byte8 >> l) & 0x01); }
        printf(" ");
        for (int l = 7; l >= 0; --l) { printf("%d", (byte9 >> l) & 0x01); }
        printf(" ");
        for (int l = 7; l >= 0; --l) { printf("%d", (byte10 >> l) & 0x01); }
        printf(" ");
        for (int l = 7; l >= 0; --l) { printf("%d", (byte11 >> l) & 0x01); }


    }
    fprintf(f0, "%d", byte0);
    fprintf(f1, "%d", byte1);
    fprintf(f2, "%d", byte2);
    fprintf(f3, "%d", byte3);
    fprintf(f4, "%d", byte4);
    fprintf(f5, "%d", byte5);
    fprintf(f6, "%d", byte6);
    fprintf(f7, "%d", byte7);
    fprintf(f8, "%d", byte8);
    fprintf(f9, "%d", byte9);
    fprintf(f10, "%d", byte10);
    fprintf(f11, "%d", byte11);

    fclose(f0);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
    fclose(f6);
    fclose(f7);
    fclose(f8);
    fclose(f9);
    fclose(f10);
    fclose(f11);

    printf("\n");

    return ret_val;
}

