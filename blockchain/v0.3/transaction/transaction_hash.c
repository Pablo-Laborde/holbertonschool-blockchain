#include "../blockchain.h"


/**
 * transaction_hash- func
 * @transaction: transaction_t const *
 * @hash_buf: uint8_t *
 * Return: uint8_t *
 */
uint8_t *transaction_hash(transaction_t const *transaction,
	uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	int in_size = 0, out_size = 0, size = 0, i = 0, j = 0;
	uint8_t *buffer = NULL;
	tx_in_t *ti = NULL;
	tx_out_t *to = NULL;

	if (!transaction || !hash_buf)
		return (NULL);
	in_size = llist_size(transaction->inputs);
	j = 32 * 3 * size;
	out_size = llist_size(transaction->outputs);
	size = j +  32 * out_size;
	printf("%d\n", size);
	buffer = malloc(size);
	if (!buffer)
		return (NULL);
	for (; i < in_size; i++)
	{
		ti = llist_get_node_at(transaction->inputs, i);
		memcpy(buffer + (i * 96), ti, 96);
	}
	for (i = 0; i < out_size; i++)
	{
		to = llist_get_node_at(transaction->outputs, i);
		memcpy(buffer + j + (i * 32), to, 32);
	}
	sha256((int8_t *)buffer, size, hash_buf);
	free(buffer);
	return (hash_buf);
}
