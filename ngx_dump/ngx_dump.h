#ifndef NGX_DUMP_H
#define NGX_DUMP_H 

#include <stdio.h>
#include "nginx.h"
#include "ngx_config.h"
#include "ngx_conf_file.h" 
#include "ngx_core.h"
#include "ngx_string.h"
#include "ngx_palloc.h"
#include "ngx_list.h"
#include "ngx_array.h"
#include "ngx_queue.h"
#include "ngx_hash.h"

#define MAX_NUM 7
#define MAX_URL_LEN 15
#define MAX_IP_LEN 15

#define NGX_HASH_ELT_SIZE(name)		\
	(sizeof(void*) + ngx_align((name)->key.len+2, sizeof(void*)))

volatile ngx_cycle_t* ngx_cycle;

typedef struct 
{
	int x;
	int y;
}my_point_t;

typedef struct 
{
	my_point_t point;
	ngx_queue_t queue;
}my_point_queue_t;

void dump_array(ngx_array_t* array);

void dump_list(ngx_list_t* list);

void dump_pool(ngx_pool_t* pool);

void dump_queue_from_head(ngx_queue_t* queue);

void dump_queue_from_tail(ngx_queue_t* queue);

void dump_hash_array(ngx_array_t* array);

void dump_hash(ngx_hash_t* hash, ngx_array_t* array);

void dump_list_part(ngx_list_t* list, ngx_list_part_t* part);

void ngx_log_error_core(ngx_uint_t level, ngx_log_t* log, ngx_err_t err, const char* fmt, ...);


#endif
