/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:31:20 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/01 13:40:22 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H


///// LINUX /////
# ifndef __unused
#  define __unused __attribute__((unused))
# endif
/////////////////

/*
*****************************************************
******** -------------- COMMON -------------- *******
*****************************************************
*/

# define NOT_FOUND					-2
# define FAILURE					-1
# define SUCCESS					0

# define FALSE						0
# define TRUE						1
# define ERROR						2

# define SH_GENERAL_ERROR			"42sh: "
# define SH_MALLOC_ERROR			"[CRITICAL] Malloc ERROR\n"

# define SH42_USAGE_1				"Usage: 42sh [long option] [-dh] "
# define SH42_USAGE_2				"[-c CMD]\n"
# define SH42_USAGE_LONG_OPTION		"\n\t--help\n\t"
# define SH42_USAGE_LONG_OPTION_2	"--debug\n"

# define NO_OPT						0x0000
# define HELP_OPT					0x0001
# define COMMAND_OPT				0x0002
# define DEBUG_OPT					0x0004
# define INTERACTIVE_OPT			0x0008
# define RECORD_HISTORY_OPT			0x0010
# define GARBAGE_COLLECTOR_OPT		0x0020

# define NO_FLAG					0x0000
# define EXPORT_VAR					0x0001
# define SET_VAR					0x0002
# define READONLY_VAR				0x0004

# define HMAP_BIN_SIZE				8
# define HMAP_BLT_SIZE				32

# define SET_TERM					0
# define RESTORE_TERM				1

/*
*****************************************************
********************* TERMMODES *********************
*****************************************************
*/

# define TERMMODE_INIT  0x00
# define TERMMODE_DFLT  0x01
# define TERMMODE_SLE   0x02
# define TERMMODE_EXEC  0x04

/*
********************** SIGNALS **********************
*****************************************************
*/

# define NB_SIGNALS		33
# define INIT_HANDLER 	0x000
# define DFLT_PROFILE 	0x001
# define SLE_PROFILE	0x002
# define EXEC_PROFILE	0x004

/*
*****************************************************
********************** BUILTIN **********************
*****************************************************
*/

# define TEST_HASH_SIZE				32
# define EXIT_FALSE					1
# define EXIT_TRUE					0
# define UNARY_OP					1
# define BINARY_OP					2

# define A_OPT						0x0001
# define E_OPT						0x0002
# define F_OPT						0x0004
# define I_OPT						0x0008
# define L_OPT						0x0010
# define N_OPT						0x0020
# define P_OPT						0x0040
# define R_OPT						0x0080
# define S_OPT						0x0100
# define T_OPT						0x0200
# define P_LOW_OPT					0x0400
# define ERROR_OPT					0x8000
# define CD_USAGE 					"cd: usage: cd [-L|-P] [dir]\n"
# define CD_ERROR_OLDPWD_NOTSET		"42sh: cd: OLDPWD not set\n"
# define NOFI 						"No such file or directory\n"
# define EXPORT_USAGE 				"export: usage: export name[=value] ..."
# define UNSET_USAGE 				"unset: usage: unset name\n"
# define FC1 						"fc: usage: fc [-e ename]"
# define FC2 						" [-lnr] [first] [last]"
# define FC3 						"fc -s [pat=rep] [command]\n"
# define FC_E 						"42sh: fc: -e: option requires an argument"

/*
*****************************************************
*********************** HASH ************************
*****************************************************
*/

