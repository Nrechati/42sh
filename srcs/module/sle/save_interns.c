/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_interns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 14:19:01 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/29 14:21:26 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void	del_interns(t_sle *sle)
{
	if (sle->interns.ps1 != NULL)
		vct_del(&sle->interns.ps1);
	if (sle->interns.ps2 != NULL)
		vct_del(&sle->interns.ps2);
	if (sle->interns.ps3 != NULL)
		vct_del(&sle->interns.ps3);
	if (sle->interns.pwd != NULL)
		vct_del(&sle->interns.pwd);
	if (sle->interns.username != NULL)
		vct_del(&sle->interns.username);
	if (sle->interns.home != NULL)
		vct_del(&sle->interns.home);
}

void		save_intern_vars(t_registry *shell, t_sle *sle)
{
	if (shell != NULL)
	{
		del_interns(sle);
		sle->interns.ps1 = vct_dups((get_var(shell->intern, INT_PS1) == NULL) ?
					"prompt> " : get_var(shell->intern, INT_PS1));
		sle->interns.ps2 = vct_dups((get_var(shell->intern, INT_PS2) == NULL) ?
					"$> " : get_var(shell->intern, INT_PS2));
		sle->interns.ps3 = vct_dups((get_var(shell->intern, INT_PS3) == NULL) ?
					">> " : get_var(shell->intern, INT_PS3));
		sle->interns.pwd = vct_dups((get_var(shell->intern, "PWD") == NULL) ?
					"pwd" : get_var(shell->intern, "PWD"));
		sle->interns.username = vct_dups((get_var(shell->intern, "USER")
					== NULL) ? "user" : get_var(shell->intern, "USER"));
		sle->interns.home = vct_dups((get_var(shell->intern, "HOME")
					== NULL) ? "~" : get_var(shell->intern, "HOME"));
	}
}
