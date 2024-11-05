/********************************************
 <<< leaf >>>
 Stem and leaf style distribution printer
 by Hilofumi Yamamoto, Institute of Science Tokyo 
 Version 2.0 2024.11.05
 by Hilofumi Yamamoto, University of Tsukuba
 Version 1.0 1996.06.18
 Usage: % leaf < data_file
*********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void stem_and_leaf(int n, int *x, int max_lines);

void stem_and_leaf(int n, int *x, int max_lines) {
    int h, i, j, k, kmin, kmax;
    int *histo = (int *)malloc(10 * max_lines * sizeof(int));
    if (histo == NULL) {
        fprintf(stderr, "Memory allocation failed for histo\n");
        exit(1);
    }

    float xmin = x[0], xmax = x[0], factor = 1.0;

    // Initialize histogram
    for (k = 0; k < 10 * max_lines; k++) histo[k] = 0;

    // Determine min and max values in x
    for (i = 1; i < n; i++) {
        if (x[i] < xmin) xmin = x[i];
        if (x[i] > xmax) xmax = x[i];
    }

    // Adjust factor to prevent overflow
    while (factor * xmax > 32767 || factor * xmin < -32767) {
        factor /= 10;
    }

    // Determine kmin and kmax based on factor
    while (1) {
        kmin = (int)(factor * xmin) / 10 - (xmin < 0);
        kmax = (int)(factor * xmax) / 10;
        if (kmax - kmin + 1 <= max_lines) break;
        factor /= 10;
    }

    printf("   stem * 10 + leaf = %.1g * data\n", factor);
    printf(" ==================================\n");
    printf(" stem | leaf (N = %d)\n", n);
    printf(" ----------------------------------\n");

    // Populate histogram
    for (i = 0; i < n; i++) {
        histo[(int)(factor * x[i]) - (x[i] < 0) - 10 * kmin]++;
    }

    // Adjust histogram for zero
    if (kmin < 0 && kmax > 0) {
        k = 0;
        for (i = 0; i < n; i++) if (x[i] == 0) k++;
        histo[-10 * kmin] -= k / 2;
        histo[-10 * kmin - 1] += k / 2;
    }

    // Print histogram
    for (k = kmin; k <= kmax; k++) {
        printf("%5d | ", k + (k < 0));
        for (j = 0; j <= 9; j++) {
            h = (k >= 0) ? histo[10 * (k - kmin) + j] : histo[10 * (k - kmin) + 9 - j];
            for (i = 0; i < h; i++) printf("%d", j);
        }
        printf("\n");
    }

    free(histo); // Free dynamically allocated memory
}

int main(void) {
    int *x = (int *)malloc(100000 * sizeof(int));
    if (x == NULL) {
        fprintf(stderr, "Memory allocation failed for x\n");
        exit(1);
    }

    char *buffer = (char *)malloc(256 * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed for buffer\n");
        free(x);
        exit(1);
    }

    int n = 0;
    while (fgets(buffer, 256, stdin) != NULL) {
        if (isdigit(buffer[0]) || buffer[0] == '.' || buffer[0] == '-') {
            x[n] = atoi(buffer);
            n++;
        } else if (isalpha(buffer[0])) {
            printf("        %s\n", buffer);
        }
    }

    stem_and_leaf(n, x, 60);

    free(x);      // Free dynamically allocated memory for x
    free(buffer); // Free dynamically allocated memory for buffer
    return 0;
}
