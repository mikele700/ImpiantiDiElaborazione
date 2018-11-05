#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

void main(int argc, char* argv[]){
	int fd = open("test.bin", O_RDONLY|O_DIRECT);
	
	if(fd != -1){
		size_t FILESIZE = strtoul(argv[1], NULL, 0);
		size_t BLOCKSIZE = strtoul(argv[2], NULL, 0);
		BLOCKSIZE -= (BLOCKSIZE%512);
		
		void* buffer;
		posix_memalign(&buffer, 512, FILESIZE);
		
		size_t count = FILESIZE/BLOCKSIZE;
		struct timeval inizio, fine;
		int* temp = buffer;
		gettimeofday(&inizio, NULL);
		for(; count > 0; count--){
			read(fd, temp, BLOCKSIZE);
			temp += BLOCKSIZE/sizeof(int);
		}
		//read(fd, buffer, FILESIZE);
		gettimeofday(&fine, NULL);
		
		/*temp = buffer;
		for(int i = 0; i<FILESIZE/sizeof(int); i++){
			printf("%d", temp[i]);
		}*/
		
		FILE* readtime;
		char nome[50] = "readtime";
		strcat(nome, argv[1]);
		strcat(nome, "x");
		strcat(nome, argv[2]);
		
		readtime = fopen(nome, "a");
		if(readtime){
			fprintf(readtime, "TIME: %ld us\n", (long)fine.tv_sec*1000000+(long)fine.tv_usec-(long)inizio.tv_sec*1000000-(long)inizio.tv_usec);
			fclose(readtime);
		}
		else
			perror("Salvataggio risultati non riuscito");
		free(buffer);
		close(fd);
	}
	else
		perror("Errore nell'apertura del file");
}
