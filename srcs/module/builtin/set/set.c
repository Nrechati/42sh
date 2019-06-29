/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:23:09 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/15 11:30:46 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

uint8_t				set_blt(t_registry *shell, __unused char **av)
{
	print_lst(shell->intern, STDOUT_FILENO, "", SET_VAR);
	return (SUCCESS);
}
