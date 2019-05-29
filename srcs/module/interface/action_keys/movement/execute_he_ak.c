/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_he_ak.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:32:21 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/29 18:41:26 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



int8_t	tc_ak_home(t_registry *shell)
{
	if (validate_interface_content(&shell->interface) == FAILURE)
		return (FAILURE);
	while (shell->interface.cursor.index > 0)
		tc_ak_arrow_left(shell);
	return (SUCCESS);
}

int8_t	tc_ak_end(t_registry *shell)
{
	if (validate_interface_content(&shell->interface) == FAILURE)
		return (FAILURE);
	while (shell->interface.cursor.index < ft_vctlen(shell->interface.line))
		tc_ak_arrow_right(shell);
	return (SUCCESS);
}
