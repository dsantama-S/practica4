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
#include "it_tcmd_test.h"

t_tc_queue tc_queue;
u32 major_frame_cnt;
u32 comm_frame_cnt;
u32 accepted;
u32 rejected;
u32 executed;
u16 generation_checksums[32];

int main(void)
{
  init_sw_variables();
  program_systick_timer_interrupt(200000);
  do {
   command_loop();
   void IT_TCMD_110_CHECK(void);
  } while(1);

return 0;
}
