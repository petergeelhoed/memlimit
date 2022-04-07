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
    printf("%17s :rlim_cur => %16lld, :rlim_max => %16lld\n",
           name, cur, max);
}

int main(int argc, char *argv[]) {
	char* p;
	int c;
	int verbose = 0;
    int wait = 0;
	int j=0;
    struct rlimit rlim;
    int64_t n = 5000000;

	int resources[] = {
		RLIMIT_CPU, 
		RLIMIT_FSIZE,
		RLIMIT_DATA, 
		RLIMIT_STACK, 
		RLIMIT_CORE, 
		RLIMIT_RSS,
		RLIMIT_NPROC,
		RLIMIT_NOFILE,
		RLIMIT_MEMLOCK,
		RLIMIT_AS,
		RLIMIT_LOCKS,
		RLIMIT_SIGPENDING,
		RLIMIT_MSGQUEUE,
		RLIMIT_NICE,
		RLIMIT_RTPRIO,
		RLIMIT_RTTIME,
		RLIMIT_NLIMITS
};
    const char *names[] = {
		"RLIMIT_CPU", 
		"RLIMIT_FSIZE",
		"RLIMIT_DATA", 
		"RLIMIT_STACK", 
		"RLIMIT_CORE", 
		"RLIMIT_RSS",
		"RLIMIT_NPROC",
		"RLIMIT_NOFILE",
		"RLIMIT_MEMLOCK",
		"RLIMIT_AS",
		"RLIMIT_LOCKS",
		"RLIMIT_SIGPENDING",
		"RLIMIT_MSGQUEUE",
		"RLIMIT_NICE",
		"RLIMIT_RTPRIO",
		"RLIMIT_RTTIME",
		"RLIMIT_NLIMITS"
};
    int nl = sizeof(resources)/sizeof(resources[0]);
    int i;
	int k = 1000;

	while ((c = getopt (argc, argv, "n:w:vhk:")) != -1)
        switch (c)
        {
            case 'h':
                fprintf(stderr,"\
-n <size of addresspace in bytes>\n\
-w <microseconds sleep>\n\
-k <char array size> (1000)\n\
verbose -v\n\
");
                return 0;
            case 'v':
                verbose = 1;
                break;
            case 'k':
                //microsecondsleep
                k = atoi(optarg);
                break;
            case 'w':
                //microsecondsleep
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
	printf("BEFORE:\n");
	print_rlimit(&rlim, "9 AS");
    for (i = 0; i < nl && verbose; i++) {
        getrlimit(resources[i], &rlim);
        print_rlimit(&rlim, names[i]);
    }
	rlim.rlim_cur = n;
	if (setrlimit(9 ,&rlim) == 0)
	{
		printf("\nAFTER:\n");
		getrlimit(9 ,&rlim); // RLIMIT_AS
		print_rlimit(&rlim, "9 AS");
		for (i = 0; i < nl && verbose; i++) {
			getrlimit(resources[i], &rlim);
			print_rlimit(&rlim, names[i]);
		}
		p++;
		while (p != NULL) 
		{
			p=(char*)malloc(k);
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
