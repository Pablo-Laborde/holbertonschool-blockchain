#include "cli.h"



/**
 * print_block -	Prints a block.
 * @d:				Struct containing all data.
 * Return:			0 on succes, non zero otherwise.
 */
int print_block(clid_t *d)
{
	int idx = 0;
	block_t *b = NULL;
	block_info_t *i = NULL;
	block_data_t *a = NULL;

	if (!d)
		return (i_error(30));
	if (!d->bc)
		return (i_error(31));
	idx = atoi(d->av[1]);
	b = llist_get_node_at(d->bc->chain, idx);
	if (!b)
		return (i_error(32));
	i = &b->info;
	a = &b->data;
	printf("Hash: ");
	fflush(NULL);
	HEX(b->hash, SHA256_DIGEST_LENGTH);
	printf("\n");
	printf("i:%d - d:%d - t:%ld - n:%ld\n", i->index, i->difficulty,
		i->timestamp, i->nonce);
	printf("prev hash:");
	fflush(NULL);
	HEX(i->prev_hash, SHA256_DIGEST_LENGTH);
	printf("\n");
	printf("buffer: (%d) %s\n", a->len, a->buffer);
	llist_for_each(b->transactions, (node_func_t)print_tx, NULL);
	return (0);
}


/**
 * print_tx -	Prints a transaction.
 * @tx:			Transaction to print
 * @idx:		Transaction index.
 * @arg:		NULL.
 * Return:		0 on succes, non zero otherwise.
 */
int print_tx(transaction_t *tx, int idx, void *arg)
{
	(void)arg;
	printf("Tx id: (idx: %d)", idx);
	fflush(NULL);
	HEX(tx->id, SHA256_DIGEST_LENGTH);
	printf("\n");
	llist_for_each(tx->inputs, (node_func_t)print_in, NULL);
	llist_for_each(tx->outputs, (node_func_t)print_out, NULL);
	return (0);
}


/**
 * print_in -	Prints an in transaction.
 * @in:			Transaction to print
 * @idx:		Transaction index.
 * @arg:		NULL.
 * Return:		0 on succes, non zero otherwise.
 */
int print_in(tx_in_t *in, int idx, void *arg)
{
	(void)arg;
	(void)idx;
	printf("In:\n");
	printf("block_hash:");
	fflush(NULL);
	HEX(in->block_hash, SHA256_DIGEST_LENGTH);
	printf("\n");
	printf("tx_id:");
	fflush(NULL);
	HEX(in->tx_id, SHA256_DIGEST_LENGTH);
	printf("\n");
	printf("tx_out_hash:");
	fflush(NULL);
	HEX(in->tx_out_hash, SHA256_DIGEST_LENGTH);
	printf("\n");
	printf("sig:");
	fflush(NULL);
	HEX(&in->sig, sizeof(sig_t));
	printf("\n");
	return (0);
}


/**
 * print_out -	Prints an out transaction.
 * @out:		Transaction to print
 * @idx:		Transaction index.
 * @arg:		NULL.
 * Return:		0 on succes, non zero otherwise.
 */
int print_out(tx_out_t *out, int idx, void *arg)
{
	(void)arg;
	(void)idx;
	printf("Out: (amount: %d)\n", out->amount);
	printf("pub:");
	fflush(NULL);
	HEX(out->pub, EC_PUB_LEN);
	printf("\n");
	printf("hash:");
	fflush(NULL);
	HEX(out->hash, SHA256_DIGEST_LENGTH);
	printf("\n");
	return (0);
}
