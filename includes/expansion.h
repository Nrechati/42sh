/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 02:50:56 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/25 17:17:14 by nrechati         ###   ########.fr       */
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

#define	MATH_TOKEN		22
#define	MATH_STATE		4
#define OCTAL_BASE		"012345678"
#define HEX_BASE		"0123456789ABCDEF"
#define DEC_BASE		"0123456789"

# define TIMES        0x001
# define DIVIDE        0x002
# define MODULO        0x004
# define PLUS       0x008
# define MINUS        0x010
# define HIGH        0x020
# define LOW        0x040
# define LEFT_P        0x080
# define RIGHT_P    0x100

typedef struct	s_arithmetic t_arithmetic;
typedef void	(*t_arithmexp)(t_arithmetic *);
typedef t_arithmexp	 t_ar_analyzer[MATH_STATE][MATH_TOKEN];
typedef enum e_mathstate	t_mathstate;

enum				e_mathstate
{
	MATH_START,
	MATH_NUMBER,
	MATH_OPERATOR,
	MATH_VARIABLE,
	MATH_OPEN_PARENT,
	MATH_CLOSE_PARENT,
	MATH_PLUS,
	MATH_MINUS,
	MATH_STOP,
	MATH_ERROR,
	MATH_END
};

enum				e_rpn
{
	RPN_OPERATOR,
	RPN_PARENTHESIS,
	RPN_NUMBER,
};

typedef union 		u_value
{
	int32_t			digit;
	uint16_t		type;
}					t_value;

typedef struct		s_rpn_tk
{
	enum e_rpn		type;
	t_value			value;
}					t_rpn_tk;

typedef struct		s_infix
{
	uint8_t			type;
	int32_t			result;
	t_stack			calcul;
}					t_infix;

struct				s_arithmetic
{
	t_vector		*input;
	t_list			*tokens;
	t_list			*current;
	t_token			*curr_token;
	t_stack			processing;
	t_list			*solving;
	t_mathstate		state;
	char			*expanded;
	size_t			end;
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
t_list		*arithmetic_analyzer(t_arithmetic *arithmetic);
void		m_error_analyzer(t_arithmetic *arithmetic);
void		m_number_analyzer(t_arithmetic *arithmetic);
void		m_operator_analyzer(t_arithmetic *arithmetic);
void		m_parenthesis_analyzer(t_arithmetic *arithmetic);
void		m_variable_analyzer(t_arithmetic *arithmetic);
void		m_plus_minus_analyzer(t_arithmetic *arithmetic);
void		m_end_analyzer(t_arithmetic *arithmetic);

int8_t			arithmetic_calculator(t_infix *infix);
uint8_t		need_pop_operator(t_rpn_tk *curr, t_stack *operator);
uint8_t		is_left_p(t_stack *operator);
int8_t			ft_shunting_yds(t_stack *infix, t_stack *rpn);
int32_t			calculate_rpn(t_stack *rpn);

t_ar_analyzer	*init_math_analyzer(void);


#endif
