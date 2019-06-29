# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/26 18:34:36 by ffoissey          #+#    #+#              #
#    Updated: 2019/06/29 19:49:58 by skuppers         ###   ########.fr        #
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
SRCS += $(SLE)
SRCS += $(ANALYZER)
SRCS += $(INTERPRETER)
SRCS += $(BUILTIN)
SRCS += $(EXPANSION)
SRCS += $(LEXER)
SRCS += $(LOGGING)
SRCS += $(PARSER)
SRCS += $(RESOLVE)
SRCS += $(HISTORY)
SRCS += $(AUTOCOMPLETION)
SRCS += $(JOBCTL)
OBJS = $(patsubst %.c, $(OPATH)%.o, $(SRCS))
OBJD = $(patsubst %.c, $(OPATH)db%.o, $(SRCS))

LIB = $(addprefix $(LPATH), $(LIBFT))
LIBDB = $(addprefix $(LPATH), $(LIBFTDB))

# ---------------------------------------------------------------------------- #
#									Compiler                                   #
# ---------------------------------------------------------------------------- #

CC = clang
LINK = $(CC) -g3
LINKD = $(CC) -g3 -fsanitize=address,undefined -fno-omit-frame-pointer
COMPILE = $(CC) -c -g3
DEBUG = $(CC) -g3 -c -fsanitize=address,undefined -fno-omit-frame-pointer

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

P_CORE += core/startup/
P_CORE += core/startup/init/
P_CORE += core/launch/
P_CORE += core/routine/
P_CORE += core/signals/
P_CORE += core/termmode/
P_CORE += core/tools/
P_CORE += core/tools/intern_var
P_CORE += core/tools/path

P_SLE += module/sle/
P_SLE += module/sle/prompt
P_SLE += module/sle/action_keys/
P_SLE += module/sle/action_keys/clipboard/
P_SLE += module/sle/action_keys/movement/
P_SLE += module/sle/init/
P_SLE += module/sle/redraw/
P_SLE += module/sle/utils/

P_ANALYZER += module/analyzer/
P_ANALYZER += module/analyzer/init/
P_ANALYZER += module/analyzer/state/
P_ANALYZER += module/analyzer/tools/

P_INTERPRETER += module/interpreter/
P_INTERPRETER += module/interpreter/core/
P_INTERPRETER += module/interpreter/maping/
P_INTERPRETER += module/interpreter/tools/

P_JOBCTL += module/jobcontrol/

P_BUILTIN += module/builtin/
P_BUILTIN += module/builtin/cd/
P_BUILTIN += module/builtin/echo/
P_BUILTIN += module/builtin/exit/
P_BUILTIN += module/builtin/export/
P_BUILTIN += module/builtin/hash/
P_BUILTIN += module/builtin/pwd/
P_BUILTIN += module/builtin/set/
P_BUILTIN += module/builtin/test/
P_BUILTIN += module/builtin/type/
P_BUILTIN += module/builtin/unset/
P_BUILTIN += module/builtin/fc/
P_BUILTIN += module/builtin/jobs/
P_BUILTIN += module/builtin/fg/
P_BUILTIN += module/builtin/bg/

P_EXPANSION += module/expansion/
P_EXPANSION += module/expansion/parameter/
P_EXPANSION += module/expansion/arithmetic/

P_LEXER += module/lexer/
P_LEXER += module/lexer/debug/
P_LEXER += module/lexer/process/

P_LOGGING += module/logging/

P_PARSER += module/parser/
P_PARSER += module/parser/init/
P_PARSER += module/parser/debug/

P_HISTORY += module/history/

P_AUTOCOMPLETION += module/autocompletion/


_SPATH += $(P_CORE)
_SPATH += $(P_SLE)
_SPATH += $(P_ANALYZER)
_SPATH += $(P_BUILTIN)
_SPATH += $(P_EXPANSION)
_SPATH += $(P_LEXER)
_SPATH += $(P_LOGGING)
_SPATH += $(P_PARSER)
_SPATH += $(P_HISTORY)
_SPATH += $(P_AUTOCOMPLETION)
_SPATH += $(P_INTERPRETER)
_SPATH += $(P_JOBCTL)

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
GC ?= 1
ifneq ($(GC), 0)
	CFLAGS += -D GC
endif
EXEC ?= 1
ifeq ($(EXEC), 0)
	CFLAGS += -D NOEXEC
