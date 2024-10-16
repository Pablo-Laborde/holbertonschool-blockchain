#include "hblk_crypto.h"


/**
 * ec_save- func
 * @key: EC_KEY *
 * @folder: char const
 * Return: int
 */
int ec_save(EC_KEY *key, char const *folder)
{
	int len = 0;

	if (!key)
		return (ec_save_errors(2));
	len = create_dir(folder);
	if (!len)
		return (ec_save_errors(1));
	ec_save_public(key, folder, len);
	ec_save_private(key, folder, len);
	return (1);
}


/**
 * ec_save_public- func
 * @key: EC_KEY *
 * @folder: char const
 * @len: int
 * Return: int
 */
int ec_save_public(EC_KEY *key, char const *folder, int len)
{
	FILE *fd = NULL;
	char *path = NULL;

	path = malloc(sizeof(char) * (len + 13));
	if (!path)
		return (ec_save_errors(3));
	strcpy(path, folder);
	strcat(path, "/");
	strcat(path, "pub_key.pem");
	fd = fopen(path, "w");
	PEM_write_EC_PUBKEY(fd, key);
	fclose(fd);
	free(path);
	return (1);
}


/**
 * ec_save_private- func
 * @key: EC_KEY *
 * @folder: char const
 * @len: int
 * Return: int
 */
int ec_save_private(EC_KEY *key, char const *folder, int len)
{
	FILE *fd = NULL;
	char *path = NULL;

	path = malloc(sizeof(char) * (len + 13));
	if (!path)
		return (ec_save_errors(3));
	strcpy(path, folder);
	strcat(path, "/");
	strcat(path, "key.pem");
	fd = fopen(path, "w");
	PEM_write_ECPrivateKey(fd, key, NULL, NULL, 0, NULL, NULL);
	fclose(fd);
	free(path);
	return (1);
}


/**
 * create_dir- func
 * @folder: char const
 * Return: int
 */
int create_dir(char const *folder)
{
	int n = 0;
	char *d = NULL;

	if (!folder)
		return (ec_save_errors(1));
	if (!folder[0])
		return (1);
	while (folder[n] != '\0')
	{
		n++;
		if ((folder[n] == '/') || folder[n] == '\0')
		{
			d = strndup(folder, n);
			mkdir(d, 0777);
			free(d);
		}
	}
	return (n);
}


/**
 * ec_save_errors- func
 * @error: int
 * Return: int
 */
int ec_save_errors(int error)
{
	if (error == 1)
		printf("Folder string is NULL.\n");
	if (error == 2)
		printf("Key is NULL.\n");
	if (error == 3)
		printf("Pathname is NULL.\n");
	return (0);
}
