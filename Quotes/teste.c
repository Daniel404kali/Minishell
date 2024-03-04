/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:02:39 by descamil          #+#    #+#             */
/*   Updated: 2024/03/03 16:14:03 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (*s2 == '\0')
		return (1);
	while (s1[i] != '\0' && i < len)
	{
		if (s1[i] == s2[j])
		{
			k = i;
			while (s1[k] == s2[j] && s2[j] != '\0' && (k < len))
			{
				k++;
				j++;
				if (s2[j] == '\0')
					return (1);
			}
			j = 0;
		}
		i++;
	}
	return (0);
}

char	*ft_remove(char *dst, const char *src, int num)
{
	int i;

	i = 0;
	while (src[num] != '\0')
		dst[i++] = src[num++];
	while (dst[i] != '\0')
		dst[i++] = '\0';
	return (dst);
}

char	*ft_find(char **envp, char *str)
{
	char	*any;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if(ft_strnstr(envp[i], str, ft_strlen(str)) == 1)
		{
			any = envp[i];
			printf("%s\n", any);
			any = ft_remove(any, any, ft_strlen(str));
			printf("%s\n", any);
			return (any);
		}
		i++;
	}
	return ("");
}

int main(int argc, char **argv, char **envp)
{
	char *any;
	int i;

	argc += 0;
	argv[0] = argv[0];
	any = ft_find(envp, "asd=");

	printf(GREEN"ANY --> %s\n", any);

	return(0);
}