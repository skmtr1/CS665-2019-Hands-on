//Sample program to show undefined behaviour
#include<stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void main(){
	int fd = open("dummy.txt",O_RDWR),choice,index;
	char c;
	struct stat sb;
	if (fstat(fd,&sb) == -1)
		perror("Couldn't get the file size.\n");
	

	char *file_in_memory = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	printf("Enter choice \n 1.Write a character \n 2.Read file 3. Exit \n");
	scanf("%d",&choice);
	while(choice != 3){
		switch(choice){
			case 1:
				printf("Enter the index between 0 and %ld \n",sb.st_size-1);
				scanf("%d",&index);
				printf("Enter character to be written \n");
				scanf("%s",&c);
				file_in_memory[index]=c;
				break;
			case 2:
				for(int i=0; i < sb.st_size; i++)
					printf("%c",file_in_memory[i]);
				printf("\n");
				break;
			case 3:
				break;

		}
		printf("Enter choice again \n 1.Write a character \n 2.Read file 3. Exit\n");
		scanf("%d",&choice);
	}
}
