/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:13:07 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/29 18:41:26 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



void	move_buffer(char *dest, t_vector *source)
{
	ft_strcpy(dest, source->buffer);
	ft_bzero(source->buffer, source->size);
}

void	realloc_vector(t_vector *dest, t_vector *source)
{
	while (dest->size < source->size)
		ft_vctrescale(dest);
	ft_bzero(dest->buffer, dest->size);
}

void	reset_vector(t_vector *line)
{
	ft_strdel(&(line->buffer));
	line->buffer = ft_strnew(16);
	line->size = 16;
}