endif
CFLAGS += $(IFLAGS)
DFLAGS = $(CFLAGS)
DFLAGS += -fsanitize=address,undefined
LFLAGS = -ltermcap

# ---------------------------------------------------------------------------- #
#									Includes                                   #
# ---------------------------------------------------------------------------- #

INCS += sh21.h
INCS += log.h
INCS += sle.h
INCS += lexer.h
INCS += parser.h
INCS += analyzer.h
INCS += builtin.h
INCS += resolve.h
INCS += history.h
INCS += autocompletion.h
INCS += define.h
INCS += struct.h
INCS += enum.h
INCS += jobctl.h

# ---------------------------------------------------------------------------- #
#									Sources                                    #
# ---------------------------------------------------------------------------- #

#						- - - - -   Core   - - - - -						   #

#Startup
CORE += main.c
CORE += options.c
CORE += grammar.c
CORE += setup.c

#Lauch
CORE += launch.c
CORE += batch_mode.c
CORE += interactive_mode.c

#Routine
CORE += routine.c
CORE += exit_routine.c

#Signals
CORE += signal_profile.c
CORE += init_signal_profile.c
CORE += exec_signals.c
CORE += sle_signals.c

#Tools
CORE += search_path.c
CORE += intern_var_free.c
CORE += intern_var_manager.c
CORE += intern_var_tools.c
CORE += list_function_pointers.c

#termmode
CORE += termmode.c

#						- - - - -  Debug Log  - - - - -						   #

LOGGING += debug_logger.c
LOGGING += print_debug.c

#						- - - - -   History   - - - - -						   #

HISTORY += history.c
HISTORY += history_tools.c
HISTORY += history_expansion.c
HISTORY += histfile.c
HISTORY += entry_manager.c
HISTORY += get_entry.c
HISTORY += print_history.c

#						- - - -  Autocompletion - - - -						   #

AUTOCOMPLETION += autocompletion.c
AUTOCOMPLETION += autocompletion_tools.c
AUTOCOMPLETION += autocompletion_tools2.c
AUTOCOMPLETION += get_completion_cmd.c
AUTOCOMPLETION += get_completion_file.c
AUTOCOMPLETION += get_completion_var.c
AUTOCOMPLETION += get_start_input.c
AUTOCOMPLETION += get_type.c
AUTOCOMPLETION += print_result.c

#						- - - - -  Built-in   - - - - -                        #

BUILTIN += blt_options.c

#JOBS
BUILTIN += bg.c
BUILTIN += fg.c
BUILTIN += jobs.c
BUILTIN += print.c
BUILTIN += get_state.c
BUILTIN += get_avs.c
#BUILTIN += utils.c


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
BUILTIN += h_opt.c
BUILTIN += h_utils.c

#PWD
BUILTIN += pwd.c

#SET
BUILTIN += set.c

#SET
BUILTIN += test.c
BUILTIN += test_callbacks.c

#TYPE
BUILTIN += type.c

#UNSET
BUILTIN += unset.c

#FC
BUILTIN += fc.c
BUILTIN += fc_list.c
BUILTIN += fc_redo.c
BUILTIN += fc_editor.c

#	    					- - - - - SLE - - - - -                           #

#Util
SLE += input_tools.c
SLE += move_tools.c
SLE += clean_registry.c

#Redraw
SLE += redraw.c
SLE += redraw_modes.c
SLE += redraw_tools.c

#Init
SLE += setup_sle.c
SLE += init_sle.c
SLE += load_sle.c
SLE += load_sle_modules.c
SLE += load_sle_struct.c
SLE += save_interns.c

#Prompt
SLE += prompt.c
SLE += get_prompt_length.c
SLE += prompt_error.c
SLE += prompt_subroutine.c
SLE += prompt_subroutine_tools.c
SLE += prompt_expansion.c
SLE += prompt_tools.c

#Action keys
SLE += execute_clipboard_copy_ak.c
SLE += execute_clipboard_cut_ak.c
SLE += execute_clipboard_paste.c
SLE += execute_arrow_ak.c
SLE += execute_he_ak.c
SLE += execute_word_jumping_ak.c
SLE += execute_special_ak.c
SLE += visual_mode.c

SLE += window.c
SLE += launch_sle.c
SLE += handle_input_keys.c
SLE += cursor.c

#			 		      - - - - - Analyzer - - - - -                         #

