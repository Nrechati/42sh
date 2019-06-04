/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 10:15:15 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/04 17:36:28 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
# define LOG_H

void	log_print(t_registry *reg, const char *importance,
						const char *message, ...);
void	init_debug_logger(t_registry *reg);
void	analyzer_print_debug(t_registry *shell, t_resolution *parse);
void	lexer_print_debug(t_registry *shell, t_list *token_list);

#endif
