#include "sh21.h"

 char		*extract_file(char *input)
{
	char	*tmp;

	if (input == NULL)
		return (NULL);
	if (*input == '/')
		input++;
	if ((tmp = ft_strrchr(input, '/')) != NULL)
	{
		ft_strdel(&input);
		return (ft_strdup(tmp + 1));
	}
	return (input);

}

static void		get_file_list(char *dirname, char *input, t_autocomplete *result, DIR *dir)
{
	struct dirent		*mydir;
	char				*data;
	size_t				len;

	result->nb = 0;
	len = input == NULL ? 0 : ft_strlen(input);
	while ((mydir = readdir(dir)) != NULL)
	{
		if (len == 0 || ft_strnequ(mydir->d_name, input, len) == TRUE)
		{
			if ((ft_strequ(mydir->d_name, ".")
				|| ft_strequ(mydir->d_name, ".."))
				&& (len == 0 && *input != '.'))
				continue ;
			data = NULL;
			if (is_a_directory(dirname, mydir->d_name) == TRUE)
				ft_asprintf(&data, "%s/ ", mydir->d_name);
			else
				ft_asprintf(&data, "%s ", mydir->d_name);
			ft_lstadd(&result->list, ft_lstnew(data, ft_strlen(data) + 1));
			result->max_len = get_maxlen(result->max_len, ft_strlen(data));
			ft_strdel(&data);
			result->nb++;
		}
	}
}

void			get_completion_file(char *input, t_autocomplete *result,
									__unused t_registry *shell)
{
	char	*clean_path;
	char	*slash;
	DIR		*dir;

	clean_path = ft_strdup((input == NULL || ft_strchr(input, '/') == NULL)
						? "." : input);
	ft_printf("\ninput: '%s' | cleanpath: '%s'\n", input, clean_path);
	if (ft_strequ("/", clean_path) == FALSE
			&& (slash = ft_strrchr(clean_path, '/')) != NULL)
		*(slash + 1) = '\0';
	if ((dir = opendir(clean_path)) != NULL)
	{
		ft_printf("\ninput: '%s' | cleanpath: '%s'\n", input, clean_path);
		input = extract_file(input);
		get_file_list(clean_path, input, result, dir);
		closedir(dir);
	}
	ft_strdel(&clean_path);
}
