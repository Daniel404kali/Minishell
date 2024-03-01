/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:31:12 by descamil          #+#    #+#             */
/*   Updated: 2024/02/29 17:19:05 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "get_next_line.h"

	/* NAMES */

typedef struct s_names
{
	pid_t	*proc;

	int		fd;
	int		num;
	int		argc;
	int		index;
	int		value;
	int		fd_tmp;
	int		num_comm;
	int		comm_midd;
	int		fd_infile;
	int		fd_outfile;

	int		fd_pipe[2];

	void	*output;

	char	*route;
	char	*input;
	char	*limiter;
	char	*command;
	char	*path_comm;

	char	**argv;
	char	**envp;
	char	**path;
	char	**entire_comm;
}			t_names;

	/* HERE */
	
typedef struct s_here
{
	char	*comm1;
	char	*comm2;
	char	*outfile;
	char	*limiter;
}			t_here;

typedef struct s_quote
{
	int		d_quote;
	int		s_quote;	
}		t_quote;

	/* MINI */

typedef struct s_mini
{
	t_here	*here;
	t_names	*names;
	t_quote	*quote;

	int		argc;
	int		count;
	int		num_error;

	char	*pwd;
	char	*error;
	char	*route;

	char	**split_line;
	char	**argv;
	char	**envp;
}			t_mini;

void	ft_set_values(t_mini *mini, char **argv, char **envp, int argc);

/* PWD */

char	*ft_find_pwd(t_mini *mini);

/* HERE DOC Y MULTIPLE */

void	ft_here_doc(t_mini *mini);


int		ft_strlen_b(const char *s);
int		ft_strchr_bonus(const char *s, int c);
int		ft_strrchr_bonus(const char *s, int c);
int		ft_strnstr(const char *s1, const char *s2, size_t len);

void	ft_last_comm(t_mini *mini);
void	ft_midd_comm(t_mini *mini);
void	ft_first_comm(t_mini *mini);
void	ft_error_bonus(char *str, int i);
void	ft_execute_bonus(t_mini *mini, char *argv);
void	ft_setvalues(t_mini *mini, char **argv, char **envp, int argc);

char	*ft_validate_comm_bonus(t_mini *mini, int i);
char	*ft_strjoin_bonus(char const *s1, char const *s2);

char	**ft_create_path_bonus(t_mini *mini);
char	**ft_split_bonus(const char *s, char c);

#endif