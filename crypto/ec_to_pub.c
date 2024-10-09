#include "hblk_crypto.h"


/**
 * ec_to_pub- func
 * @key: EC_KEY const *
 * @pub: uint8_t *
 * Return: uint8_t *
 */
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	char *buf = NULL;
	const EC_GROUP *g = NULL;
	const EC_POINT *p = NULL;

	if (!key)
		return (NULL);
	g = EC_KEY_get0_group(key);
	p = EC_KEY_get0_public_key(key);
	if (!g || !p)
		return (NULL);
	buf = EC_POINT_point2hex(g, p, POINT_CONVERSION_UNCOMPRESSED, NULL);
	strcpy((char *)pub, buf);
	OPENSSL_free(buf);
	return (pub);
}
