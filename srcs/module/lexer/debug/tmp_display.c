/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:13:18 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/29 18:41:26 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



t_registry	*g_shell;

void		print_token(void *data)
{
	t_token *token;

	token = data;
	ft_printf("type_id = [ %2d ] | type_name = [ %5s ] | data = [ %s ]\n",
				token->type, g_shell->grammar[token->type], token->data);
}
