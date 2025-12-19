/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipykhtin <ipykhtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:09:06 by jdecorte          #+#    #+#             */
/*   Updated: 2025/12/19 18:13:56 by ipykhtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *buffer, char *buf)
{
    char	*temp;

    temp = ft_strjoin(buffer, buf);
    /* if join failed, do NOT free the original buffer here (caller will handle) */
    if (!temp)
        return (NULL);
    free(buffer);
    return (temp);
}
// ...existing code...
char	*ft_next(char *buffer)
{
    int		i;
    int		j;
    char	*line;

    if (!buffer)
        return (NULL);
    i = 0;
    while (buffer[i] && buffer[i] != '\n')
        i++;
    if (!buffer[i])
    {
        free(buffer);
        return (NULL);
    }
    if (buffer[i + 1] == '\0')
    {
        free(buffer);
        return (NULL);
    }
    line = ft_calloc((ft_strlen(buffer) - i), sizeof(char));
    if (!line)
    {
        free(buffer);
        return (NULL);
    }
    i++;
    j = 0;
    while (buffer[i])
        line[j++] = buffer[i++];
    free(buffer);
    return (line);
}
// ...existing code...
char	*ft_line(char *buffer)
{
    char	*line;
    int		i;

    if (!buffer)
        return (NULL);
    i = 0;
    if (!buffer[i])
        return (NULL);
    while (buffer[i] && buffer[i] != '\n')
        i++;
    if (buffer[i] == '\n')
        line = ft_calloc(i + 2, sizeof(char));
    else
        line = ft_calloc(i + 1, sizeof(char));
    if (!line)
        return (NULL);
    i = 0;
    while (buffer[i] && buffer[i] != '\n')
    {
        line[i] = buffer[i];
        i++;
    }
    if (buffer[i] && buffer[i] == '\n')
        line[i++] = '\n';
    return (line);
}
// ...existing code...
char	*read_file(int fd, char *res)
{
    char	*buffer;
    char	*old_res;
    int		byte_read;
    int     new_res;

    new_res = 0;
    if (!res)
    {
        res = ft_calloc(1, 1);
        if (!res)
            return (NULL);
        new_res = 1;
    }
    buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    if (!buffer)
    {
        if (new_res)
            free(res);
        return (NULL);
    }
    byte_read = 1;
    while (byte_read > 0)
    {
        byte_read = read(fd, buffer, BUFFER_SIZE);
        if (byte_read == -1)
        {
            free(buffer);
            if (new_res)
                free(res);
            return (NULL);
        }
        buffer[byte_read] = 0;
        old_res = res;
        res = ft_free(res, buffer);
        if (!res)
        {
            /* ft_strjoin failed; free temporary buffer and free res only if it was newly allocated */
            free(buffer);
            if (new_res && old_res)
                free(old_res);
            return (NULL);
        }
        if (ft_strchr(buffer, '\n'))
            break ;
    }
    free(buffer);
    return (res);
}
// ...existing code...
char	*get_next_line(int fd)
{
    static char	*buffer;
    char		*line;
    char		*tmp;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (read(fd, 0, 0) < 0)
    {
        if (buffer)
        {
            free(buffer);
            buffer = NULL;
        }
        return (NULL);
    }
    tmp = read_file(fd, buffer);
    if (!tmp)
    {
        if (buffer)
        {
            free(buffer);
            buffer = NULL;
        }
        return (NULL);
    }
    buffer = tmp;
    line = ft_line(buffer);
    /* If no line can be produced (buffer empty), free static buffer and return NULL.
       This prevents calling ft_next in situations where it would allocate a new
       leftover buffer that may never be freed by the caller. */
    if (!line)
    {
        if (buffer)
        {
            free(buffer);
            buffer = NULL;
        }
        return (NULL);
    }
    buffer = ft_next(buffer);
    return (line);
}