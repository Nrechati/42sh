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

int8_t			fc_blt(t_registry *shell, char **av)
{
	t_option	option;
	int			ret;

	++av;
	ret = SUCCESS;
	option = set_options(&av, get_option_fc);
	if (option == ERROR_OPT)
		return (FAILURE);
	if (option & L_OPT)
		print_history_list(av, option);
	else if (option & S_OPT)
		ret = fc_redo(shell, av, option);
	history(shell, NULL, RESET_HEAD);
	return (ret);
}
