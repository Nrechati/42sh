/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 09:48:40 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/31 10:47:59 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "interface_functions.h"

t_coord		*index_to_coord(t_window *win, uint64_t index)
{
	t_coord	*co;

	//TODO: change global
//	ft_dprintf(3, "Index is :%d\n", index);
	if (index > vct_len(g_shell->interface.line)
				+ get_prompt_length(&g_shell->interface.prompt) + 1)
		index = vct_len(g_shell->interface.line)
				+ get_prompt_length(&g_shell->interface.prompt);

	if (win->cols == 0)
		return (NULL);
	if (!(co = malloc(sizeof(t_coord))))
		return (NULL);
//	ft_dprintf(3, "Malloc ok\n");

	co->x = (index % win->cols);
	co->y = (index / win->cols);
	return (co);
}

void		print_char(t_interface *itf, char c)
{
	write(1, &c, 1);
	itf->cursor.x++;
	if (itf->cursor.x == itf->window.cols)
	{
		itf->cursor.y++;
		itf->cursor.x = 0;
	}
	itf->cursor.index++;
}


void		print_loop(t_interface *itf, char *str)
{
	while (*str != '\0')
	{
		write(1, str, 1);
		++str;
		itf->cursor.x++;
		if (itf->cursor.x == itf->window.cols)
		{
			itf->cursor.y++;
			itf->cursor.x = 0;
		}
		itf->cursor.index++;
	}
}

int8_t		parse_effect_number(__unused char *str,__unused uint32_t index)
{
	//at most 3 digits
	uint32_t len = 0;
	while (ft_isdigit(str[index + len]))
		++len;

	char *tmp = ft_strsub(str, index, len);
	if (ft_strlen(tmp) == 0)
		return (-1);
	int32_t nbr = ft_atoi(tmp);
//	ft_dprintf(3, "|-> Parsed nbr: %d\n", nbr);
	if (nbr >= 0 && nbr <= 255)
		return (0);
	return (-1);
}

uint32_t	write_esc_sequence(char *str, uint32_t index)
{
	char		*esc;
	uint32_t	length;

	esc = NULL;
	length = 2;
//	ft_dprintf(3, "Sequencing %c\n", str[index + length]);
	if (str[index + length] != '[')
		return (length - 1);
	while (str[++length + index] != '\0')
	{

		if (str[length + index] != ';'
				&& str[length + index] != 'm'
				&& parse_effect_number(str, length + index) == -1)
			return (length);


		if (str[index + length] == 'm')
		{
			esc = ft_strsub(str, index + 1, length);
			esc[0] = 27;
			ft_printf("%s", esc);
//			ft_dprintf(3, "Seq is:|%s|\n", esc);
			ft_strdel(&esc);
			break ;
		}

	}
	return (length + 1);
}

void	print_to_window(t_interface *itf, t_vector *text)
{
	uint32_t	index;
	char		*str;

	index = 0;
	str = vct_get_string(text);
	while (str[index] != '\0')
	{
		if (str[index] == '\\' && str[index + 1] == 'e')
			index += write_esc_sequence(str, index);

		write(1, &str[index], 1);
		++index;
		itf->cursor.x++;

		if (itf->cursor.x == itf->window.cols)
		{
			itf->cursor.y++;
			itf->cursor.x = 0;
		}
	}
	itf->prompt.length = (itf->cursor.y * itf->window.cols)
			+ itf->cursor.x;
}
