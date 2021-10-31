#include <dc_application/command_line.h>
#include <dc_application/config.h>
#include <dc_application/defaults.h>
#include <dc_application/environment.h>
#include <dc_application/options.h>
#include <dc_posix/dc_stdlib.h>
#include <dc_posix/dc_string.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include <string.h>
#include <dc_posix/dc_unistd.h>
#include <unistd.h>
#include <dc_posix/dc_fcntl.h>
#include <bits/stdint-uintn.h>
#include <ctype.h>
#include <err.h>

#define BUF_SIZE 1024
#define SIZE 53

struct application_settings {
    struct dc_opt_settings opts;
    struct dc_setting_string *message;
};


void write_to_file(const struct dc_posix_env *env, struct dc_error *err, int morse_file, int *loop, uint8_t *byte);

static struct dc_application_settings *create_settings(const struct dc_posix_env *env, struct dc_error *err);

static int destroy_settings(const struct dc_posix_env *env,
                            struct dc_error *err,
                            struct dc_application_settings **psettings);

static int run(const struct dc_posix_env *env, struct dc_error *err, struct dc_application_settings *settings);

static void error_reporter(const struct dc_error *err);

static void trace_reporter(const struct dc_posix_env *env,
                           const char *file_name,
                           const char *function_name,
                           size_t line_number);


struct DataItem {
    const char *data;
    char key;
};

struct DataItem *hashArray[SIZE];
//struct DataItem *dummyItem;
struct DataItem *item;

int hashCode(char key) {
    return key % SIZE;
}

struct DataItem *search(char key) {
    //get the hash
    int hashIndex = hashCode(key);

    //move in array until an empty
    while (hashArray[hashIndex] != NULL) {

        if (hashArray[hashIndex]->key == key)
            return hashArray[hashIndex];

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }
    return NULL;
}

void insert(char key, const char *data) {

    struct DataItem *item = (struct DataItem *) malloc(sizeof(struct DataItem));
    item->data = data;
    item->key = key;

    //get the hash
    int hashIndex = hashCode(key);

    //move in array until an empty or deleted cell
    while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }
    hashArray[hashIndex] = item;
}

int main(int argc, char *argv[]) {
    dc_posix_tracer tracer;
    dc_error_reporter reporter;
    struct dc_posix_env env;
    struct dc_error err;
    struct dc_application_info *info;
    int ret_val;

    reporter = error_reporter;
    tracer = trace_reporter;
    tracer = NULL;
    dc_error_init(&err, reporter);
    dc_posix_env_init(&env, tracer);
    info = dc_application_info_create(&env, &err, "Settings Application");
    ret_val = dc_application_run(&env, &err, info, create_settings, destroy_settings, run, dc_default_create_lifecycle,
                                 dc_default_destroy_lifecycle, NULL, argc, argv);
    dc_application_info_destroy(&env, &info);
    dc_error_reset(&err);

    return ret_val;
}

static struct dc_application_settings *create_settings(const struct dc_posix_env *env, struct dc_error *err) {
    struct application_settings *settings;

    DC_TRACE(env);
    settings = dc_malloc(env, err, sizeof(struct application_settings));

    if (settings == NULL) {
        return NULL;
    }

    settings->opts.parent.config_path = dc_setting_path_create(env, err);
    settings->message = dc_setting_string_create(env, err);

    struct options opts[] = {
            {(struct dc_setting *) settings->opts.parent.config_path,
                    dc_options_set_path,
                    "config",
                    required_argument,
                    'c',
                    "CONFIG",
                    dc_string_from_string,
                    NULL,
                    dc_string_from_config,
                    NULL},
            {(struct dc_setting *) settings->message,
                    dc_options_set_string,
                    "message",
                    required_argument,
                    'm',
                    "MESSAGE",
                    dc_string_from_string,
                    "message",
                    dc_string_from_config,
                    "Hello, Default World!"},
    };

    // note the trick here - we use calloc and add 1 to ensure the last line is all 0/NULL
    settings->opts.opts_count = (sizeof(opts) / sizeof(struct options)) + 1;
    settings->opts.opts_size = sizeof(struct options);
    settings->opts.opts = dc_calloc(env, err, settings->opts.opts_count, settings->opts.opts_size);
    dc_memcpy(env, settings->opts.opts, opts, sizeof(opts));
    settings->opts.flags = "m:";
    settings->opts.env_prefix = "DC_EXAMPLE_";

    return (struct dc_application_settings *) settings;
}

static int destroy_settings(const struct dc_posix_env *env,
                            __attribute__((unused)) struct dc_error *err,
                            struct dc_application_settings **psettings) {
    struct application_settings *app_settings;

    DC_TRACE(env);
    app_settings = (struct application_settings *) *psettings;
    dc_setting_string_destroy(env, &app_settings->message);
    dc_free(env, app_settings->opts.opts, app_settings->opts.opts_count);
    dc_free(env, *psettings, sizeof(struct application_settings));

    if (env->null_free) {
        *psettings = NULL;
    }
    return 0;
}

