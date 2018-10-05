#include <zf_log.h>
#include <hdf5.h>

void 
H5F_post_vfd_swrm_log_entry(hid_t fid, int entry_type_code, char * body)
{
  if (fid < 0) 
    return; 			/* No operation */

  ZF_LOGI("%i %s", entry_type_code, body);
}

/* Test. */
int main(int argc, char** argv)
{
  H5F_post_vfd_swrm_log_entry(1, 1, "test");
}


