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
	int fd = open("test.bin", O_CREAT|O_TRUNC|O_WRONLY|O_DIRECT, S_IRWXU);
	/*
		O_SYNC  provides  synchronized  I/O  file integrity completion, meaning
       write operations will flush data and all  associated  metadata  to  the
       underlying  hardware.  O_DSYNC provides synchronized I/O data integrity
       completion, meaning write operations will flush data to the  underlying
       hardware,  but  will  only  flush metadata updates that are required to
       allow a subsequent  read  operation  to  complete  successfully.   Data
       integrity  completion can reduce the number of disk operations that are
       required for applications  that  don't  need  the  guarantees  of  file
       integrity completion.

       To  understand the difference between the two types of completion, con‐
       sider two pieces of file metadata: the file last modification timestamp
       (st_mtime)  and  the file length.  All write operations will update the
       last file modification timestamp, but only writes that add data to  the
       end  of  the  file  will change the file length.  The last modification
       timestamp is not needed to ensure that a read  completes  successfully,
       but  the  file  length is.  Thus, O_DSYNC would only guarantee to flush
       updates to the file length metadata (whereas O_SYNC would  also  always
       flush the last modification timestamp metadata).
	*/
	if(fd != -1){
		size_t FILESIZE = strtoul(argv[1], NULL, 0);
		size_t BLOCKSIZE = strtoul(argv[2], NULL, 0);
		BLOCKSIZE -= (BLOCKSIZE%512);

		void* buffer;
		int* temp;
		int stato;
		//stato = posix_memalign(&buffer, 512, FILESIZE);
		stato = posix_memalign(&buffer, 512, BLOCKSIZE);

		if(!stato){
			temp = buffer;
			srand(time(NULL));
			//for(int i = 0; i<FILESIZE/sizeof(int); i++){
			for(int i = 0; i<BLOCKSIZE/sizeof(int); i++){
				temp[i] = rand();
				//temp[i] = i;
			}

			size_t count = FILESIZE/BLOCKSIZE;
			struct timeval inizio, fine;
			temp = buffer;
			gettimeofday(&inizio, NULL);
			for(; count > 0; count--){
				write(fd, temp, BLOCKSIZE);
				//temp += BLOCKSIZE/sizeof(int);
			}
			//write(fd, buffer, FILESIZE);
			gettimeofday(&fine, NULL);

			FILE* writetime;
			char nome[50] = "writetime";
			strcat(nome, argv[1]);
			strcat(nome, "x");
			strcat(nome, argv[2]);

			writetime = fopen(nome, "a");
			if(writetime){
				//fprintf(writetime, "TIME: %ld us\n", (long)fine.tv_sec*1000000+(long)fine.tv_usec-(long)inizio.tv_sec*1000000-(long)inizio.tv_usec);
				fprintf(writetime, "%ld\n", (long)fine.tv_sec*1000000+(long)fine.tv_usec-(long)inizio.tv_sec*1000000-(long)inizio.tv_usec); // tempo in microsecondi
				fclose(writetime);
			}
			else
				perror("Salvataggio risultati non riuscito");
			free(buffer);
		}
		else
			perror("Errore nell'allocazione del buffer");
		close(fd);
	}
	else
		perror("Errore nell'apertura del file");
}
