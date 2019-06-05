/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:25:34 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/05 15:41:25 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "enum.h"
# include "define.h"
# include "libft.h"

/*
*****************************************************
*********************** LEXER ***********************
*****************************************************
*/

typedef struct s_lexer	t_lexer;
typedef void			(*t_lexing)(t_lexer *);
typedef enum e_type		t_type;

typedef struct			s_token
{
	char				*data;
	enum e_type			type;
}						t_token;

typedef struct			s_lexinfo
{
	t_lexing			lexing[STATENBR];
	enum e_type			duplicate[TOKEN_WITH_DATA];
	enum e_type			special_signs[SPECIAL_SIGNS];
}						t_lexinfo;

struct					s_lexer
{
	char				*input;
	char				buffer[BUFFER];
	char				*data;
	unsigned int		buffer_index;
	t_lexinfo			*lexinfo;
	t_list				*tokens;
	enum e_lexer_state	state;
	enum e_quote		quote;
	enum e_type			last_lexer;
	int					io_detect;
};

/*
*****************************************************
********************** PARSER ***********************
*****************************************************
*/

typedef struct			s_graph
{
	enum e_type			*good_type;
}						t_graph;

/*
*****************************************************
********************** ANALYZER *********************
*****************************************************
*/

typedef struct s_resolution	t_resolution;
typedef void				(*t_resolve)(t_resolution *);
typedef t_resolve			t_analyzer[ANALYZER_STATES][NB_OF_TOKENS];

typedef struct			s_action
{
	enum e_actions		action;
	t_list				*av;
}						t_action;

typedef struct			s_filedesc
{
	unsigned int		action;
	int32_t				first;
	int32_t				second;
}						t_filedesc;

typedef	struct			s_command
{
	t_list				*av;
	t_list				*actions;
	uint8_t				cmd_type;
}						t_command;

typedef struct			s_process
{
	char				**av;
	t_list				*env;
	t_list				*redirects;
	uint8_t				completed;
	uint8_t				stopped;
	pid_t				pid;
	int					status;
}						t_process;

typedef struct			s_job
{
	t_list				*processes;
	struct termios		*term_modes;
	pid_t				pgid;
}						t_job;

struct					s_resolution
{
	t_list				*tokens;
	t_stack				stack;
	t_stack				tree_node;
	t_token				token;
	unsigned int		special_case;
	enum e_analyzer_state	last_state;
	enum e_analyzer_state	state;
	int					valid;
};

/*
*****************************************************
********************** HISTORY **********************
*****************************************************
*/

typedef struct			s_history
{
	char				*command;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

/*
*****************************************************
**************** INTERFACE_FUNCTIONS ****************
*****************************************************
*/

typedef struct s_registry	t_registry;

typedef struct			s_termcaps
{
	char				*clear;
	char				*cs_down;
	char				*cs_right;
	char				*cs_left;
	char				*cs_up;
}						t_termcaps;

typedef struct			s_cursor
{
	uint32_t			index;
	uint32_t			x;
	uint32_t			y;
}						t_cursor;

typedef struct			s_window
{
	uint32_t			rows;
	uint32_t			cols;
	uint32_t			max_chars;
}						t_window;

typedef struct			s_interface
{
	struct termios		*term_mode;
	struct termios		*orig_mode;
	t_vector			*line;
	t_vector			*clip;
	t_history			*history_head;
	t_history			*hist_ptr;
	char				*current_line;
	char				*state;
	t_cursor			cursor;
	t_window			window;
	t_termcaps			termcaps;
	uint64_t			ak_masks[AK_AMOUNT];
	int8_t				(*tc_call[AK_AMOUNT])(struct s_registry *shell);
	uint8_t				allow_input;
}						t_interface;

/*
*****************************************************
********************** COMMON ***********************
*****************************************************
*/

typedef uint16_t		t_option;

typedef struct			s_opt
{
	char				*command_str;
	t_option			option;
}						t_opt;

typedef struct			s_variable
{
	char				*name;
	char				*data;
	t_option			flag;
}						t_variable;

typedef struct			s_fd
{
	int					in;
	int					out;
	int					err;
}						t_fd;

typedef	struct			s_hashmap
{
	t_hash				bin;
	t_hash				blt;
}						t_hashmap;

struct					s_registry
{
	const char			**grammar;
	t_list				*intern;
	t_opt				option;
	t_hashmap			hash;
	t_fd				cur_fd;
	uint8_t				analyzer_signal;

	struct s_interface	interface;		// Think to modularize
	t_list				*current_job;	// Think to modularize
};

typedef int				(*t_builtin) (t_registry *, char **);

extern t_registry		*g_shell;

/*
*****************************************************
********************** RESOLVE **********************
*****************************************************
*/

extern t_list			*g_job_head;

/*
*****************************************************
********************** BUILTIN **********************
*****************************************************
*/

typedef t_option		(*t_get_option)(char *s, t_option option);

#endif
