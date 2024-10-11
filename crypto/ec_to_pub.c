#include "hblk_crypto.h"


/**
 * ec_to_pub- func
 * @key: EC_KEY const *
 * @pub: uint8_t *
 * Return: uint8_t *
 */
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	int i = 0 ;
	char *buf = NULL;
	const EC_GROUP *g = NULL;
	const EC_POINT *p = NULL;
	point_conversion_form_t f;

	if (!key)
		return (NULL);
	g = EC_KEY_get0_group(key);
	p = EC_KEY_get0_public_key(key);
	if (!g || !p)
		return (NULL);
	f = EC_KEY_get_conv_form(key);
	buf = EC_POINT_point2hex(g, p, f, NULL);
	for (; i < EC_PUB_LEN; i++)
		pub[i] = buf[i];
	OPENSSL_free(buf);
	return (pub);
}
