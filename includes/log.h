/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 10:15:15 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/06 14:21:10 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
# define LOG_H
# include "struct.h"

void	analyzer_print_debug(t_registry *shell, t_list *command_group);
void	print_command(void *data);

#endif
