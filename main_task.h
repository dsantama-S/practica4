#ifndef MAIN_TASK_H_INCLUDED
#define MAIN_TASK_H_INCLUDED

#include "basic_types.h"

void init_sw_variables(void);

void program_systick_timer_interrupt(u32 period_usec);

void command_loop(void);

#endif // MAINTASK_H_INCLUDED