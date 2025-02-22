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
	uint8_t *r;

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
	r = unhex(d->av[2]);
	if (!r)
		return (s_error(49));
	receiver = ec_from_pub(r);
	free(r);
	if (!receiver)
		return (s_error(45));
	if (check_num(d->av[1]))
		return (s_error(48));
	amount = atoi(d->av[1]);
	tx = transaction_create(d->key, receiver, amount, d->bc->unspent);
	if (!tx)
		return (s_error(46));
	if (!transaction_is_valid(tx, d->bc->unspent))
		return (s_error(47));
	llist_add_node(d->local_pool, (llist_node_t)tx, ADD_NODE_REAR);
	printf("Transaction created.\n");
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
	{
		if ((str[i] > '9') || (str[i] < '0'))
			return (-1);
		i++;
	}
	if (i > 10)
		return (-1);
	return (0);
}


/**
 * unhex -	Converts a hexadecimal representation (string) to it's octal rep.
 * @s:		Hex string to convert.
 * Return:	Octal form.
 */
uint8_t *unhex(char *s)
{
	int i = 0, len = 0;
	uint8_t *uh = NULL, hb = 0;

	while (s[len])
		len++;
	if (len != (2 * EC_PUB_LEN))
		return (NULL);
	uh = malloc(sizeof(uint8_t) * EC_PUB_LEN);
	if (!uh)
		return (NULL);
	memset(uh, 0, EC_PUB_LEN);
	for (; i < len; i++)
	{
		hb = (uint8_t)((s[i] > '9') ? (s[i] - 'a' + 10) : (s[i] - '0'));
		uh[i / 2] = (i & 1) ? (uh[i / 2] | hb) : (hb << 4);
	}
	return (uh);
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
		printf("Wrong receiver address.\n");
	else if (no == 46)
		printf("Couldn't create transaction.\n");
	else if (no == 47)
		printf("Transaction wasn't valid.\n");
	else if (no == 48)
		printf("Amount not valid.\n");
	else if (no == 49)
		printf("String to key not valid.\n");
	return (no);
}
