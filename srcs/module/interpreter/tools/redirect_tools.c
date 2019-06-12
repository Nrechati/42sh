/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:56:23 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/12 18:03:33 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char		*get_filename(t_list *node)
{
	t_token		*token;
	char		*filename;

	token = node->data;
	filename = NULL;
	ft_asprintf(&filename, "./%s", token->data);
	return (token->data);

}

int 		get_io(t_list *node)
{
	t_token		*token;

	token = node->data;
	return (ft_atoi(token->data));
}
