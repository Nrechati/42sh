/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 02:50:12 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/04 17:57:04 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void		init_lexing(t_lexinfo *lexinfo)
{
	lexinfo->lexing[L_START] = start_lexer;
	lexinfo->lexing[L_STRING] = string_machine;
	lexinfo->lexing[L_IO_NUMBER] = number_machine;
	lexinfo->lexing[L_SIGN] = sign_machine;
	lexinfo->lexing[L_DSIGN] = double_sign_machine;
	lexinfo->lexing[L_GREATER] = greater_machine;
	lexinfo->lexing[L_LESSER] = lesser_machine;
	lexinfo->lexing[L_GREATAND] = greatand_machine;
	lexinfo->lexing[L_LESSAND] = lessand_machine;
	lexinfo->lexing[L_SQTE] = single_quote_machine;
	lexinfo->lexing[L_DQTE] = double_quote_machine;
	lexinfo->lexing[L_AND] = and_machine;
	lexinfo->lexing[L_OUT] = out_lexer;
	lexinfo->lexing[L_END] = end_machine;
}

t_lexinfo	*init_lexinfo(void)
{
	static	t_lexinfo	lexinfo;

	ft_bzero(&lexinfo, sizeof(lexinfo));
	lexinfo.special_signs[0] = E_DAND;
	lexinfo.special_signs[1] = E_OR;
	lexinfo.special_signs[2] = E_DSEMI;
	lexinfo.special_signs[3] = E_DLESS;
	lexinfo.special_signs[4] = E_DGREAT;
	lexinfo.special_signs[5] = E_LESSAND;
	lexinfo.special_signs[6] = E_GREATAND;
	lexinfo.special_signs[7] = E_LESSGREAT;
	lexinfo.special_signs[8] = E_DLESSDASH;
	lexinfo.special_signs[9] = E_CLOBBER;
	lexinfo.special_signs[10] = E_DEQ;
	lexinfo.special_signs[11] = E_NOTEQ;
	lexinfo.special_signs[12] = E_ANDGREAT;
	lexinfo.special_signs[13] = E_ANDDGREAT;
	lexinfo.duplicate[0] = E_STRING;
	lexinfo.duplicate[1] = E_IO_NUMBER;
	lexinfo.duplicate[2] = E_DB_QUOTE;
	lexinfo.duplicate[3] = E_ASSIGN;
	lexinfo.duplicate[4] = E_SPSTRING;
	init_lexing(&lexinfo);
	return (&lexinfo);
}
