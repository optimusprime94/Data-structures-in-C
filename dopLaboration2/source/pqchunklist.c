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
* F�r att finna r�tt position f�r ins�ttning m�ste en s�kning utf�ras.
* S�kningar i enkell�nkade listor kan vara 'kn�ligt'. I den h�r
* implementeringen anv�nds tv� 'paralella pekare, en f�ljer ett steg
* bakom den andra, till dess att vi finner korrekt position f�r ins�ttning
* av den nya noden. Notera specialfallet vid ins�ttning vid listans
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
		newBlock->values[0] = curBlock->values[2]; //flytta �ver 3e elementet till nya blocket.
		newBlock->values[1] = curBlock->values[3]; //flytta �ver 4e elementet till nya blocket.
		curBlock->counter -= 2; //anpassar counter minskar current med tv�
		newBlock->counter += 2; // �kar den nya counter med tv� f�r att det flyttas �ver tv� element
	}
	else{
		curBlock->counter++;
		curBlock->values[curBlock->counter];
	}
}
/* Implementation notes: DequeueMax
* --------------------------------
* Det st�rsta v�rdet sparas f�rst i listan s� att det �r
* enkelt att ta bort. Notera att minne f�r noder frig�rs
* vid borttagning ur k�n.
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
* Minnes f�rbrukningen utg�rs av minnet f�r en struct pqueueCDT +
* storleken p� summan av samtliga noder i den l�nkade listan.
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
