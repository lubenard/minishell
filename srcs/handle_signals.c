/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:21:03 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/07 18:24:04 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals_proc(int sig)
{
	extern pid_t g_pid;

	if (sig == SIGINT)
		ft_putstr("\n");
}

void	handle_signals(int sig)
{
	extern char *g_curr_dir;
	extern char *g_username;

	if (sig == SIGINT)
	{
		ft_putstr("\n");
		write_prompt(g_username, g_curr_dir);
	}
}
