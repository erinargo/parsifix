#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proquest.h"

void getValue(char* bibtex_entry, char* field, char* value) {
    char* start = strstr(bibtex_entry, field);

    if (start != NULL) {
        start += strlen(field);
        while (*start == ' ' || *start == '\t' || *start == '=' || *start == '{') {
            start++; // Skip unnecessary chars
        }

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

    getValue(bibtex_entry, "language", language);
    getValue(bibtex_entry, "author", author);
    getValue(bibtex_entry, "title", title);
    getValue(bibtex_entry, "abstract", abstract);
    getValue(bibtex_entry, "url", url);
    getValue(bibtex_entry, "doi", doi);

    char *entry_start = strstr(bibtex_entry, "@");
    char *entry_end = strstr(bibtex_entry, "{");

    if(entry_start != NULL && entry_end != NULL) {
        entry_type = (char *)malloc((entry_end - entry_start + 1) * sizeof(char));

        if(entry_type != NULL) {
            printf("%s, %s, %s", language, author, title);
            strncpy(entry_type, entry_start, entry_end - entry_start);
            snprintf(modified_entry, sizeof(modified_entry),
                     "%s{\nlanguage={%s},\nauthor={%s},\ntitle={%s},\nabstract={%s},\nurl={%s},\ndoi={%s},\n}\n\n",
                     entry_type, language, author, title, abstract, url, doi);
            free(entry_type);
        }
    }

    strcpy(output, modified_entry);
}