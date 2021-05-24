#include <stdio.h>
#include <stdlib.h>

#include "main_task.h"
#include "isocheck.h"
#include "tc_queue.h"
#include "basic_types.h"
#include "tcs_check.h"
#include "aux_functions.h"
#include "tc_execution.h"

extern u16 generation_checksums[32];
extern u32 executed;
extern u32 accepted;

void execution_6_2_TC(unsigned char tc_array[], unsigned int number_of_bytes) 
{
  accepted += 1; 
  u16 bytes_size = merge_2_hex(tc_array[2], tc_array[3]);
  u32 memory_adress_start = merge_4_hex(tc_array[4], tc_array[5], tc_array[6], tc_array[7]);
  u32 last_byte_load = (number_of_bytes - 2);
  
  unsigned char* pt_first_pos= (unsigned char*)(memory_adress_start);
  int j = 0;

  for (int i=8; i<last_byte_load; i++)
  {
    *(pt_first_pos + j) = tc_array[i];
    j++;
  }
    executed += 1;
    reject_tc(tc_array, number_of_bytes, FALSE);

}

void execution_6_9_TC(unsigned char tc_array[], unsigned int number_of_bytes) 
{
  static int i=0;
  accepted += 1;
  u16 bytes_size = merge_2_hex(tc_array[2], tc_array[3]);
  u32 memory_adress_start = merge_4_hex(tc_array[4], tc_array[5], tc_array[6], tc_array[7]);

  unsigned char* pt_first_pos = (unsigned char*)(memory_adress_start);

  if (i<33)
  {
    generation_checksums[i]=calculate_iso_checksum(pt_first_pos,bytes_size);
    i++;
  }

  else
    calculate_iso_checksum(pt_first_pos,bytes_size);

    executed += 1;
    reject_tc(tc_array, number_of_bytes, FALSE);
}
