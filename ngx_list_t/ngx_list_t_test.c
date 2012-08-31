#include "ngx_dump.h"

void ngx_list_t_test()
{
	ngx_pool_t* pool;
	int i = 0;

	printf("----------------------------------\n");
	printf("the size of ngx_list_part_t:\n");
	printf("----------------------------------\n");
	printf("%lu\n\n", sizeof(ngx_list_part_t));

	printf("----------------------------------\n");
	printf("the size of ngx_list_t:\n");
	printf("----------------------------------\n");
	printf("%lu\n\n", sizeof(ngx_list_t));

	printf("----------------------------------\n");
	printf("create a new pool:\n");
	printf("----------------------------------\n");
	pool = ngx_create_pool(1024, NULL);
	dump_pool(pool);

	printf("----------------------------------\n");
	printf("alloc an list from the pool:\n");
	printf("----------------------------------\n");
	ngx_list_t* list = ngx_list_create(pool, 5, sizeof(int));
	dump_pool(pool);

	for (i = 0; i < 300; ++i)
	{
		int* ptr = ngx_list_push(list);
		*ptr = i + 1;
	}

	printf("----------------------------------\n");
	printf("the list information:\n");
	printf("----------------------------------\n");
	dump_list(list);

	printf("----------------------------------\n");
	printf("the pool at the end:\n");
	printf("----------------------------------\n");
	dump_pool(pool);

    ngx_destroy_pool(pool);
}

int main()
{
	ngx_list_t_test();
	return 0;

}