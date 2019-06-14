#include "sh21.h"

static void			get_target_and_result(char ***av, char **target, char **result)
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

static int8_t	replace_cmd(char **cmd, char *target, char *result)
{
	char	*ptr_target;
	char	*out;
	char	*tmp;

	if (target == NULL || result == NULL)
		return (FAILURE);
	ptr_target = ft_strstr(*cmd, target);
	if (ptr_target == NULL)
		return (FAILURE);
	tmp = ft_strdup(*cmd);
	out = ft_strsub(tmp, 0, ptr_target - *cmd);
	ft_strdel(&tmp);
	tmp = ft_strjoin(out, result);
	ft_strdel(&out);
	out = ft_strjoin(tmp, ptr_target + ft_strlen(target));
	ft_strdel(&tmp);
	ft_strdel(cmd);
	*cmd = out;
	return (SUCCESS);
}

static int8_t			get_cmd(t_registry *shell, char **av, t_option option,
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
	if (*av)
	{
		if (ft_isnumeric(*av) == FALSE)
		{
			ft_dprintf(g_shell->cur_fd.err,
					"42sh: fc: history specification out of range\n");
			return (FAILURE);
		}
		param = ft_strdup(*av);
	}
	*cmd = ft_strdup(history(shell, param, GET_ENTRY | BY_ID));
	while (replace_cmd(cmd, target, result) == SUCCESS)
		;
	return (SUCCESS);
}

int8_t			fc_redo(t_registry *shell, char **av, t_option option)
{
	char		*cmd;
	t_vector	*vct_cmd;

	cmd = NULL;
	if (get_cmd(shell, av, option, &cmd) == FAILURE)
		return (FAILURE);
	ft_putendl(cmd);
	vct_cmd = vct_dups(cmd);
	execution_pipeline(shell, vct_cmd);
	vct_del(&vct_cmd);
	ft_strdel(&cmd);
	return (SUCCESS);
}
