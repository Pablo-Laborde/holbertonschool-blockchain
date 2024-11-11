#include "hblk_crypto.h"


/**
 * ec_load- func
 * @folder: char const *
 * Return: EC_KEY *
 */
EC_KEY *ec_load(char const *folder)
{
	FILE *fd = NULL;
	EC_KEY *key = NULL;

	if (!folder || (chdir(folder) == -1))
		return (NULL);
	key = EC_KEY_new_by_curve_name(EC_CURVE);
	if (!key)
		return (NULL);
	fd = fopen(PRI_FILENAME, "r");
	PEM_read_ECPrivateKey(fd, &key, NULL, NULL);
	fclose(fd);
	fd = fopen(PUB_FILENAME, "r");
	PEM_read_EC_PUBKEY(fd, &key, NULL, NULL);
	fclose(fd);
	return (key);
}
