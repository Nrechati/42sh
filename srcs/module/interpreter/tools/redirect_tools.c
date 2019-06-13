/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:56:23 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/12 18:44:01 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char		*get_filename(t_list *node)
{
	t_token		*token;
	char		*filename;

	token = node->data;
	filename = NULL;
	if (token->data[0] == '/' || ft_strnequ("./", token->data, 2))
		filename = ft_strdup(token->data);
	else
		ft_asprintf(&filename, "./%s", token->data);
	return (filename);

}

int 		get_io(t_list *node)
{
	t_token		*token;

	token = node->data;
	return (ft_atoi(token->data));
}
