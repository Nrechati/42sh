/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_editor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:28:42 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/02 19:29:19 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

static void		add_fd_to_param(char **param, int fd)
{
	char	*tmp;
	char	*fd_str;

	tmp = ft_itoa(fd);
	fd_str = ft_strjoin("fd:", tmp);
	ft_strdel(&tmp);
	if (*param != NULL)
	{
		tmp = *param;
		*param = ft_strjoin(tmp, fd_str);
		ft_strdel(&tmp);
	}
	else
		*param = ft_strdup(fd_str);
	ft_strdel(&fd_str);
}

static int8_t	launch_edition(t_registry *shell, char *editor)
{
	t_vector	*cmd;
	char		*out;
	char		*tmp;
	char		*ret;

	out = ft_strjoin(editor, " ");
	tmp = out;
	out = ft_strjoin(out, FC_FILE_TMP);
	ft_strdel(&tmp);
	cmd = vct_dups(out);
	shell->option.option &= ~(INTERACTIVE_OPT);
	execution_pipeline(shell, &cmd);
	shell->option.option |= INTERACTIVE_OPT;
	ft_strdel(&out);
	vct_del(&cmd);
	history(NULL, NULL, POP_ENTRY);
	if ((ret = get_var(shell->intern, "?")) != NULL
			&& ft_strequ(ret, "0") == FALSE)
		return (FAILURE);
	return (SUCCESS);
}

static int8_t	write_file(t_registry *shell, char **av, char *editor)
{
	int		fd;
	char	*param;

	param = NULL;
	if ((fd = open(FC_FILE_TMP, O_CREAT | O_WRONLY | O_TRUNC,
					S_IRUSR | S_IWUSR)) == FAILURE)
	{
		ft_dprintf(STDERR_FILENO,
				"42sh: fc: failed to open or create file: %s\n", FC_FILE_TMP);
		return (FAILURE);
	}
	if (get_first_last(av, &param) == FAILURE)
	{
		ft_dprintf(STDERR_FILENO,
				"42sh: fc: history specification out of range\n");
		ft_strdel(&param);
		return (FAILURE);
	}
	add_fd_to_param(&param, fd);
	history(NULL, param, PRINT_HISTORY | WITHOUT_SPACE);
	ft_strdel(&param);
	close(fd);
	return (launch_edition(shell, editor));
}

static int8_t	exec_new_pipeline(t_registry *shell)
{
	t_vector	*cmd;
	char		*line;
	int			fd;

	if ((fd = open(FC_FILE_TMP, O_RDONLY)) == FAILURE)
	{
		ft_dprintf(STDERR_FILENO,
				"42sh: fc: failed to open or create file: %s\n", FC_FILE_TMP);
		return (FAILURE);
	}
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		cmd = vct_dups(line);
		ft_strdel(&line);
		shell->option.option &= ~(INTERACTIVE_OPT);
		if (verif_line(cmd) == TRUE)
			execution_pipeline(shell, &cmd);
		shell->option.option |= INTERACTIVE_OPT;
		vct_del(&cmd);
	}
	ft_strdel(&line);
	close(fd);
	return (SUCCESS);
}

uint8_t			fc_editor(t_registry *shell, char **av, char *editor)
{
	history(NULL, NULL, POP_ENTRY);
	if (write_file(shell, av, editor) == FAILURE)
		return (1);
	if (exec_new_pipeline(shell) == FAILURE)
		return (1);
	return (SUCCESS);
}
