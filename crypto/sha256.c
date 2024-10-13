#include "hblk_crypto.h"


/**
 * sha256- func
 * @s: int8_t const *
 * @len: size_t
 * @digest: uint8_t *
 * Return: uint8_t *
 */
uint8_t *sha256(int8_t const *s, size_t len,
				uint8_t digest[SHA256_DIGEST_LENGTH])
{
	if (!digest)
		return (sha256_errors(0));
	if (!SHA256((unsigned char *)s, len, digest))
		return (sha256_errors(1));
	return (digest);
}


/**
 * sha256_errors- func
 * @error: int
 * Return: void *
 */
void *sha256_errors(int error)
{
	if (error == 1)
		printf("Failed to digest 'SHA256()'.\n");
	return (NULL);
}
