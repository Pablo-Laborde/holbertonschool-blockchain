#include "cli.h"




/**
 * 
 */
char const *cmd_name[8] = {
	"wallet_load",
	"wallet_save",
	"send",
	"mine",
	"info",
	"load",
	"save",
	NULL
};



/**
 * main -		command line interpreter
 *
 * Return:		0 on success, non zero otherwise
 */
int main(void)
{
	char *cmd[3];
	int am_arg = 0, x = 0;
	EC_KEY *wallet = NULL;

	cli_usage();
	memset(cmd, 0, 24);
	while (1)
	{
		write(1, "cmd > ", 6);
		am_arg = cmd_maker(cmd);
		if (am_arg > 3)
			cli_usage();
		else
		{
			x = select_cmd(cmd[0]);
			if (x == 0)
				wallet = wallet_load(cmd[1]);
			else if (x == 1)
				wallet_save(wallet, cmd[1]);
		}
		cmd_clean(cmd);
	}
	return (0);
}


/**
 * cmd_maker -	command retriever
 *
 * @cmd:		pointer where to save pointer to readed input
 *
 * Return:		amount of arguments
 */
int cmd_maker(char **cmd)
{
	char *str = NULL, *buffer = NULL;
	size_t size = 0, am_arg = 0;

	getline(&buffer, &size, stdin);
	str = strtok(buffer, " \n");
	while (str)
	{
		if (am_arg < 3)
			cmd[am_arg] = strdup(str);
		str = strtok(NULL, " \n");
		am_arg++;
	}
	free(buffer);
	return ((int)am_arg);
}


/**
 * cmd_clean -	frees and sets to NULL
 *
 * @cmd:		array of commands to free
 *
 * Return:		void
 */
void cmd_clean(char **cmd)
{
	int i = 0;

	for (; i < 3; i++)
		if (cmd[i])
			free(cmd[i]);
	memset(cmd, 0, 24);
}


/**
 * cli_usage -	display the posible functions
 *
 * Return:		void
 */
void cli_usage(void)
{
	printf("Usage:\n");
	printf("\twallet_load <path>\n");
	printf("\twallet_save <path>\n");
	printf("\tsend <amount> <address>\n");
	printf("\tmine\n");
	printf("\tinfo\n");
	printf("\tload <path>\n");
	printf("\tsave <path>\n");
	printf("\tto exit press Ctrl + C\n");
}


/**
 * select_cmd -	executes the correspondig function
 *
 * @command:	pointer to arguments
 *
 * Return:		position in cmd_name array on success, -1 on failure
 */
int select_cmd(char *command)
{
	int i = 0;

	if (!command)
		return (-1);
	while (cmd_name[i])
		if (!strcmp(cmd_name[i], command))
			return (i);
		else
			i++;
	return (-1);
}
