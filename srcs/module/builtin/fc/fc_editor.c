#include "sh21.h"
#include <fcntl.h>

#define FC_FILE_TMP	"/tmp/42sh-fc.tmp"

static void			add_fd_to_param(char **param, int fd)
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


static void			launch_edition(t_registry *shell, char *editor)
{
	t_vector	*cmd;
	char		*out;
	char		*tmp;

	out = ft_strjoin(editor, " ");
	tmp = out;
	out = ft_strjoin(out, FC_FILE_TMP);
	ft_strdel(&tmp);
	cmd = vct_dups(out);
	shell->option.option &= ~(INTERACTIVE_OPT);
	execution_pipeline(shell, cmd);
	shell->option.option |= INTERACTIVE_OPT;
	ft_strdel(&out);
	vct_del(&cmd);
	history(NULL, NULL, POP_ENTRY);
}

static int8_t		write_file(t_registry *shell, char **av, char *editor)
{
	int		fd;
	char	*param;

	param = NULL;
	if ((fd = open(FC_FILE_TMP, O_CREAT | O_WRONLY | O_TRUNC,
					S_IRWXU | S_IRGRP | S_IROTH)) == FAILURE)
	{
		ft_dprintf(g_shell->cur_fd.err,
				"42sh: fc: failed to open or create file: %s\n", FC_FILE_TMP);
		return (FAILURE);
	}
	if (get_first_last(av, &param) == FAILURE)
	{
		ft_dprintf(g_shell->cur_fd.err,
				"42sh: fc: history specification out of range\n");
		ft_strdel(&param);
		return (FAILURE);
	}
	add_fd_to_param(&param, fd);
	history(NULL, param, PRINT_HISTORY | WITHOUT_SPACE);
	close(fd);
	launch_edition(shell, editor);
	return (SUCCESS);
}

int8_t			exec_new_pipeline(t_registry *shell)
{
	int			fd;
	t_vector	*cmd;
	char		*line;
	
	if ((fd = open(FC_FILE_TMP, O_RDONLY)) == FAILURE)
	{
		ft_dprintf(g_shell->cur_fd.err,
				"42sh: fc: failed to open or create file: %s\n", FC_FILE_TMP);
		return (FAILURE);
	}
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		cmd = vct_dups(line);
		ft_strdel(&line);
		shell->option.option &= ~(INTERACTIVE_OPT);
		execution_pipeline(shell, cmd);
		shell->option.option |= INTERACTIVE_OPT;
		vct_del(&cmd);
	}
	close(fd);
	return (SUCCESS);
}

int8_t			fc_editor(t_registry *shell, char **av, char *editor,
						t_option option)
{
	(void)option;
	history(NULL, NULL, POP_ENTRY);
	if (write_file(shell, av, editor) == FAILURE)
		return (FAILURE);
	if (exec_new_pipeline(shell) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

