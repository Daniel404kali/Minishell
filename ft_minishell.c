/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:22:49 by descamil          #+#    #+#             */
/*   Updated: 2024/02/27 18:38:47 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_mini(void)
{
	write (1, "\t\t                                                      \n", 58);
	write (1, "\t\t _  _   __   __ _   __   ____  _  _  ____  __    __   \n", 58);
	write (1, "\t\t( \\/ ) (  ) (  ( \\ (  ) / ___)/ )( \\(  __)(  )  (  )  \n", 58);
	write (1, "\t\t/ \\/ \\  )(  /    /  )(  \\___ \\) __ ( ) _) / (_/\\/ (_/\\\n", 58);
	write (1, "\t\t\\_)(_/ (__) \\_)__) (__) (____/\\_)(_/(____)\\____/\\____/\n", 58);
	write (1, "\t\t                                                      \n", 58);
	write (1, "\t\t                                                      \n", 58);
}

char	*ft_validate_comm_term(t_mini *mini, int i)
{
	if (access(*mini->split_line, X_OK) == 0
		&& ft_strrchr_bonus(*mini->split_line, '/'))
		return (*mini->split_line);
	// if (access(*mini->split_line, X_OK) != 0
	// 	&& ft_strrchr_bonus(*mini->split_line, '/'))
	// 	write(1, "Command not found\n", 19);
	mini->names->command = ft_strjoin_bonus("/", mini->split_line[0]);
	while (mini->names->path[i] != NULL)
	{
		mini->names->path_comm = ft_strjoin_bonus(mini->names->path[i++], mini->names->command);
		if (access(mini->names->path_comm, X_OK) == 0)
			return (mini->names->path_comm);
	}
	write(1, "Command not found\n", 19);
	return (NULL);
}

void	ft_execute_term(t_mini *mini, char *argv)
{
	mini->split_line = ft_split_bonus(argv, ' ');
	if (mini->split_line == NULL)
		ft_error_bonus("Bad split", 1);
	mini->route = ft_validate_comm_term(mini, 1);
	execve(mini->route, mini->split_line, mini->names->envp);
}

int main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	char	*line;
	int		start;


	start = 1;
	ft_set_values(&mini, argv, envp, argc);
	while (1)
	{
		if (start == 1)
		{
			ft_print_mini();
			start = 0;
		}
		ft_find_pwd(&mini);
		if (mini.pwd == NULL)
			ft_error_bonus("Can't find pwd", 1);
		write(1, mini.pwd, ft_strlen(mini.pwd));
		line = get_next_line(0);
		if (line == NULL)
			break;
		mini.split_line = ft_split_bonus(line, ' ');
		int i = 0;
		while (mini.split_line[i])
			printf("%s\n", mini.split_line[i++]);
		ft_execute_term(&mini, line);
		// if (ft_funcions(&mini) == 0)
		// 	write(1, "Command not found", 18);
	}
}