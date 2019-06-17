#include "sh21.h"

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

