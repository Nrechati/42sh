/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:33:26 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/26 21:33:55 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

/*
*****************************************************
********************** BUILTIN **********************
*****************************************************
*/

enum	e_state_option
{
	E_START_OPTION,
	E_OPTION,
	E_END_OPTION,
	E_NO_OPTION
};

/*
*****************************************************
*********************** LEXER ***********************
*****************************************************
*/

enum	e_lexer_state
{
	L_PROCESS,
	L_OUT,
	L_FINISH
};

typedef enum	e_type
{
	E_DB_QUOTE,
	E_PIPE,
	E_PARENT_OPEN,
	E_PARENT_CLOSE,
	E_GREAT,
	E_LESS,
	E_SEMICOLON,
	E_BACKQUOTE,
	E_AND,
	E_HOOK_OPEN,
	E_HOOK_CLOSE,
	E_BRACKET_OPEN,
	E_BRACKET_CLOSE,
	E_HASH,
	E_PERCENT,
	E_NEWLINE,
	E_DAND,
	E_OR,
	E_DSEMI,
	E_DLESS,
	E_DGREAT,
	E_LESSAND,
	E_GREATAND,
	E_LESSGREAT,
	E_ANDDGREAT,
	E_ANDGREAT,
	E_DLESSDASH,
	E_CLOBBER,
	E_DEQ,
	E_NOTEQ,
	E_CASE,
	E_DO,
	E_DONE,
	E_ELIF,
	E_ELSE,
	E_ESAC,
	E_FI,
	E_FOR,
	E_IF,
	E_IN,
	E_THEN,
	E_UNTIL,
	E_WHILE,
	E_IO_NUMBER,
	E_ASSIGN,
	E_STRING,
	E_SPSTRING,
	E_END,
	E_ERROR,
	E_DEFAULT,
}				t_type;

typedef enum	e_mtype
{
	E_M_TIMES,
	E_M_DIVIDE,
	E_M_MODULO,
	E_M_PLUS,
	E_M_MINUS,
	E_M_OPENP,
	E_M_CLOSEP,
	E_M_LESS,
	E_M_LESSEQ,
	E_M_GREAT,
	E_M_GREATEQ,
	E_M_EQUAL,
	E_M_NEQUAL,
	E_M_AND,
	E_M_OR,
	E_M_DPLUS,
	E_M_DMINUS,
	E_M_ASSIGN,
	E_M_STRING,
	E_M_NB_DEC,
	E_M_NB_OCT,
	E_M_NB_HEX,
	E_M_DELIMITER,
	E_M_END,
	E_M_DEFAULT
}				t_mtype;

/*
*****************************************************
********************** ANALYZER *********************
*****************************************************
*/

typedef enum	e_quote
{
	QUOTE_OFF,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
	QUOTE_BACKSLASH,
}				t_quote;

enum e_actions
{
	A_STDOUT_TRUNCATE_FILE,
	A_STDOUT_APPEND_FILE,
	A_STDIN_READ_FILE,
	A_IO_TRUNCATE_FILE,
	A_IO_APPEND_FILE,
	A_IO_READ_FILE,
	A_DUP,
	A_CLOSE,
	A_MOVE,
	A_HEREDOC,
	A_HEREDOC_TRIM,
	A_IO_HEREDOC,
	A_IO_HEREDOC_TRIM,
	A_AMBIGOUS_REDIRECT,
	A_ARGS,
	A_ASSIGN,
	A_DAND,
	A_OR,
	A_END,
};

enum	e_analyzer_state
{
	P_START,
	P_END,
	P_STOP,
	P_ERROR,
	P_STRING,
	P_SPSTRING,
	P_STRING_FLUSH,
	P_SEPARATOR,
	P_REDIRECT,
	P_REDIRECT_AND,
	P_DUP_MOVE,
	P_REDIRECT_FLUSH,
	P_REDIRECT_FLUSH_AND,
	P_FILENAME,
	P_SPFILENAME,
	P_IO,
	P_IO_REDIRECT,
	P_IO_REDIRECT_AND,
	P_IO_FILENAME,
	P_IO_DUP_MOVE,
	P_IO_FLUSH,
	P_IO_FLUSH_AND,
	P_PIPE,
	P_HEREDOC,
	P_HEREDOC_REDIRECT,
	P_HEREDOC_DELIMITER,
	P_IO_HEREDOC,
	P_IO_HEREDOC_REDIRECT,
	P_IO_HEREDOC_DELIMITER,
	P_ASSIGN_NAME,
	P_ASSIGN_DATA,
	P_ASSIGN_FLUSH,
};

/*
*****************************************************
************************ SLE ************************
*****************************************************
*/

enum	prompt_type
{
	PRINT_PIPE,
	PRINT_QUOTE,
	PRINT_DQUOTE,
	PRINT_BQUOTE,
	PRINT_NL,
	PRINT_AND,
	PRINT_OR,
	PRINT_BRACE,
	PRINT_MATHS
};

enum	e_action_keys
{
	AK_ARROW_UP,
	AK_ARROW_DOWN,
	AK_ARROW_RIGHT,
	AK_ARROW_LEFT,
	AK_HOME,
	AK_END,
	AK_CTRL_A,
	AK_CTRL_E,
	AK_BACKSPACE,
	AK_DELETE,
	AK_CTRL_LEFT,
	AK_CTRL_RIGHT,
	AK_CTRL_DOWN,
	AK_CTRL_UP,
	AK_CTRL_D,
	AK_CTRL_L,
	AK_ESCAPE,
	AK_CTRL_F,
	AK_CTRL_B,
	AK_CTRL_X,
	AK_CTRL_P,
	AK_CTRL_R,
	AK_CTRL_T,
	AK_TABULATION,
};

#endif
