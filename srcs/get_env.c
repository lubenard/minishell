/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:37:25 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/03 22:09:38 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_maillon(void)

{
	t_env		*new_element;

	if (!(new_element = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	ft_bzero(new_element->env_line, 2056);
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
	if (env == NULL)
		return (NULL);
	while (env[i])
	{
		ft_strcpy(lkd_env->env_line, env[i]);
		if (env[i + 1] != NULL)
		{
			new_element = new_maillon();
			lkd_env->next = new_element;
			lkd_env->next->prev = lkd_env;
			lkd_env = lkd_env->next;
		}
		++i;
	}
	return (tmp);
}
