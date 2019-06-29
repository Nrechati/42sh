/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nrechati <Nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 02:50:56 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/29 21:59:19 by cempassi         ###   ########.fr       */
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
# define PEX_VALID_DELIM 	" :-?=+%#"
# define PEX_FIRST_DELIM 	" {}-?=+%#"
# define PEX_NEXT_DELIM 	" ${}?=+%#"
# define DEFAULT_PEX_BUFFER 64
# define EXPANDED_PARAM		0x01
# define EMPTY_PARAM		0x02

typedef struct s_parameter	t_parameter;
typedef void				(*t_paramexp)(t_parameter *);
typedef int					(*t_advanced_pex)(t_list *, t_parameter *, int);

enum						e_paramexp
{
	PEX_PARAM,
	PEX_DELIM,
	PEX_WORD,
	PEX_END
};

typedef struct				s_pex_token
{
	enum e_paramexp			type;
	char					*data;
}							t_pex_token;

struct						s_parameter
{
	t_vector				*buffer;
	t_list					*tokens;
	char					*expanded;
	char					*source;
	size_t					index;
	uint8_t					modifier;
	enum e_paramexp			state;
};

/*
********************** ARITHMETIC *********************
*/
# define MATH_TOKEN			NB_OF_MTOKENS
# define MATH_STATE			13
# define OCTAL_BASE			"012345678"
# define HEX_BASE			"0123456789ABCDEF"
# define DEC_BASE			"0123456789"

# define PRECEDENCE			0xffff0000
# define OPERATOR			0x0000ffff

# define AND 				0x00010001
# define OR 				0x00010002
# define DIFF				0x00020004
# define EQUAL				0x00020008

# define LESSEQ				0x00020010
# define GREATEQ			0x00020020
# define LESS				0x00020040
# define GREAT				0x00020080

# define PLUS				0x00040100
# define MINUS				0x00040200
# define TIMES				0x00080400
# define DIVIDE				0x00080800

# define MODULO				0x00081000
# define UNARY_PLUS			0x00102000
# define UNARY_MINUS		0x00104000

# define PRE_INCRE			0x08010000
# define POST_INCRE			0x08020000
# define PRE_DECRE			0x08040000
# define POST_DECRE			0x08080000
# define OPEN_P				0x10100000
# define CLOSE_P			0x10200000


typedef struct s_arithmetic	t_arithmetic;
typedef void				(*t_arithmexp)(t_arithmetic *);
typedef t_arithmexp			t_ar_analyzer[MATH_STATE][MATH_TOKEN];
typedef enum e_mathstate	t_mathstate;

enum						e_mathstate
{
	MATH_START,
	MATH_NUMBER,
	MATH_UNARY,
	MATH_OPERATOR,
	MATH_LOGICAL_OPERATOR,
	MATH_PREFFIX,
	MATH_SUFFIX,
	MATH_VARIABLE,
	MATH_VARIABLE_FLUSH,
	MATH_OPEN_PARENT,
	MATH_CLOSE_PARENT,
	MATH_ERROR,
	MATH_END
};

enum						e_rpn
{
	RPN_OPERATOR,
	RPN_PARENT_OPEN,
	RPN_PARENT_CLOSE,
	RPN_NUMBER,
};

typedef union				u_value
{
	int64_t					digit;
	uint64_t				type;
}							t_value;

typedef struct				s_rpn_tk
{
	enum e_rpn				type;
	t_value					value;
}							t_rpn_tk;

typedef struct				s_infix
{
	uint8_t					type;
	int64_t					result;
	t_stack					calcul;
}							t_infix;

struct						s_arithmetic
{
	t_vector				*input;
	t_list					*tokens;
	t_list					*current;
	t_token					*curr_token;
	t_stack					compare;
	t_stack					processing;
	t_stack					sign;
	t_list					*solving;
	int						parenthesis;
	t_mathstate				state;
	char					*expanded;
	size_t					end;
};

typedef struct				s_math
{
	t_vector				*input;
	t_list					*tokens;
	t_token					*current_token;
	t_stack					sign;
	t_stack					operand;
	char					*expanded;
}							t_math;

/*
************************* FUNCTIONS *****************************
*/

char						*expansion_pipeline(t_list *intern_var, char *str);
char						*expand_string(t_list *lst, char *str);
char						*tilde(t_list *intern_var, char *str);
char						*variable_expansion(t_list *intern_var, char *str);
void						quote_removal(char *str);
char						character_swap(char swapped);
t_quote						select_quoting(t_quote quote, char c);
int							check_backslash(char *dest, t_quote quote, int i);

int							parameter_expansion(t_list *intern, char **dest
													, int i);
int							parameter_get(t_list *intern
													, t_parameter *parameter);
int							parameter_parse(t_list *intern
													, t_parameter *parameter);
void						parameter_lexer(t_parameter *parameter);
void						generate_pex_token(t_parameter *param);
void						pex_word(t_parameter *param);
int			replace_expansion(t_list *intern, t_parameter *param, int mode);
int			exists_expansion(t_list *intern, t_parameter *param, int mode);
int			assign_expansion(t_list *intern, t_parameter *param, int mode);
int			default_expansion(t_list *intern, t_parameter *param, int mode);
int			prefix_expansion(t_list *intern, t_parameter *param, int mode);
int			suffix_expansion(t_list *intern, t_parameter *param, int mode);

int							get_delimiter(t_parameter *param
													, t_pex_token *token);

char						*arithmetic_expansion(t_list *intern, char *input);
int8_t						arithmetic_analyzer(t_arithmetic *arithmetic);
void						m_number_analyzer(t_arithmetic *arithmetic);
void						m_unary_analyzer(t_arithmetic *arithmetic);
void						m_operator_analyzer(t_arithmetic *arithmetic);
void						m_logical_operator(t_arithmetic *arithmetic);
void						m_preffix(t_arithmetic *arithmetic);
void						m_suffix(t_arithmetic *arithmetic);
void						m_parenthesis_analyzer(t_arithmetic *arithmetic);
void						m_variable_analyzer(t_arithmetic *arithmetic);
void						m_flush_variable_analyzer(t_arithmetic *arithmetic);
void						m_error_analyzer(t_arithmetic *arithmetic);
void						m_end_analyzer(t_arithmetic *arithmetic);

void						convert_plus_minus(t_token *token
													, t_rpn_tk *current);
void						m_get_token(t_arithmetic *arithmetic
													, t_list **node);
void						del_infix(t_infix *infix);

int8_t						calculator(t_infix *infix);
uint8_t						need_pop_operator(t_rpn_tk *curr
													, t_stack *operator);
uint8_t						is_left_p(t_stack *operator);
int8_t						ft_shunting_yds(t_stack *infix, t_stack *rpn);
int8_t						calculate_rpn(t_stack *rpn, t_infix *infix);
void						do_logical(t_rpn_tk *first, t_rpn_tk *second
													, t_rpn_tk *curr);
void						do_compare(t_rpn_tk *first, t_rpn_tk *second
													, t_rpn_tk *curr);
void						do_high_op(t_rpn_tk *first, t_rpn_tk *second
													, t_rpn_tk *curr);
void						do_low_op(t_rpn_tk *first, t_rpn_tk *second
													, t_rpn_tk *curr);
void						do_unary(t_rpn_tk *number, t_rpn_tk *curr);

t_ar_analyzer				*init_math_analyzer(void);

#endif
