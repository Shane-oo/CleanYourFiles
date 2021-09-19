#include "mergetars.h"
/*
	Depth First Sarch of sub directory
	finds the file and will then call file_atts that will determine the files attributes and add to linked list
	recursivly walks through sub directories until file is found or until directory is empty

	the do while depth first traverseal was adapted from a stack overflow post
	LINK: https://stackoverflow.com/questions/32629597/traversing-directories-using-depth-first-search-in-linux-c
*/
void listdir(char *pathName, char *currentDir, char *GarbageDir) {

  DIR *directory;
  struct dirent *dir;
  if (!(directory = opendir(pathName)))
  {
    return;
  }
  if (!(dir = readdir(directory)))
  {
    return;
  }
  char path[MAX_PATH_LENGTH];
  do {
    if (dir->d_type == DT_DIR) //is another directory
    {
      int len = snprintf(path, sizeof(path) - 1, "%s/%s", pathName, dir -> d_name);
      path[len] = 0;
      if (strcmp(dir -> d_name, ".") == 0 || strcmp(dir -> d_name, "..") == 0) //dont go into directories ending with "."
      {
        continue;
      }

      listdir(path, currentDir, GarbageDir); //recursive call
    } 
    else 
    {
      printf("file: %s\n", dir -> d_name);
      strcat(pathName, "/");
      //save the file pathName so other files in directory can be checked
      char *namedup = NULL;
      namedup = realloc(namedup, strlen(pathName)*sizeof(*namedup));//namedup = realloc(namedup, MAX_PATH_LENGTH*sizeof(*namedup));
      strcpy(namedup, pathName);
      strcat(pathName, dir -> d_name);
      file_atts(pathName, currentDir, GarbageDir);
      strcpy(pathName, namedup);
    }
  } while ((dir = readdir(directory)) != NULL);
  closedir(directory);

}
