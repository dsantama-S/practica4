#include "tc_queue.h"
#include "basic_types.h"

#include <stdio.h>
#include <stdlib.h>

void tc_queue_init(t_tc_queue* queue)
{

    for (int i=0; i<(NUM_ITEMS + 1); i++)
    {
        queue->num_bytes[i] = 0;

            for (int j=0; j<SIZE_ITEMS; j++)
        {
            queue->tc_queue[i][j] = 0;
        }
    }

    queue->first_valid_item  = 0;
    queue->next_free_spot = 0;
}

bool tc_queue_is_full(t_tc_queue* queue)
{

    bool queue_full = FALSE;
    int queue_state = ((queue->first_valid_item) - (queue->next_free_spot));

    if ((queue_state < 0) && (queue_state + (NUM_ITEMS+1) == 1))
    {
        queue_full = TRUE;
    }

    else if (queue_state == 1)
    {
        queue_full = TRUE;
    }

    return queue_full;
}

bool tc_queue_is_empty(t_tc_queue* queue)
{

    bool queue_empty = FALSE;
    int queue_state = ((queue->first_valid_item) - (queue->next_free_spot));

    if (queue_state == 0)
    {
        queue_empty = TRUE;
    }

    return queue_empty;
}

bool tc_queue_is_more_than_half_full(t_tc_queue* queue)
{

    bool queue_half_full = FALSE;
    bool queue_empty = tc_queue_is_empty(queue);
    int queue_state = ((queue->first_valid_item) - (queue->next_free_spot));

    if (queue_empty == FALSE)
    {
        if ((queue_state < 0) && ((queue_state + (NUM_ITEMS+1)) <= (NUM_ITEMS/2)))
        {
            queue_half_full = TRUE;
        }
        else if ((queue_state >= 0) &&(queue_state <= (NUM_ITEMS/2)))
        {
            queue_half_full = TRUE;
        }
    }

    return queue_half_full;
}

bool tc_queue_insert_item(t_tc_queue* queue, unsigned char data[], int num_bytes)
{

  bool queue_full = tc_queue_is_full(queue);
  bool insert_try = TRUE;

  if (queue_full == TRUE)
  {
      insert_try = FALSE;
  }

  else
  {
    queue->num_bytes[queue->next_free_spot] = num_bytes;
    for (int i=0; i<=num_bytes; i++)
    {
      queue->tc_queue[queue->next_free_spot][i] = data[i];
    }

    queue->next_free_spot += 1;

    if (queue->next_free_spot == (NUM_ITEMS+1))
    {
      queue->next_free_spot = 0;
    }
  }

  return insert_try;
}

bool tc_queue_extract_item(t_tc_queue* queue, unsigned char data[], int* num_bytes)
{

  bool queue_empty = tc_queue_is_empty(queue);
  bool extract_try = TRUE;
  static int position_in_num_bytes;

  if (queue_empty == TRUE)
  {
    extract_try = FALSE;
  }

  else
  {
    queue->num_bytes[queue->first_valid_item] = *num_bytes;

    for (int i=0; i<=*num_bytes; i++)
    {
      data[i] = queue->tc_queue[queue->first_valid_item][i];
    }

    queue->first_valid_item += 1;

    if (queue->first_valid_item == (NUM_ITEMS+1))
    {
      queue->first_valid_item = 0;
    }

  }

  return extract_try;

}
