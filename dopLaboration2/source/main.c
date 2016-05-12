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
	int value = 5;

	queue = NewPQueue(); //testar skapa en que
	if (IsEmpty(queue)) printf("IS EMPTY\n"); //testar om den är tom
	Enqueue(queue, value); //testar de olika funktionerna bara 
	//if (IsEmpty(queue)) printf("IS EMPTY\n");
	/*
	BasicPQueueTest();
	MorePQueueTest();
	PQueueSortTest();
	PQueuePerformance();
	return 0;
	*/
}
