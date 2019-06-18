/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sle_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:44:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/15 19:19:52 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	sigterm_sle(int signo)
{
	(void)signo;
}

void	sigcont_sle(int signo)
{
	(void)signo;
}

void	sigtstp_sle(int signo)
{
	(void)signo;
}

void	sigint_sle(int signo)
{
	(void)signo;
}

void	sigwinch_sle(int signo)
{
	(void)signo;
	sle(NULL, NULL, SLE_SIZE_UPDATE);
}
