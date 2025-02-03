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

/**
 * struct dcoin_s -		Struct to list coin owners.
 *
 * @next:	Next node.
 * @pub:	Public key of the coins owner.
 * @amount:	Amount owned.
 */
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
	EC_KEY *key;
	blockchain_t *bc;
	llist_t *local_pool;
	uint8_t exit_cli;
} clid_t;


/* Variables */
	extern char const *alpha_opt[];


/* Functions */

	/* cli.c */
		int free_data(clid_t *d);

	/* command.c */
		int get_input(char **av);
		void free_args(char **av);

	/* help.c */
		int basic_help(clid_t *d);

	/* menu.c */
		int (*alpha_ret(char *str))(clid_t *d);

	/* exit.c */
		int exit_cli(clid_t *d);

	/* wallet.c */
		int load_wallet(clid_t *d);
		int create_wallet(clid_t *d);
		int save_wallet(clid_t *d);
		int w_error(int no);

	/* send.c */
		int send(clid_t *d);
		int check_num(char *str);
		int s_error(int no);

	/* mine.c */
		int mine(clid_t *d);
		int bc_init(clid_t *d);
		int search_tx(transaction_t *tx, transaction_t *aux);
		void purge_tx(llist_t *local_pool, llist_t *unspent);
		int m_error(int no);

	/* info.c */
		int info(clid_t *d);
		int i_error(int no);

	/* info_b.c */
		int print_block(clid_t *d);
		int print_tx(transaction_t *tx, int idx, void *arg);
		int print_in(tx_in_t *in, int idx, void *arg);
		int print_out(tx_out_t *out, int idx, void *arg);

	/* info_d.c */
		int print_dist(clid_t *d);
		int compute_node(unspent_tx_out_t *node, int idx, dcoin_t **d_hash);
		void free_hash(dcoin_t **d_hash);
		void print_hash(dcoin_t **d_hash);

	/* info_e.c */
		int bc_dist(clid_t *d);
		int print_brief(block_t *b, int idx, void *arg);

	/* ls_chain.c */
		int load_blockchain(clid_t *d);
		int save_blockchain(clid_t *d);
		int lsb_error(int no);



#endif
