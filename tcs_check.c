#include <stdio.h>
#include <stdlib.h>

#include "main_task.h"
#include "isocheck.h"
#include "tc_queue.h"
#include "basic_types.h"
#include "tcs_check.h"
#include "aux_functions.h"
#include "tc_execution.h"

#define LOW_RANGE 0x20000000
#define UP_RANGE 0x2007FFFF

extern u32 accepted;

bool first_check(unsigned char tc_queue_0[], unsigned int number_of_bytes) 
{
  bool check_tc = TRUE;

  if ( (tc_queue_0[0] != 6) || ( (tc_queue_0[1] != 9) && (tc_queue_0[1] != 2) ) )
      check_tc = FALSE;

  return  check_tc;
}

bool tc_check_6_2(unsigned char tc_queue_1[], unsigned int number_of_bytes) 
{
  bool correct_tc = TRUE;
  u16 bytes_extent = merge_2_hex(tc_queue_1[2], tc_queue_1[3]);
  u32 range = merge_4_hex(tc_queue_1[4], tc_queue_1[5], tc_queue_1[6], tc_queue_1[7]);
  u16 check_sum = merge_2_hex(tc_queue_1[number_of_bytes-2], tc_queue_1[number_of_bytes-1]);
  u16 expected_check_sum = calculate_iso_checksum(tc_queue_1, number_of_bytes-2);

  if ( (bytes_extent < 1) || (bytes_extent > 992) ) 
    correct_tc = FALSE;
  
  else if ( (range < LOW_RANGE) || (range > UP_RANGE) )
    correct_tc = FALSE;
   
  else if ( (range + bytes_extent - 1) > UP_RANGE )
    correct_tc = FALSE;
   
  else if ( check_sum != expected_check_sum)
    correct_tc = FALSE;

  return  correct_tc;

}

bool tc_check_6_9(unsigned char tc_queue_2[], unsigned int number_of_bytes) 
{
  bool correct_tc = TRUE;
  u16 bytes_extent = merge_2_hex(tc_queue_2[2], tc_queue_2[3]);
  u32 range = merge_4_hex(tc_queue_2[4], tc_queue_2[5], tc_queue_2[6], tc_queue_2[7]);
  u16 check_sum = merge_2_hex(tc_queue_2[number_of_bytes-2], tc_queue_2[number_of_bytes-1]);
  u16 expected_check_sum = calculate_iso_checksum(tc_queue_2, number_of_bytes-2);

  if ( (bytes_extent < 1) || (bytes_extent > 65535) ) 
    correct_tc = FALSE;
  
  else if ( (range < LOW_RANGE) || (range > UP_RANGE) )
    correct_tc = FALSE;
   
  else if ( (range + bytes_extent - 1) > UP_RANGE )
    correct_tc = FALSE;
   
  else if ( check_sum != expected_check_sum)
    correct_tc = FALSE;

  return  correct_tc;
}

bool correct_V_2_TC(unsigned char tc_array[], unsigned int number_of_bytes)
{
  bool V_2_TC = TRUE;
  if ( first_check(tc_array, number_of_bytes) == TRUE )
  {
    if ( search_V2_TC(tc_array) == FALSE )
      V_2_TC = FALSE;
  }
  else  
    V_2_TC = FALSE;

  return V_2_TC;
}

bool correct_V_9_TC(unsigned char tc_array[], unsigned int number_of_bytes) 
{
  bool V_9_TC = TRUE;
  if ( first_check(tc_array, number_of_bytes) == TRUE )
  {
    if ( search_V2_TC(tc_array) == TRUE )
      V_9_TC = FALSE;
  }
  else  
    V_9_TC = FALSE;

  return V_9_TC;

}
