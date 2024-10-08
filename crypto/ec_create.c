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
		perror("Couldn't create key.\n");

	if (!EC_KEY_generate_key(key))
		perror("Couldn't init keys.\n");
	return (key);
}
