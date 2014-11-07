#include "ngx_dump.h"

void ngx_log_error_core(ngx_uint_t level, ngx_log_t* log, ngx_err_t err, const char* fmt, ...)
{
	;
}

void dump_array(ngx_array_t* array)
{
	if(array)
	{
		printf("array = 0x%x\n", array);
		printf("	.pool = 0x%x\n", array->pool);
		printf("	.elts = 0x%x\n", array->elts);
		printf("	.nelts = 0x%x\n", array->nelts);
		printf("	.size = %lu\n", array->size);
		printf("	.nalloc = %u\n", array->nalloc);

		printf("elements: ");

		int* ptr = (int*)(array->elts);
		for (;	ptr < (int*)(array->elts + array->nalloc * array->size); )
		{
			printf("0x%x ", *(ptr++));
		}

		printf("\n");
	}
}

void dump_list(ngx_list_t* list)
{
	if (list == NULL)
	{
		return;
	}

	printf("list = 0x%x\n", list);
	printf("	.last = 0x%x\n", list->last);
	printf("	.part = 0x%x\n", &(list->part));
	printf("	.size = %lu\n", list->size);
	printf("	.nalloc = %u\n", list->nalloc);
	printf("	.pool\n", list->pool);

	printf("element:\n");

	ngx_list_part_t* part = &(list->part);
	while(part)
	{
		dump_list_part(list, part);
		part = part->next;
	}
	printf("\n");
}

void dump_pool(ngx_pool_t* pool)
{
 	while(pool)
 	{
 		printf("pool = 0x%x\n", pool);
 		printf(" .d\n");
 		printf("    .last = 0x%x\n", pool->d.last);
		printf("    .end = 0x%x\n", pool->d.end);
		printf("    .next = 0x%x\n", pool->d.next);
		printf("    .failed = %d\n", pool->d.failed);
		printf(" .max = %lu\n", pool->max);
		printf(" .current = 0x%x\n", pool->current);
		printf(" .chain = 0x%x\n", pool->chain);
		printf(" .large = 0x%x\n", pool->large);
		printf(" .cleanup = 0x%x\n", pool->cleanup);
		printf(" .log = 0x%x\n", pool->log);
		printf("available pool memory = %d\n\n", pool->d.end - pool->d.last);
		pool = pool->d.next;
 	}
}

void dump_list_part(ngx_list_t* list, ngx_list_part_t* part)
{
	int* ptr = (int*)(part->elts);
	int loop = 0;

	printf(" .part = 0x%x\n", &(list->part));
	printf("	.elts = 0x%x", part->elts);

	printf("(");
	for (; loop < list->nalloc - 1; ++loop)
	{
		printf("%d, ", ptr[loop]);
	}
	printf("%d)\n", ptr[loop]);
	printf("	.nelts = %d\n", part->nelts);
	printf("	.next = 0x%x", part->next);
	if (part->next)
	{
		printf("-->\n");
	}
	printf("\n");
}

void dump_queue_from_head(ngx_queue_t *que)
{
    ngx_queue_t *q = ngx_queue_head(que);
 
    printf("(0x%x: (0x%x, 0x%x)) <==> \n", que, que->prev, que->next);
 
    for (; q != ngx_queue_sentinel(que); q = ngx_queue_next(q))
    {
        my_point_queue_t *point = ngx_queue_data(q, my_point_queue_t, queue);
        printf("(0x%x: (%-2d, %-2d), 0x%x: (0x%x, 0x%x)) <==> \n", point, point->point.x,
            point->point.y, &point->queue, point->queue.prev, point->queue.next);
    }
}
 
void dump_queue_from_tail(ngx_queue_t *que)
{
    ngx_queue_t *q = ngx_queue_last(que);
 
    printf("(0x%x: (0x%x, 0x%x)) <==> \n", que, que->prev, que->next);
 
    for (; q != ngx_queue_sentinel(que); q = ngx_queue_prev(q))
    {
        my_point_queue_t *point = ngx_queue_data(q, my_point_queue_t, queue);
        printf("(0x%x: (%-2d, %-2d), 0x%x: (0x%x, 0x%x)) <==> \n", point, point->point.x,
            point->point.y, &point->queue, point->queue.prev, point->queue.next);
    }
}

void dump_hash_array(ngx_array_t* array)
{
    char prefix[] = "          ";

    if (array == NULL)
        return;

    printf("array = 0x%x\n", array);
    printf("  .elts = 0x%x\n", array->elts);
    printf("  .nelts = %d\n", array->nelts);
    printf("  .size = %d\n", array->size);
    printf("  .nalloc = %d\n", array->nalloc);
    printf("  .pool = 0x%x\n", array->pool);

    printf("  elements:\n");
    ngx_hash_key_t *ptr = (ngx_hash_key_t*)(array->elts);
    for (; ptr < (ngx_hash_key_t*)(array->elts + array->nalloc * array->size); ptr++)
    {
        printf("    0x%x: {key = (\"%s\"%.*s, %d), key_hash = %-10ld, value = \"%s\"%.*s}\n", 
            ptr, ptr->key.data, MAX_URL_LEN - ptr->key.len, prefix, ptr->key.len, 
            ptr->key_hash, ptr->value, MAX_IP_LEN - strlen(ptr->value), prefix);
    }
    printf("\n");
}

void dump_hash(ngx_hash_t* hash, ngx_array_t* array)
{
    int loop = 0;
    char prefix[] = "          ";
    u_short test[MAX_NUM] = {0};
    ngx_uint_t key;
    ngx_hash_key_t* elts;
    int nelts;

    if (hash == NULL)
        return;

    printf("hash = 0x%x: **buckets = 0x%x, size = %d\n", hash, hash->buckets, hash->size);

    for (loop = 0; loop < hash->size; loop++)
    {
        ngx_hash_elt_t *elt = hash->buckets[loop];
        printf("  0x%x: buckets[%d] = 0x%x\n", &(hash->buckets[loop]), loop, elt);
    }
    printf("\n");

    elts = (ngx_hash_key_t*)array->elts;
    nelts = array->nelts;
    for (loop = 0; loop < nelts; loop++)
    {
        char url[MAX_URL_LEN + 1] = {0};

        key = elts[loop].key_hash % hash->size;
        ngx_hash_elt_t *elt = (ngx_hash_elt_t *) ((u_char *) hash->buckets[key] + test[key]);

        ngx_strlow(url, elt->name, elt->len);
        printf("  buckets %d: 0x%x: {value = \"%s\"%.*s, len = %d, name = \"%s\"%.*s}\n", 
            key, elt, (char*)elt->value, MAX_IP_LEN - strlen((char*)elt->value), prefix, 
            elt->len, url, MAX_URL_LEN - elt->len, prefix); //replace elt->name with url

        test[key] = (u_short) (test[key] + NGX_HASH_ELT_SIZE(&elts[loop]));
    }
}
