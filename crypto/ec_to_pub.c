#include "hblk_crypto.h"


/**
 * ec_to_pub- func
 * @key: EC_KEY const *
 * @pub: uint8_t *
 * Return: uint8_t *
 */
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	unsigned char *buffer = NULL;
	size_t len = 0, i = 0;
	point_conversion_form_t f;

	if (!key)
		return (NULL);
	f = EC_KEY_get_conv_form(key);
	len = EC_KEY_key2buf(key, f, &buffer, NULL);
	for (; i < len; i++)
		pub[i] = buffer[i];
	OPENSSL_free(buffer);
	return (pub);
}
