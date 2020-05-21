#include <memory.h>
#include "CircularQueue.h"

static Frame *queue_fetch_or_alloc(struct re_circular_queue *cq,int index) 
{
    return &cq->queue[index];
}

static void queue_lock(struct re_circular_queue *cq) 
{
	pthread_mutex_lock(&cq->mutex);
}

static void queue_unlock(struct re_circular_queue *cq) 
{
	pthread_mutex_unlock(&cq->mutex);
}

static void queue_signal(struct re_circular_queue *cq)
{
    pthread_cond_signal(&cq->cond);
}

static void queue_broadcast(struct re_circular_queue *cq) 
{
    pthread_cond_broadcast(&cq->cond);
}

static void queue_wait(struct re_circular_queue *cq) 
{
    pthread_cond_wait(&cq->cond, &cq->mutex);
}

bool re_circular_queue_init(struct re_circular_queue *cq) 
{
    memset(cq, 0, sizeof(struct re_circular_queue));

	if (pthread_mutex_init(&cq->mutex, NULL) != 0)
		return false;

	if (pthread_cond_init(&cq->cond, NULL) != 0)
		goto fail;

    cq->item_size = sizeof(Frame);
	cq->capacity = FRAME_QUEUE_SIZE;
    cq->abort	= false;
	cq->inited	= true;

	for (int i = 0; i < cq->capacity; i++) {
		cq->queue[i].frame = av_frame_alloc();
	}

    cq->size = 0;
    cq->write_index = 0;
    cq->read_index = 0;

    return true;

fail:
    pthread_mutex_destroy(&cq->mutex);
    return false;
}

void re_circular_queue_abort(struct re_circular_queue *cq) 
{
    queue_lock(cq);
    cq->abort = true;
    cq->size = 0;
	for (int i = 0; i < cq->capacity; i++) {
		cq->queue[i].err_code = ABORT;
	}
    queue_broadcast(cq);
    queue_unlock(cq);
}

void re_circular_queue_free(struct re_circular_queue *cq) 
{
    const int capacity = cq->capacity;
    Frame* frame = NULL;
    for (int i = 0; i < capacity; i++) {
        frame = &cq->queue[i];
		av_frame_unref(frame->frame);
		av_frame_free(&frame->frame);
    }

    pthread_mutex_destroy(&cq->mutex);
	pthread_cond_destroy(&cq->cond);		
}

int re_circular_queue_wait_write(struct re_circular_queue *cq) {
    queue_lock(cq);

	while ((cq->size >= cq->capacity - QUEUE_RESERVE_SIZE) && !cq->abort)
        queue_wait(cq);

	int ret = cq->abort ? 1 : 0;

    queue_unlock(cq);

	return ret;
}

Frame *re_circular_queue_peek_write(struct re_circular_queue *cq) {
	Frame* frame = &cq->queue[cq->write_index];
	av_frame_unref(frame->frame);

    return queue_fetch_or_alloc(cq, cq->write_index);
}

void re_circular_queue_advance_write(struct re_circular_queue *cq) {
    if (cq->abort) {
        return;
    }

    cq->write_index = (cq->write_index + 1) % cq->capacity;

    queue_lock(cq);
    ++cq->size;
    queue_signal(cq);
    queue_unlock(cq);
}

void re_circular_queue_wait_read(struct re_circular_queue *cq) {
    queue_lock(cq);
    while (cq->size <= 0 && !cq->abort)
        queue_wait(cq);
    queue_unlock(cq);
}

Frame *re_circular_queue_peek_read(struct re_circular_queue *cq) {
    return queue_fetch_or_alloc(cq, cq->read_index);
}

void re_circular_queue_advance_read(struct re_circular_queue *cq) {
    cq->read_index = (cq->read_index + 1) % cq->capacity;
    queue_lock(cq);
    --cq->size;
    queue_signal(cq);
    queue_unlock(cq);
}

int re_circular_queue_size(struct re_circular_queue *cq)
{
	queue_lock(cq);
	int size = cq->size;
	queue_unlock(cq);
	return size;
}

void re_circular_queue_reset(struct re_circular_queue *cq)
{
	queue_lock(cq);
	cq->size = 0;
	cq->write_index = 0;
	cq->read_index = 0;
	queue_signal(cq);
	queue_unlock(cq);
}
