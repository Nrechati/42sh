
#include "sh21.h"

static uint8_t	is_history_end(t_vector *input, size_t offset)
{
	size_t	len_op;
	int		type;
	char	*current;

	type = START_OPERATOR;
	current = input->buffer + offset;
	if (*current == ' ' || *current == '\t')
		return (TRUE);
	while (type >= 0)
	{
		len_op = ft_strlen(g_shell->grammar[type]);
		if (ft_strnequ(g_shell->grammar[type], current, len_op) == TRUE)
			return (TRUE);
		type--;
	}
	return (FALSE);
}

static int		searching(t_vector *input, t_vector *to_replace, size_t i,
					uint64_t *option)
{
	int scale;

	scale = 0;
	if (vct_charat(input, i + scale) == '!')
		scale++;
	if (vct_charat(input, i + scale) == '-')
	{
		*option |= REL;
		scale++;
	}
	while (vct_charat(input, i + scale) != '\0')
	{
		if (is_history_end(input, i + scale) == TRUE)
			break ;
		vct_add(to_replace, vct_charat(input, i + scale));
		scale++;
	}
	if (ft_isnumeric(to_replace->buffer) == TRUE)
		*option |= BY_ID;
	else
		*option |= BY_NAME;
	return (scale);
}

static char	*get_history_return(t_vector *to_replace, uint64_t option)
{
	char		*search;

	search = history(NULL, to_replace->buffer, option);
	if (search == NULL
			|| ((option & PREV) == FALSE && *to_replace->buffer == '\0'))
	{
		if (option & REL)
			vct_push(to_replace, '-');
		else if (option & PREV)
			vct_push(to_replace, '!');
		vct_push(to_replace, '!');
		ft_dprintf(2, "42sh: %s: event not found\n", to_replace->buffer);
		vct_del(&to_replace);
		return (NULL);
	}
	vct_del(&to_replace);	
	return (search);
}

static int	process_history_expansion(t_vector *input, size_t i)
{
	uint64_t	option;
	t_vector	*to_replace;
	int			scale;
	char		*search;

	option = GET_ENTRY;
	to_replace = vct_new(0);
	scale = 0;
	if (vct_charat(input, i + 1) == '!')
	{
		scale += 2;
		option |= PREV;
	}
	else if (ft_isalnum(vct_charat(input, i + 1)) == TRUE)
		scale = searching(input, to_replace, i, &option);
	else if (vct_charat(input, i + 1) == '-')
		scale = searching(input, to_replace, i, &option);
	else
		return (SUCCESS);
	if ((search = get_history_return(to_replace, option)) == NULL)
		return (FAILURE);
	vct_replace_string(input, i, i + scale, search);
	return (scale);
}

int8_t		history_expansion(t_vector *input)
{
	uint16_t	flag;
	size_t		i;
	int			ret;

	i = 0;
	flag = NO_FLAG;
	while (vct_charat(input, i) != '\0')
	{
		if (flag & BACKSLASH_FLAG)
			flag &= ~ BACKSLASH_FLAG;
		if (vct_charat(input, i) == '\\' && flag == NO_FLAG && i++)
			flag |= BACKSLASH_FLAG;
		if (vct_charat(input, i) == '\'' && flag == NO_FLAG)
			flag |= SINGLEQUOTE_FLAG;
		else if (vct_charat(input, i) == '\'' && (flag & SINGLEQUOTE_FLAG))
			flag &= ~SINGLEQUOTE_FLAG;
		else if (vct_charat(input, i) == '!' && flag == NO_FLAG)
		{
			if ((ret = process_history_expansion(input, i)) == FAILURE)
				return (FAILURE);
			i += ret;
		}
		i++;
	}
	return (SUCCESS);
}
