#include "cli.h"


/**
 * basic_help -	Displays basic functionality.
 * @d:			Struct containing all data.
 * Return:		0 on succes, non zero otherwise.
 */
int basic_help(clid_t *d)
{
	(void)d;
	printf("Usage:\n");

	printf("\twallet_load <path>\n");
	printf("\twallet_create\n");
	printf("\twallet_save <path>\n");

	printf("\tsend <amount> <address>\n");

	printf("\tmine\n");
	printf("\tbc_init\n");

	printf("\tinfo\n");
	printf("\tcoin_distribution\n");
	printf("\tbc_init\n");
	printf("\tprint_block <block index>\n");

	printf("\tload <path>\n");
	printf("\tsave <path>\n");

	printf("\thelp\n");
	printf("\texit\n");
	/* for (; alpha_opt[i]; i++)
		printf("\t%s\n", alpha_opt[i]); */
	return (0);
}
