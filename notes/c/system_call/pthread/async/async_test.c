#include <stdio.h>
#include <unistd.h>
#include "async.h"

static void test_function(void *args)
{
	printf("I want to sleep...\n");
	sleep(2);
	printf("I'm back!!!\n");
}

int main(void)
{
	struct async *a;

	a = Async.create(3);
	Async.send_task(a, test_function, NULL);
	Async.send_task(a, test_function, NULL);
	Async.send_task(a, test_function, NULL);
	Async.send_task(a, test_function, NULL);
	Async.wait(a);

	return 0;
}
