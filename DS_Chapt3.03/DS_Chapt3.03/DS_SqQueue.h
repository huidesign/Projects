#pragma once
#ifndef _DS_SQQUEUE_H
#define _DS_SQQUEUE_H

#define MAX_QSIZE	5
typedef int QElemType;
typedef struct {
	QElemType *base;
	int front;
	int rear;
}SqQueue, *SqQueuePt;
#endif