# define H_WIPE						0x001
# define H_ALL						0x002
# define H_HELP						0x004
# define HASH_GENERAL_ERROR			"42sh: hash: "
# define HASH_MALLOC_ERROR			"[CRITICAL] Malloc ERROR\n"
# define HASH_HIT_ERROR				"error hitting bin\n"
# define HASH_INVALID_OPT			": invalid option\n"
# define HASH_NO_AV					"NULL av given to built-in\n"
# define HASH_NOT_FOUND				": not found\n"
# define HASH_USAGE 				"hash: usage: hash [-ar] [utility ...]\n"
# define HASH_HELP  				"hash: help:\n"
# define HASH_H_WIPE				"\t-r: wipe all hashmap content\n"
# define HASH_H_ALL					"\t-a: wipe all and hash all PATH\n"
# define HASH_H_HELP				"\t-h: print HELP and stop builtin\n"
# define HASH_ORULE_1				"\t[overrules]: -h overrules -a "
# define HASH_ORULE_2				"and -a overrules -r\n"
# define HASH_OPT_1					"\t[usage]: options must be specified "
# define HASH_OPT_2					"before utilities regardless of order\n"
# define HASH_UTIL_1				"\t[utility]: add utility=/utility/path/"
# define HASH_UTIL_2				"name to hashmap\n"

/*
*****************************************************
********************* INTERNALS *********************
*****************************************************
*/

# define IFS_CHAR					10
# define READ_SIZE					8
# define CLIPBOARD_SZ				32

# define INT_TERM					"TERM"
# define INT_TERM_DFLT_VALUE		"dumb"

# define INT_DBG_FD					"DEBUG_FD"
# define INT_DBG_FILE				".42sh.log"

# define INT_ROWS					"ROWS"
# define INT_COLS					"COLS"

# define INT_PS1					"PS1"
# define INT_PS2					"PS2"
# define INT_PS3					"PS3"

//#define INT_PS1_VALUE "[42sh]-> "
# define INT_PS1_VALUE				"[\\e[32m42sh\\e[0m][\\e[31m\\u\\e[0m@\\e[2;33m\\h\\e[0m][\\e[34m\\w\\e[0m]-> "
# define INT_PS2_VALUE				"[\\e[31m\\u\\e[0m@\\e[33m\\h\\e[0m](\\m)> "
# define INT_PS3_VALUE				"(\\e[31mheredoc\\e[0m)> "


/*
*****************************************************
*********************** LEXER ***********************
*****************************************************
*/

# define SHELL						0x01
# define MATHS						0x02

# define CUR_CHAR					0x01
# define NEXT_CHAR					0x02
# define NEXT_NEXT_CHAR				0x04

/*
** SHELL
*/

# define NB_OF_TOKENS				49
# define NB_OF_MTOKENS				24

# define START_OPERATOR				27
# define END_OPERATOR				1
# define START_RESERVED_WORD		42
# define END_RESERVED_WORD			30

# define NO_FLAG					0x0000
# define BACKSLASH_FLAG				0x0001
# define SINGLEQUOTE_FLAG			0x0002
# define DOUBLEQUOTE_FLAG			0x0004
# define BRACEPARAM_FLAG			0x0008
# define MATHS_FLAG					0x0010

# define POSSIBLE					0
# define IMPOSSIBLE					1
# define LISTEN						2

/*
** MATHS
*/

/*
*****************************************************
********************* EXPANSION *********************
*****************************************************
*/

# define EXP_INTERUPT				" \\\t\'\"`$/"
# define EXP_CHECK					" \\\t\'\"`/"
# define BACKSLASH_DQUOTE			"\\$\"\n"
# define EXP_SPECIAL				"$0?"

/*
*****************************************************
********************** PARSER ***********************
*****************************************************
*/

# define REDIR						E_GREAT, E_LESS
# define REDIR_AND					E_GREATAND, E_LESSAND, E_ANDGREAT
# define REDIR_DB					E_DGREAT, E_DLESS, E_DLESSDASH, E_ANDDGREAT
# define ALL_REDIRECT				REDIR, REDIR_DB, REDIR_AND
# define WORD						E_STRING, E_DB_QUOTE
# define END_CMD					E_NEWLINE, E_END, E_SEMICOLON
# define E_START					E_DEFAULT

