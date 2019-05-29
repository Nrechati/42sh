/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:20:58 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:41:26 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	generate_summary(t_list **summary, t_result result)
{
	t_list		*node;

	node = ft_lstnew(&result, sizeof(t_result));
	ft_lstaddback(summary, node);
}

void	set_test(t_list **lst, t_result results)
{
	t_list		*node;

	node = ft_lstnew(&results, sizeof(t_result));
	ft_lstaddback(lst, node);
}
