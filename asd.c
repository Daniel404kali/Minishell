/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:13:48 by descamil          #+#    #+#             */
/*   Updated: 2024/02/25 19:19:48 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int ft_size(char *str)
{
    int size;

    size = printf("%s", str);
    return (size);
}

int main(void)
{
    char    *str = "FRASE";
    int     size;
    
    size = ft_size(str);

    printf("Size = %d", size);
    return(0);
}
