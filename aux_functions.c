#include <stdio.h>
#include <stdlib.h>

#include "main_task.h"
#include "isocheck.h"
#include "tc_queue.h"
#include "basic_types.h"
#include "tcs_check.h"
#include "aux_functions.h"
#include "tc_execution.h"

extern u32 major_frame_cnt;
extern u32 frame_count;
extern u32 accepted;
extern u32 rejected;
extern u32 executed;
extern t_tc_queue tc_queue;
extern u16 generation_checksums[32];

unsigned short merge_2_hex(u8 hex1, u8 hex2) 
{
  u16 number1 = hex1;
  u16 number2 = hex2;
  u16 merged_number = (number1<<8)|(number2);
  return merged_number;
}

unsigned int merge_4_hex(u8 hex1,u8 hex2,u8 hex3,u8 hex4) 
{
  u32 number1 = hex1;
  u32 number2 = hex2;
  u32 number3 = hex3;
  u32 number4 = hex4;
  u32 merged_number = (number1<<24)|(number2<<16)|(number3<<8)|(number4);

  return merged_number;
}

void reject_tc(u8 tc_array[], int size, bool rejected) 
{
  if ( (rejected == TRUE) && (tc_array[0] != 0xcd) )
    rejected += 1;
  for(int i=0; i<=size; i++)
    tc_array[i] = 0;
}

bool search_V2_TC(u8 tc_array[])
{
  bool V_2_TC = TRUE;
  if (tc_array[1] != 2) //
    V_2_TC = FALSE;

  return V_2_TC;

}

void split_short(u8* char1, u8* char2, u16 split) 
{
  *char1 = split >> 8;
  *char2 = split & 0xFF;
}

void give_expected_value(u8 array[], u8 start_val, u32 number_bytes) 
{
  for(int i=0; i<number_bytes; i++)
    array[i] = start_val + i;
}

void correct_values_1(int number_errors1, int number_errors2, int number_errors3)
{
  printf("IT_TCMD_090_CHECK_TEST\n\n");
  if (number_errors1 == 0)
    printf("PASS, first load of bytes correct\n");
  else
    printf("FAIL, first expected value of the first load of bytes: 0x00, obtained value: %x\n",*(unsigned char*)(0x20040000));
  if (number_errors2 == 0)
    printf("PASS, second load of bytes correct\n");
  else
    printf("FAIL, first expected value of the second load of bytes: 0x80, obtained value: %x\n",*(unsigned char*)(0x20040400));
  if (number_errors3 == 0)
    printf("PASS, third load of bytes correct\n");
  else
    printf("FAIL, first expected value of the third load of bytes: 0xBE, obtained value: %x\n",*(unsigned char*)(0x20040803));

  if ( (accepted == 3) && (executed == 3) && (rejected == 5) )
    printf("PASS, accepted executed and rejected TCs values are correct.\n");
  
  else  
  {
    printf("FAIL, expected accepted TCs: 3, obtained: %d.\n", accepted);
    printf("FAIL, expected executed TCs: 3, obtained: %d.\n", executed);
    printf("FAIL, expected accepted TCs: 5, obtained: %d.\n", rejected);
  }
}

void correct_values_2(int number_of_load_errors_1, int number_of_load_errors_2, int number_of_check_errors) 
{
  printf("IT_TCMD_110_CHECK_TEST\n\n");
  if ( number_of_check_errors != 0 )
  {
    printf("FAIL\nValue expected for the first check: 0xFFFF, value obtained %x.\n", generation_checksums[0]);
    printf("Value expected for the first check: 0x9CF8, value obtained %x.\n", generation_checksums[1]);
    printf("Value expected for the first check: 0x24DC, value obtained %x.\n", generation_checksums[2]);
    printf("Value expected for the first check: 0xCC4B, value obtained %x.\n", generation_checksums[3]);
  }
  else
    printf("PASS, all checksums are correct.\n");
  if ( number_of_load_errors_1 != 0 )
    printf("FAIL, first expected value of the first load of bytes: 0x00, obtained value: %x\n",*(unsigned char*)(0x20040000));
  else  
    printf("PASS, first load of bytes correct\n");
  if ( number_of_load_errors_2 != 0 )
    printf("FAIL, first expected value of the second load of bytes: 0x00, obtained value: %x\n",*(unsigned char*)(0x20040010));
  else  
    printf("PASS, second load of bytes correct\n");

  if ( (accepted == 6) && (executed == 6) && (rejected == 4) )
    printf("PASS, accepted executed and rejected TCs values are correct.\n"); 
  else  
  {
    printf("FAIL, expected accepted TCs: 6, obtained: %d.\n", accepted);
    printf("FAIL, expected executed TCs: 6, obtained: %d.\n", executed);
    printf("FAIL, expected accepted TCs: 4, obtained: %d.\n", rejected);
  }
}

void gen_TCs_6_2(u8 tc_array[], u16 number_bytes, u8 initial_value, u8 strt_ad1, u8 strt_ad2, u8 strt_ad3, u8 strt_ad4, bool correct_checksum) 
{
  u32 array_end = 8 + number_bytes;
  u32 j = 0;
  u8 char_size1;
  u8 char_size2;
  split_short(&char_size1, &char_size2, number_bytes);
  tc_array[0] = 6; tc_array[1] = 2; tc_array[2] = char_size1; tc_array[3] = char_size2; tc_array[4] = strt_ad1;
                                                          tc_array[5] = strt_ad2; tc_array[6] = strt_ad3; tc_array[7] = strt_ad4;
  for(int i=8; i<array_end; i++)
    {
      tc_array[i] = initial_value + j;
      j++;
    }
  if (correct_checksum == TRUE)
  {
    u16 checksum = calculate_iso_checksum(tc_array, array_end);
    split_short( &char_size1, &char_size2, checksum) ;

    tc_array[array_end] = char_size1;
    tc_array[array_end+1] = char_size2;
  }
  else
  {
   u16 checksum = calculate_iso_checksum(tc_array, array_end-6);
    split_short( &char_size1, &char_size2, checksum) ;
    tc_array[array_end] = char_size1;
    tc_array[array_end+1] = char_size2;
  }
}

void gen_TCs_6_9(u8 tc_array[], u16 number_bytes, u8 strt_ad1, u8 strt_ad2, u8 strt_ad3, u8 strt_ad4, bool correct_checksum) 
{
  u32 array_end = 8;
  u8 char_size1;
  u8 char_size2;
  split_short(&char_size1, &char_size2, number_bytes);
  tc_array[0] = 6; tc_array[1] = 9; tc_array[2] = char_size1; tc_array[3] = char_size2; tc_array[4] = strt_ad1;
                                                          tc_array[5] = strt_ad2; tc_array[6] = strt_ad3; tc_array[7] = strt_ad4;
  if (correct_checksum == TRUE)
  {
    u16 checksum = calculate_iso_checksum(tc_array, array_end);
    split_short( &char_size1, &char_size2, checksum) ;

    tc_array[array_end] = char_size1;
    tc_array[array_end+1] = char_size2;
  }
  else
  {
   u16 checksum = calculate_iso_checksum(tc_array, array_end-6);
    split_short( &char_size1, &char_size2, checksum) ;
    tc_array[array_end] = char_size1;
    tc_array[array_end+1] = char_size2;
  }
}
