#include <stdio.h>
#include <string.h>

#include "proquest.h"

void usage() {
    printf("This program is intended for use by researchers on the First ModulAR project.\n");
    printf("For further instructions on how to use, please see the ReadMe file.");
}

int main(int argc, char *argv[]) {
    FILE *input_file, *output_file;
    char bibtex_entry[9999];

    input_file = fopen("./input.bib", "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    output_file = fopen("./output.bib", "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return 1;
    }

    while (!feof(input_file)) {
        char output[9999];
        pq(fgets(bibtex_entry, sizeof(bibtex_entry), input_file), output);

        fputs(output, output_file);
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}