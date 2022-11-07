/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 20:42:44 by rlaforge          #+#    #+#             */
/*   Updated: 2022/11/07 17:46:54 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*dest;

	dest = malloc(sizeof(char) * (ft_strlen(s) + 1));
	ft_strcpy(dest, (char *)s);
	return (dest);
}

static void	ft_count(int n, int i[2])
{
	int	x;

	i[0] = 1;
	i[1] = 0;
	if (n < 0)
		i[1]++;
	x = n;
	while (x >= 10 || x <= -10)
	{
		x /= 10;
		i[0]++;
	}
}

char	*ft_itoa(int n)
{
	char	*tab;
	int		i[2];

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	ft_count(n, i);
	if (i[1])
		n = -n;
	tab = malloc(sizeof(char) * ((i[0] += i[1]) + 1));
	if (!tab)
		return (NULL);
	tab[i[0]] = '\0';
	while (i[0]--)
	{
		tab[i[0]] = (n % 10) + '0';
		n /= 10;
	}
	if (i[1])
		tab[0] = '-';
	return (tab);
}
