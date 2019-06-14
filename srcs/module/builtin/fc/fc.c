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
				"42sh: fc: history specification out of range\n");
	history(NULL, param, opt_history);
	ft_strdel(&param);
}

void			get_target_and_result(char ***av, char **target, char **result)
{
	if (**av == NULL)
		return ;
	*result = ft_strchr(**av, '=');
	if (*result == NULL)
		return ;
	**result = '\0';
	(*result)++;
	(*target) = **av; 
	(*av)++;
}

char			*replace_cmd(char *cmd, char *target, char *result)
{
	char	*ptr_target;
	char	*out;
	char	*tmp;

	if (target == NULL || result == NULL)
		return (cmd);
	ptr_target = ft_strstr(cmd, target);
	if (ptr_target == NULL)
		return (cmd);
	tmp = ft_strdup(cmd);
	out = ft_strsub(tmp, 0, ptr_target - cmd);
	ft_strdel(&tmp);
	tmp = ft_strjoin(out, result);
	ft_strdel(&out);
	out = ft_strjoin(tmp, ptr_target + ft_strlen(target));
	ft_strdel(&tmp);
	ft_strdel(&cmd);
	return (out);
}

int8_t			get_cmd(t_registry *shell, char **av, t_option option,
						char **cmd)
{
	char	*target;
	char	*result;
	char	*param;

	(void)option;
	target = NULL;
	result = NULL;
	param = NULL;
	get_target_and_result(&av, &target, &result);
	if (get_first_last(av, &param) == FAILURE)
	{
		ft_dprintf(g_shell->cur_fd.err,
				"42sh: fc: history specification out of range\n");
		return (FAILURE);
	}
	*cmd = ft_strdup(history(shell, param, GET_ENTRY | BY_ID));
	ft_putendl(*cmd);
	*cmd = replace_cmd(*cmd, target, result);
	return (SUCCESS);
}

int8_t			fc_blt(t_registry *shell, char **av)
{
	t_option	option;
	char		*cmd;

	++av;
	(void)shell;
	cmd = NULL;
	option = set_options(&av, get_option_fc);
	if (option == ERROR_OPT)
		return (FAILURE);
	if (option & L_OPT)
		print_history_list(av, option);
	else if (option & S_OPT)
	{
		if (get_cmd(shell, av, option, &cmd) == FAILURE)
			return (FAILURE);
		ft_putendl(cmd);
	}
	history(shell, NULL, RESET_HEAD);
	return (SUCCESS);
}
