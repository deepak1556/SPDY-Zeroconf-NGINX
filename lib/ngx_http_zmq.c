#include <ngx_core.h>
#include <ngx_conf.h>
#include <ngx_http.h>
#include <ngx_http_spdy_module.h>
#include <src/zmq.h>

static ngx_command_t ngx_http_zmq_commands[] = {

  { ngx_string("zmq_buffer_size"),
    NGX_HTTP_MAIN_CONF|NGX_CONF_TAKE1,
    ngx_conf_set_size_slot,
    NGX_HTTP_MAIN_CONF_OFFSET,
    offsetof(ngx_http_zmq_main_conf_t, buffer_size),
    &ngx_http_zmq_buffer_size_post },

  { ngx_string("zmq_type"),
    NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
    ngx_conf_set_str_slot,
    NGX_HTTP_SRV_CONF_OFFSET,
    offset(ngx_http_zmq_srv_conf_t, zmq_type),
    &ngx_http_zmq_type_post },

  { ngx_string("zmq_bind_url"),
    NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
    ngx_conf_set_str_slot,
    NGX_HTTP_SRV_CONF_OFFSET,
    offsetof(ngx_http_zmq_srv_conf_t, zmq_bind_url),
    &ngx_http_zmq_bind_url },

  ngx_null_command

};

static ngx_http_module_t ngx_http_zmq_module_ctx = {
  ngx_http_zmq_add_variables,              /* preconfiguration */
  NULL,                                    /* postconfiguration */

  ngx_http_zmq_create_main_conf,           /* create main configuration */
  ngx_http_zmq_init_main_conf,             /* init main configuration */

  ngx_http_zmq_create_srv_conf,            /* create server configuration */
  ngx_http_zmq_merge_srv_conf,             /* merge server configuration */

  NULL,
  NULL
};
    
ngx_module_t ngx_http_zmq_module = {
  NGX_MODULE_V1,
  &ngx_http_zmq_module_ctx,
  ngx_http_zmq_commands,
  NGX_HTTP_MODULE,
  NULL,
  ngx_http_zmq_module_init,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NGX_MODULE_V1_PADDING
};

static ngx_http_variable_t ngx_http_zmq_vars[] = {

};

static ngx_int_t ngx_http_zmq_add_variavles(ngx_conf_t *cf) {
  ngx_http_variable_t *var, *v;

  for(v = ngx_http_zmq_vars; v->name.len; v++) {
    var = ngx_http_add_variable(cf, &v->name, v->flags);
    if (var == NULL) {
      return NGX_ERROR;
    }

    var->get_handler = v->get_handler;
    var->data = v->data;
  }

  return NGX_OK;
}
