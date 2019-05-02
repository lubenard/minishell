/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:44:57 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/02 13:27:24 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_multiple_command(char *command, char **path, t_env *lkd_env)
{
	char **tab;
	int i;

	i = 0;
	tab = ft_strsplit(command, ';');
	while (tab[i])
	{
		get_command(tab[i], path, lkd_env);
		i++;
	}
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return ;
}
