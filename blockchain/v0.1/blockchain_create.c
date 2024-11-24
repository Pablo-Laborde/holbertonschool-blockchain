#include "blockchain.h"


/**
 * blockchain_create- func
 * Return: blockchain_t *
 */
blockchain_t *blockchain_create(void)
{
	blockchain_t *blockchain = NULL;
	block_t *block = NULL;

	blockchain = malloc(sizeof(blockchain));
	if (!blockchain)
		return (NULL);
	blockchain->chain = llist_create(0);
	if (!blockchain->chain)
	{
		free(blockchain);
		return (NULL);
	}
	block = malloc(sizeof(block_t));
	if (!block)
	{
		llist_destroy(blockchain->chain, 0, NULL);
		free(blockchain);
		return (NULL);
	}
	block->info.index = 0;
	block->info.difficulty = 0;
	if (time((time_t *)&block->info.timestamp) == -1)
	{
		llist_destroy(blockchain->chain, 0, NULL);
		free(blockchain);
		free(block);
		return (NULL);
	}
	block->info.nonce = 0;
	memset(block->info.prev_hash, 0, SHA256_DIGEST_LENGTH);
	memset(block->data.buffer, 0, BLOCKCHAIN_DATA_MAX);
	strcpy((char *)&block->data.buffer, "Holberton School");
	block->data.len = strlen((char *)block->data.buffer);
	sha256(block->data.buffer, block->data.len, block->hash);
	llist_add_node(blockchain->chain, block, ADD_NODE_FRONT);
	return (blockchain);
}
