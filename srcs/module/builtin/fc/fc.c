#include "sh21.h"

t_option		get_option_fc(char *s, t_option option)
{
	option = 0;
	while (*s)
	{
		if (*s == 'L')
			option |= L_OPT;
		else if (*s == 'P')
			option |= P_OPT;
		else
		{
			ft_dprintf(g_shell->cur_fd.err,
					"21sh: pwd: -%c: invalid option\n", *s);
			ft_dprintf(g_shell->cur_fd.err, "pwd: usage: pwd [-LP]\n");
			return (ERROR_OPT);
		}
		s++;
	}
	return (option);
}

int8_t			fc_blt(t_registry *shell, char **av)
{
	t_option	option;

	++av;
	(void)shell;
	option = set_options(&av, get_option_fc);
	if (option == ERROR_OPT)
		return (FAILURE);
	return (SUCCESS);
}
