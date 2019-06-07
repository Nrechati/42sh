/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:42:30 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/06 18:51:44 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int8_t interpreter(t_registry *shell, t_list **cmd_group)
{
	t_list *job_lst;

	(void)shell;
	job_lst = ft_lstmap(*cmd_group, group_to_job, del_group); //CALLBACK DEL

	//LSTDEL CMD_GROUP
	//LSTDEL command_av
	//LSTDEL command_action
	//free(command);

	//CALL	EXPAND AV
	//CALL	EXPAND REDIRECT
	//SET	JOBTYPE

	//OPEN & PIPE
	/*	RUN		JOB
		while (process)
		{
			el_pipeator_300();
			fork()
			{
				while (redirect)
					lstiter(dup2);
				execve(process(av));
			}
			el_closatator_3000()
		}
		waitANY(job.pgid);

	*/

	return (SUCCESS);
}



