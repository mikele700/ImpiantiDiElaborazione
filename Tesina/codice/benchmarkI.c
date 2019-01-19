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
	
	int fd = open("prova.bin", O_RDONLY|O_DIRECT);
	
	if(fd != -1){
		size_t FILESIZE = strtoul(argv[1], NULL, 0);
		size_t BLOCKSIZE = strtoul(argv[2], NULL, 0);
		BLOCKSIZE -= (BLOCKSIZE%512);

		void* buffer;
		stato = posix_memalign(&buffer, 512, BLOCKSIZE);

		if(!stato){
			size_t count = FILESIZE/BLOCKSIZE;
			struct timeval inizio, fine;
			gettimeofday(&inizio, NULL);
			for(; count > 0; count--){
				read(fd, buffer, BLOCKSIZE);
			}
			gettimeofday(&fine, NULL);

			FILE* readtime;
			char nome[50] = "readtime";
			strcat(nome, argv[1]);
			strcat(nome, "x");
			strcat(nome, argv[2]);

			readtime = fopen(nome, "a");
			if(readtime){
				fprintf(readtime, "%ld\n", 
				(long)fine.tv_sec*1000000+
				(long)fine.tv_usec-
				(long)inizio.tv_sec*1000000-
				(long)inizio.tv_usec);
				fclose(readtime);
			}
			else
				perror(
				"Salvataggio risultati non riuscito");
			free(buffer);
		}
		else
			perror("Errore nell'allocazione del buffer");
		close(fd);
	}
	else
		perror("Errore nell'apertura del file");
}
