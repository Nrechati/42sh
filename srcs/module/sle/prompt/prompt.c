/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/02 14:30:02 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "interpreter.h"

static int32_t mark_proc_status(pid_t pid, int status)
{
	t_list		*joblist;
	t_list		*proclist;
	t_job		*job;
	t_process	*process;

	(void) pid;
//	ft_printf("marking job status %d\n", pid);
	if (pid <= 0)
		return -1;
	joblist = g_shell->job_list;
		while (joblist != NULL)
		{
			job = joblist->data;
			if (job_is_stopped(job) == FALSE)
			{
				proclist = job->processes;
				while (proclist != NULL)
				{
					process = proclist->data;
					process->status = status;
//					ft_printf("Job %d is %d\n", job->pgid, status);
					if (WIFSTOPPED(status))
						process->stopped = TRUE;
					else
						process->completed = TRUE;
					proclist = proclist->next;
				}
				joblist = joblist->next;
			}
		}
		return (0);
	return (FAILURE);
}

void	notify_job_info(t_list *joblst, char *info)
{
	t_job		*job;
	t_list		*jobl;
	char		*command;

	jobl = joblst;
	while (jobl != NULL)
	{
		job = jobl->data;
		if (job_is_completed(job) == TRUE)
		{
			get_job_av(job, &command);
			ft_printf("[%d]+ %s \t %s\n", job->id, info, command);
			g_shell->active_jobs--;
			remove_job_from_list(&g_shell->job_list, job);
			update_jobinfos(g_shell);
			ft_strdel(&command);
		}
		jobl = jobl->next;
	}
}

static void	prompt_pre_process(t_sle *sle)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WNOHANG | WUNTRACED);
	mark_proc_status(pid, status);
	notify_job_info(g_shell->job_list, "Done");

	sle->state = STATE_STD;
	vct_reset(sle->line);
	vct_reset(sle->sub_line);
	vct_reset(sle->window.displayed_line);
	history(NULL, NULL, RESET_HEAD);
	update_window(sle);
}

static void	prompt_post_process(t_registry *shell, t_sle *sle)
{
	if (sle->state == STATE_SEARCH)
	{
		vct_del(&sle->line);
		sle->line = vct_dup(sle->search_line);
	}
	if (ft_strequ(vct_get_string(sle->line), "Failed") == TRUE)
	{
		vct_del(&sle->line);
		sle->line = vct_dup(sle->sub_line);
	}
	sle->state = STATE_STD;
	autocompletion(NULL, shell, NULL, RESET_RESULT);
	history(NULL, NULL, RESET_HEAD);
	vct_add(sle->line, '\n');
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	redraw(shell, sle);
	ft_putendl("");
	if (ft_strequ(sle->prompt.state, INT_PS1) == TRUE)
		verif_line(sle, sle->line);
}

t_vector	*prompt(t_registry *shell, t_sle *sle)
{
	char		character[READ_SIZE + 1];

	prompt_pre_process(sle);
	ft_bzero(character, READ_SIZE + 1);
	print_prompt(shell, sle);
	while (is_separator(character) == FALSE)
	{
		ft_bzero(character, READ_SIZE);
		if (is_eof(vct_get_string(sle->line)) == TRUE)
		{
			ft_putchar('\n');
			return (NULL);
		}
		if (read(0, character, READ_SIZE) == FAILURE)
			return (read_error(shell, sle));
		handle_input_key(shell, sle, character);
		redraw(shell, sle);
	}
	prompt_post_process(shell, sle);
	return (vct_dup(sle->line));
}

t_vector	*invoke_ps2prompt(t_registry *shell, t_sle *sle, uint32_t sle_flag)
{
	t_vector	*linesave;
	t_vector	*line;
	static const char	*prompt_type[] = {PROMPT_PIPE, PROMPT_QUOTE,
										PROMPT_DQUOTE, PROMPT_BQUOTE,
										PROMPT_NL, PROMPT_AND, PROMPT_OR,
										PROMPT_BRACE, PROMPT_MATHS};

	linesave = sle->line;
	sle->line = sle->sub_line;
	sle->prompt.missing_char = (char *)prompt_type[sle_flag & ~SLE_PS2_PROMPT];
	sle->prompt.state = INT_PS2;
	if ((line = prompt(shell, sle)) == NULL)
	{
		sle->line = linesave;
		return (NULL);
	}
	vct_del(&line);
	sle->line = linesave;
	return (vct_dup(sle->sub_line));
}

t_vector	*invoke_ps3prompt(t_registry *shell, t_sle *sle)
{
	t_vector	*linesave;
	t_vector	*line;

	linesave = sle->line;
	sle->line = sle->sub_line;
	sle->prompt.state = INT_PS3;
	if ((line = prompt(shell, sle)) == NULL)
	{
		sle->line = linesave;
		return (NULL);
	}
	vct_del(&line);
	sle->line = linesave;
	//vct_add(sle->sub_line, '\n');
	return (vct_dup(sle->sub_line));
}
