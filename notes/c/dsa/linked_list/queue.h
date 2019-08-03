#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct queueNode {
	void *value;
	struct queueNode *next;
} queueNode;

typedef struct queue {
	queueNode *head;
	queueNode *tail;
	void *(*dup)(void *ptr);
	void (*free)(void *ptr);
	int (*match)(void *ptr, void *key);
	unsigned long len;
} queue;

typedef struct queueIter {
	queueNode *next;
} queueIter;

queue *queueCreate(void);
void queueRelease(queue *q);
queue *queueDup(queue *q);
void queueReverse(queue *q);
queueNode *queueSearchKey(queue *q, void *key);
queue *queueAdd(queue *q, void *value);
void *queueDelete(queue *q);
void queueDebug(queue *q);

queueIter *queueGetIter(queue *q);
void queueReleaseIter(queueIter *iter);
queueNode *queueNext(queueIter *iter);

#endif
