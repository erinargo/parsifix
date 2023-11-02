#include <stdio.h>
#include <string.h>

void modify_bibtex_entry(char* bibtex_entry) {
    char *entry = strstr(bibtex_entry, "@");
    if(entry != NULL) {
        char modified_entry[2048];
        snprintf(modified_entry, sizeof(modified_entry), "%slanguage={en},\n", bibtex_entry);
        strcpy(bibtex_entry, modified_entry);
    }
}

int main() {
    FILE *input_file, *output_file;
    char bibtex_entry[4096];

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

    while (fgets(bibtex_entry, sizeof(bibtex_entry), input_file)) {
        modify_bibtex_entry(bibtex_entry);
        fputs(bibtex_entry, output_file);
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}