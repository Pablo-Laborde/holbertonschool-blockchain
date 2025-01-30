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
	uint8_t exit_cli;
} clid_t;



/* Functions */

	/* cli.c */

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

	/* mine.c */

	/* info.c */

	/* ls_chain.c */
		int load_blockchain(clid_t *d);
		int save_blockchain(clid_t *d);
		int lsb_error(int no);



#endif
