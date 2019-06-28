/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 17:16:28 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/26 11:32:52 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int8_t		id_to_job(t_job **job, uint64_t job_id)
{
	t_list 		*job_ptr;

	job_ptr = g_shell->job_list;
	while (job_ptr != NULL)
	{
		if (((t_job*)job_ptr->data)->id == job_id)
		{
			*job = ((t_job*)job_ptr->data);
			return (SUCCESS);
		}
		job_ptr = job_ptr->next;
	}
	return (FAILURE);
}

int8_t			get_current_job(t_job **job, char c)
{
	if ((c == '+' || c == '%' ) && g_shell->current_plus != NULL)
	{
		*job = (t_job*)g_shell->current_plus->data;
		return (SUCCESS);
	}
	else if (c == '-' && g_shell->current_minus != NULL)
	{
		*job = (t_job*)g_shell->current_minus->data;
		return (SUCCESS);
	}
	return (FAILURE);
}

int8_t			parse_jobname(t_job **job, char *jobname)
{
	t_list		*job_ptr;
	char		*jobav;

	job_ptr = g_shell->job_list;
	if (*jobname == '?')
	{
		jobname++;
		while (job_ptr != NULL)
		{
			jobav = ((t_process*)((t_job*)job_ptr->data)->processes->data)->av[0];
			if (ft_strstr(jobav, jobname) != NULL)
			{
				*job = (t_job*)job_ptr->data;
				return (SUCCESS);
			}
			job_ptr = job_ptr->next;
		}
	}
	else
	{
		while (job_ptr != NULL)
		{
			jobav = ((t_process*)((t_job*)job_ptr->data)->processes->data)->av[0];
			if (ft_strbeginswith(jobav, jobname) == TRUE)
			{
				*job = (t_job*)job_ptr->data;
				return (SUCCESS);
			}
			job_ptr = job_ptr->next;
		}
	}
	return (FAILURE);
}

int8_t			parse_jobid(t_job **job, char *param)
{
	uint32_t	job_id;

	*job = NULL;
	if (param == NULL)
		return (SUCCESS);
	if (*param == '%')
	{
		param++;
		if (ft_isnumeric(param))
		{
			job_id = ft_atoi(param);
			if (job_id != 0)
				return (id_to_job(job, job_id));
			else
				return (FAILURE);
		}
		else
		{
			if (*param == '-' || *param == '+' || *param == '%')
				return (get_current_job(job, *param));
			else
				return (parse_jobname(job, param));
		}
	}
	return (FAILURE);
}