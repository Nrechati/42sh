/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 07:55:03 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/28 10:58:27 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

uint8_t		test_simple_op_cb(void *data, __unused void *more)
{
	if (data == NULL)
		return (FALSE);
	return (TRUE);
}

int8_t		test_blt(__unused t_registry *shell, __unused char **av)
{
	return (SUCCESS);
}
