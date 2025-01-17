#include "get_next_line_bonus.h"

char	*line_reader(int fd, char *str_buf)
{
	char	*str;
	int		swcth;

	str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	swcth = 1;
	while (!ft_strchr(str_buf, '\n') && swcth != 0)
	{
		swcth = read(fd, str, BUFFER_SIZE);
		if (swcth == -1)
		{
			free(str);
			return (NULL);
		}
		str[swcth] = '\0';
		str_buf = ft_strjoin(str_buf, str);
	}
	free(str);
	return (str_buf);
}

char	*line_creater(char *str_buf)
{
	char	*str;
	int		i;

	i = 0;
	if (!str_buf[i])
		return (NULL);
	while (str_buf[i] && str_buf[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (str_buf[i] && str_buf[i] != '\n')
	{
		str[i] = str_buf[i];
		i++;
	}
	if (str_buf[i] == '\n')
	{
		str[i] = '\n';
		str[i + 1] = '\0';
	}
	else
		str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str_buf[4096];
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str_buf[fd] = line_reader(fd, str_buf[fd]);
	if (!str_buf[fd])
		return (NULL);
	str = line_creater(str_buf[fd]);
	str_buf[fd] = ft_new_str_buf(str_buf[fd]);
	return (str);
}
