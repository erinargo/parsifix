#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proquest.h"

void removeWhitespaces(char* input, char* output) {
    int i = 0, j = 0;
    while (input[i]) {
        if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n' && input[i] != '\r' && input[i] != '\f' && input[i] != '\v') {
            output[j++] = input[i];
        }
        i++;
    }
    output[j] = '\0';
}

void getValue(char* bibtex_entry, char* field, char* value) {
    char *haystack = (char *)malloc(strlen(bibtex_entry) + 1);
    removeWhitespaces(bibtex_entry, haystack);

    char* field_check = strstr(haystack, field);

    if (field_check != NULL) {
        char *start = strstr(bibtex_entry, field);

        while (*start == ' ' || *start == '\t' || *start == '=' || *start == '{') {
            start++; // Skip unnecessary chars
        }

        start += strlen(field);
        char* end = strchr(start, '}');
        if (end != NULL) {
            strncpy(value, start, end - start);
            value[end - start] = '\0';
        }
    }
}

void pq(char* bibtex_entry, char* output) {
    char modified_entry[9999];
    memset(modified_entry, 0, sizeof(modified_entry));

    char *entry_type;

    char language[1000];
    char author[1000];
    char title[1000];
    char abstract[4096];
    char url[1000];
    char doi[1000];

    getValue(bibtex_entry, "language={", language);
    getValue(bibtex_entry, "author={", author);
    getValue(bibtex_entry, "title={", title);
    getValue(bibtex_entry, "abstract={", abstract);
    getValue(bibtex_entry, "url={", url);
    getValue(bibtex_entry, "doi={", doi);

    char *entry_start = strstr(bibtex_entry, "@");
    char *entry_end = strstr(bibtex_entry, "{");

    if(entry_start != NULL && entry_end != NULL) {
        entry_type = (char *)malloc((entry_end - entry_start + 1) * sizeof(char));

        if(entry_type != NULL) {
            strncpy(entry_type, entry_start, entry_end - entry_start);
            snprintf(modified_entry, sizeof(modified_entry),
                     "%s{\nlanguage={%s},\nauthor={%s},\ntitle={%s},\nabstract={%s},\nurl={%s},\ndoi={%s},\n}\n\n",
                     entry_type, language, author, title, abstract, url, doi);
            free(entry_type);
        }
    }

    strcpy(output, modified_entry);
}