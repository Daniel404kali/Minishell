/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:23:51 by descamil          #+#    #+#             */
/*   Updated: 2024/02/29 17:20:37 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_values(t_mini *mini, char **argv, char **envp, int argc)
{
	/* t_mini */

	mini->argv = argv;
	mini->envp = envp;
	mini->argc = argc;
	mini->count = 0;

	/* t_quote */

	mini->quote = malloc(sizeof(t_quote));

	/* t_here */

	mini->here = malloc(sizeof(t_here));

	/* t_names */

	mini->names = malloc(sizeof(t_names));
	mini->names->value = 'H';
	ft_setvalues(mini, argv, envp, argc);

}

void	ft_here_values(t_mini *mini, int j)
{
	mini->here->limiter = mini->argv[j + 1];
	mini->here->comm1 = mini->argv[j + 2];
	mini->here->comm2 = mini->argv[j + 3];
	mini->here->outfile = mini->argv[j + 4];
}

char	*ft_remove_pwd(char *dst, const char *src, int num, int i)
{
	while (src[num] != '\0')
		dst[i++] = src[num++];
	dst[i++] = ' ';
	dst[i++] = '$';
	dst[i++] = ' ';
	while (dst[i] != '\0')
		dst[i++] = '\0';
	return (dst);
}

char	*ft_find_pwd(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->envp[i])
	{
		if(ft_strnstr(mini->envp[i], "PWD=", ft_strlen_b("PWD=")) == 1)
		{
			mini->pwd = mini->envp[i];
			mini->pwd = ft_remove_pwd(mini->pwd, mini->pwd, 4, 0);
			return (mini->pwd);
		}
		i++;
	}
	return (NULL);
}