#include "sh21.h"

 char		*extract_path(char *input)
{
	char	*path;
	size_t	len;

	if (input == NULL)
		return (NULL);
	path = ft_strdup(input);
	len = ft_strlen(input) - 1;
	while (len > 0 && path[len])
	{
		if (path[len - 1] == '/')
		{
			path[len] = '\0';
			break ;
		}
		len--;
	}
	return (path);
}

static void		get_file_list(char *dirname, char *input,
						t_autocomplete *result, DIR *dir)
{
	struct dirent		*mydir;
	char				*data;
	char				*fusion;
	size_t				len;

	result->nb = 0;
	len = input == NULL ? 0 : ft_strlen(input);
	while ((mydir = readdir(dir)) != NULL)
	{
		if ((ft_strequ(mydir->d_name, ".")
			|| ft_strequ(mydir->d_name, ".."))
			&& len > 0 && input[len - 1] != '.')
				continue ;
		fusion = NULL;
		if (dirname[ft_strlen(dirname) - 1 ] == '/' || mydir->d_name[0] == '/')
			ft_asprintf(&fusion, "%s%s", dirname, mydir->d_name);
		else
			ft_asprintf(&fusion, "%s/%s", dirname, mydir->d_name);
		if (len == 0 || ft_strnequ(fusion, input, len) == TRUE)
		{
			data = NULL;
			if (is_a_directory(dirname, mydir->d_name) == TRUE)
				ft_asprintf(&data, "%s/", mydir->d_name);
			else
				ft_asprintf(&data, "%s ", mydir->d_name);
			ft_lstadd(&result->list, ft_lstnew(data, ft_strlen(data) + 1));
			result->max_len = get_maxlen(result->max_len, ft_strlen(data));
			ft_strdel(&data);
			result->nb++;
		}
		ft_strdel(&fusion);
	}
}

void			get_completion_file(char *input, t_autocomplete *result,
									__unused t_registry *shell)
{
	char	*path;
	char	*transform;
	DIR		*dir;

	if (input == NULL || *input == '\0')
		transform = ft_strdup("./");
	else if (input != NULL && *input != '/')
		transform = ft_strjoin("./", input);
	else
		transform = ft_strdup(input);
	path = extract_path(transform);
	ft_printf("\nINPUT: '%s' | PATH : '%s'\n\n", transform, path);
	if ((dir = opendir(transform)) != NULL)
	{
		ft_strdel(&path);
		path = ft_strdup(transform);
		get_file_list(path, transform, result, dir);
		closedir(dir);
	}
	else if ((dir = opendir(path)) != NULL)
	{
		get_file_list(path, transform, result, dir);
		closedir(dir);
	}
	ft_strdel(&path);
	ft_strdel(&transform);
}
