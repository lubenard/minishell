/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:59:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/26 18:14:39 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_in_env(t_env *lkd_env, char *to_find)
{
	int lenght;
	int i;
	int e;

	i = 0;
	e = 0;
	lenght = ft_strlen(to_find);
	while (lkd_env)
	{
		if (ft_strncmp(lkd_env->env_line, to_find, lenght) == 0)
		{
			while (lkd_env->env_line[i] && lkd_env->env_line[i] != '=')
				i++;
			i++;
			while (lkd_env->env_line[i + e])
				e++;
			free(to_find);
			return (ft_strsub(lkd_env->env_line, i, e));
		}
		lkd_env = lkd_env->next;
	}
	free(to_find);
	return (ft_strdup(""));
}

void	error_echo(char user[33])
{
	ft_putstr("lubenash : no such user or directory: ");
	ft_putstr(user);
}

int		handle_dollar(t_env *lkd_env, char *command, int i)
{
	int		e;
	char	*str;

	e = 0;
	if (command[i] == '$' && command[i + 1] != ' ')
	{
		i++;
		while (command[i + e] && command[i + e] != ' ')
			e++;
		str = find_in_env(lkd_env, ft_strsub(command, i,e));
		ft_putstr(str);
		free(str);
		return (i += e);
	}
	return (i + 1);
}

void	verify_folder(char buffer[4096], char user_name[33])
{
	struct stat s;
	int err;

	ft_strcat(buffer, user_name);
	err = stat(buffer, &s);
	if (err == -1)
		error_echo(user_name);
	else
	{
		if (S_ISDIR(s.st_mode))
			ft_putstr(buffer);
		else
			error_echo(user_name);
	}
}

int		handle_tilde(t_env *lkd_env, char *command, int i)
{
	char	*str;
	char	buff[4096];
	char	user_name[33];
	int		e;
	int		j;

	ft_bzero(buff, 4096);
	e = 0;
	if (command[i] == '~' && command[i + 1] != ' ' && command[i + 1])
	{
		str = find_in_env(lkd_env, ft_strdup("HOME"));
		j = ft_strlen(str);
		while (command[i + e] && command[i + e] != ' ')
			e++;
		ft_strnncpy(user_name, command, i + 1, i + e);
		while (str[j] != '/')
			j--;
		ft_strncpy(buff, str, j + 1);
		verify_folder(buff, user_name);
		return (i + e);
	}
	else
	{
		str = find_in_env(lkd_env, ft_strdup("HOME"));
		ft_putstr(str);
		free(str);
	}
	return (i + 1);
}

void	echo(t_env *lkd_env, char *command)
{
	int e;
	int i;

	i = 5;
	e = 0;
	if (ft_strstr(command, "-n") != NULL)
	{
		e = 1;
		i = 8;
	}
	while (command[i])
	{
		if (command[i] == '$')
			i = handle_dollar(lkd_env, command, i);
		else if (command[i] == '~')
			i = handle_tilde(lkd_env, command, i);
		else
			ft_putchar(command[i++]);
	}
	if (e == 0)
		ft_putchar('\n');
}
