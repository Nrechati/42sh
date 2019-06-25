/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 02:50:56 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/25 09:32:34 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "struct.h"

# define COLON_ON			0x1
# define LONGEST_ON			0x2
# define PEX_STATES 		4
# define PEX_DELIMITERS 	12
# define PEX_ADVANCED_EXP 	6
# define PEX_SPECIAL		"$0?-"
# define PEX_PARAM_INTERUPT " ${}:-?=+%#\"\'"
# define PEX_VALID_DELIM " :-?=+%#"
# define PEX_FIRST_DELIM " {}-?=+%#"
# define PEX_NEXT_DELIM " ${}?=+%#"
# define DEFAULT_PEX_BUFFER 64

typedef struct	s_parameter	t_parameter;
typedef void	(*t_paramexp)(t_parameter *);
typedef int		(*t_advanced_pex)(t_list *, t_parameter *);

typedef struct	s_arithmetic t_arithmetic;
typedef void	(*t_mathexp)(t_arithmetic *);

enum	e_paramexp
{
	PEX_PARAM,
	PEX_DELIM,
	PEX_WORD,
	PEX_END
};

typedef struct	s_pex_token
{
	enum e_paramexp	type;
	char			*data;
}				t_pex_token;

struct	s_parameter
{
	t_vector		*buffer;
	t_list			*tokens;
	char			*expanded;
	char			*source;
	size_t			index;
	uint8_t			modifier;
	enum e_paramexp	state;
};

/* ********************** ARITHMETIC *********************/

#define	DEFAULT_BUFFER	32

enum e_mathexp
{
	MATH_START,
	MATH_DECIMAL,
	MATH_OCTAL,
	MATH_HEXA,
	MATH_VARIABLE,
	MATH_SIGN,
	MATH_LOGICAL,
	MATH_OUT,
	MATH_END,
};

enum e_mathtype
{
	TYPE_UNKNOWN,			//0
	TYPE_DECIMAL,			//1
	TYPE_OCTAL,				//2
	TYPE_HEXA,				//3
	TYPE_VARIABLE,			//4
	TYPE_TIME,				//5
	TYPE_DIVIDE,			//6
	TYPE_MODULO,			//7
	TYPE_ADD,				//8
	TYPE_SUBSTRACT,			//9
	TYPE_OPEN_P,			//10
	TYPE_CLOSE_P,			//11
	TYPE_INCREMENT,			//12
	TYPE_DECREMENT,			//13
	TYPE_GREATER,			//14
	TYPE_GREATER_OR,		//15
	TYPE_LOWER,				//16
	TYPE_LOWER_OR,			//17
	TYPE_EQUAL,				//18
	TYPE_NOT_EQUAL,			//19
	TYPE_ASSIGN,			//20
	TYPE_AND,				//21
	TYPE_OR,				//22
	TYPE_ERROR,				//23
};

enum				e_rpn
{
	RPN_OPERATOR,
	RPN_BRACKET,
	RPN_NUMBER,
};

typedef union 		u_value
{
	int64_t			digit;
	uint16_t		type;
}					t_value;

typedef struct		s_math
{
	enum e_mathtype	type;
	char			*value;
}					t_math;

typedef struct		s_rpn_tk
{
	enum e_rpn		token;
	t_value			value;
}					t_rpn_tk;

struct	s_arithmetic
{
	t_vector		*buffer;
	t_list			*tokens;
	char			*expanded;
	char			*source;
	size_t			index;
	uint8_t			modifier;
	enum e_mathexp	state;
	enum e_mathtype type;
};
/* ******************************************************/

char		*expansion_pipeline(t_list *intern_var, char *str);
char		*expand_string(t_list *lst, char *str);
char		*tilde(t_list *intern_var, char *str);
char		*variable_expansion(t_list *intern_var, char *str);
void		quote_removal(char *str);
char		character_swap(char swapped);
t_quote		select_quoting(t_quote quote, char c);
int			check_backslash(char *dest, t_quote quote, int i);


int			parameter_expansion(t_list *intern, char **dest, int i);
int			parameter_get(t_list *intern, t_parameter *parameter);
int			parameter_parse(t_list *intern, t_parameter *parameter);
void		parameter_lexer(t_parameter *parameter);
void		generate_pex_token(t_parameter *param);
void		pex_word(t_parameter *param);
int			get_delimiter(t_parameter *param, t_pex_token *token);
int			prefix_expansion(t_list *intern, t_parameter *param);
int			suffix_expansion(t_list *intern, t_parameter *param);
int			replace_expansion(t_list *intern, t_parameter *param);
int			exists_expansion(t_list *intern, t_parameter *param);
int			assign_expansion(t_list *intern, t_parameter *param);
int			default_expansion(t_list *intern, t_parameter *param);
void		parameter_print_debug(t_list *token_list);

char		*arithmetic_expansion(t_list *intern, char *input);

#endif
