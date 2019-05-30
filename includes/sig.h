/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:02:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/29 18:55:15 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

void	signal_analyzer(t_resolution *resolve);
void	stop_analysis(const int signo);
void	kill_process(const int signo);
void	loop_signals(void (*func)(int));
void	define_ign_signals(void);
void	define_analyzer_signals(void);
void	define_execution_signals(void);
void	define_interface_signals(void);
void	define_default_signals(void);

#endif
