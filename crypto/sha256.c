#include "hblk_crypto.h"


/**
 * sha256- func
 * @s: int8_t const *
 * @len: size_t
 * @digest: uint8_t *
 * Return: uint8_t *
 */
uint8_t *sha256(int8_t const *s, size_t len, uint8_t digest[SHA256_DIGEST_LENGTH])
{
	const EVP_MD *evp_md = NULL;

	if (!digest)
		return (NULL);
	evp_md = EVP_sha256();
	if (!EVP_Digest(s, len, digest, NULL, evp_md, NULL))
		perror("Failed to digest.");
	return (digest);
}
