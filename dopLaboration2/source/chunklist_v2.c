/* File: pqlist.c
* ------------------
* Authors: Elvir Dzeko och Carlos Penaloza, 2016
* 
* 
*/

#include "pqueue.h"
#include "genlib.h"

/* Constants */

#define MAX_ELEMENTS 4

/* Types */

typedef struct blockT {
	int nElem;
	int values[MAX_ELEMENTS];
	struct blockT *next;
} blockT;

struct pqueueCDT {
	blockT *head;
	blockT *cursor;
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
	blockT *next;

	while (pqueue->head != NULL) {
		next = pqueue->head->next;
		FreeBlock(pqueue->head);
		pqueue->head = next;
	}
	FreeBlock(pqueue);
	
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
	blockT *cur, *prev, *newCell;
	int i,j,temp, size;

	for (prev = NULL, cur = pqueue->head; cur != NULL; prev = cur, cur = cur->next) {
		if (newValue > cur->values[0]) break;
	}
	if (cur) {

		size = cur->nElem;

		if (cur->nElem < MAX_ELEMENTS) {
			//placera på rätt plats
			cur->values[cur->nElem] = newValue;
			cur->nElem++;
			i = size;
			/*----------------SORTING---------------------------*/
			while (i > 0 && cur->values[i] > cur->values[i - 1]) {
				temp = cur->values[i];
				cur->values[i] = cur->values[i - 1];
				cur->values[i - 1] = temp;

				i--;
			}
			/*----------------------------------------------------*/
		}
		else {
			newCell = New(blockT *);
			newCell->nElem = 2;
			newCell->values[0] = cur->values[0]; // Moves first 2 values to newBlock.
			newCell->values[1] = cur->values[1]; // Moves first 2 values to newBlock.
			cur->values[2] = cur->values[0]; // Moves Later values to the beginning.
			cur->values[3] = cur->values[1]; // Moves first 2 values to newBlock.
			cur->values[2] = NULL;
			cur->values[3] = NULL;
			cur->nElem = 2;
			//newCell->values[newCell->nElem] = newValue;
			//newCell->nElem++;

			newCell->next = cur;
			if (prev)
				prev->next = newCell;
			else
				pqueue->head = newCell;


		}
	}
	else {
		newCell = New(blockT *);
		newCell->nElem = 0;
		newCell->values[newCell->nElem] = newValue;
		newCell->nElem++;

		newCell->next = cur;
		pqueue->head = newCell;
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
	int value, i;

	if (IsEmpty(pqueue))
		Error("Tried to dequeue max from an empty pqueue!");

	value = pqueue->head->values[0]; // Max is at index 0, in head-block.
	
	while (pqueue->head->nElem > 0) { // while-loop because the for-loop below does not work when there is only one element.
		for (i = 0; i < pqueue->head->nElem; i++) {
			pqueue->head->values[i] = pqueue->head->values[i + 1];  // Moves values in block, from (i + 1) to i index, to remove max.
		}
		break;
	}
	pqueue->head->nElem--;  // One element less when max is removed.

	if (pqueue->head->nElem <= 0) { //removes block if there are 0 elements.
		toBeDeleted = pqueue->head;
		pqueue->head = pqueue->head->next;
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
