/*

 Copyright (C) 2018 Akadio, Inc.
 All rights reserved.

 */

#include <h5s.h>

int main(int argc, const char *argv[])
{
    /* Open file in MapR Hadoop FS. */
    hid_t fid = h5s_open("maprfs://path/to/test.h5s");
    
    /* Note: It can be any file system (local, http, s3, kafka, etc.). */    

    int i = 0;
    
    /* A spreadsheet with million columns and unlimited (*) rows. */
    int record[1000000];
    
    while(i < atoi(argv[1])) {
        /* Set record. */
        record[0] = 255;
        /* Append record to the 2d dataset (i.e., dset[*][1000000]). */
        if(h5s_write(fid, '/group/dset', record) < 0) 
            return -1;
        
    }
    return h5s_close(fid);    
}
