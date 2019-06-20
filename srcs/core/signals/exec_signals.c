/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:41:13 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/20 19:43:04 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	sigstop_exec(int signo)
{
	interpreter(NULL, NULL, signo);
}

void	sigcont_exec(__unused int signo)
{
	//
}

// C-z
void	sigtstp_exec(__unused int signo)
{
	// put current foreground job to background
	interpreter(NULL, NULL, signo);
}



void	sigttin_exec(int signo)
{
	(void)signo;
}

void	sigttou_exec(int signo)
{
	(void)signo;
}

void	sigchld_exec(int signo)
{
	(void)signo;
}
