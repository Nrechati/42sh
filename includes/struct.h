/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:25:34 by ffoissey          #+#    #+#             */
/*   Updated: 2019/06/28 19:53:03 by cempassi         ###   ########.fr       */
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

typedef uint64_t		t_option;

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

typedef	struct			s_hashmap
{
	t_hash				bin;
	t_hash				blt;
}						t_hashmap;

typedef struct			s_registry
{
	const char			**grammar;
	const char			**grammar_m;
	t_list				*intern;
	t_opt				option;
	t_hashmap			hash;

	pid_t				pid;

	t_list				*job_list;
	uint64_t			active_jobs;
	t_list				*current_plus;
	t_list				*current_minus;

	uint8_t				sigint;

	struct termios		*sle_mode;
	struct termios		*exec_mode;
	struct termios		*orig_mode;
}						t_registry;

extern t_registry		*g_shell;

/*
*****************************************************
*********************** LEXER ***********************
*****************************************************
*/

typedef struct			s_token
{
	char				*data;
	int					type;
}						t_token;

typedef struct			s_lexer
{
	t_list				*tokens;
	t_vector			*buffer;
	t_vector			*input;
	size_t				index;
	enum e_lexer_state	state;
	enum e_mtype		last_token_mtype;
	enum e_type			token_type;
	enum e_mtype		token_mtype;
	uint32_t			parenthesis;
	uint16_t			inhibitor;
	uint8_t				assignation;
}						t_lexer;

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
	uint8_t				type;
}						t_command;

typedef struct			s_group
{
	uint8_t				type;
	t_list				*command_list;
}						t_group;

typedef struct			s_process
{
	char				**av;
	t_list				*env;
	t_list				*redirects;
	uint32_t			process_type;
	pid_t				pid;
	pid_t				*pgid;
	int					status;
	uint8_t				completed;
	uint8_t				stopped;
}						t_process;

typedef struct			s_job
{
	pid_t				pgid;			/* Job process group id */
	t_list				*processes;		/* Job process list		*/
	uint8_t				state;			/* RUNNING | PENDING */
	uint8_t				job_type;
	uint32_t			signo;

	uint64_t			id;
	char				current;

	struct termios		*term_modes;	/* Saved termios mode 	*/
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

extern t_job 			*g_current_job;

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
	char				*clear_line;
	char				*clear_screen;
	char				*standout_on;
	char				*standout_off;
	char				*clear;
	char				*down;
	char				*right;
	char				*left;
	char				*up;
	char				*hidden_cursor;
	char				*normal_cursor;
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
	uint64_t			x2;
	uint64_t			y2;
	uint64_t			x3;
	uint64_t			y3;
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
	uint8_t				state;

	t_termcaps			termcaps;
	t_window			window;
	t_prompt			prompt;
	t_cursor			cursor;

	t_redrawinfo		rd_info;
	uint64_t			ak_masks[AK_AMOUNT];
	int8_t				(*actionkeys[AK_AMOUNT])(t_registry *shell, struct s_sle *sle);
	t_vector			*line;
	t_vector			*sub_line;

	t_intern			interns;

	t_vector			*line_save;

	t_vector			*search_line;
	uint16_t			search_type;

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

/*
*****************************************************
********************** HISTORY **********************
*****************************************************
*/

typedef	struct	s_entry	t_entry;

typedef struct	s_param
{
	int		first;
	int		last;
	int		fd;
}				t_param;

struct			s_entry
{
	t_entry		*next;
	t_entry		*prev;
	char		*cmd;
};

typedef struct	s_history
{
	t_entry		*entry;
	t_entry		*head_ptr;
	int			nb_of_entries;
	int			first_search;
}				t_history;

#endif
