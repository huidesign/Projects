/* 队列的顺序存贮结构（出队列时不移动元素，只改变队头元素的位置）*/
#pragma once
#ifndef _DS_QUEUE_H
#define _DS_QUEUE_H
#define QUEUE_INIT_SIZE	10
#define QUEUE_INCREMENT	2
typedef int QElemType;
typedef struct  
{
	QElemType *base;
	int front;	/* 指向队头元素 */
	int rear;	/* 指向对位元素下一位 */
	int queuesize;
}SqQueue, *SqQueuePt;
#endif