/* ���е�˳������ṹ��������ʱ���ƶ�Ԫ�أ�ֻ�ı��ͷԪ�ص�λ�ã�*/
#pragma once
#ifndef _DS_QUEUE_H
#define _DS_QUEUE_H
#define QUEUE_INIT_SIZE	10
#define QUEUE_INCREMENT	2
typedef int QElemType;
typedef struct  
{
	QElemType *base;
	int front;	/* ָ���ͷԪ�� */
	int rear;	/* ָ���λԪ����һλ */
	int queuesize;
}SqQueue, *SqQueuePt;
#endif