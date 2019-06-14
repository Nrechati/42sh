#include "sh21.h"
#include <fcntl.h>


void	read_histfile(t_registry *shell, t_history *history)
{
	char	*histfile;
	char	*cmd;
	int		fd;

	histfile = get_var(shell->intern, "HISTFILE");
	histfile = ft_strdup(histfile == NULL ? HISTFILE_DEFAULT : histfile); 
	if ((fd = open(histfile, O_CREAT | O_WRONLY,
					S_IRWXU | S_IRGRP | S_IROTH)) == FAILURE)
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
