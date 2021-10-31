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

#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <dc_posix/dc_fcntl.h>
#include <dc_posix/dc_unistd.h>
#include <bits/stdint-uintn.h>

#define BUF_SIZE 1024


static void error_reporter(const struct dc_error *err) {
    printf("\n");
    fprintf(stderr, "ERROR: %s : %s : @ %zu : %d\n", err->file_name, err->function_name, err->line_number,
            err->err_code);
    fprintf(stderr, "ERROR: %s\n", err->message);
    printf("\n");
}

int main(void) {

    struct dc_error err;
    struct dc_posix_env env;
    uint8_t byte0 = 0;
    int ret_val = EXIT_SUCCESS;

    dc_error_init(&err, NULL);
    dc_posix_env_init(&env, NULL);
    int fd0 = dc_open(&env, &err, "./program0.hamming", DC_O_RDONLY, 0);

    if (dc_error_has_no_error(&err)) {
        ssize_t nread;
        printf("sdfasfafasfasfsfasdfsf\n");
        while ((nread = dc_read(&env, &err, fd0, &byte0, 1)) > 0) {
            if (dc_error_has_error(&err)) {
                ret_val = 1;
            }
//            for (size_t j = 0; j < 7; j++) {
//                uint8_t oneByte;
//                printf("bit0: %d", (byte0 >> j) & 0x01);
//                uint8_t temp0 = (byte0 >> j) & 0x01;
//                oneByte = (byte0 >> j) & 0x01;
//            }


            printf("file: %d\n", byte0);
            if (dc_error_has_error(&err)) {
                ret_val = 2;
            }
        }
        dc_dc_close(&env, &err, fd0);
    }
    error_reporter(&err);
    return ret_val;
}