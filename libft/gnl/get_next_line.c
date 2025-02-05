#include "../libft.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

static int	read_file(int fd, char **remainder, char *buffer)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (bytes_read);
	buffer[bytes_read] = '\0';
	if (!*remainder)
		*remainder = ft_strdup("");
	temp = ft_strjoin(*remainder, buffer);
	free(*remainder);
	*remainder = temp;
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*buffer;
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (!remainder || !ft_strchr(remainder, '\n'))
	{
		bytes_read = read_file(fd, &remainder, buffer);
		if (bytes_read <= 0 && !remainder)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	line = get_line(&remainder);
	return (line);
}