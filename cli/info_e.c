#include "cli.h"



/**
 * bc_dist -	Prints the blockchain.
 * @d:			Struct containing all data.
 * Return:		0 on succes, non zero otherwise.
 */
int bc_dist(clid_t *d)
{
	if (!d)
		return (i_error(30));
	if (!d->bc)
		return (i_error(31));
	llist_for_each(d->bc->chain, (node_func_t)print_brief, NULL);
	return (0);
}


/**
 * print_brief -	Prints block briefly.
 * @b:				Block to print.
 * @idx:			Block index.
 * @arg:			NULL.
 * Return:			0 on succes, non zero otherwise.
 */
int print_brief(block_t *b, int idx, void *arg)
{
	(void)arg;
	(void)idx;
	printf("Block %d", b->info.index);
	fflush(NULL);
	HEX(b->hash, SHA256_DIGEST_LENGTH);
	printf("\n\n");
	return (0);
}
