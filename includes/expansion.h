/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 02:50:56 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/21 11:01:15 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "struct.h"

#define DEFAULT_BUFFER 64

# define PEX_STATES 4
# define PEX_PARAM_INTERUPT " ${}:-?=+%#\"\'"
# define PEX_VALID_DELIM " ${:-?=+%#"
# define PEX_FIRST_DELIM " ${}-?=+%#"
# define PEX_NEXT_DELIM " ${}?=+%#"

/* ********************** ARITHMETIC *********************/
# define MATH_STATES		16

# define HEXA_CHARSET 		"0123456789abcdefABCDEF"
# define OCTAL_CHARSET		"012345678"
# define SIGN_SET			"+-*/%()"
# define SINGLE_SIGN_SET  	"*/%()"
# define LOGICAL_SET		"<>=!&|"

# define TIMES		0x001
# define DIVIDE		0x002
# define MODULO		0x004
# define ADD		0x008
# define SUBST		0x010
# define HIGH		0x020
# define LOW		0x040
# define LEFT_P		0x080
# define RIGHT_P	0x100

# define OPENED 	0x002
# define CLOSED 	0x004
# define FAIL 		0x008
/* ******************************************************/

typedef struct	s_parameter	t_parameter;
typedef void	(*t_paramexp)(t_parameter *);

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
enum				e_mathexp
{
	MATH_START,
	MATH_DECIMAL,
	MATH_OCTAL,
	MATH_HEXA,
	MATH_SIGN,
	MATH_LOGICAL,
	MATH_VARIABLE,
	MATH_OUT,
	MATH_END,
};

enum			e_mathtype
{
	TYPE_DECIMAL,
	TYPE_OCTAL,
	TYPE_HEXA,
	TYPE_VARIABLE,
	TYPE_TIME,
	TYPE_DIVIDE,
	TYPE_MODULO,
	TYPE_ADD,
	TYPE_SUBSTRACT,
	TYPE_OPEN_P,
	TYPE_CLOSE_P,
	TYPE_INCREMENT,
	TYPE_DECREMENT,
	TYPE_GREATER,
	TYPE_GREATER_OR,
	TYPE_LOWER,
	TYPE_LOWER_OR,
	TYPE_EQUAL,
	TYPE_NOT_EQUAL,
	TYPE_ASSIGN,
	TYPE_AND,
	TYPE_OR,
	TYPE_ERROR,
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


int			parameter_expansion(t_list *intern, char **dest, int i);
int			parameter_get(t_list *intern, t_parameter *parameter);
int			parameter_parse(t_list *intern, t_parameter *parameter);
void		parameter_lexer(t_parameter *parameter);
void		generate_pex_token(t_parameter *param);
void		pex_word(t_parameter *param);

/* ********************** ARITHMETIC *********************/

char		*arithmetic_expansion(t_list *intern, char *input);

/* ******************************************************/

#endif
