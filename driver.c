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
int isDirectory(char *dirname);
int isRegularFile(char *filename);
int isEmpty(char *filename);
int makeTempDir(char *dirname);
int isDirEmpty(char *dirname);
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
  else if (argc == 2 && isFile(args[1]) == 0)
  {
    int rv = removeFile(args[1]);
    if (rv == 0)
    {
      return 0;
    }
    else
    {
      fprintf(stderr, "mdrm: unable to delete a file\n");
    }
  }
  else if (argc == 2 && isDirectory(args[1]) == 0)
  {
    if (isDirEmpty(args[1]) == 0)
    {
      int rv = removeDir(args[1]);
      if(rv ==0) return 0;
      else
      {
        printf("mdrm: failed to remove '%s' directory\n", args[1]);
      }
    }
    else
    {
      printf("mdrm: failed to remove '%s': Directory not empty\n", args[1]);
    }
  }
  else if (argc == 3 && isFile(args[1]) == 0 && strcmp(args[2], "-i") == 0)
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
  else if (argc == 3 && isFile(args[1]) == 0 && strcmp(args[2], "-fg") == 0)
  {

    int rv = getFile(args[1]);
    if (rv == 0)
    {
      return 0;
    }
    else
    {
      printf("urm: unable to locate %s file or directory\n", args[1]);
      return 0;
    }
  }
  else if (argc == 3 && isDirectory(args[1] == 0 && strcmp(args[2], "-rd")))
  {
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
  struct stat fs;
  int rv = stat(filename, &fs);
  if (rv == 0)
  {
    int t_mode = fs.st_mode;
    if (S_ISREG(t_mode))
      return 0;
    return -1;
  }
  else
  {
    perror("stat");
    exit(rv);
  }
}
int isDirectory(char *dirname)
{
  struct stat fs;
  int rv = stat(dirname, &fs);
  if (rv == 0)
  {
    int t_mode = fs.st_mode;
    if (S_ISDIR(t_mode))
      return 0;
    return -1;
  }
  else
  {
    perror("stat");
    exit(rv);
  }
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
    return -1;
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
int isDirEmpty(char *dirname)
{
  DIR *dp = opendir(dirname);
  int hasContent = 0;
  errno = 0;
  struct dirent *entry;
  if (dp == NULL)
  {
    fprintf(stderr, "mdrm: failed to remove '%s': No such file or directory", dirname);
    exit(0);
  }
  while (1)
  {
    entry = readdir(dp);
    if (entry != NULL && errno != 0)
    {
      fprintf(stderr,"mdrm: failed to remove '%s': No such file or directory",dirname);
      exit(0);
    }
    if (entry == NULL && errno == 0)
    {
      fprintf(stderr,"mdrm: failed to remove '%s': No such file or directory",dirname);
      exit(0);
    }
    else
    {
      //checck for hidden items
      if (entry->d_name[0] == '.')
        continue;
      hasContent++;
    }
  }
  if(hasContent!=0) return -1;
  return 0;
  closedir(dp);
}
