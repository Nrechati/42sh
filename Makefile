# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/26 18:34:36 by ffoissey          #+#    #+#              #
#    Updated: 2019/05/29 18:58:04 by nrechati         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
#								 Build Targets                                 #
# ---------------------------------------------------------------------------- #

NAME = 42sh
NAMEDB = 42shdb
LIBFT = libft.a
LIBFTDB = libftdb.a
SRCS += $(CORE)
SRCS += $(LINE)
SRCS += $(ANALYZER)
SRCS += $(BUILTIN)
SRCS += $(TOOLS)
SRCS += $(EXPANSION)
SRCS += $(LEXER)
SRCS += $(LOGGING)
SRCS += $(PARSER)
SRCS += $(RESOLVE)
OBJS = $(patsubst %.c, $(OPATH)%.o, $(SRCS))
OBJD = $(patsubst %.c, $(OPATH)db%.o, $(SRCS))
LIB = $(addprefix $(LPATH), $(LIBFT))
LIBDB = $(addprefix $(LPATH), $(LIBFTDB))

# ---------------------------------------------------------------------------- #
#									Compiler                                   #
# ---------------------------------------------------------------------------- #

CC = clang
LINK = $(CC)
LINKD = $(CC) -g3
COMPILE = $(CC) -c
DEBUG = $(CC) -g3 -c

# ---------------------------------------------------------------------------- #
#									Commands                                   #
# ---------------------------------------------------------------------------- #

MKDIR = mkdir -p
CLEANUP = rm -rf
PRINT = printf
CLEAR = clear
TOUCH = touch

# ---------------------------------------------------------------------------- #
#									 Output                                    #
# ---------------------------------------------------------------------------- #

