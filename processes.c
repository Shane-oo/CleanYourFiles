#include "mergetars.h"

/*
	UNTAR INPUT TAR FILE INTO A TEMP DIRECOTRY
*/
int run_extract(char *tarName, char *tempDirectory) {
  printf("extract %s files into %s\n", tarName, tempDirectory);
  int pid = fork(); //create child process
  switch (pid) {
  case -1:
    perror("Error cannot fork: ");
    exit(EXIT_FAILURE);
    break;
  case 0: {
    //using built in tar on MAC OS UNIC to untar file into tempDirectory
    if (execl("/usr/bin/tar", "-xvf", "-xf", tarName, "-C", tempDirectory, NULL) != -1)
    {
      exit(EXIT_SUCCESS);
    } 
    else
    {
      perror("Error: ");
      exit(EXIT_FAILURE);
    }
    break;
  	}
  }
  return pid;
}

/*
	MOVE (mv) FILE FROM TEMPDIRECTORY INTO THE OUTPUT DIRECTORY WHERE IT WILL BE COMPRESSED TO OUTPUT TAR FILE
*/
int mv_file(char *filePath, char *designatedDir) {
  printf("moving %s files into %s\n", filePath, designatedDir);
  int pid = fork(); //create child process
  switch (pid) {
  case -1:
    perror("Error cannot fork: ");
    exit(EXIT_FAILURE);
    break;
  case 0: {
    //using built in mv on MAC OS UNIC to move file into output directory
    if(execl("/bin/mv", "-f", filePath, designatedDir, NULL)!=-1)
    {
      exit(EXIT_SUCCESS);
    }
    else
    {
      perror("Error: ");
      exit(EXIT_FAILURE);
    }
    break;
  	}
  }
  return pid;
}

/*
	CREATE A TAR FILE THAT WILL EVENTUALLY CONTAIN ALL ACCEPTED FILES 
*/
int create_output_tar(char *outputName) {
  int pid = fork();
  switch (pid) {
  case -1:
    perror("Error cannot fork: ");
    exit(EXIT_FAILURE);
    break;
  case 0: {
    printf("*CREATING TAR FILE*\n");
    if (execl("/usr/bin/tar", "-cvf", "-cf", outputName, "/dev/null", NULL) != -1)//create a empty tar archive
    {
      exit(EXIT_SUCCESS);
    } 
    else 
    {
      perror("Error: ");
      exit(EXIT_FAILURE);
    }
    break;
  	}
  }
  return pid;
}

/*
   APPEND FILES INTO THE OUTPUT TAR FILE
*/
int add_to_tar(char *outputTarName, char *file, char *tempDirectory) {

  char cwd[MAX_PATH_LENGTH]; //string for current working directory
  char cwdWithTar[MAX_PATH_LENGTH];

  //CHECKING THE outputTarName TO SEE WHETHERE A DIRECTORY IS SPECIFIED WITH IT
  //IF NO DIRECTORY IS SPECIFED THANK THE CURRENT WORKING DIRECTORY ISNT NEEDED TO BE ADDED TO TAR NAME
  char *copyTarName = NULL; //duplicate outputTarName so original is not affected
  copyTarName = realloc(copyTarName, strlen(outputTarName)*sizeof(*copyTarName));
  strcpy(copyTarName, outputTarName);
  char *pointerForTok = NULL;
  pointerForTok = realloc(pointerForTok, strlen(outputTarName)*sizeof(*copyTarName));
  char slash[] = "/";
  pointerForTok = strtok(copyTarName, slash);
  int token = 0;
  while (pointerForTok != NULL) 
  {
    pointerForTok = strtok(NULL, slash);
    token++; //count how many "/" are in outputTarName
  }
  //if token is less than 2 then outputTarFile is in the current working directory
  //else its specifed to be elsewhere so files would immediatley be added to it without having to specify directy its in
  if (getcwd(cwd, sizeof(cwd)) != NULL && token < NONDESRIEDTOKENS)
   {
    strcpy(cwdWithTar, cwd);
    strcat(cwdWithTar, "/");
    strcat(cwdWithTar, outputTarName); //added the current working directoy to outputTarName
  }

  printf("adding %s to tar %s\n", file, outputTarName);
  int pid = fork();
  chdir(tempDirectory); //go into tempDirectory so that files dont contain /tmp/dir.XXXXXX/file only file
  switch (pid) {
  case -1:
    perror("Error cannot fork: ");
    exit(EXIT_FAILURE);
    break;
  case 0: {
    
    	if (token < NONDESRIEDTOKENS) 
    	{
    		//using built in tar on MAC OS UNIC to append file to tar
      		if (execl("/usr/bin/tar", "-rvf", "rf", cwdWithTar, file, NULL) != -1)
      		{
      	  		exit(EXIT_SUCCESS);
      		} 
      		else 
     	 	{
     	 		perror("Error: ");
     	   		exit(EXIT_FAILURE);
     	 	}
     	 	break;
    	} 
    	else 
    	{
     		 if (execl("/usr/bin/tar", "-rvf", "rf", outputTarName, file, NULL) != -1)//directory of where the is outputTar is specied to tar call
     	 	{
     	   		exit(EXIT_SUCCESS);
     	 	} 
     	 	else 
     	 	{
     	 		perror("Error: ");
     	   		exit(EXIT_FAILURE);
    	 	}
    	 	break;
  		}
 	 }
  }
  chdir(cwd); //go back to the current working directory
  return pid;
}

