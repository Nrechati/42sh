#include "sh21.h"
#include <unistd.h>

size_t	get_maxlen(size_t ref, size_t len)
{
	return (ref >= len ? ref: len);
}

uint8_t	is_cmd_delimiter(char c)
{
	if (c == '|' || c == ';' || c == '&')
		return (TRUE);
	return (FALSE);
}

int		lst_strcmp(void *data1, void *data2)
{
	return (ft_strcmp((char *)data1, (char *)data2));
}

uint8_t	is_a_directory(char *dirname, char *file)
{
	DIR		*dir;
	char	*total_name;
	int		ok;

	total_name = NULL;
	ok = FALSE;
	ft_asprintf(&total_name, "%s/%s", dirname, file);
	if ((dir = opendir(total_name)) != NULL)
	{
		if (access(total_name, R_OK) == SUCCESS)
			ok = TRUE;
		closedir(dir);
	}
	ft_strdel(&total_name);
	return (ok);
}

char			*get_home_input(char *input, t_registry *shell)
{
	char	*new_input;
	char	*var;

	if (input == NULL)
		return (NULL);
	new_input = NULL;
	while (*input == ' ' || *input == '\t' || is_cmd_delimiter(*input) == TRUE)
		input++;
	if (*input == '~' && (var = get_var(shell->intern, "HOME")) != NULL)
		ft_asprintf(&new_input, "%s%s", var, input + 1);
	else
		new_input = ft_strdup(input);
	return (new_input);
}
