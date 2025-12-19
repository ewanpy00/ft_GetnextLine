/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan <ivan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:09:06 by jdecorte          #+#    #+#             */
/*   Updated: 2025/12/19 18:44:24 by ivan             ###   ########.fr       */
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
static char	*ft_realloc_join(char *s1, char *s2, size_t s1_len, size_t s2_len)
{
	char	*res;
	size_t	i;
	size_t	j;

	res = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < s2_len)
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = 0;
	return (res);
}

char	*read_file(int fd, char *res)
{
    char	*buffer;
    char	*old_res;
    char	*new_res;
    int		byte_read;
    int     res_owned;
    size_t  res_len;
    size_t  buffer_len;

    res_owned = 0;
    res_len = 0;
    if (!res)
    {
        res = ft_calloc(1, 1);
        if (!res)
            return (NULL);
        res_owned = 1;
        res_len = 0;
    }
    else
    {
        res_len = ft_strlen(res);
    }
    buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    if (!buffer)
    {
        if (res_owned)
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
            /* Only free res if we own it (newly allocated in this function).
               If res was passed from outside (static buffer), let caller handle it */
            if (res_owned)
                free(res);
            return (NULL);
        }
        if (byte_read == 0)
            break;
        buffer[byte_read] = 0;
        buffer_len = byte_read;
        old_res = res;
        new_res = ft_realloc_join(res, buffer, res_len, buffer_len);
        if (!new_res)
        {
            /* ft_realloc_join failed; don't free old_res here (caller will handle it).
               Free the temporary buffer. */
            free(buffer);
            if (res_owned)
                free(old_res);
            return (NULL);
        }
        /* If we owned the old res, free it now. Otherwise, let caller handle it. */
        if (res_owned)
            free(old_res);
        res = new_res;
        res_owned = 1;
        res_len += buffer_len;
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
        /* If read_file failed:
           - read_file only frees buffers it allocated (res_owned = 1)
           - If buffer was passed to read_file, it was NOT freed by read_file
           - So we need to free buffer here if it exists */
        if (buffer)
        {
            free(buffer);
            buffer = NULL;
        }
        return (NULL);
    }
    /* If buffer was passed to read_file and read_file succeeded, buffer was
       replaced by tmp. We need to free the old buffer if it exists. */
    if (buffer && buffer != tmp)
    {
        free(buffer);
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