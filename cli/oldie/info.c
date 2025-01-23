#include "cli.h"



/**
 * info -		prints some blockchain data
 *
 * @blockchain:	referenced blockchain
 *
 * @local_pool:	transactions list
 *
 * Return:		void
 */
void info(blockchain_t *blockchain, llist_t *local_pool)
{
	int no_blocks = 0, no_unspent = 0, no_tx = 0;

	if (blockchain)
	{
		if (blockchain->chain)
			no_blocks = llist_size(blockchain->chain);
		if (blockchain->unspent)
			no_unspent = llist_size(blockchain->unspent);
	}
	if (local_pool)
		no_tx = llist_size(local_pool);
	printf("No. of blocks:\t\t\t\t%d\n", no_blocks);
	printf("No. of unspent transaction output:\t%d\n", no_unspent);
	printf("No. of pennding transactions:\t\t%d\n", no_tx);
}


/**
 * print_dist -	Prints the distribution of coins.
 * @unspent:	List of unspent transactions.
 * Return:		Void.
 */
void print_dist(llist_t *unspent)
{
	dcoin_t *d_hash[256];

	if (!unspent)
		return;
	memset(d_hash, 0, sizeof(dcoin_t *) * 256);
	llist_for_each(unspent, (node_func_t)compute_node, d_hash);
	print_hash(d_hash);
	free_hash(d_hash);
}


/**
 * compute_node -	Adds a new node or updates the amount of an existing one.
 * @node:			Node to gather the inormation from.
 * @idx:			Nodes index, not used.
 * @d_hash:			Hash table where to save data in.
 * Return:			An integer.
 */
int compute_node(unspent_tx_out_t *node, int idx, dcoin_t **d_hash)
{
	dcoin_t *owner = NULL;

	(void)idx;
	owner = d_hash[node->out.pub[0]];
	if (owner)
		while (memcmp(owner->pub, node->out.pub, EC_PUB_LEN))
			owner = owner->next;
	if (!owner)
	{
		owner = malloc(sizeof(dcoin_t));
		owner->next = d_hash[node->out.pub[0]];
		memcpy(owner->pub, node->out.pub, EC_PUB_LEN);
		owner->amount = 0;
		d_hash[node->out.pub[0]] = owner;
	}
	owner->amount += node->out.amount;
	return (0);
}


/**
 * free_hash -	Frees a hash table.
 * @d_hash:		Hash table to be freed.
 * Return:		Void.
 */
void free_hash(dcoin_t **d_hash)
{
	int i = 0;
	dcoin_t *a = NULL, *b = NULL;

	for (; i < 256; i++)
	{
		a = d_hash[i];
		while (a)
		{
			b = a->next;
			free(a);
			a = b;
		}
	}
}


/**
 * print_hash -	Prints the hash table data.
 * @d_hash:		Hash table to be printed.
 * Return:		void
 */
void print_hash(dcoin_t **d_hash)
{
	int i = 0, total = 0;
	dcoin_t *a = NULL;

	for (; i < 256; i++)
	{
		a = d_hash[i];
		while (a)
		{
			HEXS(a->pub, EC_PUB_LEN);
			printf(": %u\n", a->amount);
			total += a->amount;
			a = a->next;
		}
	}
	printf("\nTotal amount of coins: %u\n", total);
}