/*
*****************************************************
********************* GRAMMAR ***********************
*****************************************************
*/

/*
** SHELL GRAMMAR
*/

# define N_DB_QUOTE					"\""
# define N_PIPE						"|"
# define N_PARENT_OPEN				"("
# define N_PARENT_CLOSE				")"
# define N_GREAT					">"
# define N_LESS						"<"
# define N_SEMICOLON				";"
# define N_BACKQUOTE				"`"
# define N_AND						"&"
# define N_HOOK_OPEN				"{"
# define N_HOOK_CLOSE				"}"
# define N_BRACKET_OPEN				"["
# define N_BRACKET_CLOSE			"]"
# define N_HASH						"#"
# define N_PERCENT					"%"
# define N_NEWLINE					"\n"
# define N_DAND						"&&"
# define N_OR						"||"
# define N_DSEMI					";;"
# define N_DLESS					"<<"
# define N_DGREAT					">>"
# define N_LESSAND					"<&"
# define N_GREATAND					">&"
# define N_LESSGREAT				"<>"
# define N_ANDDGREAT				"&>>"
# define N_ANDGREAT					"&>"
# define N_DLESSDASH				"<<-"
# define N_CLOBBER					">|"
# define N_DEQ						"=="
# define N_NOTEQ					"!="
# define N_CASE						"case"
# define N_DO						"do"
# define N_DONE						"done"
# define N_ELIF						"elif"
# define N_ELSE						"else"
# define N_ESAC						"esac"
# define N_FI						"fi"
# define N_FOR						"for"
# define N_IF						"if"
# define N_IN						"in"
# define N_THEN						"then"
# define N_UNTIL					"until"
# define N_WHILE					"while"
# define N_IO_NUMBER				"IO nb"
# define N_ASSIGN					"(=)"
# define N_STRING					"word"
# define N_END						"end"
# define N_ERROR					"ERROR"
# define N_START					"START"

/*
** SHELL MATHS
*/

# define M_TIMES					"*"
# define M_DIVIDE					"/"
# define M_MODULO					"%"
# define M_PLUS						"+"
# define M_MINUS					"-"
# define M_OPENP					"("
# define M_CLOSEP					")"
# define M_LESS						"<"
# define M_LESSEQ					"<="
# define M_GREAT					">"
# define M_GREATEQ					">="
# define M_EQUAL					"=="
# define M_NEQUAL					"!="
# define M_AND						"&&"
# define M_OR						"||"
# define M_DPLUS					"++"
# define M_DMINUS					"--"
# define M_ASSIGN					"(=)"
# define M_STRING					"word"
# define M_NB_DEC					"nb dec"
# define M_NB_OCT					"nb oct"
# define M_NB_HEX					"nb hex"
# define M_DELIMITER				"blank"
# define M_END						"end"
# define M_START					"START"

/*
*****************************************************
********************** ANALYZER *********************
*****************************************************
*/

# define ANALYZER_STATES			33
# define FD_DUP						0x001
# define FD_MOVE					0x002
# define FD_REDIRECT				0x004
# define FD_CLOSE					0x008
# define FD_CLOSE_SPECIAL			0x010
# define FD_PIPE_IN					0x020
# define FD_PIPE_OUT				0x040
# define FD_OPEN_ERROR				0x080
# define FD_DUP_ERROR				0x100
# define FD_CRITICAL_ERROR			0x200
# define FD_BAD_DESCRIPTOR			0x400
# define FD_AMBIGOUS_REDIRECT		0x800

# define COMMAND_ASSIGN				0x001
# define COMMAND_RUN				0x002

# define GROUP_RUN					0x000
# define GROUP_BG					0x001
# define GROUP_AND					0x002
# define GROUP_OR					0x004

# define QUOTING					0x001
# define HERETRIM					0x002
# define TO_CLOSE					0x004
# define NO_PIPE					0x008
# define VALID_PROCESS				0x010

