#include "get_next_line.h"

char	*ft_line(int fd, char *line)
{
	char	*buff;
	ssize_t	bytes_read;

	if (fd < 0)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(line, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buff);
			if (line)
				free(line);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		line = ft_strjoin(line, buff);
		if (!line)
		{
			free(buff);
			return (NULL);
		}
	}
	free(buff);
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*ft_next_line(char *line)
{
	char	*next_line;
	size_t	i;
	size_t	len;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	len = i;
	if (line[i] == '\n')
		len++;
	next_line = (char *)malloc(sizeof(char) * (len + 1));
	if (!next_line)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		next_line[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		next_line[i] = '\n';
		i++;
	}
	next_line[i] = '\0';
	return (next_line);
}

char	*new_line(char *line)
{
	char	*new_buffer;
	size_t	i;
	size_t	j;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
	{
		free(line);
		return (NULL);
	}
	i++;
	new_buffer = (char *)malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (!new_buffer)
	{
		free(line);
		return (NULL);
	}
	j = 0;
	while (line[i] != '\0')
		new_buffer[j++] = line[i++];
	new_buffer[j] = '\0';
	free(line);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char			*line;
	char				*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_line(fd, line);
	if (!line)
		return (NULL);
	next_line = ft_next_line(line);
	if (!next_line)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	line = new_line(line);
	return (next_line);
}