ANALYZER += analyzer.c
ANALYZER += init_analyzer.c
ANALYZER += init_heredoc_analyzer.c
ANALYZER += init_io_analyzer.c
ANALYZER += init_io_redirect_analyzer.c
ANALYZER += init_start_analyzer.c
ANALYZER += init_string_analyzer.c
ANALYZER += init_assign_analyzer.c
ANALYZER += analyzer_interface.c
ANALYZER += analyzer_tools.c
ANALYZER += filename_analyzer.c
ANALYZER += heredoc_analyzer.c
ANALYZER += io_redirect_analyzer.c
ANALYZER += pipe_analyzer.c
ANALYZER += redirect_analyzer.c
ANALYZER += string_analyzer.c
ANALYZER += assign_analyzer.c
ANALYZER += token_tools.c

#			 		      - - - - - Interpreter - - - - -                         #

INTERPRETER += interpreter.c
INTERPRETER += map.c
INTERPRETER += list_tools.c
INTERPRETER += generate_env.c
INTERPRETER += pipe_interpreter.c
INTERPRETER += fork_process.c
INTERPRETER += redirects.c
INTERPRETER += redirect_functions.c
INTERPRETER += io_redirect_functions.c
INTERPRETER += redirect_tools.c
INTERPRETER += waiter.c
INTERPRETER += heredoc_interpreter.c
INTERPRETER += map_tools.c
INTERPRETER += interpreter_tools.c
INTERPRETER += process_tools.c
INTERPRETER += print_tools.c
INTERPRETER += background_job.c

#						   - - - - Jobcontrol - - - -                          #

JOBCTL += jobctl.c
JOBCTL += utils.c
JOBCTL += update_jobs.c

#						   - - - - Expansion - - - -                           #

EXPANSION += expansion.c
EXPANSION += expansion_debug.c
EXPANSION += quoting.c
EXPANSION += tilde.c
EXPANSION += variable.c
EXPANSION += parameter.c
EXPANSION += parameter_lexer.c
EXPANSION += parameter_lexer_word.c
EXPANSION += parameter_parser.c
EXPANSION += parameter_get.c
EXPANSION += parameter_actions.c
EXPANSION += parameter_suffix_prefix.c

EXPANSION += arithmetic.c
EXPANSION += arithmetic_analyzer.c
EXPANSION += arithmetic_variable.c
EXPANSION += arithmetic_base_states.c
EXPANSION += arithmetic_preffix_plus_minus.c
EXPANSION += arithmetic_tools.c
EXPANSION += math_analyzer.c

EXPANSION += calculator.c
EXPANSION += shunting_yard.c
EXPANSION += calculate_rpn.c
EXPANSION += math.c

#						   - - - -   Lexer   - - - -                           #

LEXER += lexer.c
LEXER += tmp_display.c
LEXER += lexer_tools.c
LEXER += checker_module.c
LEXER += lexer_interface.c
LEXER += set_inhibitor.c

LEXER += lexer_maths_interface.c

#						     - - - - Parser  - - - -                           #

PARSER += parser.c
PARSER += parser_subprompt.c
PARSER += init_parser.c
PARSER += ways_graph.c
PARSER += ways_graph_word.c


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
	$(LINK) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LDLIBN) $(LFLAGS) -o $@
	$(PRINT) "$(GREEN)$@ is ready\n$(NC)"

$(OBJS) : $(OPATH)%.o : %.c $(INCS) Makefile
	$(COMPILE) $(CFLAGS) $(CPPFLAGS) $< -o $@
	$(PRINT) "$(ONELINE)$(CYAN)Compiling $<                   $(NC)\n"

$(LIB) : FORCE
	$(MAKE) -C $(LPATH)

#					 - - - - - Debug Compilation - - - - -                     #

$(NAMEDB) : $(CLEAR) $(LIBDB) $(OPATH) $(OBJD)
	$(LINKD) $(OBJD) $(DFLAGS) $(LDFLAGS) $(LDLIBD) $(LFLAGS) -o $@
	$(PRINT) "$(GREEN)$@ is ready\n$(NC)"

$(OBJD) : $(OPATH)db%.o : %.c $(INCS) Makefile
	$(DEBUG) $(DFLAGS) $(CPPFLAGS) $< -o $@
	$(PRINT) "$(ONELINE)$(PURPLE)Compiling $< for debug                   $(NC)\n"

$(LIBDB) : FORCE
	$(MAKE) -C $(LPATH) debug

#					 - - - - - - - - - - - - - - - - - - -                     #
#
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
