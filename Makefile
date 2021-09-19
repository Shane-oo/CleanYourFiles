mergetars : mergetars.o parentProccesses.o clean.o readingFiles.o processes.o linkedList.o subDir.o
	cc -std=c99 -Wall -pedantic -Werror -o mergetars \
		mergetars.o parentProccesses.o clean.o readingFiles.o processes.o linkedList.o subDir.o

readingFiles.o : readingFiles.c mergetars.h
	cc -std=c99 -Wall -pedantic -Werror -c readingFiles.c

parentProccesses.o : parentProccesses.c mergetars.h
	cc -std=c99 -Wall -pedantic -Werror -c parentProccesses.c

mergetars.o : mergetars.c mergetars.h
	cc -std=c99 -Wall -pedantic -Werror -c mergetars.c

clean.o : clean.c mergetars.h
	cc -std=c99 -Wall -pedantic -Werror -c clean.c	

processes.o : processes.c mergetars.h
	cc -std=c99 -Wall -pedantic -Werror -c processes.c	

linkedList.o : linkedList.c mergetars.h
	cc -std=c99 -Wall -pedantic -Werror -c linkedList.c

subDir.o : subDir.c mergetars.h
	cc -std=c99 -Wall -pedantic -Werror -c subDir.c

clean:
	rm -f *.o mergetars