#include "list.h"
#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node* PtNode;

typedef struct node {
	ListElem element;
	PtNode next, prev;
} Node;

typedef struct listImpl {
	PtNode header, trailer;
	int size;
} ListImpl;


static PtNode nodeAtRank(PtList list, int rank) {
	
	int currentRank = 0;
	PtNode currentNode = list->header->next;
	while (currentNode != NULL) { 

		if (currentRank == rank) return currentNode;

		currentRank++;
		currentNode = currentNode->next;
	}
	return NULL;
}


PtList listCreate() {
		
	ListImpl* linkedList = (ListImpl*) malloc(sizeof(ListImpl));
	if(linkedList == NULL)
		return NULL;
	linkedList->size = 0;
	linkedList->header = (PtNode) malloc(sizeof(Node));
	if(linkedList->header == NULL){
		free(linkedList);
		return NULL;
	}
	linkedList->trailer = (PtNode) malloc(sizeof(Node));
	if(linkedList->trailer == NULL){
		free(linkedList->header);
		free(linkedList);
		return NULL;
	}
	linkedList->header->next = linkedList->trailer;
	linkedList->trailer->prev = linkedList->header;
	return linkedList;
}

int listDestroy(PtList *ptList) {
	PtList listToDestroy = *ptList;
	if(listToDestroy == NULL)
		return LIST_NULL;
	PtNode nextNode = listToDestroy->header;
	while(nextNode == NULL){
		PtNode aux = nextNode->next;
		free(nextNode);
		nextNode = aux;
	}
	free(listToDestroy);
	*ptList = NULL;

	return LIST_OK;
}

int listAdd(PtList list, int rank, ListElem elem) {
	if (list == NULL) return LIST_NULL;
	if(rank < 0 || rank > list->size) return LIST_INVALID_RANK;
	PtNode nodeToAdd = (PtNode)malloc(sizeof(Node));
	nodeToAdd->element = elem;
	PtNode nodeRank = nodeAtRank(list, rank);
	PtNode prevNode = nodeRank->prev;
	nodeToAdd->next = nodeRank;
	nodeToAdd->prev = prevNode;
	nodeRank->prev = nodeToAdd;
	prevNode->next = nodeToAdd;
	list->size++;
	return LIST_OK;
}

int listRemove(PtList list, int rank, ListElem *ptElem) {
	if (list == NULL) return LIST_NULL;
	if(rank < 0 || rank > list->size) return LIST_INVALID_RANK;
	PtNode nodeToRemove = nodeAtRank(list, rank);
	*ptElem = nodeToRemove->element;
	nodeToRemove->prev->next = nodeToRemove->next;
	nodeToRemove->prev->next->prev = nodeToRemove->prev;
	list->size--;
	free(nodeToRemove);

	return LIST_OK;
}

int listGet(PtList list, int rank, ListElem *ptElem) {
	if (list == NULL) return LIST_NULL;
	if(rank < 0 || rank > list->size) return LIST_INVALID_RANK;
	PtNode currentNode = nodeAtRank(list, rank);
	/*
	for(int i = 0; i < list->size; i++){
		currentNode = currentNode->next;
	}
	*/
	*ptElem = currentNode->element;
	return LIST_OK;
}

int listSet(PtList list, int rank, ListElem elem, ListElem *ptOldElem) {
	if (list == NULL) return LIST_NULL;
	if(rank < 0 || rank > list->size) return LIST_INVALID_RANK;
	PtNode currentNode = nodeAtRank(list, rank);
	/*
	for(int i = 0; i < list->size; i++){
		currentNode = currentNode->next;
	}
	*/
	*ptOldElem = currentNode->element;
	currentNode->element = elem;
	return LIST_OK;
}

int listSize(PtList list, int *ptSize) {
	if (list == NULL) return LIST_NULL;

	*ptSize = list->size;

	return LIST_OK;
}

bool listIsEmpty(PtList list) {
	if (list == NULL) return 1;

	return (list->size == 0);
}

int listClear(PtList list) {
	if (list == NULL) return LIST_NULL;
	
	PtNode currentNode = list->header->next;
	while(currentNode != list->trailer){
		PtNode aux = currentNode->next;
		free(currentNode);
		currentNode = aux;
	}
	list->header->next = list->trailer;
	list->trailer->prev = list->header;
	list->size = 0;

	return LIST_OK;
}

void listPrint(PtList list) {
	if (list == NULL) {
		printf("(LIST NULL)\n");
	}
	else if (listIsEmpty(list)) {
		printf("(LIST EMPTY)\n");
	}
	else {
		printf("List contents (by rank): \n");
		PtNode nextNode = list->header;
		while(nextNode->next != list->trailer){
			listElemPrint(nextNode->next->element);
			printf("\n");
			nextNode = nextNode->next;
		}	
	}
	printf("\n");
}

