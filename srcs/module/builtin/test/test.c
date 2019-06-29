/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 07:55:03 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/29 14:51:54 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int				ft_tabsize(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}


uint8_t			test_not(uint8_t status)
{
	if (status == TRUE)
		return (FALSE);
	return (TRUE);
}

int8_t			test_single_arg(char *arg)
{
	if (*arg == 0)
		return (FALSE);
	return (TRUE);
}

int8_t			two_arg_input(t_hash *callbacks, char **av)
{
	char		*type;
	char		*arg;
	t_test_cb	test;

	type = av[0];
	arg = av[1];
	if ((test = ft_hmap_getdata(callbacks, type)) == NULL)
	{
		ft_dprintf(2, "42sh: test: %s: unary operator expected\n", type);
		return (ERROR);
	}
	return (test(arg, NULL));
}

int8_t			three_arg_input(t_hash *callbacks, char **av)
{
	char		*type;
	char		*first;
	char		*second;
	t_test_cb	test;

	type = av[1];
	first = av[0];
	second = av[2];
	if ((test = ft_hmap_getdata(callbacks, type)) == NULL)
	{
		ft_dprintf(2, "42sh: test: %s: binary operator expected\n", type);
		return (ERROR);
	}
	return (test(first, second));
}

void			load_test_hashmap(t_hash *callbacks)
{
	ft_hmap_insert(callbacks, "-b", test_b_cb);
	ft_hmap_insert(callbacks, "-c", test_c_cb);
	ft_hmap_insert(callbacks, "-d", test_d_cb);
	ft_hmap_insert(callbacks, "-e", test_e_cb);
	ft_hmap_insert(callbacks, "-f", test_f_cb);
	ft_hmap_insert(callbacks, "-g", test_g_cb);
	ft_hmap_insert(callbacks, "-L", test_caps_l_cb);
	ft_hmap_insert(callbacks, "-p", test_p_cb);
	ft_hmap_insert(callbacks, "-r", test_r_cb);
	ft_hmap_insert(callbacks, "-S", test_caps_s_cb);
	ft_hmap_insert(callbacks, "-s", test_s_cb);
	ft_hmap_insert(callbacks, "-u", test_u_cb);
	ft_hmap_insert(callbacks, "-W", test_w_cb);
	ft_hmap_insert(callbacks, "-x", test_x_cb);
	ft_hmap_insert(callbacks, "-z", test_z_cb);
	ft_hmap_insert(callbacks, "=", test_equal_cb);
	ft_hmap_insert(callbacks, "!=", test_diff_cb);
	ft_hmap_insert(callbacks, "-eq", test_eq_cb);
	ft_hmap_insert(callbacks, "-ne", test_ne_cb);
	ft_hmap_insert(callbacks, "-gt", test_gt_cb);
	ft_hmap_insert(callbacks, "-ge", test_ge_cb);
	ft_hmap_insert(callbacks, "-lt", test_lt_cb);
	ft_hmap_insert(callbacks, "-le", test_le_cb);
}

uint8_t			handle_input(t_hash *callbacks, int ac, char **av, int i)
{
	uint8_t		status;

	if (ac == 1)
		status = test_single_arg(av[1]);
	else if (ac == 2)
		status = two_arg_input(callbacks, av + i);
	else if (ac == 3)
		status = three_arg_input(callbacks, av + i);
	else
	{
		ft_dprintf(2, "42sh: test: Too many arguments");
		status = ERROR;
	}
	return (status);
}

int8_t			test_blt(__unused t_registry *shell, char **av)
{
	int				i;
	int 			ac;
	uint8_t			status;
	t_hash			callbacks;

	status = 0;
	ft_bzero(&callbacks, sizeof(t_hash));
	callbacks = ft_hmap_init(TEST_HASH_SIZE);
	load_test_hashmap(&callbacks);
	i = 1 + (ft_strequ(av[1], "!"));
	ac = ft_tabsize(av) - i;
	if (ac == 0)
		return (EXIT_FALSE);
	status = handle_input(&callbacks, ac, av, i);
	ft_hmap_free_content(&callbacks, ft_free);
	ft_free(&callbacks);
	ft_printf("status bf = %d | i = %d\n", status, i);
	if (i > 1 && status != ERROR)
		status = test_not(status);
	ft_printf("status = %d | i = %d\n", status, i);
	if (status == FALSE)
		return (EXIT_FALSE);
	else if (status == TRUE)
		return (EXIT_TRUE);
	return (ERROR);
}
