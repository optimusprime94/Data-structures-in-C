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
	int nElements;
	int elements[MAX_ELEMS_PER_BLOCK];
	struct blockT *next;
} blockT;

struct pqueueCDT {
	int nBlocks;
	blockT *head;
};

/* Exported entries */


pqueueADT NewPQueue(void) //NewPQueue ska nu fungera riktigt! allokerar minne till en pq och ett nytt block.
{
	pqueueADT pqueue;

	pqueue = New(pqueueADT);
	pqueue->nBlocks = 0;
	pqueue->head = New(blockT *);
	pqueue->head->nElements = 0;
	pqueue->head->next = NULL;

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
	return (pqueue->head->nElements == NULL);
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

void Enqueue(pqueueADT pqueue, int newValue) //FUNKAR EJ RIKTIGT �N
{
	blockT *cur, *prev, *newBlock;
	int i, split = 0, size;

	if (pqueue->head->nElements == 0) {
		pqueue->head->elements[pqueue->head->nElements] = newValue;
		pqueue->head->nElements++;
	}

	//felet ligger n�gonstans ner�t
	for (prev = NULL, cur = pqueue->head; cur != NULL; prev = cur, cur = cur->next) {
		for (i = 0; i < cur->nElements; i++) {
			if (cur->elements[i] < newValue) split = i;  break;
		} break;
	}
	size = cur->nElements;
	if (size == 4) printf("FULL");

	else if (size > 0 && size < 4) {
		for (i = size; i >= split; i--) {
			cur->elements[size] = cur->elements[size - 1];
		}
		cur->elements[split] = newValue;
		cur->nElements++;
	}

}




/* Implementation notes: DequeueMax
* --------------------------------
* Det st�rsta v�rdet sparas f�rst i listan s� att det �r
* enkelt att ta bort. Notera att minne f�r noder frig�rs
* vid borttagning ur k�n.
*/

int DequeueMax(pqueueADT pqueue) // Tror denna funkar nu
{
	blockT *toBeDeleted;
	int value, i;

	if (IsEmpty(pqueue))
		Error("Tried to dequeue max from an empty pqueue!");
	
	value = pqueue->head->elements[0]; //Removes The MAX value which is in the first block, And in index 0.
	/* For-loop to reorganize the elements and put the new Max in index 0 */
	for (i = 1; i <= pqueue->head->nElements; i++) {
		pqueue->head->elements[i - 1] = pqueue->head->elements[i];
	}
	if (pqueue->head->nElements == 0) { // Removes the block if there is only one value, the max value.
		toBeDeleted = pqueue->head;
		pqueue->head = pqueue->head->next;
		FreeBlock(toBeDeleted);
	}
	pqueue->head->nElements--; //When Max is removed there is one element less in the block, so nElements is - 1.
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
