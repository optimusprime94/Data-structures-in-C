/*
* File: pqlist.c
* ------------------
*
* Niclas �strand, Data- och programstrukturer HT-2003
* Senast modifierad: 23/7 - 2003
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
* F�r att finna r�tt position f�r ins�ttning m�ste en s�kning utf�ras.
* S�kningar i enkell�nkade listor kan vara 'kn�ligt'. I den h�r
* implementeringen anv�nds tv� 'paralella pekare, en f�ljer ett steg
* bakom den andra, till dess att vi finner korrekt position f�r ins�ttning
* av den nya noden. Notera specialfallet vid ins�ttning vid listans
* huvud.
*/

void Enqueue(pqueueADT pqueue, int newValue)
{
	blockT *cur, *prev, *newCell;
	int i,j,temp;

	for (prev = NULL, cur = pqueue->head; cur != NULL; prev = cur, cur = cur->next) {
		if (newValue > cur->values[0]) break;
	}
	if (cur) {
		if (cur->nElem < MAX_ELEMENTS) {
			//placera p� r�tt plats
			cur->values[cur->nElem] = newValue;
			cur->nElem++;
			/*----------------SORTERING---------------------------*/
			for (i = 0; i <= cur->nElem; i++) {
				for (j = 0; j <= cur->nElem; j++) {

					if (cur->values[i] > cur->values[j]) { // ta bort det h�r!
						temp = cur->values[i];
						cur->values[i] = cur->values[j];
						cur->values[j] = temp;
					}
				}
			}
			/*----------------------------------------------------*/
		}
		else {
			newCell = New(blockT *);
			newCell->nElem = 0;
			newCell->values[newCell->nElem] = newValue;
			newCell->nElem++;

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
		if (prev)
			prev->next = newCell;
		else
			pqueue->head = newCell;
	}
	}


/* Implementation notes: DequeueMax
* --------------------------------
* Det st�rsta v�rdet sparas f�rst i listan s� att det �r
* enkelt att ta bort. Notera att minne f�r noder frig�rs
* vid borttagning ur k�n.
*/

int DequeueMax(pqueueADT pqueue) // Funkar med f�r linked list.
{
	blockT *toBeDeleted;
	int value, i;

	if (IsEmpty(pqueue))
		Error("Tried to dequeue max from an empty pqueue!");

	value = pqueue->head->values[0]; // Max is at index 0, in head-block.
						
	for (i = 0; i <= pqueue->head->nElem; i++) {  
		pqueue->head->values[i] = pqueue->head->values[i + 1];  // Moves values in block, from (i + 1) to i index, to remove max.
	}
	pqueue->head->nElem--;  // One element less when max is removed.

	if (pqueue->head->nElem == 0) { //removes block if there are 0 elements.
		toBeDeleted = pqueue->head;
		pqueue->head = pqueue->head->next;
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