# One Line
ONELINE =\e[1A\r

# Colors
NC = \033[0m
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m

# ---------------------------------------------------------------------------- #
#								  Directories                                  #
# ---------------------------------------------------------------------------- #

LPATH = libft/
OPATH = objs/
IPATH += includes/
IPATH += libft/includes/

P_CORE += core/routine/
P_CORE += core/startup/
P_CORE += core/startup/init/
P_CORE += core/signals/

P_LINE += module/interface/
P_LINE += module/interface/prompt
P_LINE += module/interface/action_keys/
P_LINE += module/interface/history/
P_LINE += module/interface/action_keys/clipboard/
P_LINE += module/interface/action_keys/movement/
P_LINE += module/interface/core/
P_LINE += module/interface/init/
P_LINE += module/interface/redraw/
P_LINE += module/interface/utils/

P_ANALYZER += module/analyzer/
P_ANALYZER += module/analyzer/init/
P_ANALYZER += module/analyzer/state/

P_BUILTIN += module/builtin/
P_BUILTIN += module/builtin/cd/
P_BUILTIN += module/builtin/echo/
P_BUILTIN += module/builtin/exit/
P_BUILTIN += module/builtin/export/
P_BUILTIN += module/builtin/hash/
P_BUILTIN += module/builtin/pwd/
P_BUILTIN += module/builtin/set/
P_BUILTIN += module/builtin/type/
P_BUILTIN += module/builtin/unset/

P_EXPANSION += module/expansion/

P_LEXER += module/lexer/
P_LEXER += module/lexer/debug/
P_LEXER += module/lexer/init/
P_LEXER += module/lexer/state_machine/

P_LOGGING += module/logging/

P_PARSER += module/parser/
P_PARSER += module/parser/init/
P_PARSER += module/parser/debug/

P_RESOLVE += module/resolve/

P_TOOLS += tools/

_SPATH += $(P_CORE)
_SPATH += $(P_LINE)
_SPATH += $(P_ANALYZER)
_SPATH += $(P_BUILTIN)
_SPATH += $(P_TOOLS)
_SPATH += $(P_EXPANSION)
_SPATH += $(P_LEXER)
_SPATH += $(P_LOGGING)
_SPATH += $(P_PARSER)
_SPATH += $(P_RESOLVE)

SPATH += $(addprefix srcs/, $(_SPATH))

# ---------------------------------------------------------------------------- #
#									 vpath                                     #
# ---------------------------------------------------------------------------- #

vpath %.c $(SPATH) $(TPATH)
vpath %.h $(IPATH)

# ---------------------------------------------------------------------------- #
#							   Compilation Flags                               #
# ---------------------------------------------------------------------------- #

IFLAGS = $(addprefix -I, $(IPATH))
LDLIBN = -lft
LDLIBD = -lftdb
LDFLAGS = -L $(LPATH)
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += $(IFLAGS)
DFLAGS += $(CFLAGS)
DFLAGS += -fsanitize=address,undefined
LFLAGS = -ltermcap

# ---------------------------------------------------------------------------- #
#									Includes                                   #
# ---------------------------------------------------------------------------- #

INCS += sh21.h
INCS += log.h
INCS += interface_functions.h
INCS += lexer.h
INCS += parser.h
INCS += analyzer.h
INCS += builtin.h
INCS += resolve.h
INCS += history.h
INCS += define.h
INCS += struct.h
INCS += enum.h

# ---------------------------------------------------------------------------- #
#									Sources                                    #
# ---------------------------------------------------------------------------- #

#						- - - - -   Core   - - - - -						   #

CORE += main.c
CORE += options.c
CORE += grammar.c
CORE += routine.c
CORE += exec_signals.c
CORE += interface_signals.c
CORE += signal_handler.c
CORE += setup.c

#						- - - - -  Debug Log  - - - - -						   #

LOGGING += debug_logger.c
LOGGING += print_debug.c

#						- - - - -  Built-in   - - - - -                        #

BUILTIN += blt_options.c

#CD
BUILTIN += cd.c
BUILTIN += cd_cdpath.c
BUILTIN += cd_additions.c
BUILTIN += cd_simple.c

#ECHO
BUILTIN += echo.c

#EXIT
BUILTIN += exit.c

#EXPORT
BUILTIN += export.c

#HASH
BUILTIN += hash.c

#PWD
BUILTIN += pwd.c

#SET
BUILTIN += set.c

#TYPE
BUILTIN += type.c

#UNSET
BUILTIN += unset.c

#						- - - - - Line edtion - - - - -                        #

#History
LINE += history.c

#Utilities
LINE += validate_interface.c
LINE += get_prompt_len.c
LINE += input_tools.c
LINE += shift_tools.c
LINE += move_tools.c
LINE += realloc_vector.c
LINE += clean_registry.c
LINE += set_quote.c
LINE += ft_putc.c
LINE += is_eof.c
LINE += print.c

#Redraw
LINE += clean_screen.c
LINE += redraw_prompt.c

#Initialization
LINE += load_interface_config.c
LINE += load_termcap_strings.c

#Core
LINE += window_cursor.c
LINE += term_mode.c
LINE += launch_interface.c
LINE += validate_quoting.c
LINE += handle_input_keys.c

#Prompt
LINE += prompt.c
LINE += sub_prompt.c

#Action keys
LINE += init_clipboard.c
LINE += init_ak_keycodes.c
LINE += execute_clipboard_copy_ak.c
LINE += execute_clipboard_cut_ak.c
LINE += execute_clipboard_paste.c
LINE += execute_arrow_ak.c
LINE += execute_he_ak.c
LINE += execute_word_jumping_ak.c
LINE += execute_ctrl_ak.c
LINE += execute_special_ak.c

#			 		      - - - - - Analyzer - - - - -                         #

ANALYZER += analyzer.c
ANALYZER += init_analyzer.c
ANALYZER += init_heredoc_analyzer.c
ANALYZER += init_io_analyzer.c
ANALYZER += init_io_redirect_analyzer.c
ANALYZER += init_start_analyzer.c
ANALYZER += init_string_analyzer.c
ANALYZER += analyzer_interface.c
ANALYZER += analyzer_tools.c
ANALYZER += filename_analyzer.c
ANALYZER += heredoc_analyzer.c
ANALYZER += io_redirect_analyzer.c
ANALYZER += pipe_analyzer.c
ANALYZER += redirect_analyzer.c
ANALYZER += string_analyzer.c

#						   - - - - Expansion - - - -                           #

EXPANSION += expansion.c
EXPANSION += quoting.c
EXPANSION += tilde.c
EXPANSION += variable.c

#						   - - - -   Lexer   - - - -                           #

LEXER += lexer.c
LEXER += tmp_display.c
LEXER += init_lexer.c
LEXER += generate_token.c
LEXER += machine_interface.c
LEXER += quotes_states.c
LEXER += redirect_states.c
LEXER += sign_states.c
LEXER += states.c

#						     - - - - Parser  - - - -                           #

PARSER += parser.c
PARSER += parser_debug.c
PARSER += generate_graph.c
PARSER += ways_graph.c
PARSER += ways_graph_word.c

#						     - - - - Resolve - - - -                           #

RESOLVE += job_tools.c
RESOLVE += launch_job.c
RESOLVE += launch_process.c
RESOLVE += waitjob.c

#						     - - - -  Tools  - - - -                           #

TOOLS += free_node.c
TOOLS += internals.c
TOOLS += list_functions.c
TOOLS += list_functions2.c
TOOLS += print_opt.c
TOOLS += read_filedesc.c
TOOLS += utils.c

# ---------------------------------------------------------------------------- #
#									 Rules                                     #
# ---------------------------------------------------------------------------- #

all : $(NAME)

run : $(NAME)
	./$<

drun : $(NAMEDB)
		./$< -d

debug : $(NAMEDB)

lldb : $(NAMEDB)
	lldb -- ./$< -d

test : $(NAMET)
	./$<

#					 - - - - - Normal Compilation - - - - -                    #

$(NAME) : $(CLEAR) $(LIB) $(OPATH) $(OBJS)
	$(LINK) $(OBJS) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBN) $(LFLAGS) -o $@
	$(PRINT) "$(GREEN)$@ is ready\n$(NC)"

$(OBJM) : $(OPATH)%.o : %.c $(INCS) Makefile
	$(COMPILE) $(CFLAGS) $(CPPFLAGS) $< -o $@
	$(PRINT) "$(ONELINE)$(BLUE)Compiling $<                   $(NC)\n"

$(OBJS) : $(OPATH)%.o : %.c $(INCS) Makefile
	$(COMPILE) $(CFLAGS) $(CPPFLAGS) $< -o $@
	$(PRINT) "$(ONELINE)$(BLUE)Compiling $<                   $(NC)\n"

$(LIB) : FORCE
	$(MAKE) -C $(LPATH)

#					 - - - - - Debug Compilation - - - - -                     #

$(NAMEDB) : $(CLEAR) $(LIBDB) $(OPATH) $(OBJD)
	$(LINKD) $(OBJD) $(DFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBD) $(LFLAGS) -o $@
	$(PRINT) "$(GREEN)$@ is ready\n$(NC)"

$(OBJD) : $(OPATH)db%.o : %.c $(INCS) Makefile
	$(DEBUG) $(DFLAGS) $(CPPFLAGS) $< -o $@
	$(PRINT) "$(ONELINE)$(BLUE)Compiling $< for debug                   $(NC)\n"

$(LIBDB) : FORCE
	$(MAKE) -C $(LPATH) debug

$(CLEAR):
	$@

$(OPATH) :
	$(MKDIR) $(OPATH)

clean :
	$(MAKE) -C $(LPATH) clean
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(NAME).dSYM
	$(PRINT) ".o file deleted\n"

fclean : clean
	$(MAKE) -C $(LPATH) fclean
	$(CLEANUP) $(NAME)
	$(CLEANUP) $(NAMEDB)
	$(CLEANUP) $(NAMET)
	$(PRINT) "Executables destroyed\n"

re : fclean all

help :
	@$(PRINT) "Rules available : all, clean,  fclean, re, and help\n"

FORCE:

.PHONY : all 21 21debug lexer lexerdb clean fclean re help FORCE
.SILENT:
