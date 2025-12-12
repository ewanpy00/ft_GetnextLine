/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipykhtin <ipykhtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:36:29 by ipykhtin          #+#    #+#             */
/*   Updated: 2025/12/12 19:04:57 by ipykhtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char *extract_line(char **remainder){
    char *line;
    char *new_remainder;
    char *newline_pos;
    size_t line_length;

    if(!*remainder || **remainder == '\0')
        return NULL;
    newline_pos = ft_strchr(*remainder, '\n');
    if(newline_pos){
        line_length = newline_pos - *remainder + 1;
        line = malloc(line_length + 1);                                                                                                                 
        if(!line)
            return NULL;
        ft_strncpy(line, *remainder, line_length);
        line[line_length] = '\0';
        new_remainder = ft_strdup(newline_pos + 1);
        free(*remainder);
        *remainder = new_remainder;
    } else {
        line = strdup(*remainder);
        free(*remainder);
        *remainder = NULL;
    }
    return line;
}

static char *str_join_and_free(char *s1, char *s2){
    size_t len1;
    size_t len2;
    len1 = 0;
    len2 = 0;
    if(s1)
        len1 = ft_strlen(s1);
    if(s2)
        len2 = ft_strlen(s2);
    char *new_str = malloc(len1 + len2 + 1);
    if(!new_str)
        return NULL;
    if(s1)
        ft_strcpy(new_str, s1);
    if(s2)
        ft_strcpy(new_str + len1, s2);
    new_str[len1 + len2] = '\0';
    free(s1);
    return new_str;
}

char *get_next_line(int fd){
    static char *remainder;
    char buffer[BUFFER_SIZE + 1];
    ssize_t bytes_read;

    if(fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    while(bytes_read = read(fd, buffer, BUFFER_SIZE), bytes_read > 0){
        buffer[bytes_read] = '\0';
        remainder = str_join_and_free(remainder, buffer);
        if(ft_strchr(remainder, '\n'))
            break;
    }
    return extract_line(&remainder);
}

// int main(){
//     int fd = open("text.txt", O_RDONLY);
//     char *line;

//     if (fd == -1)
//         return 1;

//     while ((line = get_next_line(fd)) != NULL) {
//         printf("%s", line);
//         free(line);
//     }

//     close(fd);
//     return 0;
// }