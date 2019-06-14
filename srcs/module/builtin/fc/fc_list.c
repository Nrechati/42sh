#include "sh21.h"

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

void			print_history_list(char **av, t_option option)
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
				"42sh: fc: history specification out of range\n");
	history(NULL, param, opt_history);
	ft_strdel(&param);
}