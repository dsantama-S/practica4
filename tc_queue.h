#ifndef TC_QUEUE_H_INCLUDED
#define TC_QUEUE_H_INCLUDED

#include "basic_types.h"
#define NUM_ITEMS 10
#define SIZE_ITEMS 1040

typedef struct
{
    unsigned char tc_queue[NUM_ITEMS + 1][SIZE_ITEMS];
    int num_bytes[NUM_ITEMS + 1];
    int first_valid_item;
    int next_free_spot;

}   t_tc_queue;

void tc_queue_init(t_tc_queue* queue);

bool tc_queue_is_full(t_tc_queue* queue);

bool tc_queue_is_empty(t_tc_queue* queue);

bool tc_queue_is_more_than_half_full(t_tc_queue* queue);

bool tc_queue_insert_item(t_tc_queue* queue, unsigned char data[], int num_bytes);

bool tc_queue_extract_item(t_tc_queue* queue, unsigned char data[], int* num_bytes);

#endif
