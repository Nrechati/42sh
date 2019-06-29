/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termmode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:13:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/06/29 19:30:04 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "sh21.h"
#include <termios.h>
#include <unistd.h>

static int16_t          init_term_modes(struct termios *sle,
                                struct termios *exec,
                                struct termios *original)
{
    if ((tcgetattr(STDIN_FILENO, original)) == FAILURE)
        return (CRITICAL_ERROR | TERMMDE_FAIL);

    if ((tcgetattr(STDIN_FILENO, exec)) == FAILURE)
        return (CRITICAL_ERROR | TERMMDE_FAIL);

	if ((tcgetattr(STDIN_FILENO, sle)) == FAILURE)
        return (CRITICAL_ERROR | TERMMDE_FAIL);

    sle->c_lflag &= ~(ICANON);
	sle->c_lflag &= ~(ECHO);
	sle->c_lflag |= ISIG;
	sle->c_cc[VMIN] = 1;
	sle->c_cc[VTIME] = 0;
    return (SUCCESS);
}

static int16_t          set_mode(__unused struct termios *mode)
{
//	if (mode == NULL)
//		return (FAILURE);
	if (tcsetattr(STDOUT_FILENO, TCSANOW, mode) == FAILURE)
		return (FAILURE | TERMMDE_FAIL);
	return (SUCCESS);
//	return (FAILURE);
}

int16_t          term_mode(uint8_t mode_flag)
{
	static struct termios	sle_ios;
	static struct termios	exe_ios;
	static struct termios	dfl_ios;

    if (mode_flag == TERMMODE_INIT)
		return (init_term_modes(&sle_ios,
								&exe_ios,
								&dfl_ios));

	else if (mode_flag == TERMMODE_DFLT)
        return (set_mode(&dfl_ios));

	else if (mode_flag == TERMMODE_SLE)
        return (set_mode(&sle_ios));

	else if (mode_flag == TERMMODE_EXEC)
        return (set_mode(&exe_ios));
	return (SUCCESS);
}
