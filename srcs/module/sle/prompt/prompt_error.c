/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/27 16:07:27 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

inline t_vector *read_error(t_registry *shell, t_sle *sle)
{
	if (ft_strequ(sle->prompt.state, INT_PS1) == FALSE)
	{
		g_shell->sigint = FALSE;
		sle->prompt.state = INT_PS1;
		return (NULL);
	}
	vct_del(&(sle->prompt.text));
	return (prompt(shell, sle));
}