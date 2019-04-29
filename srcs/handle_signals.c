/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:21:03 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/30 00:15:46 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals_proc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
	}
	signal(SIGINT, handle_signals_proc);
}

void	handle_signals(int sig)
{
	extern char *curr_dir;
	extern char *username;

	if (sig == SIGINT)
	{
		ft_putstr("\n");
		write_prompt(username, curr_dir);
	}
	signal(SIGINT, handle_signals);
}


