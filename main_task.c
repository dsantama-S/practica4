#include <stdio.h>
#include <stdlib.h>

#include "main_task.h"
#include "isocheck.h"
#include "tc_queue.h"
#include "basic_types.h"
#include "tcs_check.h"
#include "aux_functions.h"
#include "tc_execution.h"

#define REG_SYSTICK_CTRL   *(u32*)(0xE000E010u) 
#define REG_SYSTICK_RELOAD *(u32*)(0xE000E014u)

extern u32 major_frame_cnt;
extern u32 frame_count;
extern u32 accepted;
extern u32 rejected;
extern u32 executed;
extern t_tc_queue tc_queue;

void init_sw_variables(void)
{

  tc_queue_init(&tc_queue);
  major_frame_cnt = 0;
  frame_count = 0;
  accepted = 0;
  rejected = 0;
  executed = 0;

}

void program_systick_timer_interrupt (u32 period_usec) 
{
  REG_SYSTICK_RELOAD = period_usec;
  REG_SYSTICK_CTRL = 7;
}

void command_loop(void) 
{
  u8 tc_arrays[NUM_ITEMS+1][SIZE_ITEMS];
  if ( tc_queue_is_empty(&tc_queue) == FALSE )
  {
    for (int i=0; i<NUM_ITEMS; i++) 
    {
      tc_queue_extract_item(&tc_queue, tc_arrays[i], &tc_queue.num_bytes[i]);

      if ( correct_V_2_TC(tc_arrays[i], tc_queue.num_bytes[i]) == TRUE )
      {
        if ( tc_check_6_2(tc_arrays[i], tc_queue.num_bytes[i]) == TRUE )
          execution_6_2_TC(tc_arrays[i], tc_queue.num_bytes[i]);
        
        else
          discard_tc(tc_arrays[i], tc_queue.num_bytes[i], TRUE);
      }

      else if ( correct_V_9_TC(tc_arrays[i], tc_queue.num_bytes[i]) == TRUE )
      {
        if ( tc_check_6_9(tc_arrays[i], tc_queue.num_bytes[i]) == TRUE )
          execution_6_9_TC(tc_arrays[i], tc_queue.num_bytes[i]);

        else
          discard_tc(tc_arrays[i], tc_queue.num_bytes[i], TRUE);
      }
      else  
        discard_tc(tc_arrays[i], tc_queue.num_bytes[i], TRUE);
    }
  }
}


