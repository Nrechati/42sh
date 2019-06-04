/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 22:18:22 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/04 17:57:48 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void	print_filedesc(void *data)
{
	t_filedesc	*fd;

	fd = data;
	if (fd->action & FD_CLOSE)
		ft_printf("Closing FD : %d\n", fd->second);
	else if (fd->action & FD_WRITE)
		ft_printf("FD : %d >>> FD : %d\n", fd->first, fd->second);
	else if (fd->action & FD_READ)
		ft_printf("FD : %d <<< FD : %d\n", fd->first, fd->second);
}

static void	print_process(void *data)
{
	t_process	*process;

	process = data;
	ft_putchar('\n');
	ft_showtab(process->av);
	ft_lstiter(process->fd, print_filedesc);
}

void		analyzer_print_debug(t_registry *shell, t_resolution *resolve)
{
	if ((shell->option.option & DEBUG_OPT) != FALSE)
	{
		ft_putstr("\n\033[33m-------------- PARSER --------------");
		if (resolve->valid == 1)
			ft_lstiter(((t_job *)(resolve->job_list->data))->process_list,
					print_process);
		else
			ft_putstr(NULL);
		ft_putendl("------------------------------------\033[0m\n");
	}
}

void		lexer_print_debug(t_registry *shell, t_list *token_list)
{
	if (token_list != NULL && (shell->option.option & DEBUG_OPT) != FALSE)
	{
		ft_putendl("\n\033[34m-------------- LEXER ---------------");
		ft_lstiter(token_list, print_token);
		ft_putendl("------------------------------------\033[0m");
	}
}
