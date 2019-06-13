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
			ft_dprintf(g_shell->cur_fd.err,
					"21sh: fc: -%c: invalid option\n", *s);
			ft_dprintf(g_shell->cur_fd.err, "%s\n%s\n%s\n",
					"fc: usage: fc [-r][-e editor] [first[last]]",
					"\t   fc -l[-nr] [first[last]]",
					"\t   fc -s[old=new][first]");
			return (ERROR_OPT);
		}
		s++;
	}
	return (option);
}

static int8_t	get_first_last(char **av, char **param)
{
	char	*last;
	char	*tmp;

	last = NULL;
	while (*av != NULL)
	{
		if (ft_isnumeric(*av) == FALSE)
			return (FAILURE);
		if (*param == NULL)
			*param = ft_strjoin("first:", *av);
		else
		{
			last = ft_strjoin("last:", *av);
			tmp = *param;
			*param = ft_strjoin(tmp, last);
			ft_strdel(&tmp);
			ft_strdel(&last);
			return (SUCCESS);
		}
		av++;
	}
	return (SUCCESS);
}

static void		print_history_list(char **av, t_option option)
{
	char		*param;
	uint64_t	opt_history;

	param = NULL;
	opt_history = PRINT_HISTORY;
	if ((option & N_OPT) == FALSE)
		opt_history |= PRINT_ID;
	if ((option & R_OPT))
		opt_history |= REVERSE;
	if (get_first_last(av, &param) == FAILURE)
		ft_dprintf(g_shell->cur_fd.err,
				"42sh: fc: history specification out of range");
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
