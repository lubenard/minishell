/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:05:25 by lubenard          #+#    #+#             */
/*   Updated: 2019/03/21 17:54:20 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*extract_params(char *command)
{
	int		i;
	int		e;
	char	*ret;

	i = 0;
	while (command[i] != ' ')
		++i;
	while (command[i] == ' ')
		++i;
	e = i;
	while (command[e])
		++e;
	ret = ft_strsub(command, i, e);
	return (ret);
}

void		unset_env(t_env *lkd_env, char *command)
{
	char	*to_extract;
	int		i;
	char	*to_remove;

	i = 0;
	to_remove = extract_params(command);
	while (lkd_env->next)
	{
		while (lkd_env->env_line[i] != '=')
			++i;
		to_extract = ft_strsub(lkd_env->env_line, 0, i);
		if (ft_strcmp(to_extract, to_remove) == 0)
			lkd_env->prev->next = lkd_env->next;
		free(to_extract);
		i = 0;
		lkd_env = lkd_env->next;
	}
	free(to_remove);
}
