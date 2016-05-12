/*
* File: pqchunklist.c
* ------------------
* Author: Elvir Dzeko
* 
* 
*/

#include "pqueue.h"
#include "genlib.h"

/* Constants */

#define MAX_ELEMS_PER_BLOCK 4

/* Types */

typedef struct blockT {
	int counter;
	int values[MAX_ELEMS_PER_BLOCK];
	struct blockT *next;
} blockT;

struct pqueueCDT {
	blockT *head;
};

/* Exported entries */

pqueueADT NewPQueue(void)
{
	pqueueADT pqueue;

	pqueue = New(pqueueADT);
	pqueue->head = NULL;

	return (pqueue);
}

void FreePQueue(pqueueADT pqueue)
{
	/*
	blockT *next;

	while (pqueue->head != NULL) {
		next = pqueue->head->next;
		FreeBlock(pqueue->head);
		pqueue->head = next;
	}
	FreeBlock(pqueue);
	*/
}

bool IsEmpty(pqueueADT pqueue)
{
	return (pqueue->head == NULL);
}

bool IsFull(pqueueADT pqueue)
{
	return (FALSE);
}

/* Implementation notes: Enqueue
* -----------------------------
* För att finna rätt position för insättning måste en sökning utföras.
* Sökningar i enkellänkade listor kan vara 'knöligt'. I den här
* implementeringen används två 'paralella pekare, en följer ett steg
* bakom den andra, till dess att vi finner korrekt position för insättning
* av den nya noden. Notera specialfallet vid insättning vid listans
* huvud.
*/

void Enqueue(pqueueADT pqueue, int newValue)
{
	blockT *cur, *prev, *newBlock, *curBlock;
	int i;

	if (IsEmpty) {
		newBlock = New(blockT *);
		newBlock->values[newBlock->counter] = newValue;
		newBlock->counter++;
	}
	for (prev = NULL, cur = pqueue->head; cur != NULL; prev = cur, cur = cur->next) {
		if (newValue > cur->values[0]) break;
	}

	curBlock = cur;
	if (curBlock->counter = 4) {
		newBlock = New(blockT *);
		newBlock->values[0] = curBlock->values[2]; //flytta över 3e elementet till nya blocket.
		newBlock->values[1] = curBlock->values[3]; //flytta över 4e elementet till nya blocket.
		curBlock->counter -= 2; //anpassar counter minskar current med två
		newBlock->counter += 2; // ökar den nya counter med två för att det flyttas över två element
	}
	else{
		curBlock->counter++;
		curBlock->values[curBlock->counter];
	}
}
/* Implementation notes: DequeueMax
* --------------------------------
* Det största värdet sparas först i listan så att det är
* enkelt att ta bort. Notera att minne för noder frigörs
* vid borttagning ur kön.
*/

int DequeueMax(pqueueADT pqueue)
{
	blockT *toBeDeleted;
	int value;

	if (IsEmpty(pqueue))
		Error("Tried to dequeue max from an empty pqueue!");
	
	value = pqueue->head->values[0];
	pqueue->head = pqueue->head->next;

	if (pqueue->head->counter == 0) { // Removes the block if there is only one value, the max value.
		toBeDeleted = pqueue->head;
		FreeBlock(toBeDeleted);
	}

	return (value);
}

/* Implementation notes: BytesUsed
* -------------------------------
* Minnes förbrukningen utgörs av minnet för en struct pqueueCDT +
* storleken på summan av samtliga noder i den länkade listan.
*/

int BytesUsed(pqueueADT pqueue)
{
	int total;
	blockT *cur;

	total = sizeof(*pqueue);
	for (cur = pqueue->head; cur != NULL; cur = cur->next)
		total += sizeof(*cur);

	return (total);
}
