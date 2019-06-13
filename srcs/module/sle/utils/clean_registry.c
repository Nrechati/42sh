/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_registry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:14:21 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/06 14:35:20 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "sh21.h"

void		unload_prompt(__unused t_sle *sle)
{
	vct_del(&sle->prompt.text);
}

void		unload_window(t_sle *sle)
{
	vct_del(&sle->window.displayed_line);
}

void		unload_clipboard(t_sle *sle)
{
	vct_del(&sle->clip);
}

void		unload_line(t_sle *sle)
{
	vct_del(&sle->line);
	vct_del(&sle->sub_line);
}

void		unload_interns(t_sle *sle)
{
	vct_del(&sle->interns.ps1);
	vct_del(&sle->interns.ps2);
	vct_del(&sle->interns.ps3);
	vct_del(&sle->interns.pwd);
	vct_del(&sle->interns.username);
	vct_del(&sle->interns.home);
}

void		unload_termcaps(t_sle *sle)
{
	ft_strdel(&sle->termcaps.standout_on);
	ft_strdel(&sle->termcaps.standout_off);
	ft_strdel(&sle->termcaps.clear);
	ft_strdel(&sle->termcaps.down);
	ft_strdel(&sle->termcaps.up);
	ft_strdel(&sle->termcaps.right);
	ft_strdel(&sle->termcaps.left);
}

static void	sle_destroy(t_sle *sle)
{
	unload_line(sle);
	unload_clipboard(sle);
	unload_prompt(sle);
	unload_window(sle);
	unload_termcaps(sle);
	unload_interns(sle);
}

void	sle_teardown(t_sle *sle)
{
	unset_term_mode(sle);
	sle_destroy(sle);
}
