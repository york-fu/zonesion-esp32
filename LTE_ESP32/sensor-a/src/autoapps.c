#include <contiki.h>

PROCESS_NAME(gsm);
PROCESS_NAME(u_zhiyun);
PROCESS_NAME(at);
PROCESS_NAME(sensor);
struct process * const autostart_processes[] = {
  &gsm,
  &u_zhiyun,
  &at,
  &sensor,
  NULL
};
