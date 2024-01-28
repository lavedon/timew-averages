#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <time.h>

int main( int argc, char *argv[])
{
    FILE* inputFile = NULL;
    char line[256];

    if (argc != 2) {
      fprintf( stderr, "usage: %s inputFileName\n", argv[0]);
      exit( EXIT_FAILURE );
    }
    
    if (NULL == (inputFile = fopen(argv[1], "r"))) {
      fprintf(stderr, "ERROR: input file: %s: %s\n", argv[1], strerror(errno));
      exit(EXIT_FAILURE);
    }
    fprintf(stderr, "%s opened for reading.\n", argv[1]);
    
    while (fgets(line, sizeof(line), inputFile)) {
        char *startStr = strtok(line, " -");
        char *endStr = strtok(NULL, " #");

        struct tm startTime, endTime;
        time_t startEpoch, endEpoch;

        strptime(startStr, "%Y%m%dT%H%M%SZ", &startTime);
        strptime(endStr, "%Y%m%dT%H%M%SZ", &endTime);

        startEpoch = mktime(&startTime);
        endEpoch = mktime(&endTime);

        double diff = difftime(endEpoch, startEpoch);
        printf("Time difference: %.f seconds\n", diff);
    }

    fclose(inputFile);
    return 0;
}
