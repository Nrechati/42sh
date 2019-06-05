/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bacth_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:16:26 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/05 10:20:01 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>

static char	*ft_strjoinfree(char *s1, const char *s2, const int8_t todel)
{
	char	*join;

	if ((join = ft_strnew(ft_strlen(s1) + ft_strlen(s2))) == NULL)
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcat(join, s2);
	if (todel == 1)
		ft_strdel(&s1);
	return (join);
}

static char	*read_input(const int fd)
{
	char	*final;
	char	buffer[16];

	final = NULL;
	ft_memset(buffer, 0, 16);
	while (read(fd, buffer, 15) > 0)
	{
		if (final == NULL)
			final = ft_strdup(buffer);
		else
			final = ft_strjoinfree(final, buffer, 1);
		ft_memset(buffer, 0, 16);
	}
	return (final);
}

static inline char		*read_input_cmd(t_registry *shell)
{
	if (shell->option.option & COMMAND_OPT)
		return (ft_strdup(shell->option.command_str));
	return (read_input(STDIN_FILENO));
}

void					batch_mode(t_registry *shell)
{
	char	*command;

	command = read_input_cmd(shell);
/*	if (ft_strcheck(command, ft_isprint) == TRUE)
		execution_pipeline(shell, command);
	else
		ft_dprintf(2, "21sh: Not a valid input.\n");*/
	ft_strdel(&command);
}

