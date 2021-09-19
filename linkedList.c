#include "mergetars.h"
/*
	The linked list functions and implementation were made with help from user Mahonri Moriancumer
	LINK: https://stackoverflow.com/questions/23279119/creating-and-understanding-linked-lists-of-structs-in-c

*/

/*
	Finds the parent node of the node with a certain filePath
	moves unwated file to garbage
*/
listOfFiles *findParent(char *filePath, char *GarbageDir) {

  listOfFiles *checkNode = listHead;
  listOfFiles *parent = NULL;
  while (checkNode != NULL)
   {
    if (strcmp(checkNode->node.fileName, filePath) == 0) 
    {
      break;
    }
    parent = checkNode; //saves the parent
    checkNode = checkNode->next;
  }
  printf("remove to %s\n", GarbageDir);
  place_file_into_diff_dir(checkNode->node.filePath, GarbageDir); //move the nodes file that needs to be deleted in garbage directory
  return parent;
}
/*
	removes the mode from the linked list
*/
void * deleteNode(char *filePath, listOfFiles *TheNode, char *GarbageDir) {
  listOfFiles * parent = NULL;
  parent = findParent(filePath, GarbageDir);
  if (parent == NULL) //its the head
  { 
    listHead = TheNode->next;
  } 
  else 
  {
    parent->next = TheNode->next; //remove link to Node now parent points to what TheNode was pointing to
  }
  return 0;
}
/*
	Removes the temperoary folder label in the path[] name
	checks merging conditions
	if allowed merging adds to linked list of files
*/
int add_To_List_Of_Files(char path[], int timeModified, int fileSize, char * tempDirectory, char * GarbageDir) {
 
  listOfFiles *newNode = NULL;
  newNode = realloc(newNode, sizeof(*newNode)); 
  snprintf(newNode->node.filePath, sizeof(newNode->node.filePath), "%s", path); //set the filePath

  char *pathdup = NULL; //duplicate the path for strok
  pathdup = realloc(pathdup, strlen(path)*sizeof(*pathdup));
  strcpy(pathdup, path);

  //REMOVING TEMP/DIR.XXXXXX FROM PATH NAME SO ONLY EXACT FILEPATH IS CHECKED FOR DUPLICATES
  char *p = NULL;
  p = realloc(p, strlen(path)*sizeof(*p));
  char slash[] = "/";
  char *filePath = NULL;
  filePath = realloc(filePath,strlen(path)*sizeof(*filePath));
  p = strtok(pathdup, slash);
  int token = 0;
  while (token < NONDESRIEDTOKENS) //removing TEMP/DIR.XXXXXX 
  {
    p = strtok(NULL, slash);
    token++;
  }
  while (p != NULL) 
  {
    //copying the full string of desried path Name
    filePath = strcat(filePath, p);
    filePath = strcat(filePath, "/");
    p = strtok(NULL, slash);
  }


  //CHECKING MERGING CONDITIONS RETURN -1 WHEN FILE CANT BE ADDED INTO LINKED LIST DUE
  //CALL DELETENODE() WHEN A NODE NEEDS REPLACING
  listOfFiles *testNode = NULL;
  if ((testNode = fileNameExits(filePath)) != NULL) 
  {
    printf("file has the same path name. checking timeModified\n");
    if (testNode->node.timeModified > timeModified) 
    {
      printf("file of later time modification already in output\n");
      return -1;
    } 
    else if (testNode->node.timeModified < timeModified) 
    {
      printf("same file of later time exists overwite previous installed file\n");
      deleteNode(filePath, testNode, GarbageDir);

    } 
    else if (testNode->node.timeModified == timeModified) 
    {
      printf("same time mod checking fileSize\n");
      	if (testNode->node.fileSize > fileSize) 
      	{
       		printf("file of greater size already in output\n");
       		return -1;
     	} 
     	else if (testNode->node.fileSize < fileSize)
     	 {
        	printf("same file of larger exists overwite previous installed file\n");
        	deleteNode(filePath, testNode, GarbageDir);
     	 } 
      	else if (testNode->node.fileSize == fileSize) 
      	{
        	printf("same fileSize\n");
        	printf("override current file with this one as its in later tarfile in input command line");
        	deleteNode(filePath, testNode, GarbageDir);
    	}
    }
  }
  //ADDING ALLOWWED NODE INTO LINKED LIST
  snprintf(newNode -> node.fileName, sizeof(newNode -> node.fileName), "%s", filePath);
  snprintf(newNode -> node.tempDirectory, sizeof(newNode -> node.tempDirectory), "%s", tempDirectory);
  newNode -> node.timeModified = timeModified;
  newNode -> node.fileSize = fileSize;
  newNode -> next = listHead;
  listHead = newNode;

  printf("%s\n",path);
  return 0;
}
/*
	cheking if filename already exits in existing linked list
*/
listOfFiles *fileNameExits(char *fileName) {

  listOfFiles *checkNode = listHead;
  listOfFiles *exactNode = NULL;
  int exists = -1;
  while (checkNode != NULL) {

    if (strcmp(checkNode -> node.fileName, fileName) == 0) // equal the same if 0
    {
      exists = 0; //found exact filename
      exactNode = checkNode; //save the node
      break;
    }
    checkNode = checkNode -> next;
  }
  if (exists == -1) 
  {
    printf("no match found\n");

  } 
  else
   {
    printf("match found\n");
  }
  return exactNode;
}
/*
	simple getter function for returning the list head of linked list
	unable to simply have this variable in mergetars.c main()
*/
listOfFiles *getHead() {
  return listHead;
}
