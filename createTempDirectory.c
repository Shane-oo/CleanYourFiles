#include "mergetars.h"



char *create_Dir(char *tarName){
	
	/*CREATE A TEMPORARY DIRECOTRY AND PUT ALL OF THAT TAR'S FILE INSIDE IT*/
	char *tempDirectory =malloc(1000+1); //change 1000 to the approatie memory allocation?
	strcpy(tempDirectory,TEMPLATE);
	
	mkdtemp(tempDirectory);
	printf("%s\n",tempDirectory);



	return tempDirectory;	

}
