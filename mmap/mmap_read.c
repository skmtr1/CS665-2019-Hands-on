//Sample program to show undefined behaviour
#include<stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void main(){
	int fd = open("dummy.txt",O_RDONLY, S_IRUSR | S_IWUSR),temp;
	struct stat sb;
	if (fstat(fd,&sb) == -1){
		perror("Couldn't get the file size.\n");
	}
	printf("file size is %ld\n",sb.st_size);
	char *file_in_memory = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
	printf("Printing file, as an array of characters..\n\n");
	printf("Enter some number to continue\n");
	scanf("%d",&temp);
	for(int i=0; i < sb.st_size; i++){
		printf("%c",file_in_memory[i]);
	}
	printf("\n");
}
