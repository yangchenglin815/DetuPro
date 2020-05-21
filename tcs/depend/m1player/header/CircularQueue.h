#ifndef _CIRCLE_QUEUE_H
#define _CIRCLE_QUEUE_H

#include <pthread.h>

extern "C"{
#include "libavutil/frame.h"
}

#define FRAME_QUEUE_SIZE 6
#define QUEUE_RESERVE_SIZE 2

typedef enum ErrCode{
	OK		= 0,
	ABORT	= -1
}ErrCode;

typedef struct Frame {
	long		serial;
	double      pts;
	AVFrame		*frame;
	ErrCode		err_code;
	bool		decode_successd;
} Frame;

typedef struct re_circular_queue {
	pthread_mutex_t mutex;
	pthread_cond_t cond;

	Frame queue[FRAME_QUEUE_SIZE];

    int item_size;
    int capacity;
    int size;

    int write_index;
    int read_index;

    bool abort;
	bool inited;
}re_circular_queue_t;

bool re_circular_queue_init(struct re_circular_queue *cq);

void re_circular_queue_abort(struct re_circular_queue *cq);

void re_circular_queue_free(struct re_circular_queue *cq);

int  re_circular_queue_wait_write(struct re_circular_queue *cq);

Frame *re_circular_queue_peek_write(struct re_circular_queue *cq);

void re_circular_queue_advance_write(struct re_circular_queue *cq);

void re_circular_queue_wait_read(struct re_circular_queue *cq);

Frame *re_circular_queue_peek_read(struct re_circular_queue *cq);

void re_circular_queue_advance_read(struct re_circular_queue *cq);

int re_circular_queue_size(struct re_circular_queue *cq);

void re_circular_queue_reset(struct re_circular_queue *cq);

#endif
