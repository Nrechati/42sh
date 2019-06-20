/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machine_interface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:28:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/20 11:23:26 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	space_lexer(t_lexer *machine)
{
	if (machine->assign_detect == ASSIGN_NEXT)
	{
		if (get_buffer(machine, CUR_CHAR) == '\0')
		{
			vct_add(machine->buffer, ' ');
			machine->last_lexer = E_STRING;
			machine->state = L_OUT;
			machine->assign_detect = ASSIGN_ON;
		}
		else if (ft_strchr("\t ", get_input(machine, CUR_CHAR)) != NULL)
			machine->index++;
	}
	else
	{
		machine->io_detect = 0;
		while (ft_strchr("\t ", get_input(machine, CUR_CHAR)) != NULL)
			machine->index++;
		machine->state = L_START;
	}
}

static char *get_search(char *str)
{
	t_vector	*search;
	char		*tmp;

	search = vct_new(0);
	while (ft_strchr(ALLCHAR, *str) == NULL && *str != ' ' && *str != '\t')
		vct_add(search, *str++);
	tmp = ft_strdup(search->buffer);
	vct_del(&search);
	return (tmp);
}

void	call_history(t_lexer *machine, size_t initial_scale, uint64_t option)
{
	char	*search;
	char	*replace;
	size_t	len;

	search = NULL;
	if (machine->input->buffer[machine->index + initial_scale - 1] == '!')
		replace = history(NULL, NULL, option);
	else
	{
		search = get_search(machine->input->buffer
				+ machine->index + initial_scale);
		if (ft_isnumeric(search) == TRUE)
			replace = history(NULL, search, option | BY_ID);
		else
			replace = history(NULL, search, option | BY_NAME);
	}
	if (replace != NULL)
	{
		len = ft_strlen(search) + initial_scale;
		vct_replace_string(machine->input, machine->index,
				machine->index + len, replace);
	}
	else
	{
		ft_dprintf(2, "42sh: %s: event not found", search);
		/// EXIT LEXER
	}
	history(NULL, NULL, RESET_HEAD);
	ft_strdel(&replace);
	ft_strdel(&search);
}

void	history_replace(t_lexer *machine)
{
	if (get_input(machine, CUR_CHAR) == '!')
	{
		ft_printf("'%c'\n", get_input(machine, NEXT_CHAR));
		if (get_input(machine, NEXT_CHAR) == '!')
			call_history(machine, 2, GET_ENTRY | PREV);
		else if (ft_isalnum(get_input(machine, NEXT_CHAR)) == TRUE)
			call_history(machine, 2, GET_ENTRY);
		else if (get_input(machine, NEXT_CHAR) == '-'
			&& ft_isalnum(get_input(machine, NEXT_NEXT_CHAR)) == TRUE)
			call_history(machine, 3, GET_ENTRY | REL);
	}
}

void	start_lexer(t_lexer *machine)
{
//	history_replace(machine);
	if (get_input(machine, CUR_CHAR) == '\0')
		machine->state = assign_special(machine) ? L_SPACE : L_END;
	else if (get_input(machine, CUR_CHAR) == '\\')
	{
		machine->index++;
		add_to_buffer(machine);
		machine->last_lexer = E_STRING;
		machine->state = L_STRING;
	}
	else if (ft_strchr("\t ", get_input(machine, CUR_CHAR)) != NULL)
		machine->state = L_SPACE;
	else if (ft_strchr(SIGN_DETECT, get_input(machine, CUR_CHAR)) != NULL)
		machine->state = L_SIGN;
	else if (ft_isdigit(get_input(machine, CUR_CHAR)) == TRUE)
		machine->state = L_IO_NUMBER;
	else
		machine->state = L_STRING;
}

void	end_machine(t_lexer *machine)
{
	if (get_buffer(machine, CUR_CHAR) != '\0')
		machine->state = L_OUT;
	else if (machine->last_lexer != E_END)
	{
		machine->last_lexer = E_END;
		machine->state = L_OUT;
	}
	else
		machine->state = L_FINISH;
}

void	out_lexer(t_lexer *machine)
{
	t_list	*node;
	t_token	token;

	token = generate_token(machine);
	if ((node = ft_lstnew(&token, sizeof(token))) == NULL)
		return ;
	ft_lstaddback(&machine->tokens, node);
	machine->state = L_START;
}
