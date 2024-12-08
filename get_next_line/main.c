#include "get_next_line.h"


#define path "multiple_nlx5"
int main ()
{
    int fd;
    char *line;

    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        printf("Error\n");
        return (1);
    }
    line = get_next_line(fd);
    printf("%s", line);


    close(fd);
    return (0);
}
