/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:05:25 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/08 22:19:55 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*extract_params(char *command)
{
	int		i;
	int		e;

	i = 0;
	e = 0;
	while (command[i] && command[i] != ' ')
		++i;
	while (command[i] == ' ' || command[i] == '\t')
		++i;
	while (command[i + e])
		++e;
	return (ft_strsub(command, i, e));
}

void		unset_env(t_env *lkd_env, char *command)
{
	char	*to_extract;
	int		i;
	char	*to_remove;

	to_remove = (ft_strchr(command, '=')) ? extract_params(command)
		: extract_first_env(command, 1);
	while (lkd_env)
	{
		i = 0;
		while (lkd_env->env_line[i] != '=')
			++i;
		to_extract = ft_strsub(lkd_env->env_line, 0, i);
		if (ft_strcmp(to_extract, to_remove) == 0
			&& (lkd_env->next || lkd_env->prev))
		{
			if (lkd_env->prev)
				lkd_env->prev->next = lkd_env->next;
			if (lkd_env->next)
				lkd_env->next->prev = lkd_env->prev;
			free(to_extract);
			free(lkd_env);
			break ;
		}
		free(to_extract);
		lkd_env = lkd_env->next;
	}
	free(to_remove);
}
