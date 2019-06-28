/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_equality_cb.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 08:49:09 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/28 09:05:15 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

uint8_t		test_equal_cb(void *data, void *more)
{
	char	*s1;
	char	*s2;

	s1 = data;
	s2 = more;
	if (!s1 || !s2)
		return (ERROR);
	return (ft_strequ(s1, s2));
}

uint8_t		test_diff_cb(void *data, void *more)
{
	char	*s1;
	char	*s2;

	s1 = data;
	s2 = more;
	if (!s1 || !s2)
		return (ERROR);
	if (ft_strequ(s1, s2) == TRUE)
		return (FALSE);
	return (TRUE);
}

uint8_t		test_eq_cb(void *data, void *more)
{
	char	*n1;
	char	*n2;

	n1 = data;
	n2 = more;
	if (!n1 || !n2)
		return (ERROR);
	if (ft_atoi(n1) == ft_atoi(n2))
		return (TRUE);
	return (FALSE);
}

uint8_t		test_ne_cb(void *data, void *more)
{
	char	*n1;
	char	*n2;

	n1 = data;
	n2 = more;
	if (!n1 || !n2)
		return (ERROR);
	if (ft_atoi(n1) != ft_atoi(n2))
		return (TRUE);
	return (FALSE);
}
