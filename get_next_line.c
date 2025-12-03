/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipykhtin <ipykhtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:36:29 by ipykhtin          #+#    #+#             */
/*   Updated: 2025/12/03 15:04:42 by ipykhtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int str_chr(const char *s, int c){
    while(*s){
        if(*s == (char)c)
            return 1;
        s++;
    }
    if(c == '\0' && *s == '\0')
        return 1;
    return 0;
}

char *extract_line(char **remainder){
    char *line;
    char *new_remainder;
    char *newline_pos;
    size_t line_length;

    if(!*remainder || **remainder == '\0')
        return NULL;
    newline_pos = strchr(*remainder, '\n');
    if(newline_pos){
        line_length = newline_pos - *remainder + 1;
        line = malloc(line_length + 1);
        if(!line)
            return NULL;
        strncpy(line, *remainder, line_length);
        line[line_length] = '\0';
        new_remainder = strdup(newline_pos + 1);
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
    size_t len1 = s1 ? strlen(s1) : 0;
    size_t len2 = s2 ? strlen(s2) : 0;
    char *new_str = malloc(len1 + len2 + 1);
    if(!new_str)
        return NULL;
    if(s1)
        strcpy(new_str, s1);
    if(s2)
        strcpy(new_str + len1, s2);
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
    // fd = open("text.txt", O_RDONLY);
    while(bytes_read = read(fd, buffer, BUFFER_SIZE), bytes_read > 0){
        buffer[bytes_read] = '\0';
        remainder = str_join_and_free(remainder, buffer);
        if(str_chr(remainder, '\n'))
            break;
    }
    return extract_line(&remainder);
}

int main(){
    int fd = open("text.txt", O_RDONLY);
    char *line;

    if (fd == -1)
        return 1;

    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}