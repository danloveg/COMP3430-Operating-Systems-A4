// -----------------------------------------------------------------------------
// test.c
//
// PURPOSE: Tests functions in mymem.c
// AUTHOR: Daniel Lovegrove
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <assert.h>
#include "mymem.h"

int main(int argc, char*argv[]) {
    void * chunk1, * chunk2, *chunk3, * chunk4;
    int numNodes;

    // Initialize memory
    myinit(65536);

    // Test contiguous allocating and freeing of memory
    printf("Testing contiguous allocation and deallocation...\n");
    chunk1 = mymalloc(64);
    assert(chunk1 != NULL && "mymalloc returned NULL pointer");
    chunk2 = mymalloc(64);
    assert(chunk1 != NULL && "mymalloc returned NULL pointer");
    chunk3 = mymalloc(64);
    assert(chunk1 != NULL && "mymalloc returned NULL pointer");
    chunk4 = mymalloc(64);
    assert(chunk1 != NULL && "mymalloc returned NULL pointer");
    numNodes = numNodesOnFreeList();
    assert(numNodes == 1 && "Number of nodes is not 1");

    myfree(chunk1, 64);
    myfree(chunk2, 64);
    myfree(chunk3, 64);
    myfree(chunk4, 64);

    printf("PASS\n");


    // Test freeing in reverse order
    printf("\nTesting freeing in reverse order...\n");

}
