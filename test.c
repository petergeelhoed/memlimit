#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

void print_rlimit(struct rlimit *r, const char *name) {
    int64_t cur;                /* Soft limit */
    int64_t max;                /* Hard limit */
    cur = r->rlim_cur;
    max = r->rlim_max;
    printf("RLIMIT_%s :rlim_cur => %lld, :rlim_max => %lld\n",
           name, cur, max);
}

int main(int argc, char *argv[]) {
	char* p;
	int c;
    int wait = 0;
	int j=0;
    struct rlimit rlim;
    int64_t n = 5000000;
	while ((c = getopt (argc, argv, "n:w:")) != -1)
        switch (c)
        {
            case 'w':
                //addresspace
                wait = atoi(optarg);
                break;
            case 'n':
                //addresspace
                n = atoll(optarg);
                break;
			default:
				abort();
		}


	getrlimit(9 ,&rlim); // RLIMIT_AS

	print_rlimit(&rlim, "AS");
	rlim.rlim_cur = n;
	if (setrlimit(9 ,&rlim) == 0)
	{
		getrlimit(9 ,&rlim); // RLIMIT_AS
		print_rlimit(&rlim, "AS");
		p++;
		while (p != NULL) 
		{
			p=(char*)malloc(1000);
			j++;
			if (wait) usleep(wait); // if you want to see this in htop
			if (j%10000==0)printf("%d allocations\n",j);
		}
		printf("%d allocations\n",j);
	}
	else
	{
		printf("error setting limit\n");
	}
	return 0;
}
