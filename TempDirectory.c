#include "mergetars.h"

/*	
	CREATE A TEMPORARY DIRECOTRY FOR FILES TO BE EXTRACTED INTO FROM INPUT TAR FILE
*/
char * create_Dir() {
  char * tempDirectory = NULL;
  tempDirectory = realloc(tempDirectory, sizeof(MAX_PATH_LENGTH)); //CHANGE BYTE SIZE TO WHATS NEEDED!

  strcpy(tempDirectory, TEMPLATE);

  mkdtemp(tempDirectory);
  printf("%s\n", tempDirectory);
  return tempDirectory;
}

/*
	CALLS THE FUNCTION WHERE A CHILD PROCESSES IS CREATED AND UNTARS THE INPUT TAR FILE
	PARENT WAITS FOR CHILD PROCESS TO FINISH UNTARTING TAR INTO DIRECTORY
*/
void * extract_tar(char * tarName, char * tempDirectory) {
  int pid, status;
  pid = run_extract(tarName, tempDirectory);

  printf("parent waits for pid = %i\n", pid);
  if ((pid = wait( & status) > 0)) {
    printf("pid = %i terminated with %i \n", pid, status); //succesful termination if status = 0
    if (status == 0) {
      printf("\nsuccesful untared %s into %s\n", tarName, tempDirectory);
    }
  }
  return 0;
}

/*
	CALLS THE FUNCTION WHERE A CHILD PROCESSES IS CREATED AND MOVES DESIRED FILES INTO OUTPUT DIRECTORY
	PARENT WAITS FOR CHILD PROCESS TO FINISH MOVING FILES INTO OUTPUT DIRECOTORY
*/
char * place_file_into_diff_dir(char * tempDirectory, char * outputDir) {

  printf(" %s", tempDirectory);
  int pid, status;
  pid = mv_file(tempDirectory, outputDir);

  printf("parent waits for pid = %i\n", pid);

  if ((pid = wait( & status) > 0)) {
    printf("pid = %i terminated with %i \n", pid, status);
    if (status == 0) {
      printf("\nsuccesful moved file\n");
    }
  }

  return 0;

}

/*
	CALLS THE FUNCTION WHERE A CHILD PROCESSES IS CREATED AND COMPRESSES DESIRED FILES THAT ARE IN OUTPUT DIRECTORY
	PARENT WAITS FOR CHILD PROCESS TO FINISH CREATING OUTPUT TAR FILE

*/
void * run_create_tar(char * outputName) {

  int pid, status;

  pid = create_output_tar(outputName);

  printf("parent waits for pid = %i\n", pid);

  if ((pid = wait( & status) > 0)) {
    printf("pid = %i terminated with %i \n", pid, status);
    if (status == 0) {
      printf("succesful creation of %s\n", outputName);
    }
  }
  return 0;
}

void * append_files(char * outputTarName, char * tempDirectory, char * GarbageDir, char * fileName) {

  char * filePath1 = NULL;

  int pid, status;
  pid = add_to_tar(outputTarName, fileName, tempDirectory);

  printf("parent waits for pid = %i\n", pid);

  if ((pid = wait( & status) > 0)) {
    printf("pid = %i terminated with %i \n", pid, status);
    if (status == 0) {
      printf("\nsuccesful appended file to tar\n");
    }
  }

  return 0;

}
