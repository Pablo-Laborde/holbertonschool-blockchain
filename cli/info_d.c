#include "cli.h"



/**
 * print_dist -	Prints the distribution of coins.
 * @d:			Struct containing all data.
 * Return:		0 on succes, non zero otherwise.
 */
int print_dist(clid_t *d)
{
	dcoin_t *d_hash[256];

	if (!d)
		return (i_error(30));
	if (!d->bc)
		return (i_error(31));
	memset(d_hash, 0, sizeof(dcoin_t *) * 256);
	llist_for_each(d->bc->unspent, (node_func_t)compute_node, d_hash);
	print_hash(d_hash);
	free_hash(d_hash);
	return (0);
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
