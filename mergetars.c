
//  Author:             Shane Monck


#include "mergetars.h"

int main(int argc, char * argv[]) {
  //Checking for correct input
  if (argc == 1)
  {
    printf("No input paramter in command line\nExpected :./mergetars input_tarfile1[input_tarfile2 ...] output_tarfile");
    exit(EXIT_FAILURE);
  }
  char outputTarFile[MAX_PATH_LENGTH];
  strcpy(outputTarFile ,argv[argc - 1]);
  run_create_tar(outputTarFile); //creating the output tar file 

  char *GarbageDir = NULL;
  GarbageDir = create_Dir(); //create a directory where files not to be merged will go
  strcat(GarbageDir, "/");

  int input = 1; //walk through command line but not last command line entry
  char *tempDirectory = NULL;
  while (input != argc - 1) 
  {
    tempDirectory = create_Dir(); //create directory where tar files will be emptied to
    strcat(tempDirectory, "/");

    extract_tar(argv[input], tempDirectory); //untar files into the temporary directory

    file_Details(tempDirectory, GarbageDir); //Read the files now in tempDirectory and add them to the linked list of files
    										 //otherwise send file to Garbage Directory

    // STORE TEMP DIRECTORIES INTO A LIST, SO THEY ARE REMBERED & SO THEY CAN BE CLEANED 
    listOfTempDirs *TempDirNode = NULL;
    TempDirNode = realloc(TempDirNode, sizeof( *TempDirNode)); 
    snprintf(TempDirNode->node.tempDirectory, sizeof(TempDirNode->node.tempDirectory), "%s", tempDirectory);//save the temp directory in node
    TempDirNode->next = listHeadOfTemps;
    listHeadOfTemps = TempDirNode;
    input++;
  }

  listOfFiles *headOfFilesList = getHead(); //get the Head of the linked list of files created inside linkedList.c
  listOfFiles *tempForAppending = headOfFilesList;
 
  // APPEND FINAL FILES IN LINKED LIST OF FILES INTO THE OUTPUT TAR FILE 
  while (tempForAppending != NULL) 
  {
    if (tempForAppending->node.inOutputTar != -1) //append files that are not marked as being in outputTar
    {
      printf("APPENDING %s to %s\n", tempForAppending->node.fileName,outputTarFile );
      append_files(outputTarFile , tempForAppending->node.tempDirectory, GarbageDir, tempForAppending->node.fileName); //add to outputTar
      tempForAppending->node.inOutputTar = -1;
      
    }
    place_file_into_diff_dir(tempForAppending->node.filePath, GarbageDir); //move file to garbage
    tempForAppending = tempForAppending->next;
  }

  // PERFORM CLEANING OF GARBAGE DIRECTORY AND ALL TEMP DIRECTORIES MADE
  clean(GarbageDir);
  listOfTempDirs *tempForCleaningDirs = listHeadOfTemps;
  while (tempForCleaningDirs  != NULL) 
  {
    clean(tempForCleaningDirs -> node.tempDirectory);
    tempForCleaningDirs = tempForCleaningDirs-> next;
  }
  free(tempDirectory);
  free(GarbageDir);
  free(headOfFilesList);
  free(tempForAppending);
  return 0;
}
