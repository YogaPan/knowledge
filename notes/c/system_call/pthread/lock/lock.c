#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#ifdef USE_LOCK
static pthread_mutex_t lock;
#endif
static int number;

static void *producer(void *param)
{
	int i;

#ifdef USE_LOCK
	pthread_mutex_lock(&lock);
#endif
	printf("I'm in critical\n");
	for (i = 0; i < 1000000; i++)
		number++;
	printf("I'm out\n");

#ifdef USE_LOCK
	pthread_mutex_unlock(&lock);
#endif
	pthread_exit(NULL);
}

static void *consumer(void *param)
{
	int i;

#ifdef USE_LOCK
	pthread_mutex_lock(&lock);
#endif
	printf("I'm in critical\n");
	for (i = 0; i < 1000000; i++)
		number--;
	printf("I'm out\n");
#ifdef USE_LOCK
	pthread_mutex_unlock(&lock);
#endif
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t producer_tid, consumer_tid;

#ifdef USE_LOCK
	pthread_mutex_init(&lock, NULL);
#endif

	pthread_create(&producer_tid, NULL, consumer, NULL);
	pthread_create(&consumer_tid, NULL, producer, NULL);

	pthread_join(producer_tid, NULL);
	pthread_join(consumer_tid, NULL);

	printf("%d\n", number);

	return 0;
}
