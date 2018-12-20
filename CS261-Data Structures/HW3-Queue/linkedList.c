#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/* TO COMPILE:
 Linux: gcc -shared -Wl,-soname,linkedList -o linkedList.so -fPIC linkedList.c
 Mac: gcc -shared -Wl,-install_name,linkedList.so -o linkedList.so -fPIC linkedList.c
*/

/* Double Link*/
struct DLink {
	TYPE value;
	struct DLink * next;
	struct DLink * prev;

};

/* Double Linked List with Head and Tail Sentinels  */

struct linkedList{
	int size;
	struct DLink * firstLink;
	struct DLink * lastLink;
};

/*
	initList
	param lst the linkedList
	pre: lst is not null
	post: lst size is 0
*/

void _initList (struct linkedList *lst) {
	struct DLink *tempFirst = malloc(sizeof(struct DLink));
	struct DLink *tempLast = malloc(sizeof(struct DLink));
	lst->firstLink = tempFirst;
	lst->lastLink = tempLast;

	tempFirst->prev = lst->lastLink;
	tempFirst->next = lst->lastLink;
	tempLast->prev = lst->firstLink;
	tempLast->next = lst->firstLink;

	lst->size = 0;
}

/*
 createList
 param: none
 pre: none
 post: firstLink and lastLink reference sentinels
 */

struct linkedList *createLinkedList()
{
	struct linkedList *newList = malloc(sizeof(struct linkedList));
	_initList(newList);
	return(newList);
}

/*
	_addLinkBeforeBefore
	param: lst the linkedList
	param: l the  link to add before
	param: v the value to add
	pre: lst is not null
	pre: l is not null
	post: lst is not empty
*/

/* Adds Before the provided link, l */

void _addLinkBefore(struct linkedList *lst, struct DLink *l, TYPE v)
{
	struct DLink * newLink = malloc(sizeof(struct DLink));
	newLink->value = v;
	newLink->prev = l->prev;
	if (l = lst->firstLink) {
		lst->firstLink = newLink;
		if (!l->value) {
			newLink->next = l->next;
			free(l);
		}
		else {
			l->prev = newLink;
			newLink->next = l;
		}
	}
	else {
		l->prev = newLink;
		newLink->next = l;
	}
	lst->size++;
}

/*
	_removeLink
	param: lst the linkedList
	param: l the linke to be removed
	pre: lst is not null
	pre: l is not null
	post: lst size is reduced by 1
*/
void _removeLink(struct linkedList *lst, struct DLink *l)
{
    if(l == lst->lastLink){
        lst->lastLink = l->prev;
    }
    else if(l == lst->firstLink){
        lst->firstLink = l->next;
    }
	l->prev->next = l->next;
	l->next->prev = l->prev;
	free(l);
	lst->size--;
}

/*
	isEmptyList
	param: lst the linkedList
	pre: lst is not null
	post: none
*/
int isEmptyList(struct linkedList *lst) {
	return lst->size == 0;
}

/* De-allocate all links of the list

	param: 	lst		pointer to the linked list
	pre:	none
	post:	All links (including the two sentinels) are de-allocated
*/
void freeLinkedList(struct linkedList *lst)
{
	while(!isEmptyList(lst)) {
		/* remove the link right after the first sentinel */
		_removeLink(lst, lst->firstLink->next);
	}
	/* remove the first and last sentinels */
	free(lst->firstLink);
	free(lst->lastLink);
}

/* 	Deallocate all the links and the linked list itself.

	param: 	v		pointer to the dynamic array
	pre:	v is not null
	post:	the memory used by v->data is freed
*/
void deleteLinkedList(struct linkedList *lst)
{
	assert (lst != 0);
	freeLinkedList(lst);
	free(lst);
}


/* Function to print list
 Pre: lst is not null
 */
void _printList(struct linkedList* lst)
{
	if (!isEmptyList(lst)) {
		struct DLink * currentLink = lst->firstLink;
		for (int i = 0; i < lst->size; i++) {
			printf("%d", currentLink->value);
			currentLink = currentLink->next;
		}
		free(currentLink);
	}

}

/* ************************************************************************
	Deque Interface Functions
************************************************************************ */

/*
	addFrontList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/
void addFrontList(struct linkedList *lst, TYPE e){
	_addLinkBefore(lst, lst->firstLink, e);
}

/*
	addBackList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/
void addBackList(struct linkedList *lst, TYPE e) {
	struct DLink * newLink = malloc(sizeof(struct DLink));
	newLink->value = e;
	newLink->next = lst->firstLink;
	if (!lst->lastLink->value) {
		newLink->prev = lst->lastLink->prev;
		_removeLink(lst, lst->lastLink);
	}
	else {
		lst->lastLink->next = newLink;
		newLink->prev = lst->lastLink;
	}
	lst->lastLink = newLink;
	lst->size++;
}

/*
	frontList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: none
*/
TYPE frontList (struct linkedList *lst) {
	return lst->firstLink->value;
}

/*
	backList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: lst is not empty
*/
TYPE backList(struct linkedList *lst)
{
	return lst->lastLink->value;
}



/*
	removeFrontList
	param: lst the linkedList
	pre:lst is not null
	pre: lst is not empty
	post: size is reduced by 1
*/
void removeFrontList(struct linkedList *lst) {
	_removeLink(lst, lst->firstLink);
}

/*
	removeBackList
	param: lst the linkedList
	pre: lst is not null
	pre:lst is not empty
	post: size reduced by 1
*/
void removeBackList(struct linkedList *lst) {
	_removeLink(lst, lst->lastLink);
}
