/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:37:25 by lubenard          #+#    #+#             */
/*   Updated: 2019/03/21 18:21:37 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_maillon(void)
{
	t_env		*new_element;

	if (!(new_element = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

t_env	*get_env(char **env)
{
	t_env	*lkd_env;
	t_env	*tmp;
	int		i;
	t_env	*new_element;

	i = 0;
	lkd_env = new_maillon();
	tmp = lkd_env;
	while (env[i])
	{
		ft_strcpy(lkd_env->env_line, env[i]);
		new_element = new_maillon();
		lkd_env->next = new_element;
		lkd_env->next->prev = lkd_env;
		lkd_env = lkd_env->next;
		++i;
	}
	return (tmp);
}
