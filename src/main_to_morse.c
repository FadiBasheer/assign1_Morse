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
#include <string.h>

int main(void) {
    display("Hello, World!");
    const char *strs[36] = {"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.",
                            ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--",
                            "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--",
                            "--.."};

    printf("num: %s\n", strs[38 - 27]);
    size_t len = strlen(strs[38 - 27]);
    printf("%d\n", len);
//    for (int i = 0; i < len; i++) {
//        printf("%c", source[i]);
//    }
    printf("num: %s\n", strs[35]);

    return EXIT_SUCCESS;
}