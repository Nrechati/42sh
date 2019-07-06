/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_profile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 18:20:57 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/06 12:21:54 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		load_signal_profile(uint8_t profile_flag)
{
	if (profile_flag == DFLT_PROFILE)
		load_profile_dflt();
	else if (profile_flag == SLE_PROFILE)
		load_profile_sle();
	else if (profile_flag == EXEC_PROFILE)
		load_profile_exec();
}
