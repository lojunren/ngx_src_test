#include "ngx_dump.h"

void ngx_array_t_test()
{
	ngx_pool_t* pool;
	int i = 0;

	printf("--------------------------------\n");
   	printf("the size of ngx_array_t: \n");
	printf("--------------------------------\n");
	printf("%lu\n\n", sizeof(ngx_array_t));

	printf("--------------------------------\n");
	printf("create a new pool: \n");
	printf("--------------------------------\n");
	pool = ngx_create_pool(1024, NULL);
	dump_pool(pool);

	printf("--------------------------------\n");
	printf("alloc an array from the pool: \n");
	printf("--------------------------------\n");
	ngx_array_t* array = ngx_array_create(pool, 10, sizeof(int));
	dump_pool(pool);

	for(i = 0; i < 100; ++i)
	{
		int* ptr = ngx_array_push(array);
		*ptr = i + 1;
	}

	dump_array(array);

	ngx_array_destroy(array);
	ngx_destroy_pool(pool);
}

int main()
{
	ngx_array_t_test();
	return 0;
}