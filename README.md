# CleanYourFiles

C program to help in the organisation and cleaning of files that exists in direcorties on Ubuntu machines
Program will interact with the system and decide which files to keep in a directory. Files to be cleaned must be already in a .tar archival file

To create a tar file run this line in terminal:
$tar -czf taredFiles.tar DirToBeTared

To tar multiple dirs into one tar simply:
$tar -czf taredFiles.tar DirToBeTared DirToBeTared2 DirToBeTared3 (and so on...)

HOW TO RUN MERGETARS
$cd intoDirectory 
$make
$./mergetars taredFiles.tar taredFiles2.tar taredFiles3.tar outPut.tar

last file will be the cleaned tar file and unless specified will be placed in cwd 
