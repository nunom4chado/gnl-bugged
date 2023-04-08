#include "get_next_line.h"

int ft_strlen(char *str)
{
    int i = 0;
    if (!str)
        return (i);
    while(str[i])
        i++;
    return (i);
}

char *ft_strchr(char *str, char c)
{
    while(*str)
    {
        if (*str == c)
            return (str);
        str++;
    }
    return (NULL);
}

/**
 * if stopnl (stop new line) is truthy
 * will only join until new line
*/
char    *ft_strjoin(char *s1, char *s2, int stopnl)
{
    if (!s1)
    {
        s1 = malloc(1);
        s1[0] = '\0';
    }
    int i = 0;
    int len = ft_strlen(s1) + ft_strlen(s2);
    if (!len)
    {
        free(s1);
        return (NULL);
    }
    char *new = malloc(len + 1);
    while (s1[i])
    {
        new[i] = s1[i];
        i++;
    }
    while (*s2)
    {
        if (stopnl && *s2 == '\n')
        {
            new[i++] = '\n';
            break;
        }
        new[i++] = *s2++;
    }
    new[i] = '\0';
    free(s1);
    return (new);
}

char *has_line(char **next)
{
    char *line = NULL;
    char *tmp;
    char *newline;
    if (next && *next)
    {
        line = ft_strjoin(line, *next, 1);
        newline = ft_strchr(*next, '\n');
        if (newline)
        {
            // pay atention to newline + 1, cuz we want the char after the newline
            tmp = ft_strjoin(NULL, newline + 1, 0);
            free(*next);
            *next = tmp;
        }
        else
        {
            free(*next);
            *next = NULL;
        }
    }
    return (line);
}

char *get_next_line(int fd)
{
    int rbytes = 0;
    char *newline;
    char *buffer;
    static char *next = NULL;
    char *line = NULL;

    if (BUFFER_SIZE <= 0 || fd < 0)
        return (NULL);
    // if next has content copy to line
    line = has_line(&next);
    if (line)
        return (line);
    buffer = malloc(BUFFER_SIZE + 1);
    while((rbytes = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[rbytes] = '\0';
        // copy to line
        line = ft_strjoin(line, buffer, 1);
        newline = ft_strchr(buffer, '\n');
        if (newline)
        {
            // copy the content after newline to next
            next = ft_strjoin(next, newline + 1, 0);
            break;
        }
    }
    free(buffer);
    if (!line || rbytes == -1)
    {
        free(next);
        return (NULL);
    }
    return(line);
}

#include <fcntl.h>
#include <stdio.h>
int main(void)
{
    char *line;
    int fd;

    fd = open("files/multiple_line_no_nl", O_RDONLY);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}