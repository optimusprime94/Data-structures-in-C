/* File: pqlist.c
* ------------------
* Authors: Elvir Dzeko och Carlos Penaloza, 2016
* 
* Random numbers blir inte sorterade!
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
	blockT *cur, *prev, *newBlock, *tempBlock;
	int i,j,temp, size;

	for (prev = NULL, cur = pqueue->head; cur != NULL; prev = cur, cur = cur->next) {
		if (newValue > cur->values[cur->nElem - 1]) break; // Compares to the last value in sorted block, because if it is bigger, then it should not go to the next.
		if (cur->next == NULL) break;
	}
	if (cur) {
		/* Inserts element in block */
		if (cur->nElem < MAX_ELEMENTS) {
			cur->values[cur->nElem] = newValue;
			cur->nElem++;
			i = cur->nElem - 1;
			/*----------------SORTING---------------------------*/
			while (i > 0 && cur->values[i] > cur->values[i - 1]) {
				temp = cur->values[i];
				cur->values[i] = cur->values[i - 1];
				cur->values[i - 1] = temp;

				i--;
			}
			/*----------------------------------------------------*/
		}
		/* Splits block when full */
		else {
			newBlock = New(blockT *);
			newBlock->nElem = 2;
			newBlock->values[0] = cur->values[0]; 
			newBlock->values[1] = cur->values[1]; 
			cur->values[0] = cur->values[2]; 
			cur->values[1] = cur->values[3];
			cur->values[2] = NULL;
			cur->values[3] = NULL;
			cur->nElem = 2;

			newBlock->next = cur;
			if (prev)
				prev->next = newBlock;
			else
				pqueue->head = newBlock;

			if (newValue > cur->values[0])
				tempBlock = newBlock;
			else  tempBlock = cur;

			tempBlock->values[tempBlock->nElem] = newValue;
			tempBlock->nElem++;
			i = tempBlock->nElem-1;
			/*----------------SORTING---------------------------*/
			while (i > 0 && tempBlock->values[i] > tempBlock->values[i - 1]) {
				temp = tempBlock->values[i];
				tempBlock->values[i] = tempBlock->values[i - 1];
				tempBlock->values[i - 1] = temp;

				i--;
			}
			/*----------------------------------------------------*/

		}
	}
	/* Creates first block */
	else {
		newBlock = New(blockT *);
		newBlock->nElem = 0;
		newBlock->values[newBlock->nElem] = newValue;
		newBlock->nElem++;
		newBlock->next = cur;
		if (prev)
			prev->next = newBlock;
		else
			pqueue->head = newBlock;
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

	value = pqueue->head->values[0]; // Max value is at index 0, in head-block.

	/* Re-organizes values when max is removed */
	while (pqueue->head->nElem > 0) { 
		for (i = 0; i < pqueue->head->nElem; i++) {
			pqueue->head->values[i] = pqueue->head->values[i + 1]; 
		}
		break;
	}
	pqueue->head->nElem--;  // because (max) is removed.
	/* Frees block when empty */
	if (pqueue->head->nElem <= 0) { 
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
