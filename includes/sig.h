/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:02:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/29 18:41:26 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

void	signal_parser(t_parser *parser);
void	stop_parsing(const int signo);
void	kill_process(const int signo);
void	loop_signals(void (*func)(int));
void	define_ign_signals(void);
void	define_parser_signals(void);
void	define_execution_signals(void);
void	define_interface_signals(void);
void	define_default_signals(void);

#endif
