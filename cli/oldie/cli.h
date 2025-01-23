#ifndef CLI_H
#define CLI_H


/* Libraries */

	#include "string.h"
	#include "stdio.h"
	#include "stdlib.h"

	#include "unistd.h"


	#include "../crypto/hblk_crypto.h"
	#include "../blockchain/v0.3/blockchain.h"

	#include "hex/hex.h"



/* Structures */

typedef struct dcoin_s
{
	struct dcoin_s *next;
	uint8_t pub[EC_PUB_LEN];
	uint32_t amount;
} dcoin_t;


/**
 * struct cli_data_s -	Struct that contains all the data needed to pass
 *						to functions.
 *
 * @av:		Array of arguments.
 */
typedef struct cli_data_s
{
	char *av[3];
} clid_t;


/* Variables */

	extern char const *cmd_name[];


/* Functions */

	/* cli.c */
		int cmd_maker(char **cmd);
		void cmd_clean(char **cmd);
		void cli_usage(void);
		int select_cmd(char *command);

	/* wallet.c */
		EC_KEY *wallet_load(char *path);
		void wallet_save(EC_KEY *key, char *path);

	/* send.c */
		transaction_t *send(EC_KEY *sender, char **arg, llist_t *all_unspent,
			llist_t *local_pool);
		int check_num(char *str);
		void *send_error(int error);

	/* mine.c */
		blockchain_t *mine(llist_t *local_pool, blockchain_t *blockchain,
			EC_KEY *receiver);
		int search_tx(transaction_t *tx, transaction_t *aux);
		void purge_tx(llist_t *local_pool, llist_t *unspent);

	/* info.c */
		void info(blockchain_t *blockchain, llist_t *local_pool);
		void print_dist(llist_t *unspent);
		int compute_node(unspent_tx_out_t *node, int idx, dcoin_t **d_hash);
		void free_hash(dcoin_t **d_hash);
		void print_hash(dcoin_t **d_hash);

	/* ls_blockchain.c */
		blockchain_t *load(char *path);
		int save(char *path, blockchain_t *blockchain);



#endif
