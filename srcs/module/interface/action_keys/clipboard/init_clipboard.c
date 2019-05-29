/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clipboard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 00:17:19 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/29 18:41:26 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/*
**		Initialise the clipboard vector.
*/

t_vector	*allocate_clipboard(t_registry *shell)
{
	t_vector		*clipboard;

	if ((clipboard = ft_vctnew(CLIPBOARD_SZ)) == NULL)
	{
		log_print(shell, LOG_ERROR, "Clipboard allocation failed.\n");
		return (NULL);
	}
	return (clipboard);
}
