#include <stdio.h>
#include <stdlib.h>

#include "main_task.h"
#include "isocheck.h"
#include "tc_queue.h"
#include "basic_types.h"
#include "tcs_check.h"
#include "aux_functions.h"
#include "tc_execution.h"
#include "sync_task.h"

extern t_tc_queue tc_queue;
extern u32 major_frame_cnt;
extern u32 frame_count;
extern u32 accepted;
extern u32 rejected;
extern u32 executed;
extern u16 generation_checksums[32];

void IT_TCMD_090(void) 
{
  u8 TC_1[1002], TC_2[1002], TC_3[13], TC_4[1003], TC_5[10], TC_6[15], TC_7[1002], TC_8[1002];

  gen_TCs_6_2(TC_1, 992, 0x00, 0x20, 0x04, 0x00, 0x00, TRUE);
  gen_TCs_6_2(TC_2, 992, 0x80, 0x20, 0x04, 0x04, 0x00, TRUE);
  gen_TCs_6_2(TC_4, 993, 0xFF, 0x20, 0x04, 0x00, 0x00, TRUE);
  gen_TCs_6_2(TC_5, 0, 0x01, 0x20, 0x04, 0x00, 0x00, TRUE);
  gen_TCs_6_2(TC_6, 5, 0x10, 0x20, 0x07, 0xFF, 0xFC, TRUE);
  gen_TCs_6_2(TC_7, 992, 0x00, 0x1F, 0xFF, 0xFF, 0x00, TRUE);
  gen_TCs_6_2(TC_8, 992, 0x02, 0x20, 0x04, 0x00, 0x00, FALSE);
  
  TC_3[0] = 6; TC_3[1] = 2; TC_3[2] = 0x00; TC_3[3] = 0x03; 

  TC_3[4] = 0x20; TC_3[5] = 0x04; TC_3[6] = 0x08; TC_3[7] = 0x03; 

  TC_3[8] = 0xBE; TC_3[9] = 0xBA; TC_3[10] = 0xCA;

  u8 char_extent1;
  u8 char_extent2;

  u16 checksum_tc_3 = calculate_iso_checksum(TC_3, 11);
  split_short(&char_extent1, &char_extent2, checksum_tc_3);
  
  TC_3[11] = char_extent1; TC_3[12] = char_extent2;

  tc_queue_insert_item(&tc_queue, TC_1, 1002); tc_queue_insert_item(&tc_queue, TC_2, 1002); tc_queue_insert_item(&tc_queue, TC_3, 13);
         tc_queue_insert_item(&tc_queue, TC_4, 1003); tc_queue_insert_item(&tc_queue, TC_5, 10); tc_queue_insert_item(&tc_queue, TC_6, 15);
                                                             tc_queue_insert_item(&tc_queue, TC_7, 1002); tc_queue_insert_item(&tc_queue, TC_8, 1002);

}

void IT_TCMD_110(void) 
{
  u8 TC_6_2_1[23]; u8 TC_6_2_2[74];
  TC_6_2_1[0]=6; TC_6_2_1[1]=2; TC_6_2_1[2]=0x00; TC_6_2_1[3]=0x0D;
        TC_6_2_1[4]=0x20; TC_6_2_1[5]=0x04; TC_6_2_1[6]=0x00; TC_6_2_1[7]=0x00;
              TC_6_2_1[8]=0x00; TC_6_2_1[9]=0x00; TC_6_2_1[10]=0x00; TC_6_2_1[11]=0xAB; 
                    TC_6_2_1[12]=0xCD; TC_6_2_1[13]=0xEF; TC_6_2_1[14]=0x01; TC_6_2_1[15]=0x14; 
                          TC_6_2_1[16]=0x56; TC_6_2_1[17]=0xF8; TC_6_2_1[18]=0x9A; TC_6_2_1[19]=0x00; TC_6_2_1[20]=0x01; 
  u8 char_extent1;
  u8 char_extent2;
  u16 checksum_tc_3 = calculate_iso_checksum(TC_6_2_1, 21);
  split_short(&char_extent1, &char_extent2, checksum_tc_3);
  TC_6_2_1[21] = char_extent1; TC_6_2_1[22] = char_extent2;
  gen_TCs_6_2(TC_6_2_2,64,0x00,0x20,0x04,0x00,0x10,TRUE);
  
  u8 TC_6_9_1[10], TC_6_9_2[10], TC_6_9_3[10], TC_6_9_4[10], TC_6_9_5[10], TC_6_9_6[10], TC_6_9_7[10], TC_6_9_8[10];
  gen_TCs_6_9(TC_6_9_1,3,0x20,0x04,0x00,0x00,TRUE);
  gen_TCs_6_9(TC_6_9_2,4,0x20,0x04,0x00,0x03,TRUE);
  gen_TCs_6_9(TC_6_9_3,6,0x20,0x04,0x00,0x07,TRUE);
  gen_TCs_6_9(TC_6_9_4,64,0x20,0x04,0x00,0x10,TRUE);
  gen_TCs_6_9(TC_6_9_5,0,0x20,0x04,0x00,0x00,TRUE);
  gen_TCs_6_9(TC_6_9_6,5,0x20,0x07,0xFF,0xFC,TRUE);
  gen_TCs_6_9(TC_6_9_7,992,0x1F,0xFF,0xFF,0x00,TRUE);
  gen_TCs_6_9(TC_6_9_8,65535,0x20,0x04,0x00,0x00,FALSE);

  tc_queue_insert_item(&tc_queue, TC_6_2_1, 23); tc_queue_insert_item(&tc_queue, TC_6_2_2, 74);
   tc_queue_insert_item(&tc_queue, TC_6_9_1, 10); tc_queue_insert_item(&tc_queue, TC_6_9_2, 10); 
    tc_queue_insert_item(&tc_queue, TC_6_9_3, 10); tc_queue_insert_item(&tc_queue, TC_6_9_4, 10);
     tc_queue_insert_item(&tc_queue, TC_6_9_5, 10); tc_queue_insert_item(&tc_queue, TC_6_9_6, 10); 
      tc_queue_insert_item(&tc_queue, TC_6_9_7, 10); tc_queue_insert_item(&tc_queue, TC_6_9_8, 10);
}

