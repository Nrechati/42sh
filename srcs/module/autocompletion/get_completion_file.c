#include "sh21.h"

static char		*extract_file(char *input)
{
	char	*tmp;

	if (input == NULL)
		return (NULL);
	if ((tmp = ft_strrchr(input, '/')) != NULL)
		return (tmp + 1);
	return (input);

}

static uint8_t	is_a_directory(char *dirname, char *file)
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

	clean_path = ft_strdup((input == NULL || *input == '\0') ? "." : input);
	if (ft_strequ("/", clean_path) == FALSE
			&& (slash = ft_strrchr(clean_path, '/')) != NULL)
		*(slash + 1) = '\0';
	ft_printf("\nopen: '%s', input: '%s'\n", clean_path, input);
	if ((dir = opendir(clean_path)) != NULL)
	{
		input = extract_file(input);
		get_file_list(clean_path, input, result, dir);
		closedir(dir);
	}
	ft_strdel(&clean_path);
}
