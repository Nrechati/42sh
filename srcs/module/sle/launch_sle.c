/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_sle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:33:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/05 10:23:23 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>

uint8_t		sle_getinput(t_registry *shell, t_vector **in)
{
	if (in == NULL)
		return (FAILURE);
	*in = prompt(shell, INT_PS1);
	if (*in == NULL)
		return (FAILURE); // read fail / Malloc fail
	if (ft_strequ(vct_get_string(*in), "\0"))
		return (LINE_FAIL);
	if (is_eof(vct_get_string(*in)))
		return (FAILURE);
	return (SUCCESS);
}
