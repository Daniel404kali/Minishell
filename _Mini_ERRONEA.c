/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _Mini_ERRONEA.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:34:45 by descamil          #+#    #+#             */
/*   Updated: 2024/02/27 17:24:47 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	int		i;

	i = -1;
	ft_set_values(&mini, argv, envp, argc);

	while (mini.count < argc)
	{
		if (ft_strnstr(argv[mini.count], "here_doc", ft_strlen_b("here_doc")) == 1)
		{
			ft_here_values(&mini, mini.count);
			ft_here_doc(&mini);
			unlink(".here_doc");
			mini.count += 4;
		}
		else if (ft_strnstr(argv[mini.count], "cd", ft_strlen_b("cd")) == 1)
		{	
			printf("CD = %d\n", mini.count++);
			printf("RUTA = %d\n", mini.count);
		}
		else if (ft_strnstr(argv[mini.count], "pwd", ft_strlen_b("pwd")) == 1)
		{
			if (ft_find_pwd(&mini) == 1)
				write(1, mini.pwd, ft_strlen(mini.pwd));
			else
				ft_error_bonus("Can't find PWD", 1);
		}
		else if (ft_strnstr(argv[mini.count], "echo", ft_strlen_b("echo")) == 1)
			printf("ECHO\n");
		else if (ft_strnstr(argv[mini.count], "export", ft_strlen_b("export")) == 1)
			printf("EXPORT\n");
		else if (ft_strnstr(argv[mini.count], "unset", ft_strlen_b("unset")) == 1)
			printf("UNSET\n");
		else if (ft_strnstr(argv[mini.count], "env", ft_strlen_b("env")) == 1)
			printf("ENV\n");
		else if (ft_strnstr(argv[mini.count], "exit", ft_strlen_b("exit")) == 1)
			printf("EXIT\n");
		mini.count++;
	
	}
	return (0);
}
	// while (++i < mini.argc)
	// 	printf("POSICION ->	[%d]\tCONTENIDO -->	[ %s ]\n", i, mini.argv[i]);
	// printf("LIMITER	=	%s\n", mini.here->limiter);