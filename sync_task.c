#include <stdio.h>
#include <stdlib.h>

#include "main_task.h"
#include "isocheck.h"
#include "tc_queue.h"
#include "basic_types.h"
#include "tcs_check.h"
#include "aux_functions.h"
#include "tc_execution.h"
#include "it_tcmd_test.h"

extern u32 major_frame_cnt;
extern u32 comm_frame_cnt;
extern u32 accepted;
extern u32 rejected;
extern u32 executed;
extern t_tc_queue tc_queue;
extern u16 generation_checksums[32];

/*
  Updates the counter for second and interruptions in a fiven second.
  Out: Updates those counters
*/
void update_frame_counters(void) 
{
  if (comm_frame_cnt == 49)
    {
      comm_frame_cnt = 0;
      major_frame_cnt += 1;
    }

    else  
      comm_frame_cnt += 1;
}

/*
  This is the function at where the processor jumps whenever thare's a systick type interruption.
  Out: Inserts the TCs in the queue.
*/
void SysTick_Handler(void) 
{
  update_frame_counters();
  
  if ( (major_frame_cnt == 5) && (comm_frame_cnt == 10) )
    IT_TCMD_090();

  if ( (major_frame_cnt == 10) && (comm_frame_cnt == 0) )
    IT_TCMD_090_CHECK();        

/*  if ( (major_frame_cnt == 3) && (comm_frame_cnt == 40) )
    IT_TCMD_110();

  if ( (major_frame_cnt == 10) && (comm_frame_cnt == 0) )
    IT_TCMD_110_CHECK(); */

}
