/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 07:55:03 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/28 12:31:44 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

uint8_t		test_not_cb(__unused void *data, __unused void *more)
{
	return (TRUE);
}

uint8_t		test_simple_op_cb(void *data, __unused void *more)
{
	if (data == NULL)
		return (FALSE);
	return (TRUE);
}

static void		init_callbacks(uint8_t (*callbacks[TEST_CB])(void *data, void *more))
{
	callbacks[0] = &test_b_cb;
	callbacks[1] = &test_c_cb;
	callbacks[2] = &test_d_cb;
	callbacks[3] = &test_e_cb;
	callbacks[4] = &test_f_cb;
	callbacks[5] = &test_g_cb;
	callbacks[6] = &test_caps_l_cb;
	callbacks[7] = &test_p_cb;
	callbacks[8] = &test_r_cb;
	callbacks[9] = &test_caps_s_cb;
	callbacks[10] = &test_s_cb;
	callbacks[11] = &test_u_cb;
	callbacks[12] = &test_w_cb;
	callbacks[13] = &test_x_cb;
	callbacks[14] = &test_z_cb;
	callbacks[15] = &test_equal_cb;
	callbacks[16] = &test_diff_cb;
	callbacks[17] = &test_eq_cb;
	callbacks[18] = &test_ne_cb;
	callbacks[19] = &test_gt_cb;
	callbacks[20] = &test_ge_cb;
	callbacks[21] = &test_lt_cb;
	callbacks[22] = &test_le_cb;
	callbacks[23] = &test_not_cb;
	callbacks[24] = &test_simple_op_cb;
}

int8_t		test_blt(__unused t_registry *shell, __unused char **av)
{
	static uint8_t (*callbacks[TEST_CB])(void *data, void *more);

	if (callbacks[0] == NULL)
		init_callbacks(callbacks);
	return (SUCCESS);
}
