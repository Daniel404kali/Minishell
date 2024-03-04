/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_take_comm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:32:55 by descamil          #+#    #+#             */
/*   Updated: 2024/03/04 19:39:36 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	leaks(void)
{
	system("leaks -q Quotes");
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		i;
	
	if (argc == 1)
	{
		printf(PURPLE"FEW ARGS"RESET BLUE"	->"RESET RED"	[ERROR]\n"RESET);
		return (0);
	}
	ft_values(&data, argv, envp);
	

	i = 0;
	while (i != -1 && data.str[i] != '\0')
		i = ft_valid_quotes(&data, i);
	if (i == -1)
	{
		printf(RED"		[ERROR]\n"RESET);
		free(data.str);
		return (0);
	}
	else
	{
		printf(PURPLE"	%d\n"RESET, data.command_len);
		printf(CYAN"%s\n"RESET, data.str);
		printf(GREEN"		[VALID]\n"RESET);
	}
	// // r = ft_remove_quotes(&data);
	// printf(YELLOW"	[%s]\n"RESET, data.rm_str);
	// if (r == 0)
	// 	printf(RED"		[ERROR]\n"RESET);
	// else
	// 	printf(GREEN"		[VALID]\n"RESET);
	// while (envp[i])
	// 	printf("%s\n", envp[i++]);
	atexit(leaks);
	printf("%s\n", data.str);
	free(data.str);
	return (0);
}
