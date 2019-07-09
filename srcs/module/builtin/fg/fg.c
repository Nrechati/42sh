/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:37:48 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 10:46:14 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_job	*get_current(void)
{
	if (g_shell->current_plus != NULL
		&& g_shell->current_plus->data != NULL)
		return ((((t_job *)(g_shell->current_plus)->data)));
	return (NULL);
}

int8_t	fg_blt(t_registry *shell, char **av)
{
	t_job	*job;
	int8_t	result;
	uint8_t	ret;

	if (jobctl_is_active(shell) == FALSE
			|| am_i_forked(shell, "fg") == TRUE)
		return (FAILURE);
	++av;
	job = NULL;
	result = 0;
	ret = SUCCESS;
	if (av != NULL)
		result = parse_jobid(&job, *av);
	if (result == BAD_PERCENTAGE || result == FAILURE
				|| (result == SUCCESS && shell->current_plus == NULL))
	{
		if (result == BAD_PERCENTAGE)
			ft_dprintf(2, "fg: usage: fg [%%jobID]\n");
		ft_dprintf(2, "42sh: fg: no current job\n");
		ret = 1;
	}

	else if (job == NULL && shell->current_plus != NULL)
		job = get_current();

	jobctl(shell, job, JOBCTL_PUTINFG);
	return (ret);
}
