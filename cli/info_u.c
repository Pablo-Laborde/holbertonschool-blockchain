#include "cli.h"



/**
 * print_unspent -	Prints unspent list.
 * @d:			Struct containing all data.
 * Return:		0 on succes, non zero otherwise.
 */
int print_unspent(clid_t *d)
{
	if (!d)
		return (i_error(30));
	if (!d->bc)
		return (i_error(31));
	if (!d->bc->unspent)
		return (i_error(34));
	if (!llist_size(d->bc->unspent))
		printf("Empty unspent list.\n");
	llist_for_each(d->bc->unspent, (node_func_t)print_uto, NULL);
	return (0);
}


/**
 * print_uto -	Prints an unspent node.
 * @uto:		Node to print.
 * @idx:		Node index, not used.
 * @arg:		NULL
 * Return:		An integer.
 */
int print_uto(unspent_tx_out_t *uto, int idx, void *arg)
{
	(void)idx;
	(void)arg;
	printf("Block Hash: ");
	fflush(NULL);
	HEX(uto->block_hash, SHA256_DIGEST_LENGTH);
	printf("\n");
	printf("Tx id: ");
	fflush(NULL);
	HEX(uto->tx_id, SHA256_DIGEST_LENGTH);
	printf("\n");
	print_out(&uto->out, 0, NULL);
	return (0);
}
