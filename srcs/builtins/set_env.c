/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:57:20 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/23 14:37:01 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_first_env(char *command, int mode)
{
	int i;
	int e;

	i = 0;
	e = 0;
	if (mode == 0)
	{
		while (command[i] != '=' && command[i])
			++i;
		return (ft_strsub(command, 0, i));
	}
	else if (mode == 1)
	{
		while (command[i] && command[i] != ' ')
			++i;
		while (command[i] == ' ')
			++i;
		while (command[i + e] && command[i + e] != '=')
			++e;
		if (e == 0)
			return (ft_strdup(command));
		return (ft_strsub(command, i, e));
	}
	return (NULL);
}

void	set_env(t_env *lkd_env, char *command)
{
	t_env	*new_element;
	t_env	*tmp;
	char	*to_add;
	char	*to_extract;
	char	*to_search;

	if (ft_strchr(command, '=') == 0)
		return ;
	to_search = extract_first_env(command, 1);
	to_add = extract_params(command);
	while (lkd_env)
	{
		to_extract = extract_first_env(lkd_env->env_line, 0);
		if (ft_strcmp(to_extract, to_search) == 0)
		{
			free(to_extract);
			unset_env(lkd_env, to_search);
			while (lkd_env->prev)
				lkd_env = lkd_env->prev;
			while (lkd_env)
			{
				if (!lkd_env->next)
					tmp = lkd_env;
				lkd_env = lkd_env->next;
			}
			break ;
		}
		if (!lkd_env->next)
			tmp = lkd_env;
		lkd_env = lkd_env->next;
		free(to_extract);
	}
	if (!lkd_env)
		lkd_env = tmp;
	free(to_search);
	new_element = new_maillon();
	lkd_env->next = new_element;
	lkd_env->next->prev = lkd_env;
	ft_strcpy(lkd_env->next->env_line, to_add);
	free(to_add);
}
