#include "mergetars.h"

/*
	depth first search to find files and call clean() to remove the file
*/
void *delete_files(char *filename) {
    DIR *directory;
   struct dirent *dir;
  if (!(directory = opendir(filename)))
  {
    return 0;
  }
  if (!(dir = readdir(directory)))
  {
    return 0;
  }
  char path[MAX_PATH_LENGTH];
  do {
    if (dir->d_type == DT_DIR)
    {
      int len = snprintf(path, sizeof(path) - 1, "%s/%s", filename, dir->d_name);
      path[len] = 0;
      if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)//dont go into directories ending with "."
      {
        continue;
      }
      delete_files(path);
    } 
    else {

      strcat(filename, "/");
      char *namedup = NULL; //create duplicate of filename so other files can be removed 
      namedup = realloc(namedup, MAX_PATH_LENGTH);
      strcpy(namedup, filename);
      strcat(filename, dir->d_name);
      clean(filename);//delete file
      strcpy(filename, namedup);//remake back to duplicate
    }
  } while ((dir = readdir(directory)) != NULL);
  closedir(directory);
  return 0;
}
/*
	recursilvey delete all empty sub directories in temp directory
*/
void *delete_Empty_SubDis(char *subDir) {

  DIR * directory;
  struct dirent * dir;

  if (!(directory = opendir(subDir)))
  {
    return 0;
  }
  if (!(dir = readdir(directory)))
  {
    return 0;
  }  
  char path[MAX_PATH_LENGTH];
  do {
    if (dir->d_type == DT_DIR)
     {
      int len = snprintf(path, sizeof(path) - 1, "%s/%s", subDir, dir -> d_name);
      path[len] = 0;
      if (strcmp(dir -> d_name, ".") == 0 || strcmp(dir -> d_name, "..") == 0)
      {
        continue;
      }
      remove(path); //deletes empty sub dir
      delete_Empty_SubDis(path);
    }

  } while ((dir = readdir(directory)) != NULL);

  closedir(directory);
  remove(path);
  return 0;
}
/*
	cleans the tempDirectoy and all of its files
*/
void clean(char *filepath) {
  int size = strlen(filepath);
  if (filepath[size] != '.') //dont go into sub dirs ending in'.'
  {
    delete_files(filepath);
  }
  int del = remove(filepath);
  if (del != 0) //filepath contains more files to delete
  {
    delete_files(filepath);
    delete_Empty_SubDis(filepath);
    del = remove(filepath);
    if (del != 0)
    {
      printf("error has occured\n");
    }
    else
    {
    	printf("succesful clean of all files in %s is deleted\n",filepath);
    }
  }
}
