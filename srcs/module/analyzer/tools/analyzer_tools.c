/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 13:37:40 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/27 23:23:20 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

int		is_ionumber(t_resolution *resolve, char *str)
{
	int		len;

	resolve->state = resolve->state == P_REDIRECT_AND
			? P_DUP_MOVE : P_IO_DUP_MOVE;
	if (ft_strcheck(str, ft_isdigit) == 1)
		return (1);
	len = ft_strlen(str);
	str[len - 1] = character_swap(str[len - 1]);
	if (ft_strcheck(str, ft_isdigit) == 1)
	{
		str[len - 1] = character_swap('\0');
		if (str[len - 1] == '-')
		{
			resolve->special_case ^= TO_CLOSE;
			return (1);
		}
	}
	str[len - 1] = character_swap('\0');
	return (0);
}

uint8_t	check_access(char *data)
{
	struct stat	stat;

	if (access(data, F_OK) != SUCCESS)
		return (TRUE);
	lstat(data, &stat);
	if (stat.st_mode & S_IFDIR)
		ft_dprintf(2, "42sh: %s: Is a directory\n", data);
	else if (access(data, R_OK) != SUCCESS)
		ft_dprintf(2, "42sh: %s: Permission denied\n", data);
	else
		return (TRUE);
	return (FALSE);
}

void	check_filename(t_resolution *resolve)
{
	if (resolve->token.data == NULL
			|| check_access(resolve->token.data) == FALSE)
	{
		error_analyzer(resolve);
		ft_strdel(&resolve->token.data);
	}
}

void	delete_analyzer(t_resolution *resolve)
{
	ft_stckdestroy(&resolve->stack, del_token);
}

void	set_group_type(t_group *group, t_action *action)
{
	if (action->type == A_DAND)
		group->type |= GROUP_AND;
	else if (action->type == A_OR)
		group->type |= GROUP_OR;
	else if (action->type == A_END)
		group->type |= GROUP_RUN;
	else if (action->type == A_AND)
		group->type |= GROUP_BG;
}
