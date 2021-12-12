
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <dc_application/command_line.h>
#include <dc_application/config.h>
#include <dc_application/options.h>
#include <dc_posix/dc_string.h>
#include <dc_posix/dc_unistd.h>
#include <dc_util/dump.h>
#include <dc_util/streams.h>
#include <getopt.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define SIZE 55

struct application_settings {
    struct dc_opt_settings opts;
    struct dc_setting_string *message;
};


static struct dc_application_settings *create_settings(const struct dc_posix_env *env, struct dc_error *err);

static int destroy_settings(const struct dc_posix_env *env,
                            struct dc_error *err,
                            struct dc_application_settings **psettings);

static int run(const struct dc_posix_env *env, struct dc_error *err, struct dc_application_settings *settings);

static void error_reporter(const struct dc_error *err);

struct DataItem {
    char data;
    const char *key;
};


struct DataItem *hashArray[SIZE];
struct DataItem *item;

/**
 * Generating the hashcode
 * @param key
 * @return
 */
static int hashCode(const char *key) {
    long location = 0;
    for (size_t j = 0; j < strlen(key); j++) {
        location += (long) ((key[j] - 44) * (pow(26, (double) j)));
    }
    if (location < 0) {
        location *= -1;
    }
    return ((int) location % SIZE);
}

/**
 * search in the HashMap
 * @param key
 * @return
 */
static struct DataItem *search(char *key) {
    //get the hash
    int hashIndex = hashCode(key);
    if (hashIndex < 0) {
        hashIndex *= -1;
    }
    //move in array until an empty
    while (hashArray[hashIndex] != NULL) {

        if (strcmp(hashArray[hashIndex]->key, key) == 0)
            return hashArray[hashIndex];

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }
    return NULL;
}

/**
 * Insert to the HashMap
 * @param key
 * @param data
 */
static void insert(const char *key, char data) {
    item = (struct DataItem *) malloc(sizeof(struct DataItem));
    item->data = data;
    item->key = key;

    //get the hash
    int hashIndex = hashCode(key);

    if (hashIndex < 0) {
        hashIndex *= -1;
    }
    //move in array until an empty or deleted cell
    while (hashArray[hashIndex] != NULL) {
        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }
    hashArray[hashIndex] = item;
}

/**
 * The main function
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {
    dc_posix_tracer tracer;
    dc_error_reporter reporter;
    struct dc_posix_env env;
    struct dc_error err;
    struct dc_application_info *info;
    int ret_val;

    reporter = error_reporter;
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
    DC_TRACE(env);
    app_settings = (struct application_settings *) settings;

    char chars[BUF_SIZE];
    ssize_t nread;
    char byte = 0;
    int ret_val = EXIT_SUCCESS;

    insert(".-", 'A');
    insert("-...", 'B');
    insert("-.-.", 'C');
    insert("-..", 'D');
    insert(".", 'E');
    insert("..-.", 'F');
    insert("--.", 'G');
    insert("....", 'H');
    insert("..", 'I');
    insert(".---", 'J');
    insert("-.-", 'K');
    insert(".-..", 'L');
    insert("--", 'M');
    insert("-.", 'N');
    insert("---", 'O');
    insert(".--.", 'P');
    insert("--.-", 'Q');
    insert(".-.", 'R');
    insert("...", 'S');
    insert("-", 'T');
    insert("..-", 'U');
    insert("...-", 'V');
    insert(".--", 'W');
    insert("-..-", 'X');
    insert("-.--", 'Y');
    insert("--..", 'Z');
    insert("-----", '0');
    insert(".----", '1');
    insert("..---", '2');
    insert("...--", '3');
    insert("....-", '4');
    insert(".....", '5');
    insert("-....", '6');
    insert("--...", '7');
    insert("---..", '8');
    insert("----.", '9');
    insert(".-...", '&');
    insert(".----.", '\'');
    insert(".--.-.", '@');
    insert("-.--.-", ')');
    insert("-.--.", '(');
    insert("---...", ':');
    insert("--..--", ',');
    insert("-...-", '=');
    insert("-.-.--", '!');
    insert(".-.-.-", '.');
    insert("-....-", '-');
    insert("------..-.-----", '%');
    insert(".-.-.", '+');
    insert(".-..-.", '"');
    insert("..--..", '?');
    insert("-..-.", '/');
    insert("........", '\\');
    insert(".-.-", '\n');


    if (dc_error_has_no_error(err)) {
        char final_string[30];
        memset(final_string, 0, 30);

        char space[] = " ";

        // 15 is the maximum length that we have, which is '%'
        char ch[15];
        memset(ch, 0, 15);
        nread = (dc_read(env, err, STDIN_FILENO, chars, BUF_SIZE)) - 1;
        if (dc_error_has_error(err)) {
            ret_val = 1;
        }

        for (ssize_t i = 0; i <= nread; i++) {
            byte = chars[i];
            for (ssize_t l = 0; l < 4; l++) {
                uint16_t temp = 0;
                temp = byte & 192;
                temp = temp >> 6;
                byte = ((char) (byte << 2));

                if (temp == 1) {
                    strcat(ch, "-");
                } else if (temp == 2) {
                    strcat(ch, ".");
                } else if (temp == 0) {

                    item = search(ch);

                    if (item != NULL) {
                        strcat(final_string, &item->data);
                    }
                    memset(ch, 0, 15);
                } else if (temp == 3) {
                    strcat(final_string, space);
                }
            }
        }
        printf("final_string: %s\n", final_string);
    }
    error_reporter(err);

    return ret_val;
}

static void error_reporter(const struct dc_error *err) {
    fprintf(stderr, "ERROR: %s : %s : @ %zu : %d\n", err->file_name, err->function_name, err->line_number, 0);
    fprintf(stderr, "ERROR: %s\n", err->message);
}

