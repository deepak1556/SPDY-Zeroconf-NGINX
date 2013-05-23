#ifndef _NGX_HTTP_ZMQ_MODULE_H_INCLUDED_
#define _NGX_HTTP_ZMQ_MODULE_H_INCLUDED_

#include <ngx_config.h>
#include <ngx_core.h>

typedef struct {
  size_t       buffer_size;
  u_char       *buffer;
}ngx__http_zmq_main_conf_t;

// Initialize a socket connection

void ngx_http_zmq_enable(ngx_str_t *socket_type, ngx_url_t *u)

//  Receive ZMQ string from socket and convert into C string

static char *ngx_http_zmq_srecv(void *socket)

extern ngx_module_t ngx_http_zmq_module_t;

#endif
