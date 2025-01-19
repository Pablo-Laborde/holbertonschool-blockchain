#include "blockchain.h"


/**
 * blockchain_serialize -	serialize blockchain
 *
 * @blockchain:		points to the Blockchain to be serialized
 *
 * @path:			contains the path to a file to serialize the Blockchain
 *					into
 *
 * Return:			0 upon success, or -1 upon failure
 *
 * If path points to an existing file, it must be overwritten
 */
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	uint32_t no_blocks = 0;
	FILE *fd = NULL;

	if (!blockchain || !path)
		return (-1);
	fd = fopen(path, "w");
	if (!fd)
		return (-1);
	if (fseek(fd, 0, SEEK_SET) == -1)
		return (-1);
	fprintf(fd, "HBLK0.3\x01");
	no_blocks = llist_size(blockchain->chain);
	fwrite(&no_blocks, sizeof(uint8_t), 4, fd);
	no_blocks = llist_size(blockchain->unspent);
	fwrite(&no_blocks, sizeof(uint8_t), 4, fd);
	if (llist_for_each(blockchain->chain, (node_func_t)save_block, fd) == -1)
		return (-1);
	if (llist_for_each(blockchain->unspent, (node_func_t)save_unspent, fd)
			== -1)
		return (-1);
	fflush(fd);
	fclose(fd);
	return (0);
}


/**
 * save_block -		serializes a block
 *
 * @block:			block to serialize
 *
 * @index:			blocks index
 *
 * @fd:				file descriptor to write data
 *
 * Return:			an integer
 */
int save_block(block_t *block, uint32_t index, FILE *fd)
{
	uint32_t size = 0;

	(void)index;
	fwrite(block, sizeof(uint8_t), 56, fd);
	fwrite(&block->data.len, sizeof(uint8_t), 4, fd);
	fwrite(block->data.buffer, sizeof(uint8_t), block->data.len, fd);
	fwrite(block->hash, sizeof(uint8_t), SHA256_DIGEST_LENGTH, fd);
	if (block->transactions)
	{
		size = llist_size(block->transactions);
		fwrite(&size, sizeof(uint8_t), 4, fd);
		if (llist_for_each(block->transactions, (node_func_t)save_tx, fd)
				== -1)
			return (-1);
	}
	else
	{
		size = -1;
		fwrite(&size, sizeof(uint8_t), 4, fd);
	}
	return (0);
}


/**
 * save_tx -		serializes a transaction
 *
 * @tx:				transaction to serialize
 *
 * @index:			transactions index
 *
 * @fd:				file descriptor to write data
 *
 * Return:			an integer
 */
int save_tx(transaction_t *tx, uint32_t index, FILE *fd)
{
	uint32_t size = 0;

	(void)index;
	fwrite(tx->id, sizeof(uint8_t), SHA256_DIGEST_LENGTH, fd);
	size = llist_size(tx->inputs);
	fwrite(&size, sizeof(uint8_t), 4, fd);
	size = llist_size(tx->outputs);
	fwrite(&size, sizeof(uint8_t), 4, fd);
	if (llist_for_each(tx->inputs, (node_func_t)save_in, fd) == -1)
		return (-1);
	if (llist_for_each(tx->outputs, (node_func_t)save_out, fd) == -1)
		return (-1);
	return (0);
}


/**
 * save_in -		serializes a transaction
 *
 * @in:				in transaction to serialize
 *
 * @index:			in transaction index
 *
 * @fd:				file descriptor to write data
 *
 * Return:			an integer
 */
int save_in(tx_in_t *in, uint32_t index, FILE *fd)
{
	(void)index;
	fwrite(in, sizeof(uint8_t), sizeof(tx_in_t), fd);
	return (0);
}


/**
 * save_out -		serializes a transaction
 *
 * @out:			transaction to serialize
 *
 * @index:			transactions index
 *
 * @fd:				file descriptor to write data
 *
 * Return:			an integer
 */
int save_out(tx_out_t *out, uint32_t index, FILE *fd)
{
	(void)index;
	fwrite(out, sizeof(uint8_t), sizeof(tx_out_t), fd);
	return (0);
}
