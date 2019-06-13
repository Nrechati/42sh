#include "sh21.h"

t_option		get_option_fc(char *s, t_option option)
{
	option = 0;
	while (*s)
	{
		if (*s == 'n')
			option |= N_OPT;
		else if (*s == 'l')
			option |= L_OPT;
		else if (*s == 'r')
			option |= R_OPT;
		else if (*s == 'e')
			option |= E_OPT;
		else if (*s == 's')
			option |= S_OPT;
		else
		{
			///// USAGE FC
			ft_dprintf(g_shell->cur_fd.err,
					"21sh: pwd: -%c: invalid option\n", *s);
			ft_dprintf(g_shell->cur_fd.err, "pwd: usage: pwd [-LP]\n");
			return (ERROR_OPT);
		}
		s++;
	}
	return (option);
}

static char		*get_first_last(char **av)
{
	char	*first;
	char	*last;
	char	*param;

	if (*av != NULL)
		first = ft_strjoin("first:", *av++);
	else
		return (NULL);
	if (*av != NULL)
		last = ft_strjoin("last:", *av++);
	else
		return (first);
	param = ft_strjoin(first, last);
	ft_strdel(&first);
	ft_strdel(&last);
	return (param);
}

static void		print_history_list(char **av, t_option option)
{
	char		*param;
	uint64_t	opt_history;

	opt_history = PRINT_HISTORY;
	if ((option & N_OPT) == FALSE)
		opt_history |= PRINT_ID;
	if ((option & R_OPT))
		opt_history |= REVERSE;
	param = get_first_last(av);
	history(NULL, param, opt_history);
	ft_strdel(&param);
}

int8_t			fc_blt(t_registry *shell, char **av)
{
	t_option	option;

	++av;
	(void)shell;
	option = set_options(&av, get_option_fc);
	if (option == ERROR_OPT)
		return (FAILURE);
	if (option & L_OPT)
		print_history_list(av, option);
	history(shell, NULL, RESET_HEAD);
	return (SUCCESS);
}
