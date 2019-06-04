/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/04 17:55:01 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
/*
static void			reset_prompt(__unused t_registry *shell,__unused char **av)
{
<<<<<<< HEAD:srcs/module/builtin/unset/unset.c
	if (ft_strequ(*av, "*") == TRUE)
		fill_interface_related_internals(shell);
	else if (ft_strequ(*av, "PS1") == TRUE)
		get_prompt_ps1(shell);
	else if (ft_strequ(*av, "PS2") == TRUE)
		add_var(&shell->intern, INT_PS2, INT_PS2_VALUE, SET_VAR);
	else if (ft_strequ(*av, "PS3") == TRUE)
		add_var(&shell->intern, INT_PS3, INT_PS3_VALUE, SET_VAR);
	else if (ft_strequ(*av, "PS4") == TRUE)
		add_var(&shell->intern, INT_PS4, INT_PS4_VALUE, SET_VAR);
=======
//	if (ft_strequ(*av, "*") == TRUE)
//		fill_interface_related_internals(shell);
//	else if (ft_strequ(*av, "PS1") == TRUE)
//		get_prompt_ps1(shell);
//	else if (ft_strequ(*av, "PS2") == TRUE)
//		add_internal(shell, INT_PS2, INT_PS2_VALUE);
//	else if (ft_strequ(*av, "PS3") == TRUE)
//		add_internal(shell, INT_PS3, INT_PS3_VALUE);
//	else if (ft_strequ(*av, "PS4") == TRUE)
//		add_internal(shell, INT_PS4, INT_PS4_VALUE);
>>>>>>> origin/sle:srcs/builtin/unset_blt/unset_blt.c
}
*/
int8_t				unset_blt(t_registry *shell, char **av)
{
	++av;
	if (*av == NULL)
	{
		ft_dprintf(shell->cur_fd.err, UNSET_USAGE);
		return (FAILURE);
	}
	if (shell->intern != NULL)
		free_node(&shell->intern, *av);
//read-only
	return (SUCCESS);
}
