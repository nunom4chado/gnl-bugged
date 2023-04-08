#include "get_next_line.h"

int ft_strlen(char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return (i);
}

char    *ft_strjoin(char *s1, char *s2)
{
    if (!s1)
    {
         s1 = malloc(1);
        *s1 = '\0';
    }
    char *to_free = s1;
    char *new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    int i = 0;
    while (*s1)
        new[i++] = *s1++;
    while (*s2)
        new[i++] = *s2++;
    new[i] = '\0';
    free(to_free);
    return (new);
}

char *get_next_line(int fd)
{
    int rbytes = 0;
    char *buffer;
    static char *data = NULL;
    static char *next = NULL;
    char *line = NULL;
    int i;

    if (BUFFER_SIZE <= 0 || fd < 0)
        return (NULL);
    if (!data)
    {
        buffer = malloc(BUFFER_SIZE + 1);
        while((rbytes = read(fd, buffer, BUFFER_SIZE)) > 0)
        {
            buffer[rbytes] = '\0';
            data = ft_strjoin(data, buffer);
        }
        free(buffer);
        next = data;
    }
    if (!data)
        return (NULL);
    i = 0;
    while(next[i] && next[i] != '\n')
        i++;
    if (next[i] == '\n')
        i++;
    if (!i)
    {
        free(data);
        return (NULL);
    }
    line = malloc(i + 1);
    i = 0;
    while(*next && *next != '\n')
        line[i++] = *next++;
    if (*next == '\n')
        line[i++] = *next++;
    line[i] = '\0';
   
    if (!*next)
    {
        free(data);
        data = NULL;
    }
    return(line);
}
/*
#include <fcntl.h>
#include <stdio.h>
int main(void)
{
    char *line;
    int fd;

    fd = open("files/42_with_nl", O_RDONLY);
    while (1)
    {
        line = get_next_line(fd);
        printf("%s", line);
        if (!line)
            break;
        free(line);
    }

    close(fd);
    return (0);
}
*/