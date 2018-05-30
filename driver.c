/*
  Name: rm-urm utility
  Environment: Linux based operating system
  Developer: Mudassar Ali
  Resident: Lahore, Pakistan
  Language: GNU C
  Version: 1.0.0
*/
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "rmutils.h"
#include "urmutils.h"

#define DEFAULT_MODE 0700
#define DIR_NAME ".mdrm_temp"

extern int errno;
int isFile(char *filename);
int isDir(char *dirname);
int isRegularFile(char *filename);
int isEmpty(char *filename);
int makeTempDir(char *dirname);
int main(int argc, char **args)
{
  char choice;
  DIR *dir = opendir(DIR_NAME);
  errno = 0;
  if (dir == NULL)
  {
    int rv = makeTempDir(".mdrm_temp");
  }
  if (argc == 1)
  {
    fprintf(stderr, "rm: missing operands\nTry 'rm --help' for more information.\n");
  }
  else if (argc == 2 && isFile(args[1]))
  {
    int rv = removeFile(args[1]);
    if (rv == 0)
    {
      return 0;
    }
    else
    {
      fprintf(stderr, "rm: unable to delete a file\n");
    }
  }
  else if (argc == 2 && isDir(args[1]))
  {
    removeDir(args[1]);
  }
  else if (argc == 3 && isFile(args[1]) && strcmp(args[2], "-i") == 0)
  {
    if (isRegularFile(args[1]) == 0)
    {
      printf("rm: remove regular file (Y|N)? ");

      while ((choice = getchar()) != '\n' && choice != EOF)
      {
        if (choice == 'y' || choice == 'Y')
        {
          int rv = removeFile(args[1]);
          if (rv == 0)
          {
            return 0;
          }
          else
          {
            fprintf(stderr, "rm: unable to delete file\n");
            return 0;
          }
        }
        else if (choice == 'n' || choice == 'N')
        {
          return 0;
        }
        else
        {
          fprintf(stderr, "rm: invalid option\n");
        }
      }
    }
    else
    {
      return 0;
    }
  }
  else if (argc == 3 && isFile(args[1]) && strcmp(args[2], "-fg") == 0)
  {

    int rv = getFile(args[1]);
    if (rv == 0)
    {
      return 0;
    }
    else
    {
      printf("urm: unable to locate %s file or directory\n",args[1]);
      return 0;
    }
  }
  return 0;
}
int makeTempDir(char *dirname)
{
  int rv = mkdir(dirname, DEFAULT_MODE);
  return rv;
}
int isFile(char *filename)
{
  return 1;
}
int isDir(char *dirname)
{
  return 1;
}
int isRegularFile(char *filename)
{
  struct stat fs;
  int rv = stat(filename, &fs);
  if (rv == 0)
  {
    int t_mode = fs.st_mode;
    if (S_ISREG(t_mode))
      return 0;
    return 0;
  }
  else
  {
    perror("stat");
    exit(rv);
  }
}
int isEmpty(char *filename)
{
  return 1;
}