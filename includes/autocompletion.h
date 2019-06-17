#ifndef AUTOCOMPLETION_H
# define AUTOCOMPLETION_H 

# define RESET_RESULT	0x0001
# define NEW_SEARCH		0x0002

enum e_result_type
{
	CMD_TYPE,
	VARIABLE_TYPE,
	VARIABLE_BRACKET_TYPE,
	FILE_TYPE
};

typedef struct			s_autocomplete
{
	char				**result_tab;
	size_t				nb;
	size_t				max_len;
	enum e_result_type	type;
}						t_autocomplete;


typedef 	void (t_completion_fct)(char *, t_autocomplete *, t_registry *);

char				*autocompletion(char *input, t_registry *shell,
										int col, uint64_t option);
enum e_result_type	get_result_type(char *input);
char				*get_start_input(char *input, enum e_result_type type);

uint8_t				is_cmd_delimiter(char c);
size_t				get_maxlen(size_t ref, size_t len);

void	get_completion_cmd(char *input, t_autocomplete *result, t_registry *shell);
void	get_completion_var(char *input, t_autocomplete *result, t_registry *shell);
void	get_completion_file(char *input, t_autocomplete *result, t_registry *shell);
#endif
