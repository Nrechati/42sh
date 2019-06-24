/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 17:16:28 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/24 19:07:07 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"


//void	remove_job_from_joblist();

t_job	*id_to_job(uint64_t job_id)
{
	t_list 		*job_ptr;

	job_ptr = g_shell->job_list;
	while (job_ptr != NULL)
	{
		if (((t_job*)job_ptr->data)->id == job_id)
			return ((t_job*)job_ptr->data);
		job_ptr = job_ptr->next;
	}
	return (NULL);
}

t_job			*get_current_job(char c)
{
	if (c == '+')
		return ((t_job *)g_shell->current_plus->data);
	else
		return ((t_job *)g_shell->current_minus->data);
}

t_job			*parse_jobname(char *jobname)
{
	uint32_t	i;
	t_list		*job_ptr;
	char		*jobav;

	i = 1;
	job_ptr = g_shell->job_list;
	while (job_ptr != NULL)
	{
		jobav = ((t_process*)((t_job*)job_ptr->data)->processes->data)->av[0];
		if (ft_strbeginswith(jobav, jobname) == TRUE)
			return ((t_job*)job_ptr->data);
		job_ptr = job_ptr->next;
	}
	return (NULL);
}

t_job			*parse_jobid(char *param)
{
	uint32_t	job_id;

	if (param == NULL)
		return (NULL);
	if (*param == '%')
	{
		param++;
		if (ft_isnumeric(param))
		{
			job_id = ft_atoi(param);
			if (job_id != 0)
				return (id_to_job(job_id));
			else
				return (NULL);
		}
		else
		{
			if (*param == '-' || *param == '+')
				return (get_current_job(*param));
			else
				return (parse_jobname(param));
		}
	}
	return (NULL);
}

