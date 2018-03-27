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
    assert(chunk1 != NULL && "FAIL: mymalloc returned NULL pointer");
    chunk2 = mymalloc(64);
    assert(chunk2 != NULL && "FAIL: mymalloc returned NULL pointer");
    chunk3 = mymalloc(64);
    assert(chunk3 != NULL && "FAIL: mymalloc returned NULL pointer");
    chunk4 = mymalloc(64);
    assert(chunk4 != NULL && "FAIL: mymalloc returned NULL pointer");

    myfree(chunk1, 64);
    myfree(chunk2, 64);
    myfree(chunk3, 64);
    myfree(chunk4, 64);
    numNodes = numNodesOnFreeList();
    assert(numNodes == 1 && "FAIL: Number of nodes is not 1");

    printf("PASS\n");


    // Test amalgamating from behind only
    printf("\nTesting amalgamating from behind...\n");
    chunk1 = mymalloc(64);
    assert(chunk1 != NULL && "FAIL: mymalloc returned NULL pointer");
    chunk2 = mymalloc(64);
    assert(chunk2 != NULL && "FAIL: mymalloc returned NULL pointer");
    chunk3 = mymalloc(64);
    assert(chunk3 != NULL && "FAIL: mymalloc returned NULL pointer");

    myfree(chunk2, 64);
    myfree(chunk3, 64);
    myfree(chunk1, 64);
    numNodes = numNodesOnFreeList();
    assert(numNodes == 1 && "FAIL: Number of nodes is not 1");

    printf("PASS\n");


    // Test amalgamating from the front
    printf("\nTesting amalgamating from the front...\n");
    chunk1 = mymalloc(64);
    assert(chunk1 != NULL && "FAIL: mymalloc returned NULL pointer");
    chunk2 = mymalloc(64);
    assert(chunk2 != NULL && "FAIL: mymalloc returned NULL pointer");
    chunk3 = mymalloc(64);
    assert(chunk3 != NULL && "FAIL: mymalloc returned NULL pointer");

    myfree(chunk1, 64);
    myfree(chunk2, 64);
    myfree(chunk3, 64);
    numNodes = numNodesOnFreeList();
    assert(numNodes == 1 && "FAIL: Number of nodes is not 1");

    printf("PASS\n");


    // Test amalgamating from both sides
    printf("\nTesting amalgamating from both sides...\n");
    chunk1 = mymalloc(64);
    assert(chunk1 != NULL && "FAIL: mymalloc returned NULL pointer");
    chunk2 = mymalloc(64);
    assert(chunk2 != NULL && "FAIL: mymalloc returned NULL pointer");
    chunk3 = mymalloc(64);

    myfree(chunk1, 64);
    myfree(chunk3, 64);
    myfree(chunk2, 64);
    numNodes = numNodesOnFreeList();
    assert(numNodes == 1 && "FAIL: Number of nodes is not 1");

    printf("PASS\n");
}
