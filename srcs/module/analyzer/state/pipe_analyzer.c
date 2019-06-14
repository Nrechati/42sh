/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_analyzer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:57:46 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/11 13:54:00 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>
#include <unistd.h>

void	pipe_analyzer(t_resolution *resolve)
{
	resolve->state = P_PIPE;
	get_token(resolve);
}
