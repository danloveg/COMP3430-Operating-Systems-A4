// include stdio.h to get a definition of NULL
#include <stdio.h>

// include header file for linked list data structure definitions
# include "list.h"

// include header file for memory management routine definitions
# include "mymem.h"


// routine to insert a new <key,value> pair into the list.
void listInsert(listNodePtr *list, long value) {
	listNodePtr		newNode;

	newNode=(listNodePtr) mymalloc(sizeof(listNode));
	newNode->data=value;
	if (*list==NULL) {
		// first insertion into empty list
		newNode->next=NULL;
		*list=newNode;
	} else {
		// insert new node at head of list - easy
		newNode->next=*list;
		*list=newNode;
	}
} // end listInsert

int main(int argc, char*argv[]) {

  listNodePtr   listHead;
  listNodePtr   curr;
  long          val;

  listHead=NULL;

  // call myinit to initialize the memory manager
  myinit(65536);

  // read integers until zero entering them into the linked list
  do {
    printf("Enter an integer (zero to terminate): ");
    scanf("%ld",&val);
    if (val!=0) {
      // add number to list
      listInsert(&listHead,val);
    }  // end if
  } while (val!=0);

  // print the linked list
  printf("The integers on the linked list are:\n");
  for (curr=listHead;curr!=NULL;curr=curr->next) {
    printf("%ld\n",curr->data);
  } // end for

  // print the number of nodes on the freelist - should be 1
  printf("Number of nodes on the freelist is %d.\n",numNodesOnFreeList());

  // safely free the space allocated for the nodes of the linked list
  printf("Deleting the linked list nodes.\n");
  curr = listHead;
  while(curr != NULL) {
    listNodePtr next = curr->next;
    myfree(curr,sizeof(listNode));
    curr = next;
  } // end while

  printf("All done.\n\n");
} // end main
