
#include "usart.h"
#include "lib/ringbuf.h"

#define RECV_BUF_SIZE   256  //contiki ringbuf 最大不能超过256，
static struct ringbuf _recv_ring;

static int gsm_recv_ch(char ch)
{
  return ringbuf_put(&_recv_ring, ch);
}

void gsm_inf_init(void)
{
  static uint8_t _recv[RECV_BUF_SIZE];
  
  ringbuf_init(&_recv_ring, _recv, (uint8_t)RECV_BUF_SIZE);
  uart1_init(115200);
  uart1_set_input(gsm_recv_ch);
}

void gsm_uart_write(char *buf, int len)
{
  for (int i=0; i<len; i++) {
    uart1_putc(buf[i]);
  }
}

int gsm_uart_read_ch(void)
{
  return ringbuf_get(&_recv_ring);
}