/* File: main.c
 * ------------
 * Enkelt huvudprogram för laboration #2 - Prioritetskö.
 *
 * Niclas Åstrand, Data- och programstrukturer HT-2003
 * Senast modifierad 23/7 - 2003
 */

#include <stdio.h>
#include "genlib.h"
#include "pqueuetest.h"
#include "performance.h"

int main()
{
	pqueueADT queue;

	queue = NewPQueue(); //testar skapa en que

	if (IsEmpty(queue)) printf("IS EMPTY\n"); //testar om den är tom
	Enqueue(queue, 5); //testar de olika funktionerna bara 
	Enqueue(queue, 3); //testar de olika funktionerna bara 
	Enqueue(queue, 8); //testar de olika funktionerna bara 
	Enqueue(queue, 6);
	Enqueue(queue, 4);
	Enqueue(queue, 2);
	Enqueue(queue, 7);

	if (IsEmpty(queue)) printf("IS EMPTY\n");
	printf("%d ", DequeueMax(queue));
	printf("%d ", DequeueMax(queue));
	printf("%d ", DequeueMax(queue));
	printf("%d ", DequeueMax(queue));
	printf("%d ", DequeueMax(queue));
	printf("%d ", DequeueMax(queue));

	if (IsEmpty(queue)) printf("IS EMPTY\n");
	getchar();
	//if (IsEmpty(queue)) printf("IS EMPTY\n");
	/*
	BasicPQueueTest();
	MorePQueueTest();
	PQueueSortTest();
	PQueuePerformance();
	return 0;
	*/
}
