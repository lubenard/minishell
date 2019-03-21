/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:59:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/03/21 17:37:16 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_usage(void)
{
	ft_putstr("Please learn how to use echo\n");
}

void	echo(char *command)
{
	int i;
	int e;

	e = 0;
	i = 5;
	if (ft_strstr(command, "-n") != NULL)
	{
		e = 1;
		i = 8;
	}
	while (command[i])
		ft_putchar(command[i++]);
	if (e == 0)
		ft_putchar('\n');
}
