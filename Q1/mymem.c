#include <stdio.h>
#include <stdlib.h>

#include "mymem.h"


freeListNodePtr   freeListHead;  // pointer to free list ordered by
				 // starting address



// routine to return the maximum of two unsigned long integers
unsigned long max(unsigned long v1, unsigned long v2) {
  if (v1>=v2) {
    return (v1);
  } else {
    return (v2);
  } // end if
} // end max



// routine to allocate the space to be managed
void myinit(unsigned long areasz) {

  int  numNodesInSpace;

  numNodesInSpace=areasz/MINALLOCSIZE;
  if (numNodesInSpace*MINALLOCSIZE!=areasz) {
	// round up to a multiple of MINALLOCSIZE since we never want a free
	// area that is too small to hold free list node
	areasz=(numNodesInSpace+1)*MINALLOCSIZE;
} // end if


  // get the space
  freeListHead=(freeListNodePtr)malloc(areasz);

  // build a single free list node in the space
  freeListHead->size=areasz;
  freeListHead->next=NULL;
} // end myinit


// routine to print the number of nodes on the freelist
//- used to check if amalgamation worked.
int numNodesOnFreeList() {

  int numNodes;
  freeListNodePtr curr;

  numNodes=0;
  for (curr=freeListHead;curr!=NULL;curr=curr->next) numNodes++;
  return(numNodes);
} // end numNodesOnFreeList

// routine to allocate some space from the system
//   - uses the first fit algorithm to find free space to use
void *mymalloc(unsigned long sz) {

  unsigned long   allocSz;
  freeListNodePtr space;
  freeListNodePtr prev;
  freeListNodePtr curr;

  // we will always allocate an area at least large enough to contain
  // the free list structure when it is later freed
  allocSz=max(sz,MINALLOCSIZE);

  // use first fit to find an area from which to allocate 'allocSz'
  // bytes - we assume the list is ordered by address
  prev=NULL;
  for (curr=freeListHead;((curr!=NULL)&&(curr->size<allocSz));curr=curr->next) {
    prev=curr;
  } // end for
  // now allocate space from region pointed to by curr
  if (curr->size==allocSz) {
    // perfect fit so remove node from freelist
    if (prev==NULL) {
      // remove first node from freelist
      freeListHead=freeListHead->next;
    } else {
      // remove interior node from freelist
      prev->next=curr->next;
    } // end if
    space=curr;
  } else {
    // allocate part of free area (at the end) and leave the rest
    space=(freeListNodePtr)((unsigned long)curr+curr->size-allocSz);
    curr->size-=allocSz;
  } // end if
  return((void *)space);
} // end mymalloc


// routine to free some space and return it to the system
//   - You must add code to do free space amalgamation
void myfree(void *addr, unsigned long sz) {

  unsigned long     freeSz;
  freeListNodePtr   curr;
  freeListNodePtr   prev;
  freeListNodePtr   startAddr;
  freeListNodePtr   prevNode;
  freeListNodePtr   nextNode;

  // we always free an area at least as big as a free list structure
  freeSz=max(sz,MINALLOCSIZE);

  // return the area of size 'freeSz' bytes to the free list
  // amalgamating the area with any adjacent free areas.
  startAddr=(freeListNodePtr)addr;

  // search list for a node with an end address 1 less than startAddr
  // and for a node with a start address 1 greated than addr+freeSz
  prevNode=NULL;
  nextNode=NULL;
  prev=NULL;
  for (curr=freeListHead;((curr!=NULL)&&((prevNode==NULL)||
					 (nextNode==NULL)));curr=curr->next) {
    if (((freeListNodePtr)((unsigned long)curr+curr->size))==addr) {
      prevNode=curr;
    } // end if
    if (((freeListNodePtr)((unsigned long)addr+freeSz))==curr) {
      nextNode=curr;
    } // end if
    prev=curr;
  } // end for

  // Now handle the amalgamation and return to the free list
  //   Don't forget to unlink nodes on the list that are no longer
  //   neeeded
  if (prevNode!=NULL) {
    if (nextNode!=NULL) {
      // CASE 1: amalgmation with free nodes on either side
      printf("Case 1\n");
      prevNode -> size = prevNode -> size + freeSz + nextNode -> size;
      prevNode -> next = nextNode -> next;
    } else {
      // CASE 2: amalgamation with just preceding free node
      printf("Case 2\n");
      prevNode -> size = prevNode -> size + freeSz;
    } // end if
  } else {
    if (nextNode!=NULL) {
      // CASE 3: amalgamation with just the following free node
      printf("Case 3\n");

    } else {
      // CASE 4: no amalgamation - just insert into list at correct point

      // our new node is at the address being freed
      freeListNodePtr newNode = (freeListNodePtr) addr;
      newNode -> size = freeSz;

      if (newNode < prev) {
        newNode -> next = prev;
        // Assign new node to the head if necessary
        if (prev == freeListHead) {
          freeListHead = newNode;
        } else {
          prev = newNode;
        }
      } else {
        newNode -> next = prev -> next;
        prev -> next = newNode;
      }
    } // end if
  } //end if
} // end myfree
