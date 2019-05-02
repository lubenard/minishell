/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:59:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/02 15:57:12 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		str = find_in_env(lkd_env, ft_strsub(command, i, e));
		ft_putstr(str);
		free(str);
		return (i += e);
	}
	return (i + 1);
}

void	verify_folder(char buffer[4096], char user_name[33])
{
	struct stat		s;
	int				err;

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
	ft_bzero(user_name, 33);
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
		handle_tilde2(lkd_env);
	return (i + 1);
}

int		return_i(char *command)
{
	int i;

	i = 0;
	while (command[i] == ' ')
		i++;
	while (command[i] && command[i] != ' ')
		i++;
	return (++i);
}

void	echo(t_env *lkd_env, char *command)
{
	int e;
	int i;

	e = 0;
	i = return_i(command);
	if (ft_strstr(command, "-n") != NULL)
	{
		e = 1;
		i += 3;
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
