/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:57:32 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/26 10:34:15 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *command)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(" : command not found ¯\\_(ツ)_/¯\n", 2);
}

char	*extract_command(char *command)
{
	int i;
	int e;

	i = 0;
	e = 0;
	while (command[i] != ' ' && command[i])
		++i;
	return (ft_strlower(ft_strsub(command, 0, i)));
}

int		count_args(char *command, int i)
{
	int nbr_args;

	nbr_args = 0;
	while (command[i])
	{
		if (command[i] > 32 && command[i + 1] < 33)
			nbr_args++;
		i++;
	}
	return (nbr_args);
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
				echo(lkd_env, command);
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
				execute_command(get_right_path, extract_command(command),
					ft_split_whitespaces(command), compact_env(lkd_env));
			else
				error(first_command);
			free(first_command);
		}
	}
	else
		free_lkd_env(lkd_env);
}
