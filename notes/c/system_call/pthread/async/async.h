#ifndef __ASYNC_H__
#define __ASYNC_H__

#include <pthread.h>

struct async_task {
	void (*func)(void *args);
	void *args;
	struct async_task *next;
};

struct async {
	pthread_mutex_t lock;
	pthread_cond_t notify;
	pthread_t *threads;
	int thread_num;
	int count;
	int shutdown;
	struct async_task *head, *tail;
};

struct async_operations {
	struct async *(*create)(int thread_num);
	int (*send_task)(struct async *self, void (*func)(void *args), void *args);
	void (*wait)(struct async *self);
} Async;

#endif /* __ASYNC_H__ */
