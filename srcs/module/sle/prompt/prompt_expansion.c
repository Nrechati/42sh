/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:45:20 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/07 20:53:17 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		p_insert_missing(t_sle *sle, t_vector *text, uint64_t index)
{
	if (sle->prompt.missing_char != NULL)
		vct_replace_string(text, index, index + 2,
						sle->prompt.missing_char);
}

void		p_insert_name(t_vector *text, uint64_t index)
{
	vct_replace_string(text, index, index + 2, "42sh");
}

void		p_insert_username(t_sle *sle, t_vector *text, uint64_t index)
{
	char	*username;

	username = vct_get_string(sle->interns.username);
	username = ft_strdup(username == NULL ? "user" : username);
	vct_replace_string(text, index, index + 2, username);
	ft_strdel(&username);
}

void		p_insert_success(t_vector *text, uint64_t index)
{
	char	*success;

	success = get_var(g_shell->intern, "?");
	vct_replace_string(text, index, index + 2, success);
}

void		p_insert_job(t_vector *text, uint64_t index)
{
	char	*success;

	success = get_var(g_shell->intern, "!");
	vct_replace_string(text, index, index + 2, success);
}
