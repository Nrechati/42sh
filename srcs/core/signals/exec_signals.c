/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:41:13 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/18 16:28:01 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	sigint_exec(int signo)
{
	interpreter(NULL, NULL, TO_KILL);
	//set state |= SIGINT;
	(void)signo;
}

void	sigill_exec(int signo)
{
	(void)signo;
}

void	sigtrap_exec(int signo)
{
	(void)signo;
}

void	sigabrt_exec(int signo)
{
	(void)signo;
}

void	sigfpe_exec(int signo)
{
	(void)signo;
}

void	sigbus_exec(int signo)
{
	(void)signo;
}

void	sigsegv_exec(int signo)
{
	(void)signo;
}

void	sigsys_exec(int signo)
{
	(void)signo;
}

void	sigquit_exec(int signo)
{
	(void)signo;
}

void	sigterm_exec(int signo)
{
	(void)signo;
}

void	sigcont_exec(int signo)
{
	(void)signo;
}

void	sigtstp_exec(int signo)
{
	(void)signo;
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
