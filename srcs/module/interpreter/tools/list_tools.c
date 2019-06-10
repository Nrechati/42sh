/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 17:56:27 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/10 16:53:56 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		del_action(void *data)
{
	t_action 	*action;

	action = data;
	ft_lstdel(&action->data, del_token);		//Leak probable;

}

void		del_command(void *data)
{
	t_command *command;

	command = data;
	ft_lstdel(&command->av, del_token);
	ft_lstdel(&command->actions, del_action);
}

void		del_group(void *data)
{
	t_group		*group;

	group = data;
	ft_lstdel(&group->command_list, del_command);
}
