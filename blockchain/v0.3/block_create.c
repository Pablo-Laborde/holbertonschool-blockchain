#include "blockchain.h"


/**
 * block_create -	creates a Block structure and initializes it
 *
 * @prev:			is a pointer to the previous Block in the Blockchain
 *
 * @data:			points to a memory area to duplicate in the Block’s data
 *
 * @data_len:		stores the number of bytes to duplicate in data.
 *					If data_len is bigger than BLOCKCHAIN_DATA_MAX,
 * 					then only BLOCKCHAIN_DATA_MAX bytes must be duplicated.
 *
 * Return:			pointer to the allocated Block
 *
 * The new Block’s index must be the previous Block’s index + 1
 *
 * The new Block’s difficulty and nonce must both be initialized to 0
 *
 * The new Block’s timestamp should be initialized using the time(2)
 * system call. It is normal if your value differs from the following example.
 *
 * The new Block’s hash must be zeroed
 */
block_t *block_create(block_t const *prev, int8_t const *data,
	uint32_t data_len)
{
	block_t *nb = NULL;
	uint32_t dl = 0;

	if (!data)
		return (NULL);
	nb = malloc(sizeof(block_t));
	if (!nb)
		return (NULL);
	if (!prev)
		nb->info.index = 0;
	else
		nb->info.index = prev->info.index + 1;
	nb->info.difficulty = 0;
	nb->info.timestamp = time(NULL);
	nb->info.nonce = 0;
	memcpy(nb->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);
	dl = (data_len > BLOCKCHAIN_DATA_MAX) ? BLOCKCHAIN_DATA_MAX : data_len;
	memcpy(nb->data.buffer, data, dl);
	nb->data.len = dl;
	memset(nb->hash, 0, SHA256_DIGEST_LENGTH);
	nb->transactions = llist_create(MT_SUPPORT_FALSE);
	return (nb);
}
