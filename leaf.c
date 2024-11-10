#include "leaf.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define DATE "Last change: 2024/11/10-19:59:54.05"
#define VERSION "2.0"

OptionType get_option(const char *arg) {
  if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) return OPTION_HELP;
  if (strcmp(arg, "-q") == 0 || strcmp(arg, "--quiet") == 0) return OPTION_QUIET;
  if (strcmp(arg, "-v") == 0 || strcmp(arg, "--verbose") == 0) return OPTION_VERBOSE;
  return OPTION_UNKNOWN;
}

void print_header(float factor, int n) {
  printf("stem * 10 + leaf = %.1g * data  (N = %d)\n", factor, n);
  printf("--------------------\n");
}

void stem_and_leaf(int n, int *x, int max_lines, int quiet, int verbose) {
  int h, i, j, k, kmin, kmax, max_stem_width;
  int *histo = (int *)malloc(10 * max_lines * sizeof(int));
  if (histo == NULL) {
    fprintf(stderr, "Memory allocation failed for histo\n");
    exit(1);
  }

  float xmin = x[0], xmax = x[0], factor = 1.0;

  // Initialize histogram
  for (k = 0; k < 10 * max_lines; k++) histo[k] = 0;

  // Find min and max in data
  for (i = 1; i < n; i++) {
    if (x[i] < xmin) xmin = x[i];
    if (x[i] > xmax) xmax = x[i];
  }

  // Display initial min and max if verbose is enabled
  if (verbose) {
    printf("Initial xmin: %f, xmax: %f\n", xmin, xmax);
  }

  // Scale factor to avoid overflow
  while (factor * xmax > 32767 || factor * xmin < -32767) {
    factor /= 10;
  }

  // Determine kmin and kmax based on scaled xmin and xmax
  while (1) {
    kmin = (int)floor(factor * xmin / 10);
    kmax = (int)ceil(factor * xmax / 10);
    if (kmax - kmin + 1 <= max_lines) break;
    factor /= 10;
  }

  // Display factor, kmin, and kmax if verbose is enabled
  if (verbose) {
    printf("Factor: %.1g, kmin: %d, kmax: %d\n", factor, kmin, kmax);
  }

  // Calculate width for stem display alignment
  int max_stem = (kmax > -kmin) ? kmax : -kmin;
  max_stem_width = snprintf(NULL, 0, "%+d", max_stem);

  if (!quiet) {
    printf("Stem * 10 + Leaf = Data  (N = %d)\n", n);
    printf("-----------------------------\n");
  }

  // Populate histogram (single pass)
  for (i = 0; i < n; i++) {
    int stem = (int)floor(factor * x[i] / 10);
    int leaf = abs((int)(factor * x[i]) % 10);
    histo[(stem - kmin) * 10 + leaf]++;
  }

  // Print histogram with aligned stems
  for (k = kmin; k <= kmax; k++) {
    int stem = k;
    printf("%*d | ", max_stem_width, stem);

    // Display leaves for this stem
    for (j = 0; j <= 9; j++) {
      h = histo[(k - kmin) * 10 + j];
      for (i = 0; i < h; i++) printf("%d", j);
    }
    printf("\n");
  }

  free(histo);
}

int parse_line(const char *buffer, int *x, int *n, int verbose) {
  if (isdigit(buffer[0]) || buffer[0] == '.' || buffer[0] == '-') {
    x[*n] = atoi(buffer);
    (*n)++;
    if (verbose) {
      printf("Parsed number: %d\n", x[*n - 1]);
    }
    return 1;
  } else if (isalpha(buffer[0])) {
    printf("%s\n", buffer);
    return 0;
  }
  return -1;
}

void process_file(const char *filename, int *x, int max_lines, int quiet, int verbose) {
  FILE *input = fopen(filename, "r");
  if (input == NULL) {
    fprintf(stderr, "Error: Cannot open file %s\n", filename);
    return;
  }

  int n = 0;
  char buffer[BUFFER_SIZE];

  if (!quiet) {
    printf("\nFilename: %s\n", filename);
  }

  if (fgets(buffer, sizeof(buffer), input) != NULL && !quiet) {
    printf("%s\n", buffer);
  }

  while (fgets(buffer, sizeof(buffer), input) != NULL) {
    parse_line(buffer, x, &n, verbose);
  }
  fclose(input);

  if (n > 0) {
    stem_and_leaf(n, x, max_lines, quiet, verbose);
  } else {
    printf("No numerical data found in file %s\n", filename);
  }
}

void process_stdin(int *x, int max_lines, int quiet, int verbose) {
  int n = 0;
  char buffer[BUFFER_SIZE];

  if (!quiet) {
    printf("\nStandard input:\n");
  }

  if (fgets(buffer, sizeof(buffer), stdin) != NULL && !quiet) {
    printf("%s\n", buffer);
  }

  while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
    parse_line(buffer, x, &n, verbose);
  }

  if (n > 0) {
    stem_and_leaf(n, x, max_lines, quiet, verbose);
  } else {
    printf("No numerical data found in standard input\n");
  }
}

void usage() {
  printf("Usage: leaf [options] [data_file1 data_file2 ...]\n");
  printf("Stem and leaf style distribution printer\n");
  printf("by Hilofumi Yamamoto, Institute of Science Tokyo\n");
  printf("Version %s %s\n", VERSION, DATE);
  printf("Options:\n");
  printf("  -h, --help     Show this help message and exit\n");
  printf("  -q, --quiet    Suppress header output\n");
  printf("  -v, --verbose  Show detailed processing information\n");
}

int main(int argc, char *argv[]) {
  int quiet = 0;
  int verbose = 0;

  for (int i = 1; i < argc; i++) {
    switch (get_option(argv[i])) {
      case OPTION_HELP:
        usage();
        return 0;
      case OPTION_QUIET:
        quiet = 1;
        break;
      case OPTION_VERBOSE:
        verbose = 1;
        break;
      case OPTION_UNKNOWN:
        if (argv[i][0] != '-') {
          int *x = (int *)malloc(MAX_DATA_SIZE * sizeof(int));
          if (x == NULL) {
            fprintf(stderr, "Memory allocation failed for x\n");
            exit(1);
          }
          process_file(argv[i], x, 60, quiet, verbose);
          free(x);
        } else {
          fprintf(stderr, "Unknown option: %s\n", argv[i]);
          usage();
          return 1;
        }
        break;
    }
  }

  if (argc == 1 || (quiet && argc == 2)) {
    int *x = (int *)malloc(MAX_DATA_SIZE * sizeof(int));
    if (x == NULL) {
      fprintf(stderr, "Memory allocation failed for x\n");
      exit(1);
    }
    process_stdin(x, 60, quiet, verbose);
    free(x);
  }

  return 0;
}
