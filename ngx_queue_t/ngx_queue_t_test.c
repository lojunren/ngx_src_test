#include "ngx_dump.h"

#define POINTS_LEN 6

ngx_int_t my_point_cmp(const ngx_queue_t* lhs, const ngx_queue_t* rhs)
{
	my_point_queue_t* pt1 = ngx_queue_data(lhs, my_point_queue_t, queue);
	my_point_queue_t* pt2 = ngx_queue_data(rhs, my_point_queue_t, queue);

	if (pt1->point.x < pt2->point.x)
		return 0;
	else if(pt1->point.x > pt2->point.x)
		return 1;
	else if(pt1->point.y < pt2->point.y)
		return 0;
	else if(pt1->point.y > pt2->point.y)
		return 1;

	return 1;
}

void ngx_queue_t_test()
{
	int i = 0;
	ngx_pool_t* pool;
	ngx_queue_t* myque;
	my_point_queue_t* point;
	my_point_t points[POINTS_LEN] = {
		{10, 1}, {20, 9}, {9, 9}, {90, 80}, {5, 3}, {50, 20}
	};

	printf("----------------------------------------\n");
	printf("the size of ngx_queue_t: \n");
	printf("----------------------------------------\n");
	printf("%lu\n\n", sizeof(ngx_queue_t));

	printf("----------------------------------------\n");
	printf("create a new pool: \n");
	printf("----------------------------------------\n");
	pool = ngx_create_pool(1024, NULL);
	dump_pool(pool);

	printf("----------------------------------------\n");
	printf("alloc a queue head and nodes: \n");
	printf("----------------------------------------\n");
	myque = ngx_palloc(pool, sizeof(ngx_queue_t));
	ngx_queue_init(myque);

	for(i = 0; i < POINTS_LEN; ++i)
	{
		point = (my_point_queue_t*)ngx_palloc(pool, sizeof(my_point_queue_t));
		point->point.x = points[i].x;
		point->point.y = points[i].y;
		ngx_queue_init(&point->queue);

		ngx_queue_insert_head(myque, &point->queue);
	}

	dump_queue_from_tail(myque);
	printf("\n");

	printf("----------------------------------------\n");
	printf("sort the queue: \n");
	printf("----------------------------------------\n");
	ngx_queue_sort(myque, my_point_cmp);
	dump_queue_from_head(myque);
	printf("\n");

	printf("----------------------------------------\n");
	printf("the pool at the end: \n");
	printf("----------------------------------------\n");
	dump_pool(pool);
	ngx_destroy_pool(pool);
}

int main()
{
	ngx_queue_t_test();
	return 0;
}
