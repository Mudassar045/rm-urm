# rm-urm (mdrm)
rm-urm is Linux based utility which is based on GNU C to remove file permanently and recover file from meta data. It's a research based project, fetching data from meta data. At beginning, rm-urm will work for singal file/directory but later on it will surely handle multiple files/directories.
** User Modes **
```
1. Interactive mode
2. Non-Interactive mode
```
** Options **
```
-s  : secure removal of file by rewritting bytes with **_NULL** or with anything
-i  : let enable interactive mode so user can remove files interactively
-d  : to remove directory recursively
-fg : to get a file which is deleted intentionally or unintentionaly
-dg : to get a directory which is deleted intentionally or unintentionaly  
```
