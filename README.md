# rm-urm (mdrm)
rm-urm is Linux based utility which is based on GNU C to remove file permanently and recover file from meta data. It's a research based project, fetching data from meta data. 
At beginning, rm-urm will work as trash bin for singal file/directory but later on it will surely handle multiple files/directories.

### MDRM-TrashBin Specifications

**User Modes**
```
1. Interactive mode
2. Non-Interactive mode
```
**Options**
```
-s  : secure removal of file by rewritting bytes with NULL or with anything
-i  : let enable interactive mode so user can remove files interactively
-rd : to remove directory recursively
-fg : to get a file which is deleted intentionally or unintentionaly
-dg : to get a directory which is deleted intentionally or unintentionaly
-sd : secure removal of directory having contents.
```
**Install/Uninstall Procedure**
```
1. make
2. make clean
3. make install
