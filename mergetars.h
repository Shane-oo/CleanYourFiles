#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/param.h>

#define TEMPLATE "/tmp/dir.XXXXXX"
#define NONDESRIEDTOKENS 2
#define MAX_FILENAME_LENGTH 255 //Linux has a maximum filename length of 255 characters
#define MAX_PATH_LENGTH 4096 //Linux has a maximum path of 4096 characters

extern char *create_Dir();

extern int run_extract(char * , char * );

extern void *extract_tar(char * , char * );

extern void *file_Details(char * , char * );

extern void clean(char * );

extern void *delete_files(char * );

extern void *run_create_tar(char * );

extern int create_output_tar(char * );

extern int mv_file(char * , char * );

extern void listdir(char * , char * , char * );

typedef struct fileData {
  char fileName[MAX_FILENAME_LENGTH];
  char filePath[MAX_PATH_LENGTH];
  int timeModified;
  int fileSize;
  int inOutputTar;
  char tempDirectory[sizeof(TEMPLATE)];
}fileData; // declare the global struct

typedef struct listOfFiles {
  struct listOfFiles *next; //point to the next pointer in list
  fileData node;
}listOfFiles;

typedef struct listOfTempDirs {
  struct listOfTempDirs *next; //point to the next pointer in list
  fileData node;

}listOfTempDirs;

static listOfTempDirs *listHeadOfTemps = NULL;

static listOfFiles *listHead = NULL;

extern char *place_file_into_diff_dir(char * , char * );

extern int add_To_List_Of_Files(char[], int, int, char * , char * );

extern listOfFiles *fileNameExits(char * );

extern void *file_atts(char * , char * , char * );

extern void *append_files(char * , char * , char * , char * );

extern int add_to_tar(char * , char * , char * );

extern listOfFiles *getHead();