void IT_TCMD_090_CHECK(void) 
{
  unsigned int memory_adress_start_1 = 0x20040000; unsigned int memory_adress_start_2 = 0x20040400; 
                                                                          unsigned int memory_adress_start_3 = 0x20040803;
  unsigned char* pt_first_pos_1= (unsigned char*)(memory_adress_start_1);
  unsigned char* pt_first_pos_2= (unsigned char*)(memory_adress_start_2); 
  unsigned char* pt_first_pos_3= (unsigned char*)(memory_adress_start_3);

  unsigned char expected_val_1[992], expected_val_2[992], expected_val_3[3] = {0xBE,0xBA,0xCA};
  give_expected_value(expected_val_1, 0, 992);
  give_expected_value(expected_val_2, 0x80, 992);
  
  int number_of_errors_1 = 0, number_of_errors_2 = 0, number_of_errors_3 = 0;
  for(int i=0; i<992; i++)
  {
    if ( ( *(pt_first_pos_1 + i) != expected_val_1[i] ) )
      number_of_errors_1 = 1;

    if ( ( *(pt_first_pos_2 + i) != expected_val_2[i] ) )
      number_of_errors_2 = 1;
  }
  for(int i=0; i<3; i++)
  {
    if ( *(pt_first_pos_3 + i) != expected_val_3[i] )
    number_of_errors_3 = 1;
  }
  correct_values_1(number_of_errors_1, number_of_errors_2, number_of_errors_3);
}

void IT_TCMD_110_CHECK(void) 
{
  unsigned int memory_adress_start_1 = 0x20040000; unsigned int memory_adress_start_2 = 0x20040010;
  unsigned char* pt_first_pos_1= (unsigned char*)(memory_adress_start_1);
  unsigned char* pt_first_pos_2= (unsigned char*)(memory_adress_start_2);
  unsigned char expected_val_2[64];

  unsigned short expected_checksum[4] = {0xFFFF,0x9CF8,0x24DC,0xCC4B};
  unsigned char expected_val_1[13] = {0x00,0x00,0x00,0xAB,0xCD,0xEF,0x01,0x14,0x56,0xF8,0x9A,0x00,0x01};
  give_expected_value(expected_val_2, 0x00, 64);

  int number_of_load_errors_1 = 0, number_of_load_errors_2 = 0;
  int number_of_check_errors = 0;
  for(int i=0; i<64; i++)
  {
    if ( ( *(pt_first_pos_2 + i) != expected_val_2[i] ) )
      number_of_load_errors_2 = 1;
  }
  for(int i=0; i<13; i++)
  {
    if ( ( *(pt_first_pos_1 + i) != expected_val_1[i] ) )
      number_of_load_errors_1 = 1;
  }
  for(int i=0; i<4; i++)
  {
    if ( (generation_checksums[i] != expected_checksum[i] ) )
      number_of_check_errors++;
  }
  correct_values_2(number_of_load_errors_1, number_of_load_errors_2, number_of_check_errors);
}