# define IS_BLT						0x0001
# define IS_BIN						0x0002
# define IS_ABS						0x0004
# define IS_ASSIGN					0x0008
# define IS_NOTFOUND				0x0010
# define IS_OPEN_FAILED				0x0020
# define IS_DUP_FAILED				0x0040
# define IS_CRITICAL				0x0080
# define IS_EXP_ERROR				0x0100
# define IS_ALONE					0x1000

/*
*****************************************************
******************** JOBCONTROL *********************
*****************************************************
*/

# define JOBCTL_PLUS					0x01
# define JOBCTL_MINUS					0x02
# define JOBCTL_LIST					0x01 /* List jobs in bg | Builtin jobs */
# define JOBCTL_LONG					0x02
# define JOBCTL_ID						0x04
# define JOBCTL_PUTINBG					0x08 /* Save job to jobctl module */
# define JOBCTL_PUTINFG					0x10 /* Restore bg job to fg | builtin fg */
# define JOBCTL_RUNINBG					0x20 /* Exec a bg job in bg | builtin bg */

/*
*****************************************************
******************** INTERPRETER ********************
*****************************************************
*/

# define REDIRECT_ACTION			17
# define FREE_INTERPRETER			-1

# define CLOSED_STDIN				0x001
# define CLOSED_STDOUT				0x002
# define CLOSED_STDERR				0x004

# define PENDING					0x00
# define RUNNING					0x01
# define ENDED						0x02
# define KILLED						0x04
# define SUCCEDED					0x08
# define FAILED						0x10
# define STOPPED					0x20

# define TRIM_OFF					0x00
# define TRIM_ON					0x01

# define INTERPRETER_NOT_FOUND		": command not found\n"
# define INTERPRETER_FORK_ERROR		" fork error\n"
# define INTERPRETER_EXECVE_ERROR	" execve fail\n"

/*
*****************************************************
************************ SLE ************************
*****************************************************
*/

# define STATE_STD		0x00
# define STATE_VISUAL	0x01
# define STATE_SEARCH	0x02
# define STATE_AUTOCP	0x04

# define PROMPT_PIPE	"pipe"
# define PROMPT_QUOTE	"quote"
# define PROMPT_DQUOTE	"dquote"
# define PROMPT_BQUOTE	"bquote"
# define PROMPT_NL		"nl"
# define PROMPT_AND		"and"
# define PROMPT_OR		"or"
# define PROMPT_BRACE	"braceparam"
# define PROMPT_MATHS	"mathsubst"

# define SLE_GET_INPUT		0x0100
# define SLE_PS2_PROMPT		0x0200
# define SLE_PS3_PROMPT		0x0400
# define SLE_CC				0x0800
# define SLE_RD_PROMPT		0x1000
# define SLE_SIZE_UPDATE	0x2000
# define SLE_EXIT			0x4000

# define RD_NONE        0x001 /* No redraw at all*/
# define RD_CLEAR       0x002 /* Redraw th entire window*/
# define RD_LINE      	0x004 /* Redraw entire line */
# define RD_LAST        0x008 /* redraw only last char of line vect */
# define RD_FPTP        0x010 /* From point to point (index / t_coord) */
# define RD_FPTE        0x020 /* From point to end */
# define RD_FSTP        0x040 /* From start to point */
# define RD_CEND        0x080 /* Put cursor at end */
# define RD_CHOME       0x100 /* Put cursor at home */
# define RD_CMOVE       0x200 /* Put cursor to point / index */
# define RD_VISUAL		0x400
# define RD_SEARCH      0x800
# define BAD_PERCENTAGE		0x001
# define CRITICAL_ERROR     0x001
# define MALLOC_FAIL        0x002
# define VCT_FAIL           0x004
# define INVALID_TERM       0x008
# define TERMMDE_FAIL       0x010
# define TGETSTR_FAIL       0x020
# define INTERNAL_FAIL      0x040
# define LINE_FAIL          0x080
# define WINDOW_FAIL        0x100
# define CURSOR_FAIL        0x200
# define PRMPT_FAIL         0x400
# define INVALID_TERMCAPS	0x800
# define SETUP_DONE			0x800
# define P_DATE				'd'
# define P_NAME				's'
# define P_USER				'u'
# define P_CWD				'w'
# define P_HOST				'h'
# define P_MISS				'm'
# define P_ESCAPE			'e'

