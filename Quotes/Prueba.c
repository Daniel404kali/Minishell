/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Prueba.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:34:01 by descamil          #+#    #+#             */
/*   Updated: 2024/03/04 19:29:01 by descamil         ###   ########.fr       */
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

char	*ft_set_zero(char *ptr, int point)
{
	int		len;

	len = ft_strlen(ptr);
	while (len-- >= point)
		ptr[len] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size_total;
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	size_total = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	ptr = (char *)malloc(sizeof(char) * (size_total + 1));
	if (ptr == NULL)
		return (NULL);
	while ((char *)s1 && (char)s1[i] != '\0')
		ptr[j++] = (char)s1[i++];
	j = 0;
	while ((char *)s2 && (char)s2[j] != '\0')
		ptr[i++] = (char)s2[j++];
	ptr[i] = '\0';
	if (!s1)
		free((char *)s1);
	return (ptr);
}


char	*ft_divjoin(char *str, char *any, int i)
{
	char 	*tmp;
	char	*final;
	int		length;
	int		j;
	int		k;
	int		l;

	k = i;
	l = i;
	j = 0;
	length = 0;
	while (str[l] != '\"')
		l++;
	k = l;
	while (str[k++] != '\0')
		length++;
	tmp = malloc(length + 1);
	if (tmp == NULL)
		return (NULL);
	while (str[l] != '\0')
		tmp[j++] = str[l++];
	tmp[j] = '\0';
	str = ft_set_zero(str, i);
	final = ft_strjoin(str, any);
	final = ft_strjoin(final, tmp);
	free(tmp);
	return (final);
}

int main(int argc, char **argv)
{
	char	*any = "123456789";
	char	*str;
	int		i = 2;
	
	str = malloc(ft_strlen(argv[1]) + 1);
	strlcpy(str, argv[1], ft_strlen(argv[1]) + 1);
	

	str = ft_divjoin(str, any, i);

	printf("%s\n", str);
	return (0);
}
