#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "hexdump.h"

/**
 * Generate the hexdump of infile, and write result to outfile
 * 1. return 1 if success, and 0 otherwise
 * 2. outfile should not be created if infile does not exist
 */
int hexdump(const char * infile, const char * outfile) {
    // first get FD number
    int fdIn;
    fdIn = open(infile, O_RDONLY);
    
    // need file size, use fstat
    struct stat * statsForFile;
    fstat(fdIn, statsForFile);


    //create a buffer and load data into buffer
    const char * buf; 
    read(fdIn,buf, statsForFile->st_size);

   // printf("%s",buf);
    
    
    return 0;
}