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
	
	int fd = open("test.bin", O_CREAT|O_TRUNC|O_WRONLY|
	O_DIRECT,S_IRWXU);

	if(fd != -1){
		size_t FILESIZE = strtoul(argv[1], NULL, 0);
		size_t BLOCKSIZE = strtoul(argv[2], NULL, 0);
		BLOCKSIZE -= (BLOCKSIZE%512);

		void* buffer;
		int* temp;
		int stato;
		stato = posix_memalign(&buffer, 512, BLOCKSIZE);

		if(!stato){
			temp = buffer;
			srand(time(NULL));
			for(int i = 0; i<BLOCKSIZE/sizeof(int);
			i++){
				temp[i] = rand();
			}

			size_t count = FILESIZE/BLOCKSIZE;
			struct timeval inizio, fine;
			temp = buffer;
			gettimeofday(&inizio, NULL);
			for(; count > 0; count--){
				write(fd, temp, BLOCKSIZE);
			}
			gettimeofday(&fine, NULL);

			FILE* writetime;
			char nome[50] = "writetime";
			strcat(nome, argv[1]);
			strcat(nome, "x");
			strcat(nome, argv[2]);

			writetime = fopen(nome, "a");
			if(writetime){
				fprintf(writetime, "%ld\n", 
				(long)fine.tv_sec*1000000+
				(long)fine.tv_usec-
				(long)inizio.tv_sec*1000000-
				(long)inizio.tv_usec);
				fclose(writetime);
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
