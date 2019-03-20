/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:57:20 by lubenard          #+#    #+#             */
/*   Updated: 2019/03/20 20:04:52 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_env(t_env *lkd_env, char *command)
{
	t_env *new_element;

	(void)command;
	while (lkd_env->next)
		lkd_env = lkd_env->next;
	new_element = new_maillon();
	lkd_env->next = new_element;
	ft_strcpy(lkd_env->env_line, "FOO=bar");
}
