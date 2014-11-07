/**
 * ngx_pool_t test, to test ngx_palloc, ngx_palloc_block, ngx_palloc_large
 */

 #include"ngx_dump.h"

 void ngx_pool_t_test()
 {
 	int i = 0;
 	ngx_pool_t* pool;

 	printf("------------------------------\n");
 	printf("the size of the ngx_pool_data_t: \n");
 	printf("------------------------------\n");
 	printf("%lu\n\n", sizeof(ngx_pool_data_t));

 	printf("------------------------------\n");
 	printf("the size of the ngx_pool_t: \n");
  	printf("------------------------------\n");
  	printf("%lu\n\n", sizeof(ngx_pool_t));

 	printf("------------------------------\n");
 	printf("the size of the ngx_pool_large_t: \n");
 	printf("------------------------------\n");
 	printf("%lu\n\n", sizeof(ngx_pool_large_t));

 	printf("------------------------------\n");
 	printf("create a new pool:\n");
 	printf("------------------------------\n");
 	pool = ngx_create_pool(1024, NULL);
 	dump_pool(pool);


 	printf("------------------------------\n");
 	printf("alloc block 1 from the poll:\n");
 	printf("------------------------------\n");
 	ngx_palloc(pool, 512);
 	dump_pool(pool);

 	printf("------------------------------\n");
 	printf("alloc block 2 from the pool:\n");
 	printf("------------------------------\n");
 	ngx_palloc(pool, 512);
 	dump_pool(pool);

 	printf("------------------------------\n");
 	printf("alloc block 3 from the pool:\n");
 	printf("------------------------------\n");
 	ngx_palloc(pool, 512);
 	dump_pool(pool);

 	printf("------------------------------\n");
 	printf("alloc 1 large memory from the pool: \n");
 	printf("------------------------------\n");
 	ngx_palloc(pool, 40960);
 	dump_pool(pool);

 	printf("------------------------------\n");
 	printf("alloc 2 large memory from the pool: \n");
 	printf("------------------------------\n");
 	ngx_palloc(pool, 40960);
 	dump_pool(pool);

 	printf("------------------------------\n");
 	printf("alloc 3 large memory from the pool:\n");
  	printf("------------------------------\n");
  	ngx_palloc(pool, 40960);
  	dump_pool(pool);

 	printf("------------------------------\n");
 	printf("alloc n large memory from the pool:\n");
 	printf("------------------------------\n");
 	for (i = 3; i < 30; ++i)
 	{
 		ngx_palloc(pool, 40960);
 	}

 	dump_pool(pool);
 	ngx_destroy_pool(pool);
 }

 int main()
 {
 	ngx_pool_t_test();
 	return 0;
 }
