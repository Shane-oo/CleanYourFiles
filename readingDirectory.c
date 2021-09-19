#include "mergetars.h"
/*
	OPENING TEMPDIRECORTY AND READING FILES IN DIRECTORY
	IF FILE IN DIRECTORY IF A REGULAR FILE add_To_output_files() IS CALLED AND ITS ADDED TO THE DATASTRUCTURE
	IF FILE IS ANOTHER DIRECTORY ITSELF RECURSIVELY WALK THROUGH SUBDIRECTORY'(s) UNTIL REGULAR FILE'(s) ARE FOUND
*/
void *file_Details(char *currentDir, char *GarbageDir) {

  DIR *directory; //declare DIR pointer
  struct dirent *dir;
  directory = opendir(currentDir); //go into the desired directory
  if (directory == NULL) 
  {
    perror("Error oping directory: ");
    exit(EXIT_FAILURE);
  }
  char path[MAX_PATH_LENGTH];
  while ((dir = readdir(directory)) != NULL) 
  {
    struct stat statBuffer; 
    struct stat *p = &statBuffer;
    sprintf(path, "%s/%s", currentDir, dir->d_name);
    if (stat(path, p) != 0) 
    {
      perror("error occcured: ");	
    } 
    else if (S_ISREG(p->st_mode))
    {
      printf("%s is a regular file\n", path);
      file_atts(path, currentDir, GarbageDir);//get file data and add it to linked list

    } 
    else if (S_ISDIR(p->st_mode)) 
    {
      int size = strlen(path);
      if (path[size - 1] != '.') //dont not want to go into subDirs that end with "."
      {
        printf("%s is a subdirectory\n", path);
        listdir(path, currentDir, GarbageDir); //call a fucniton that perfroms a DFS of the sub directory
      }
    }
  }
  closedir(directory);
  return 0;
}
/*
	Function that uses stat to find the files time mod & byte size 
	and calls the function that would pottentially add it to the list of Files to be merged

*/
void *file_atts(char *file_Path, char *currentDir, char *GarbageDir) {
  struct stat statBuffer; 
  if (stat(file_Path, &statBuffer) == 0)
   {
    if ((add_To_List_Of_Files(file_Path, (int) statBuffer.st_mtime, (int) statBuffer.st_size, currentDir, GarbageDir)) == 0) 
    {	
      //FILE WAS ALLOWED MERGE
      printf("succesfully added %s to output_files\n", file_Path);

    } 
    else 
    {
      printf("dupilcate file not added to output_files %s GOING to GarbageDir %s\n", file_Path, GarbageDir);
      place_file_into_diff_dir(file_Path, GarbageDir);
    }
  }
  return 0;
}
