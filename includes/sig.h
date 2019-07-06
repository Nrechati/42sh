/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:02:22 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/06 12:21:26 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include <sys/types.h>
# include <signal.h>
# include "struct.h"

void					load_signal_profile(uint8_t profileglag);
void					load_profile_exec(void);
void					load_profile_sle(void);
void					load_profile_dflt(void);

/*
**** HANDLER EXEC
*/
void	sigstop_exec(int signo);
void	init_exec_signals(void);

void	sigttou_exec(int signo);
void	sigttin_exec(int signo);
void	sigtstp_exec(int signo);

void	sigill_exec(int signo);
void	sigtrap_exec(int signo);
void	sigabrt_exec(int signo);
void	sigfpe_exec(int signo);
void	sigbus_exec(int signo);
void	sigsegv_exec(int signo);
void	sigsys_exec(int signo);
void	sigcont_exec(int signo);
void	sigtstp_exec(int signo);
void	sigttin_exec(int signo);
void	sigttou_exec(int signo);
void	sigchld_exec(int signo);

/*
**** HANDLER SLE
*/

void	sigterm_sle(int signo);
void	sigcont_sle(int signo);
void	sigtstp_sle(int signo);
void	sigint_sle(int signo);
void	sigwinch_sle(int signo);

#endif
