/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:59:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/25 15:52:44 by lubenard         ###   ########.fr       */
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

void	handle_dollar(t_env *lkd_env, char *command)
{
	int		e;
	int		i;
	char	*str;

	e = 0;
	i = 5;
	while (command[i])
	{
		if (command[i] == '$' && command[i + 1] != ' ')
		{
			i++;
			while (command[i + e] && command[i + e] != ' ')
				e++;
			str = find_in_env(lkd_env, ft_strsub(command, i,e));
			ft_putstr(str);
			free(str);
			i += e - 1;
		}
		else
			ft_putchar(command[i]);
		i++;
	}
	ft_putchar('\n');
}

void	echo(t_env *lkd_env, char *command)
{
	int e;
	int i;

	i = 5;
	e = 0;
	if (ft_strchr(command, '$'))
	{
		handle_dollar(lkd_env, command);
		return ;
	}
	if (ft_strstr(command, "-n") != NULL)
	{
		e = 1;
		i = 8;
	}
	while (command[i])
		ft_putchar(command[i++]);
	if (e == 0)
		ft_putchar('\n');
}
