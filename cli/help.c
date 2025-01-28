#include "cli.h"


/**
 * basic_help -	Displays basic functionality.
 * @d:		Struct containing all data.
 * Return:		0 on succes, -1 on failure.
 */
int basic_help(clid_t *d)
{
	(void)d;
	printf("Usage:\n");
	printf("\twallet_load <path>\n");
	printf("\twallet_save <path>\n");
	printf("\tsend <amount> <address>\n");
	printf("\tmine\n");
	printf("\tinfo\n");
	printf("\tload <path>\n");
	printf("\tsave <path>\n");
	printf("\thelp\n");
	printf("\texit\n");
	return (0);
}
