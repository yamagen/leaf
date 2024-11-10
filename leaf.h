// leaf.h
#ifndef LEAF_H
#define LEAF_H

#define MAX_DATA_SIZE 100000
#define BUFFER_SIZE 256

// オプションの種類を定義
typedef enum {
    OPTION_UNKNOWN = 0,
    OPTION_HELP,
    OPTION_QUIET,
    OPTION_VERBOSE
} OptionType;

// 関数宣言
OptionType get_option(const char *arg);
void stem_and_leaf(int n, int *x, int max_lines, int quiet, int verbose);
void print_header(float factor, int n);
void process_file(const char *filename, int *x, int max_lines, int quiet, int verbose);
void process_stdin(int *x, int max_lines, int quiet, int verbose);
int parse_line(const char *buffer, int *x, int *n, int verbose);
void usage();

#endif // LEAF_H
