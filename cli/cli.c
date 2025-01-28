#include "cli.h"



/**
 * main -		Command line interpreter.
 *
 * Return:		0 on success, non zero otherwise.
 */
int main(void)
{
	clid_t d;
	int (*func)(clid_t *);

	memset(&d, 0, sizeof(clid_t));
	while (!d.exit_cli)
	{
		get_input(d.av);
		if (d.av[0])
		{
			func = alpha_ret(d.av[0]);
			if (func)
				func(&d);
			free_args(d.av);
		}
	}
	return (0);
}
