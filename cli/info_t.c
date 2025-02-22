#include "cli.h"



/**
 * print_lp -	Prints the local pool of transactions.
 * @d:			Struct containing all data.
 * Return:		0 on succes, non zero otherwise.
 */
int print_lp(clid_t *d)
{
	if (!d)
		return (i_error(30));
	if (!d->local_pool)
		return (i_error(33));
	if (!llist_size(d->local_pool))
		printf("Local pool is empty.\n");
	if (!d->local_pool)
		printf("NILL\n");
	llist_for_each(d->local_pool, (node_func_t)print_tx, NULL);
	return (0);
}
