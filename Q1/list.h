// the type definition for a linked list node
typedef struct ln {
	long		data;
	struct ln	*next;
} listNode, *listNodePtr;

// prototype definitions for the list operations
void listInsert(listNodePtr *list, long value);
