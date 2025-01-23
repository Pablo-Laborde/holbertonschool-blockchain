#include "cli.h"


/**
 * load -		loads a blockchain
 *
 * @path:		path to file
 *
 * Return:		blockchain
 */
blockchain_t *load(char *path)
{
	if (!path)
	{
		printf("Path not valid.\n");
		return (NULL);
	}
	return (blockchain_deserialize(path));
}

/**
 * save -		loads a blockchain
 *
 * @path:		path to file
 *
 * @blockchain:	blockchain to serialize
 *
 * Return:		0 on success, non zero otherwise
 */
int save(char *path, blockchain_t *blockchain)
{
	if (!path)
	{
		printf("Path not valid.\n");
		return (1);
	}
	return (blockchain_serialize(blockchain, path));
}
