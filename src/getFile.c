#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#define MAX_BYTES 1024
#define MAX_CHARS 1024
char *concat1(const char *, const char *);
int isAvailableFile(char *filename);
int getFile(char *filename)
{
        if (isAvailableFile(filename) == 0)
        {
                struct stat mystat;
                char buff[MAX_CHARS];
                char *oldFilePath = concat1(".mdrm_temp/", filename);
                int rv = stat(oldFilePath, &mystat);
                int mode_t = mystat.st_mode;
                int fdf = open(oldFilePath, O_RDONLY);
                int fds = open(filename, O_TRUNC | O_CREAT | O_RDWR, mode_t);
                if (fds == -1)
                {
                        fprintf(stderr, "rm: unable to get file");
                        exit(0);
                }
                else
                {
                        while (1)
                        {
                                int byte_t = read(fdf, buff, MAX_BYTES);
                                if (byte_t <= 0)
                                {
                                        break; // file reading complete
                                }
                                write(fds, buff, byte_t);
                        }
                }
                close(fdf); // file descriptor 
                close(fds); // file descriptor 
                rv = remove(oldFilePath);
                if (rv == -1)
                {
                        fprintf(stderr, "rm: unable to perform get operation");
                        return -1;
                }
                else
                        return 0;
        }
        else
        {
                return -1;
        }
}
char *concat1(const char *s1, const char *s2)
{
        char *result = malloc(strlen(s1) + strlen(s2) + 1); //+1 for the null-terminator
        //in real code you would check for errors in malloc here
        strcpy(result, s1);
        strcat(result, s2);
        return result;
}
int isAvailableFile(char *filename)
{
        char *filepath = concat1(".mdrm_temp/", filename);
        int fd = open(filepath, O_RDONLY);
        if (fd == -1)
        {
                return -1;
        }
        else
        {
                return 0;
        }
}