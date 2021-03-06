/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:59:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/15 12:55:49 by lubenard         ###   ########.fr       */
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
		while (command[i + e] && command[i + e] != ' '
		&& ft_isalnum(command[i + e]))
			e++;
		str = find_in_env(lkd_env, ft_strsub(command, i, e));
		ft_putstr(str);
		free(str);
		return (i + e);
	}
	return (i + 1);
}

void	verify_folder(char buffer[4096], char user_name[33], char *str)
{
	struct stat		s;
	int				err;

	free(str);
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
		while (command[i + e] && (command[i + e] != ' '
		|| command[i + e] != '\t'))
			e++;
		ft_strnncpy(user_name, command, i + 1, i + e);
		j = ft_strlen(str);
		while (str[j] != '/')
			j--;
		ft_strncpy(buff, str, j + 1);
		verify_folder(buff, user_name, str);
		return (i + e + 1);
	}
	else
		return (handle_tilde2(lkd_env, i));
}

int		return_i(char *command)
{
	int i;

	i = 0;
	while (command[i] == ' ' || command[i] == '\t')
		i++;
	while (command[i] && ft_isalnum(command[i]))
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
	while (command[i - 1])
	{
		if (command[i] == '\t' || (command[i] == ' '
		&& (command[i + 1] == ' ' || command[i - 1] == ' ')))
			i++;
		else if (command[i] == '$')
			i = handle_dollar(lkd_env, command, i);
		else if (command[i] == '~')
			i = handle_tilde(lkd_env, command, i);
		else
			ft_putchar(command[i++]);
	}
	if (e == 0)
		ft_putchar('\n');
}
