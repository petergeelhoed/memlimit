#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() 
{
	char* p;
	int i=0;

	p++;
	while (p!=NULL) {
		p=(char*)malloc(1000);
		i++;
		usleep(1000); // if you want to see this in htop
	}
	printf("%d allocations\n",i);
	return 0;
}
