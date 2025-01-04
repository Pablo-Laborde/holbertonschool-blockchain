#include "cli.h"


/**
 * send -			send an amount of coins
 *
 * @sender:			senders key
 *
 * @arg:			arguments
 *
 * @all_unspent:	list of unspent transactions
 *
 * Return:			transaction on SUCCESS, NULL otherwise
 */
transaction_t *send(EC_KEY *sender, char **arg, llist_t *all_unspent)
{
	transaction_t *tx = NULL;
	EC_KEY *receiver = NULL;
	uint32_t amount = 0;

	if (!arg[0] || !arg[1])
	{
		printf("No ammount or address specified.\n");
		return (NULL);
	}
	if (!sender)
	{
		printf("No sender specified.\n");
		return (NULL);
	}
	if (!all_unspent)
	{
		printf("No unspent transaction available.\n");
		return (NULL);
	}
	receiver = ec_from_pub((uint8_t const *)arg[1]);
	if (!receiver || check_num(arg[0]))
	{
		printf("Amount no valid or wrong address.\n");
		return (NULL);
	}
	amount = atoi(arg[0]);
	tx = transaction_create(sender, receiver, amount, all_unspent);
	if (!tx)
	{
		printf("Couldn't create transaction.\n");
		return (NULL);
	}
	return (tx);
}


/**
 * check_num -	checks if a string is a valid unsigned intger
 *
 * @str:		string to converto to integer
 *
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
