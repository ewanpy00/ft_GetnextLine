/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipykhtin <ipykhtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:36:57 by ipykhtin          #+#    #+#             */
/*   Updated: 2025/12/12 19:05:21 by ipykhtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return 1;
        s++;
    }
    if (c == '\0' && *s == '\0')
        return 1;
    return 0;
}
size_t ft_strlen(const char *s)
{
    size_t len = 0;
    while (s[len])
        len++;
    return len;
}

void ft_strcpy(char *dest, const char *src)
{
    size_t i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

char *ft_strdup(const char *s)
{
    size_t len = ft_strlen(s);
    char *dup = malloc(len + 1);
    if (!dup)
        return NULL;
    ft_strcpy(dup, s);
    return dup;
}

void ft_strncpy(char *dest, const char *src, size_t n)
{
    size_t i = 0;
    while (i < n && src[i])
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }
}