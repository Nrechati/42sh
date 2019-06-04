/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 10:09:57 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/04 10:52:56 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "interface_functions.h"

uint64_t    assign_keycodes(t_interface *itf)
{
	itf->visual_mode = FALSE;
	itf->ak_masks[AK_ARROW_RIGHT] = AK_ARROW_RIGHT_MASK;
	itf->ak_masks[AK_ARROW_LEFT] = AK_ARROW_LEFT_MASK;
	itf->ak_masks[AK_ARROW_UP] = AK_ARROW_UP_MASK;
	itf->ak_masks[AK_ARROW_DOWN] = AK_ARROW_DOWN_MASK;
	itf->ak_masks[AK_HOME] = AK_HOME_MASK;
	itf->ak_masks[AK_END] = AK_END_MASK;
	itf->ak_masks[AK_BACKSPACE] = AK_BACKSPACE_MASK;
	itf->ak_masks[AK_DELETE] = AK_DELETE_MASK;
	itf->ak_masks[AK_CTRL_A] = AK_CTRL_A_MASK;
	itf->ak_masks[AK_CTRL_E] = AK_CTRL_E_MASK;
	itf->ak_masks[AK_CTRL_D] = AK_CTRL_D_MASK;
	itf->ak_masks[AK_CTRL_L] = AK_CTRL_L_MASK;
	itf->ak_masks[AK_ESCAPE] = AK_ESCAPE_MASK;
	itf->ak_masks[AK_CTRL_F] = AK_CTRL_F_MASK;
	itf->ak_masks[AK_CTRL_X] = AK_CTRL_X_MASK;
	itf->ak_masks[AK_CTRL_B] = AK_CTRL_B_MASK;
	itf->ak_masks[AK_CTRL_P] = AK_CTRL_P_MASK;
	itf->ak_masks[AK_CTRL_LEFT] = AK_CTRL_LEFT_MASK;
	itf->ak_masks[AK_CTRL_RIGHT] = AK_CTRL_RIGHT_MASK;
	itf->ak_masks[AK_CTRL_DOWN] = AK_CTRL_DOWN_MASK;
	itf->ak_masks[AK_CTRL_UP] = AK_CTRL_UP_MASK;

	itf->ak_masks[AK_TABULATION] = AK_TAB_MASK;

    return (SUCCESS);
}

uint64_t    link_keys_functions(__unused int8_t (*tc_call[AK_AMOUNT])(t_registry *shell))
{
    tc_call[AK_ARROW_LEFT] = &ak_arrow_left;
	tc_call[AK_ARROW_RIGHT] = &ak_arrow_right;
	tc_call[AK_HOME] = &ak_home;
	tc_call[AK_END] = &ak_end;
	tc_call[AK_BACKSPACE] = &ak_backspace;
	tc_call[AK_DELETE] = &ak_delete;
	tc_call[AK_CTRL_A] = &ak_home;
	tc_call[AK_CTRL_E] = &ak_end;
	tc_call[AK_CTRL_D] = &ak_ctrl_d;
	tc_call[AK_CTRL_L] = &ak_ctrl_l;
	tc_call[AK_CTRL_UP] = &ak_ctrl_up;
	tc_call[AK_CTRL_DOWN] = &ak_ctrl_down;
	tc_call[AK_CTRL_LEFT] = &ak_ctrl_left;
	tc_call[AK_CTRL_RIGHT] = &ak_ctrl_right;
	tc_call[AK_CTRL_F] = &ak_enter_visual_mode;
	tc_call[AK_ESCAPE] = &ak_exit_visual_mode;
	tc_call[AK_CTRL_X] = &ak_cut_selection;
	tc_call[AK_CTRL_B] = &ak_copy_selection;
	tc_call[AK_CTRL_P] = &ak_paste_clipboard;
	tc_call[AK_ARROW_UP] = &ak_arrow_up;
	tc_call[AK_ARROW_DOWN] = &ak_arrow_down;
/*
	tc_call[AK_TABULATION] = &tc_ak_hightab;
*/
    return (SUCCESS);
}

uint64_t    set_interface_internals(t_registry *shell)
{
	if (add_internal(shell, INT_PS1, INT_PS1_VALUE) == FAILURE)
		return (INTERNAL_FAIL);
	if (add_internal(shell, INT_PS2, INT_PS2_VALUE) == FAILURE)
		return (INTERNAL_FAIL);
	if (add_internal(shell, INT_PS3, INT_PS3_VALUE) == FAILURE)
		return (INTERNAL_FAIL);
	if (add_internal(shell, INT_PS4, INT_PS4_VALUE) == FAILURE)
		return (INTERNAL_FAIL);
    return (SUCCESS);
}

uint64_t    init_line(t_interface *interface)
{
	if ((interface->line = vct_new(0)) == NULL)
		return (CRITICAL_ERROR | LINE_FAIL);
	if ((interface->sub_line = vct_new(0)) == NULL)
		return (CRITICAL_ERROR | LINE_FAIL);
 	if ((interface->clip = vct_new(0)) == NULL)
		return (CRITICAL_ERROR | LINE_FAIL);
   return (SUCCESS);
}
