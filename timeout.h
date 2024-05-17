#ifndef TIMEOUT_H
#define TIMEOUT_H

#define TIMEOUT_ELAPSED_CHECK_U32(timeout_start, current_tick, timeout_time)   \
  ((current_tick > timeout_start + timeout_time))
#endif /*TIMEOUT_H*/