static int run(const struct dc_posix_env *env, struct dc_error *err, struct dc_application_settings *settings) {
    struct application_settings *app_settings;
    const char *message;
    DC_TRACE(env);
    app_settings = (struct application_settings *) settings;
    message = dc_setting_string_get(env, app_settings->message);
    printf("prog1 says \"%s\"\n", message);

    char chars[BUF_SIZE];
    ssize_t nread;
    int ret_val = 0;

    insert('A', ".-");
    insert('B', "-...");
    insert('C', "-.-.");
    insert('D', "-..");
    insert('E', ".");
    insert('F', "..-.");
    insert('G', "--.");
    insert('H', "....");
    insert('I', "..");
    insert('J', ".---");
    insert('K', "-.-");
    insert('L', ".-..");
    insert('M', "--");
    insert('N', "-.");
    insert('O', "---");
    insert('P', ".--.");
    insert('Q', "--.-");
    insert('R', ".-.");
    insert('S', "...");
    insert('T', "-");
    insert('U', "..-");
    insert('V', "...-");
    insert('W', ".--");
    insert('X', "-..-");
    insert('Y', "-.--");
    insert('Z', "--..");
    insert('0', "-----");
    insert('1', ".----");
    insert('2', "..---");
    insert('3', "...--");
    insert('4', "....-");
    insert('5', ".....");
    insert('6', "-....");
    insert('7', "--...");
    insert('8', "---..");
    insert('9', "----.");
    insert('&', ".-...");
    insert('\'', ".----.");
    insert('@', ".--.-.");
    insert(')', "-.--.-");
    insert('(', "-.--.");
    insert(':', "---...");
    insert(',', "--..--");
    insert('=', "-...-");
    insert('!', "-.-.--");
    insert('.', ".-.-.-");
    insert('-', "-....-");
    insert('+', ".-.-.");
    insert('"', ".-..-.");
    insert('?', "..--..");
    insert('/', "-..-.");
    insert('\n', ".-.-");

    nread = (dc_read(env, err, STDIN_FILENO, chars, BUF_SIZE)) - 1;
    printf("str_len: %zu\n", nread);

    int morse_file = dc_open(env, err, "./program0.hamming", DC_O_CREAT | DC_O_WRONLY, S_IRUSR | S_IWUSR);
    if (dc_error_has_error(err)) {
        ret_val = 1;
        printf("ret_val %d", ret_val);
    }
    uint8_t byte = 0;

    int loop = 0;
    for (ssize_t i = 0; i < nread; i++) {
        uint8_t c = (uint8_t) toupper(chars[i]);

        const char *st;
        item = search((char) toupper(chars[i]));

        if (item != NULL) {
            printf("Element found: %s\n", item->data);
            st = item->data;
        } else if (chars[i] == ' ') {
            st = " ";
        } else {
            printf("Element not found\n");
        }

        for (ssize_t l = 0; l < ((ssize_t) strlen(st)); l++) {
            if (st[l] == '-') {
                byte = (uint8_t) (byte << 2);
                byte = byte | 0x01;
                write_to_file(env, err, morse_file, &loop, &byte);

            } else if (st[l] == '.') {
                byte = (uint8_t) (byte << 2);
                byte = byte | 0x02;
                write_to_file(env, err, morse_file, &loop, &byte);

            } else {
                byte = (uint8_t) (byte << 2);
                byte = byte | 0x03;
                write_to_file(env, err, morse_file, &loop, &byte);
            }
        }
        byte = (uint8_t) (byte << 2);
        byte = byte | 0x00;
        write_to_file(env, err, morse_file, &loop, &byte);
    }
    byte = (uint8_t) (byte << 2);
    byte = byte | 0x00;
    write_to_file(env, err, morse_file, &loop, &byte);
    byte = (uint8_t) (byte << 2);
    byte = byte | 0x00;
    write_to_file(env, err, morse_file, &loop, &byte);

    if (loop != 0) {
        dc_write(env, err, morse_file, &byte, 1);
        if (dc_error_has_error(err)) {
            ret_val = 9;
            printf("ret_val %d", ret_val);
        }
    };
    printf("byte final: %d\n", byte);

    error_reporter(err);

    return EXIT_SUCCESS;
}

static void error_reporter(const struct dc_error *err) {
    fprintf(stderr, "ERROR: %s : %s : @ %zu : %d\n", err->file_name, err->function_name, err->line_number, 0);
    fprintf(stderr, "ERROR: %s\n", err->message);
}

static void trace_reporter(__attribute__((unused)) const struct dc_posix_env *env,
                           const char *file_name,
                           const char *function_name,
                           size_t line_number) {
    fprintf(stdout, "TRACE: %s : %s : @ %zu\n", file_name, function_name, line_number);
}


void write_to_file(const struct dc_posix_env *env, struct dc_error *err, int morse_file, int *loop, uint8_t *byte) {
    (*loop) += 2;
//    printf("loop: %d\n", *loop);
//    printf("byte: %d\n", *byte);
    if (dc_error_has_error(err)) {
        printf("ret_val %d\n", 99);
    }
    if (*loop == 8) {
        dc_write(env, err, morse_file, byte, 1);
        *byte = 0;
        (*loop) = 0;
    }
}
