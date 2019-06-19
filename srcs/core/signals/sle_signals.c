/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sle_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:44:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/19 18:52:17 by skuppers         ###   ########.fr       */
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

void	sigint_sle(__unused int signo)
{
	sle(NULL, NULL, SLE_RD_PROMPT);
}

void	sigwinch_sle(__unused int signo)
{
	sle(NULL, NULL, SLE_SIZE_UPDATE);
}
