#include "hblk_crypto.h"


/**
 * ec_from_pub- func
 * @pub: uint8_t const *
 * Return: EC_KEY *
 */
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *key = NULL;

	if (!pub)
		return (ec_from_pub_errors(0));
	key = EC_KEY_new_by_curve_name(EC_CURVE);
	if (!key)
		return (ec_from_pub_errors(1));
	if (!EC_KEY_oct2key(key, (unsigned char *)pub, EC_PUB_LEN, NULL))
		return (ec_from_pub_errors(2));
	EC_KEY_set_private_key(key, NULL);
	return (key);
}


/**
 * ec_from_pub_errors- func
 * @error: int
 * Return: void *
 */
void *ec_from_pub_errors(int error)
{
	if (error == 1)
		printf("Key is NULL.\n");
	if (error == 2)
		printf("Failed to set public key.\n");
	return (NULL);
}
