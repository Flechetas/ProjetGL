#include <string.h>

#include "cli/cli.h"

int endsWith(char *string, const char *suff)
{
    if(strlen(suff) == 0) {
        return -1;
    }
    string = strrchr(string, suff[0]);

    if (string != NULL) {
        return strcmp(string, suff);
    }

    return -1;
}
