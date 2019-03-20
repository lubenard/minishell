/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:15:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/03/20 19:00:55 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_env *lkd_env)
{
	while (lkd_env->next)
	{
		ft_putstr(lkd_env->env_line);
		ft_putchar('\n');
		lkd_env = lkd_env->next;
	}
}