# define FAIL_EOF					42
# define AK_AMOUNT					24

# define AK_ESCAPE_MASK				0x1b00000000000000
# define AK_ARROW_UP_MASK			0x1b5b410000000000
# define AK_ARROW_DOWN_MASK 		0x1b5b420000000000
# define AK_ARROW_RIGHT_MASK		0x1b5b430000000000
# define AK_ARROW_LEFT_MASK 		0x1b5b440000000000
# define AK_HOME_MASK 				0x1b5b480000000000
# define AK_END_MASK 				0x1b5b460000000000
# define AK_CTRL_A_MASK 			0x0100000000000000
# define AK_CTRL_E_MASK		   		0x0500000000000000
# define AK_DELETE_MASK		   		0x1b5b337e00000000
# define AK_BACKSPACE_MASK		 	0x7f00000000000000
# define AK_CTRL_D_MASK 			0x0400000000000000
# define AK_CTRL_L_MASK				0x0c00000000000000
# define AK_CTRL_F_MASK				0x0600000000000000

# define AK_CTRL_X_MASK				0x1800000000000000
# define AK_CTRL_B_MASK				0x0200000000000000
# define AK_CTRL_P_MASK				0x1000000000000000

# define AK_CTRL_R_MASK				0x1200000000000000
# define AK_CTRL_T_MASK				0x1400000000000000
# define AK_CTRL_UP_MASK			0x1b5b313b35410000
# define AK_CTRL_DOWN_MASK			0x1b5b313b35420000
# define AK_CTRL_RIGHT_MASK			0x1b5b313b35430000
# define AK_CTRL_LEFT_MASK			0x1b5b313b35440000
# define AK_TAB_MASK				0x0900000000000000

/*
*****************************************************
************************ LOG ************************
*****************************************************
*/

# define LOG_OK						"[OK]"
# define LOG_INFO 					"[INFO]"
# define LOG_WARNING				"[WARNING]"
# define LOG_ERROR					"[ERROR]"
# define LOG_CRITICAL				"[CRITICAL]"

/*
*****************************************************
********************** HISTORY **********************
*****************************************************
*/
# define REV_SEARCH					"(rev-search)"
# define INC_SEARCH                 "(inc-search)"
# define SEARCH_SUFFIX		        "``:"

# define HISTFILE_DEFAULT			".42sh_history"
# define FC_FILE_TMP				"/tmp/42sh-fc.tmp"
# define HISTSIZE_DEFAULT			500

# define INIT_HISTORY				0x000001
# define FREE_HISTORY				0x000002
# define PRINT_HISTORY				0x000004
# define WRITE_HISTFILE				0x000008
# define ADD_ENTRY					0x000010
# define POP_ENTRY					0x000020
# define GET_ENTRY					0x000040
# define WITHOUT_SPACE				0x000080
# define BY_ID						0x000100
# define BY_NAME					0x000200
# define PRINT_ID					0x000400
# define REVERSE					0x000800
# define REL						0x001000
# define PREV						0x002000
# define NEXT						0x004000
# define RESET_HEAD					0x008000

/*
*****************************************************
*********************** SIGNAL **********************
*****************************************************
*/

# define SSIG_KILL                  9
# define SSIG_INT                   2
# define SSIG_QUIT                  3
# define SSIG_STOP                  19
# define SSIG_SEGV					11
# define SSIG_ABT					6

#endif
