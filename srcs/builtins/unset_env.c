/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:05:25 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/22 17:14:04 by lubenard         ###   ########.fr       */
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
	while (command[i] == ' ')
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

	i = 0;
	printf("a remove %s\n", command);
	if (ft_strchr(command, '='))
		to_remove = extract_params(command);
	else
		to_remove = extract_first_env(command, 1);
	while (lkd_env)
	{
		while (lkd_env->env_line[i] != '=')
			++i;
		to_extract = ft_strsub(lkd_env->env_line, 0, i);
		if (ft_strcmp(to_extract, to_remove) == 0)
		{
			lkd_env->prev->next = lkd_env->next;
			free(to_extract);
			break ;
		}
		free(to_extract);
		i = 0;
		lkd_env = lkd_env->next;
	}
	free(to_remove);
}
