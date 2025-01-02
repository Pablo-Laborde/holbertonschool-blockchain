#ifndef CLI_H
#define CLI_H


/* Libraries */

	#include "string.h"
	#include "stdio.h"
	#include "stdlib.h"

	#include "unistd.h"


	#include "../crypto/hblk_crypto.h"
	#include "../blockchain/v0.3/blockchain.h"



/* Functions */

	/* cli.c */
		int cmd_maker(char **cmd);
		void cmd_clean(char **cmd);
		void cli_usage(void);
		int select_cmd(char *command);

	/* wallet.c */
		EC_KEY *wallet_load(char *path);
		void wallet_save(EC_KEY *key, char *path);



#endif
