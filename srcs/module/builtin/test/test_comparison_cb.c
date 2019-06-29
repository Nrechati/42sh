/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_comparison_cb.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 08:48:25 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/29 13:20:25 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

uint8_t		test_gt_cb(void *data, void *more)
{
	char	*n1;
	char	*n2;

	n1 = data;
	n2 = more;
	if (!n1 || !n2)
		return (ERROR);
	if (ft_atoi(n1) > ft_atoi(n2))
		return (TRUE);
	return (FALSE);
}

uint8_t		test_ge_cb(void *data, void *more)
{
	char	*n1;
	char	*n2;

	n1 = data;
	n2 = more;
	if (!n1 || !n2)
		return (ERROR);
	if (ft_atoi(n1) >= ft_atoi(n2))
		return (TRUE);
	return (FALSE);
}

uint8_t		test_lt_cb(void *data, void *more)
{
	char	*n1;
	char	*n2;

	n1 = data;
	n2 = more;
	if (!n1 || !n2)
		return (ERROR);
	if (ft_atoi(n1) < ft_atoi(n2))
		return (TRUE);
	return (FALSE);
}

uint8_t		test_le_cb(void *data, void *more)
{
	char	*n1;
	char	*n2;

	n1 = data;
	n2 = more;
	if (!n1 || !n2)
		return (ERROR);
	if (ft_atoi(n1) <= ft_atoi(n2))
		return (TRUE);
	return (FALSE);
}
