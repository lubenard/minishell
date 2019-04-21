/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:57:20 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/21 10:23:47 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_first_env(char *command)
{
	int i;

	i = 0;
	while (command[i] != '=' && command[i])
		++i;
	return (ft_strsub(command, 0, i));
}

void	set_env(t_env *lkd_env, char *command)
{
	t_env	*new_element;
	char	*to_add;
	char	*to_extract;
	char	*to_search;

	to_search = extract_first_env(command);
	to_add = extract_params(command);
	while (lkd_env->next)
	{
		to_extract = extract_first_env(lkd_env->env_line);
		printf("lkd_env->env_line = %s\nto_search = %s\nBRUH = %d\n",to_extract,to_search,ft_strcmp(to_extract, to_add));
		if (ft_strcmp(to_extract, to_search) == 0)
			unset_env(lkd_env, to_add);
		lkd_env = lkd_env->next;
		free(to_extract);
	}
	free(to_search);
	free(to_add);
	new_element = new_maillon();
	lkd_env->next = new_element;
	ft_strcpy(lkd_env->env_line, to_add);
}
