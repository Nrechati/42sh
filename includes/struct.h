/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:25:34 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/13 17:42:44 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "enum.h"
# include "define.h"
# include "libft.h"

/*
*****************************************************
********************** COMMON ***********************
*****************************************************
*/

extern const char		**g_grammar; // TEMP

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

typedef struct			s_registry
{
	t_list				*intern;
	t_opt				option;
	t_hashmap			hash;

	t_fd				cur_fd;				// Out
	uint8_t				analyzer_signal;	// Out
	t_list				*current_job;		// Out
}						t_registry;

extern t_registry		*g_shell;

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
	t_vector			*buffer;
	t_vector			*input;
	t_lexinfo			*lexinfo;
	char				*data;
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

typedef struct		s_parser
{
	t_graph			*graph;
	const char		**grammar;
}					t_parser;


/*
*****************************************************
********************** ANALYZER *********************
*****************************************************
*/
typedef struct s_resolution	t_resolution;
typedef void				(*t_resolve)(t_resolution *);
typedef t_resolve			t_analyzer[ANALYZER_STATES][NB_OF_TOKENS];
typedef struct s_redirect	t_redirect;
typedef struct s_action		t_action;
typedef void				(*t_set_redirect)(t_registry *, t_redirect *, t_action *);
typedef t_set_redirect		t_redirection[REDIRECT_ACTION];

struct					s_redirect
{
	char				*file;
	int32_t				from;
	int32_t				to;
	uint16_t			type;
};

struct					s_action
{
	enum e_actions		type;
	t_list				*data;
};

typedef	struct			s_command
{
	t_list				*av;
	t_list				*actions;
}						t_command;

typedef struct			s_group
{
	uint8_t				group_type;
	t_list				*command_list;
}						t_group;

typedef struct			s_process
{
	char				**av;
	t_list				*env;
	t_list				*redirects;
	uint8_t				process_type;
	uint8_t				completed;
	uint8_t				stopped;
	pid_t				pid;
	pid_t				*pgid;
	int					status;
}						t_process;

typedef struct			s_job
{
	pid_t				pgid;
	uint8_t				job_type;
	t_list				*processes;
	struct termios		*term_modes;
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
************************ SLE ************************
*****************************************************
*/

typedef struct			s_coord
{
	uint64_t			x;
	uint64_t			y;
}						t_coord;

typedef struct			s_termcaps
{
	char				*ring;
	char				*standout_on;
	char				*standout_off;
	char				*clear;
	char				*down;
	char				*right;
	char				*left;
	char				*up;
}						t_termcaps;

typedef struct			s_prompt
{
	uint64_t			length;
	t_vector			*text;
	char				*state;
	char				*missing_char;
}						t_prompt;

typedef struct			s_cursor
{
	uint64_t			x;
	uint64_t			y;
	uint64_t			index;
}						t_cursor;

typedef struct			s_window
{
	uint32_t			rows;
	uint32_t			cols;
	uint32_t			rd_flag;
	uint64_t			max_chars;
	uint64_t			point_cursor;
	uint64_t			point1;
	uint64_t			point2;
	t_vector			*displayed_line;
}						t_window;

typedef struct 			s_redrawinfo
{
	uint64_t			line_len;
	uint64_t			disp_len;
	uint64_t			prompt_len;
	uint64_t			lines_amount;

}						t_redrawinfo;

typedef struct 			s_intern
{
	t_vector			*ps1;
	t_vector			*ps2;
	t_vector			*ps3;
	t_vector			*pwd;
	t_vector			*username;
	t_vector			*home;
}						t_intern;

typedef struct			s_sle
{
	struct termios		*term_mode;
	struct termios		*orig_mode;
	t_termcaps			termcaps;
	t_window			window;
	t_prompt			prompt;
	t_cursor			cursor;
	t_redrawinfo		rd_info;
	uint64_t			ak_masks[AK_AMOUNT];
	int8_t				(*actionkeys[AK_AMOUNT])(struct s_sle *sle);
	t_vector			*line;
	t_vector			*sub_line;

	t_intern			interns;

	//visual mode
	uint8_t				visual_mode;
	int64_t				vis_start;
	int64_t				vis_stop;

	t_vector			*clip;
}						t_sle;

/*
*****************************************************
********************** BUILTIN **********************
*****************************************************
*/

typedef int				(*t_builtin) (t_registry *, char **);
typedef t_option		(*t_get_option)(char *s, t_option option);

/*
*****************************************************
********************** RESOLVE **********************
*****************************************************
*/

extern t_list			*g_job_head;

#endif
