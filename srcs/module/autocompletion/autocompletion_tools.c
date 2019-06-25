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
		ok = TRUE;
		closedir(dir);
	}
	ft_strdel(&total_name);
	return (ok);
}
