#include "blockchain.h"


/**
 * block_destroy- func
 * @block: block_t *
 * Return: void
 */
void block_destroy(block_t *block)
{
	llist_destroy(block->transactions, 1, (node_dtor_t)transaction_destroy);
	free(block->transactions);
	free(block);
}
