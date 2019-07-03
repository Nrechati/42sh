/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:28:31 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/02 19:28:32 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_option		get_option_fc(char *s, t_option option)
{
	option = 0;
	while (*s)
	{
		if (*s == 'n')
			option |= N_OPT;
		else if (*s == 'l')
			option |= L_OPT;
		else if (*s == 'r')
			option |= R_OPT;
		else if (*s == 's')
			option |= S_OPT;
		else if (option == 0 && ft_isdigit(*s) == TRUE)
			return (option);
		else
		{
			ft_dprintf(STDERR_FILENO,
					"42sh: fc: -%c: invalid option\n", *s);
			ft_dprintf(STDERR_FILENO, "%s%s or %s", FC1, FC2, FC3);
			return (ERROR_OPT);
		}
		s++;
	}
	return (option);
}

static char		*get_fc_options(char ***av, t_option *option)
{
	char	*editor;

	editor = NULL;
	if (*av == NULL)
		return (NULL);
	if (ft_strequ(**av, "-e") == TRUE)
	{
		(*av)++;
		if (**av == NULL || ***av == '-' || ***av == '\0')
		{
			ft_dprintf(STDERR_FILENO, "%s\n%s%s or %s", FC_E, FC1, FC2, FC3);
			*option = ERROR_OPT;
		}
		else
		{
			*option = E_OPT;
			editor = ft_strdup(**av);
			(*av)++;
		}
	}
	if (*option == ERROR_OPT)
		return (NULL);
	*option |= set_options(av, get_option_fc);
	return (editor);
}

static char		*get_default_editor(t_registry *shell)
{
	char	*editor;

	editor = get_var(shell->intern, "FCEDIT");
	editor = ft_strdup(editor == NULL ? "ed" : editor);
	return (editor);
}

uint8_t			fc_blt(t_registry *shell, char **av)
{
	t_option	option;
	char		*editor;
	int			ret;

	++av;
	option = 0;
	if ((shell->option.option & INTERACTIVE_OPT) == FALSE)
		return (SUCCESS);
	editor = get_fc_options(&av, &option);
	if (option == ERROR_OPT)
		ret = 2;
	else if (option & S_OPT)
		ret = fc_redo(shell, av);
	else if (option & L_OPT)
		ret = fc_list(av, option);
	else
	{
		if (editor == NULL)
			editor = get_default_editor(shell);
		ret = fc_editor(shell, av, editor);
	}
	history(shell, NULL, RESET_HEAD);
	ft_strdel(&editor);
	return (ret);
}
