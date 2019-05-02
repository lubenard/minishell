/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:57:32 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/02 17:06:38 by lubenard         ###   ########.fr       */
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
	while (command[e] == ' ')
		e++;
	while (command[e + i] != ' ' && command[e + i])
		++i;
	return (ft_strlower(ft_strsub(command, e, i)));
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

int		get_command(char *command, char **path, t_env *lkd_env)
{
	char *first_command;
	char *get_right_path;

	if (ft_strchr(command, ';'))
		return (get_multiple_command(command, path, lkd_env));
	if (ft_strcmp(command, "exit") != 0)
	{
		if (ft_isblank(command) != -1)
		{
			first_command = extract_command(command);
			if (command[ft_strlen(command) - 2] == 9)
				autocomplete(path, command);
			else if (!ft_strcmp(first_command, "echo"))
				echo(lkd_env, command);
			else if (!ft_strcmp(first_command, "env") && !ft_strstr(command, "-i"))
				print_env(lkd_env);
			else if (!ft_strcmp(first_command, "setenv"))
				set_env(lkd_env, command);
			else if (!ft_strcmp(first_command, "unsetenv"))
				unset_env(lkd_env, command);
			else if (!ft_strcmp(first_command, "cd") || !ft_strcmp(first_command, ".."))
				cd(lkd_env, command);
			else if ((get_right_path = external_command(path, first_command))
				!= NULL)
				execute_command(get_right_path, extract_command(command),
					ft_split_whitespaces(command), compact_env(lkd_env));
			else
				error(first_command);
			free(first_command);
		}
		return (1);
	}
	else
		free_lkd_env(lkd_env);
	return (0);
}
