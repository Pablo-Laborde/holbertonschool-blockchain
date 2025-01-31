#include "cli.h"



/**
 * send -	Creates a transaction.
 * @d:		Struct containing all data.
 * Return:	0 on succes, non zero otherwise.
 */
int send(clid_t *d)
{
	transaction_t *tx = NULL;
	EC_KEY *receiver = NULL;
	uint32_t amount = 0;

	if (!d)
		return (s_error(40));
	if (!d->av[1] || !d->av[2])
		return (s_error(41));
	if (!d->key)
		return (s_error(42));
	if (!d->bc)
		return (s_error(43));
	if (!d->bc->unspent)
		return (s_error(44));
	receiver = ec_from_pub((uint8_t const *)d->av[2]);
	if (!receiver || check_num(d->av[1]))
		return (s_error(45));
	amount = atoi(d->av[1]);
	tx = transaction_create(d->key, receiver, amount, d->bc->unspent);
	if (!tx)
		return (s_error(46));
	if (!transaction_is_valid(tx, d->bc->unspent))
		return (s_error(47));
	llist_add_node(d->local_pool, (llist_node_t)tx, ADD_NODE_REAR);
	return (0);
}


/**
 * check_num -	checks if a string is a valid unsigned intger
 * @str:		string to converto to integer
 * Return:		0 if valid, non zero otherwise
 */
int check_num(char *str)
{
	int i = 0;

	while (str[i])
		if ((str[i] > '9') || (str[i] < '0'))
			return (-1);
	if (i > 10)
		return (-1);
	return (0);
}


/**
 * s_error -	Handles errors.
 * @no:			Error index.
 * Return:		Number that represents the error.
 */
int s_error(int no)
{
	if (no == 40)
		printf("No struct with data specified.\n");
	else if (no == 41)
		printf("No ammount or address specified.\n");
	else if (no == 42)
		printf("No sender specified.\n");
	else if (no == 43)
		printf("No blockchain initialized.\n");
	else if (no == 44)
		printf("No unspent transaction available.\n");
	else if (no == 45)
		printf("Amount no valid or wrong address.\n");
	else if (no == 46)
		printf("Couldn't create transaction.\n");
	else if (no == 47)
		printf("Transaction wasn't valid.\n");
	return (no);
}
