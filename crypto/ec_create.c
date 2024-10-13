#include "hblk_crypto.h"


/**
 * ec_create- func
 * Return: EC_KEY *
 */
EC_KEY *ec_create(void)
{
	EC_KEY *key = NULL;

	key = EC_KEY_new_by_curve_name(EC_CURVE);
	if (!key)
		ec_create_errors(1);
	if (!EC_KEY_generate_key(key))
		ec_create_errors(2);
	return (key);
}


/**
 * ec_create_errors- func
 * @error: int
 * Return: void *
 */
void *ec_create_errors(int error)
{
	if (error == 1)
		printf("Couldn't create key.\n");
	if (error == 2)
		printf("Couldn't init keys.\n");
	return (NULL);
}
