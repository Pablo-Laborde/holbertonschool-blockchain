#include "blockchain.h"


/**
 * block_create- func
 * @prev: block_t const *
 * @data: int8_t const
 * @data_len: uint32_t
 * Return: block_t *
 */
block_t *block_create(block_t const *prev, int8_t const *data,
	uint32_t data_len)
{
	block_t *nb = NULL;

	nb = malloc(sizeof(block_t));
	if (!nb)
		return (NULL);
	nb->info.index = prev->info.index + 1;
	nb->info.difficulty = 0;
	nb->info.timestamp = time(NULL);
	nb->info.nonce = 0;
	memcpy(nb->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);
	memcpy(&nb->data, data, data_len);
	memset(nb->hash, 0, SHA256_DIGEST_LENGTH);
	return (nb);
}
