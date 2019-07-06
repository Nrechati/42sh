/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:03:06 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/07 01:38:03 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int8_t	assign_to_var(t_list **env_lst, char *assign)
{
	t_list		*node;
	t_variable	variable;
	size_t		pos;

	ft_bzero(&variable, sizeof(t_variable));
	pos = ft_strcspn(assign, "=");
	variable.name = ft_strsub(assign, 0, pos);
	variable.data = ft_strdup(assign + pos + 1);
	variable.flag = SET_VAR | EXPORT_VAR;
	if (variable.name == NULL || variable.data == NULL)
		return (FAILURE);
	if ((node = ft_lstnew(&variable, sizeof(t_variable))) == NULL)
	{
		ft_strdel(&variable.data);
		ft_strdel(&variable.name);
		return (FAILURE);
	}
	ft_lstaddback(env_lst, node);
	return (TRUE);
}

static void		remove_args(char **av)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = av[0];
	while (av[i] != NULL)
	{
		av[i] = av[i + 1];
		i++;
	}
	ft_strdel(&tmp);
}

void			print_var(void *data)
{
	t_variable	*current;

	current = data;
	ft_printf("%s=%s\n", current->name, current->data);
	return ;
}

static uint8_t	print_env(t_registry *shell, t_process *process)
{
	t_list		*tmp_env;

	if (write(1, NULL, 0) == FAILURE)
	{
		ft_putendl_fd("21sh: env: write error: Bad file descriptor", 2);
		return (FALSE);
	}
	tmp_env = ft_lstfilter(shell->intern, NULL, is_export, copy_var);
	if (ft_lstiter_ctx(process->env, tmp_env, variable_update) == FAILURE)
		return (FALSE);
	ft_lstiter(tmp_env, print_var);
	ft_lstdel(&tmp_env, free_node);
	return (TRUE);
}

uint8_t			env_blt(t_registry *shell, char **av, t_process *process)
{
	uint8_t		ret;

	ret = SUCCESS;
	(void)av;
	(void)shell;
	remove_args(process->av);
	while (ft_strchr(process->av[0], '='))
	{
		if (assign_to_var(&process->env, process->av[0]) == FAILURE)
			return (2);
		remove_args(process->av);
	}
	if (process->av[0] == NULL)
	{
		if (print_env(shell, process) == FALSE)
			return (2);
	}
	else
	{
		process->type = 0;
		process->completed = 0;
		run_process(process, 0);
	}
	return (ret);
}
