#include "blockchain.h"


/**
 * block_destroy- func
 * @block: block_t *
 * Return: void
 */
void block_destroy(block_t *block)
{
	transaction_destroy(block->transaction);
	free(block);
}
