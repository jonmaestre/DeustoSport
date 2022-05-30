#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void logger(const char* user, const char* action, const char* fileName) {

    time_t now;
    time(&now);

    FILE* file;
    file = fopen(fileName,"w");

    fprintf(file, "%s [%s]: %s\n", ctime(&now), user, action);

    fclose(f);

}

