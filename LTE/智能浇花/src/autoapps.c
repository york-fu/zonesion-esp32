#include <contiki.h>

PROCESS_NAME(esp32);
PROCESS_NAME(at);
PROCESS_NAME(sensor);

struct process * const autostart_processes[] = {
  &esp32,
  &at,
  &sensor,
  NULL
};
