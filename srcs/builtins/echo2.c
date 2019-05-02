/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:45:42 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/02 15:56:16 by lubenard         ###   ########.fr       */
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

void	handle_tilde2(t_env *lkd_env)
{
	char *str;

	str = find_in_env(lkd_env, ft_strdup("HOME"));
	ft_putstr(str);
	free(str);
}

