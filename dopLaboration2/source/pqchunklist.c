/*
* File: heapQueue.c
* ------------------
*
* Carlos Peñaloza / Elvir Dzeko
* Senast modifierad: 16/05 - 2016
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
* För att finna rätt position för insättning måste en sökning utföras.
* Sökningar i enkellänkade listor kan vara 'knöligt'. I den här
* implementeringen används två 'paralella pekare, en följer ett steg
* bakom den andra, till dess att vi finner korrekt position för insättning
* av den nya noden. Notera specialfallet vid insättning vid listans
* huvud.
*/

void Enqueue(pqueueADT pqueue, int newValue) //FUNKAR EJ RIKTIGT ÄN
{

		blockT *cur, *prev, *newBlock;
		int size, i, j, temp;

		for (prev = NULL, cur = pqueue->head; cur != NULL; prev = cur, cur = cur->next) {
			for (i = 0; i < cur->nElements; i++) {
				if (cur->elements[i] <= newValue) break;
			} break;
		}
		size = cur->nElements;

		if (prev)
			prev->next = cur;
		else
			pqueue->head = cur;
	
		if (size == MAX_ELEMS_PER_BLOCK) {
			newBlock = New(blockT *);
			newBlock->nElements = 0;
			newBlock->next = NULL;

			if (prev)
				cur->next = newBlock;
		}

		if (size >= 0 && size <= MAX_ELEMS_PER_BLOCK) {

			cur->elements[size] = newValue;
			cur->nElements++;

/*----------------SORTERING---------------------------*/
			for (i = 0; i <= size; i++) {
				for (j = 0; j <= size; j++) {

					if (cur->elements[i] > cur->elements[j]) { // ta bort det här!
						temp = cur->elements[i];
						cur->elements[i] = cur->elements[j];
						cur->elements[j] = temp;
					}
				}
			}
/*----------------------------------------------------*/
		}
}




/* Implementation notes: DequeueMax
* --------------------------------
* Det största värdet sparas först i listan så att det är
* enkelt att ta bort. Notera att minne för noder frigörs
* vid borttagning ur kön.
*/

int DequeueMax(pqueueADT pqueue) // Tror denna funkar nu
{
	blockT *toBeDeleted;
	int value, i;

	if (IsEmpty(pqueue))
		Error("Tried to dequeue max from an empty pqueue!");
	
	value = pqueue->head->elements[0]; //Removes The MAX value which is in the first block, And in index 0.
	/* For-loop to reorganize the elements and put the new Max in index 0 */
	for (i = 0; i <= pqueue->head->nElements; i++) {
		pqueue->head->elements[i] = pqueue->head->elements[i+1];
	}
	pqueue->head->nElements--; //When Max is removed there is one element less in the block, so nElements is - 1.

	if (pqueue->head->nElements == -1) { // Removes the block if there is only one value, the max value.
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
