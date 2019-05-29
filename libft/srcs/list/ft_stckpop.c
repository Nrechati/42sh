/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stckpop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:57:29 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:41:26 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"
#include "ft_malloc.h"

void	*ft_stckpop(t_stack *stack)
{
	t_list		*holder;
	void		*data;

	if (!stack->head)
		return (NULL);
	holder = stack->head;
	stack->head = stack->head->next;
	data = holder->data;
	ft_free(holder);
	stack->size--;
	return (data);
}
