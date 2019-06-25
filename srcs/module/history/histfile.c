#include "sh21.h"
#include <fcntl.h>

static char		*get_histfile(t_registry *shell)
{
	char	*home;
	char	*histfile;

	home = get_var(shell->intern, "HOME");
	histfile = get_var(shell->intern, "HISTFILE");
	if (histfile != NULL)
		return (ft_strdup(histfile));
	if (home != NULL)
	{
		ft_asprintf(&histfile, "%s/%s",
					home, histfile == NULL ? HISTFILE_DEFAULT : histfile); 
		return (histfile);
	}
	return (NULL);
}

static int		get_histsize(t_registry *shell)
{
	char	*tmp;
	int		histsize;

	tmp = get_var(shell->intern, "HISTSIZE");
	if (tmp == NULL)
		histsize = HISTSIZE_DEFAULT;
	else
		histsize = ft_atoi(tmp);
	if (histsize < 128 || histsize > 32768)
		histsize = HISTSIZE_DEFAULT;
	return (histsize);
}

void			read_histfile(t_registry *shell, t_history *history)
{
	char	*histfile;
	char	*cmd;
	int		fd;

	histfile = get_histfile(shell);
	if (histfile == NULL)
		return ;
	if ((fd = open(histfile, O_CREAT | O_RDONLY,
					S_IRUSR | S_IWUSR)) == FAILURE)
		return ;
	ft_strdel(&histfile);
	cmd = NULL;
	while (get_next_line(fd, &cmd) > 0)
	{
		add_entry(&history->entry, create_entry(cmd));
		ft_strdel(&cmd);
		history->head_ptr = history->entry;
		history->nb_of_entries++;
	}
	close(fd);
}

void			write_histfile(t_registry *shell, t_history *history)
{
	t_entry	*entry;
	char	*histfile;
	int		histsize;
	int		i;
	int		fd;

	histfile = get_histfile(shell);
	if (histfile == NULL)
		return ;
	if ((fd = open(histfile, O_CREAT | O_WRONLY | O_TRUNC,
					S_IRUSR | S_IWUSR)) == FAILURE)
		return ;
	ft_strdel(&histfile);
	entry = entry_roll_back(history->entry); 
	histsize = get_histsize(shell);
	i = 0;
	while (entry != NULL)
	{
		if (history->nb_of_entries - i <= histsize)
			ft_putendl_fd(entry->cmd, fd);
		i++;
		entry = entry->next;
	}
	close(fd);
}
