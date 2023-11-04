#include <stdio.h>
#include <string.h>

#include "proquest.h"

void getValue(char* bibtex_entry, char* field, char* value) {
    char* start = strstr(bibtex_entry, field);
    if (start != NULL) {
        start += strlen(field);
        char* end = strchr(start, '}');
        if (end != NULL) {
            strncpy(value, start, end - start);
            value[end - start] = '\0';
        }
    }
}

void pq(char* bibtex_entry, char* output) {
    char modified_entry[4096];
    memset(modified_entry, 0, sizeof(modified_entry));

    char entry_type[100];
    memset(entry_type, 0, sizeof(entry_type));

    if (sscanf(bibtex_entry, "@%99[^{]{", entry_type) != 1) {
        return;
    }

    char language[100] = "N/A";
    char author[100] = "N/A";
    char title[100] = "N/A";
    char abstract[2048] = "N/A";
    char url[100] = "N/A";
    char doi[100] = "N/A";

    // Search for and extract values manually
    getValue(bibtex_entry, "language={", language);
    getValue(bibtex_entry, "author={", author);
    getValue(bibtex_entry, "title={", title);
    getValue(bibtex_entry, "abstract={", abstract);
    getValue(bibtex_entry, "url={", url);
    getValue(bibtex_entry, "doi={", doi);

    snprintf(modified_entry, sizeof(modified_entry),
             "@%s{\nlanguage={%s},\nauthor={%s},\ntitle={%s},\nabstract={%s},\nurl={%s},\ndoi={%s},\n}\n\n",
             entry_type, language, author, title, abstract, url, doi);

    strcpy(output, modified_entry);
}