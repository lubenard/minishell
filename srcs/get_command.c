/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:57:32 by lubenard          #+#    #+#             */
/*   Updated: 2019/03/21 17:19:08 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

void	error(char *command)
{
	ft_putstr("Error: ");
	ft_putstr(command);
	ft_putstr(" : command not found ¯\\_(ツ)_/¯\n");
}

char	*extract_command(char *command)
{
	int i;

	i = 0;
	while (command[i] != ' ' && command[i])
		++i;
	return (ft_strsub(command, 0, i));
}

void	free_lkd_env(t_env *lkd_env)
{
	t_env *tmp;

	while (lkd_env)
	{
		tmp = lkd_env;
		lkd_env = lkd_env->next;
		free(tmp);
	}
}

void	get_command(char *command, char **path, t_env *lkd_env)
{
	char *first_command;
	char *get_right_path;

	if (ft_strcmp(command, "exit") != 0)
	{
		if (ft_isblank(command) != -1)
		{
			first_command = extract_command(command);
			if (ft_strcmp(first_command, "echo") == 0)
				echo(command);
			else if (ft_strcmp(first_command, "env") == 0)
				print_env(lkd_env);
			else if (ft_strcmp(first_command, "setenv") == 0)
				set_env(lkd_env, command);
			else if (ft_strcmp(first_command, "unsetenv") == 0)
				unset_env(lkd_env, command);
			else if (ft_strcmp(first_command, "cd") == 0)
				cd(lkd_env, command);
			else if ((get_right_path = external_command(path, first_command))
				!= NULL)
				execute_command(get_right_path, command);
			else
				error(first_command);
			free(first_command);
		}
	}
	else
		free_lkd_env(lkd_env);
}
