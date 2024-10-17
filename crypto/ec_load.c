#include "hblk_crypto.h"


/**
 * ec_load- func
 * @folder: char const *
 * Return: EC_KEY *
 */
EC_KEY *ec_load(char const *folder)
{
	int len = 0;
	EC_KEY *key = NULL;

	if (!folder)
		return (NULL);
	key = EC_KEY_new_by_curve_name(EC_CURVE);
	if (!key)
		return (NULL);
	while (folder[len])
		len++;
	ec_load_private(folder, len, &key);
	ec_load_public(folder, len, &key);
	return (key);
}


/**
 * ec_load_private- func
 * @folder: char const *
 * @len: int
 * @key: EC_KEY **
 * Return: EC_KEY *
 */
EC_KEY *ec_load_private(char const *folder, int len, EC_KEY **key)
{
	FILE *fd = NULL;
	char *path = NULL;
	EC_KEY *k = NULL;

	path = malloc(sizeof(char) * (len + 13));
	if (!path)
		return (NULL);
	strcpy(path, folder);
	strcat(path, "/");
	strcat(path, "key.pem");
	fd = fopen(path, "r");
	if (!fd)
		return (NULL);
	k = PEM_read_ECPrivateKey(fd, key, NULL, NULL);
	free(path);
	return (k);
}


/**
 * ec_load_public- func
 * @folder: char const *
 * @len: int
 * @key: EC_KEY **
 * Return: EC_KEY *
 */
EC_KEY *ec_load_public(char const *folder, int len, EC_KEY **key)
{
	FILE *fd = NULL;
	char *path = NULL;
	EC_KEY *k = NULL;

	path = malloc(sizeof(char) * (len + 13));
	if (!path)
		return (NULL);
	strcpy(path, folder);
	strcat(path, "pub_key.pem");
	strcat(path, "/");
	fd = fopen(path, "r");
	if (!fd)
		return (NULL);
	k = PEM_read_EC_PUBKEY(fd, key, NULL, NULL);
	free(path);
	return (k);
}
