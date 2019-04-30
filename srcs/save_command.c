/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 00:23:47 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/30 13:31:55 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_command(char *command)
{
	int file;

	if (access(".history", F_OK) == -1)
	{
		file = open(".history", O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
		ft_putendl_fd(command, file);
		close(file);
	}
	else
	{
		file = open(".history", O_RDWR | O_APPEND);
		ft_putendl_fd(command, file);
		close(file);
	}
}
