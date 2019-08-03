#include <stdlib.h>
#include <pthread.h>
#include "async.h"

static void *threader(void *args)
{
	struct async *self = (struct async *)args;
	struct async_task *tmp;
	struct async_task task;

	for (;;) {
		pthread_mutex_lock(&self->lock);

		if (self->count == 0 && !self->shutdown)
			pthread_cond_wait(&self->notify, &self->lock);
		if (self->count == 0 && self->shutdown) {
			pthread_mutex_unlock(&self->lock);
			break;
		}

		tmp = self->head;
		task = *tmp;

		if (self->count == 1)
			self->head = self->tail = NULL;
		else
			self->head = self->head->next;
		free(tmp);

		self->count--;

		pthread_mutex_unlock(&self->lock);

		task.func(task.args);
	}

	pthread_exit(NULL);
}

static void async_destroy(struct async *self)
{
	pthread_mutex_destroy(&self->lock);
	pthread_cond_destroy(&self->notify);
	free(self->threads);
	free(self);
}

struct async *async_create(int thread_num)
{
	int i;
	struct async *self;

	self = malloc(sizeof(*self));
	if (!self)
		return NULL;

	self->count = 0;
	self->shutdown = 0;
	self->head = self->tail = NULL;
	self->thread_num = thread_num;
	self->threads = malloc(sizeof(pthread_t) * thread_num);
	if (!self->threads) {
		free(self);
		return NULL;
	}

	pthread_mutex_init(&self->lock, NULL);
	pthread_cond_init(&self->notify, NULL);

	for (i = 0; i < thread_num; i++)
		pthread_create(&self->threads[i], NULL, threader, self);

	return self;
}

int async_send_task(struct async *self,
		     void (*func)(void *args),
		     void *args)
{
	struct async_task *task;

	task = malloc(sizeof(*task));
	if (!task)
		return 1;

	task->func = func;
	task->args = args;
	task->next = NULL;

	pthread_mutex_lock(&self->lock);

	if (self->count == 0) {
		self->head = self->tail = task;
	} else {
		self->tail->next = task;
		self->tail = task;
	}

	self->count++;
	pthread_mutex_unlock(&self->lock);

	pthread_cond_signal(&self->notify);

	return 0;
}

void async_wait(struct async *self)
{
	int i;

	pthread_mutex_lock(&self->lock);
	self->shutdown = 1;
	pthread_mutex_unlock(&self->lock);

	pthread_cond_broadcast(&self->notify);

	for (i = 0; i < self->thread_num; i++)
		pthread_join(self->threads[i], NULL);
	async_destroy(self);
}

struct async_operations Async = {
	.create    = async_create,
	.send_task = async_send_task,
	.wait      = async_wait,
};
