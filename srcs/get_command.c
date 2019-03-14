/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:57:32 by lubenard          #+#    #+#             */
/*   Updated: 2019/03/14 23:42:54 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline static void		error(char *command)
{
	ft_putstr("Error: ");
	ft_putstr(command);
	ft_putstr(" : command not found ¯\\_(ツ)_/¯\n");
}

void					get_command(char *command, char **path)
{
	(void)path;
	if (ft_strcmp(command, "exit") != 0)
		error(command);
}
