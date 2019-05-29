/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <skuppers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:01:44 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/07 15:03:04 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "parser.h"
#include "lexer.h"

int		check_token(t_parser *parse)
{
	if (parse->token.type == E_SEMICOLON)
		return (0);
	if (parse->token.type == E_PIPE)
		return (0);
	if (parse->token.type == E_END)
		return (0);
	if (parse->token.type == E_NEWLINE)
		return (0);
	return (1);
}

void	error_parser(t_parser *parse)
{
	parse->state = P_ERROR;
	parse->valid = -1;
	ft_strdel(&parse->token.data);
	while (check_token(parse))
	{
		get_token(parse);
		ft_strdel(&parse->token.data);
	}
	parse->token.type = E_DEFAULT;
	ft_lstdel(&parse->process.fd, close_fd);
}

void	separator_parser(t_parser *parse)
{
	parse->state = P_SEPARATOR;
}

void	stop_parser(t_parser *parse)
{
	t_list		*node;

	parse->state = P_STOP;
	node = ft_lstnew(&parse->process, sizeof(t_process));
	ft_lstaddback(&parse->job.process_list, node);
	node = ft_lstnew(&parse->job, sizeof(t_job));
	ft_lstaddback(&parse->job_list, node);
	parse->token.type = E_DEFAULT;
	parse->valid = 1;
}

void	end_parser(t_parser *parse)
{
	t_list		*node;

	parse->state = P_END;
	node = ft_lstnew(&parse->process, sizeof(t_process));
	ft_lstaddback(&parse->job.process_list, node);
	node = ft_lstnew(&parse->job, sizeof(t_job));
	ft_lstaddback(&parse->job_list, node);
	get_token(parse);
	parse->valid = 1;
}
