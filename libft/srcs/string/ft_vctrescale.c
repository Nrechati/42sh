/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vctrescale.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 10:39:36 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/29 18:41:26 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_vctrescale(t_vector *vector)
{
	char	*new;

	if (!(new = ft_strnew(vector->size + VECTOR_BUFFER_SIZE)))
		return (1);
	vector->size += VECTOR_BUFFER_SIZE;
	ft_strcpy(new, vector->buffer);
	ft_strdel(&(vector->buffer));
	vector->buffer = new;
	return (0);
}
