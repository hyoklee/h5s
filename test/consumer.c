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
           
    /* Poll interval in nano second. */    
    int interval = 10;
    
    /* The number of records poll() has returned. */    
    int n = 0;               

    /* One row of record buffer from spreadsheet.  */
    int record[1000000];

    int i = 0;
    
    while(true) {
        if((n = h5s_poll(fid, "/group/dset", interval)) > 0) {
            for(i = 0; i < n; i++){
                h5s_read(fid, "/group/dset", &record);
                /* your_process_function(record); */
            }
        }
    }
    return h5s_close(fid);    
 }
