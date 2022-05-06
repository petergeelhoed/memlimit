#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>


/* function declaration */
void printstack();
void printstack2() { printstack(); }
 
int main () {

   int ret;
 
   /* calling a function to get max value */
   printstack2();

   printstack2();


   return 0;
}
 
void printstack()
{
    void *array[30]; size_t size; char **strings; size_t i;

    size = backtrace(array, 30);
    strings = backtrace_symbols(array, size);

    printf("Obtained %zd stack frames.\n", size);

    for(i = 0; i < size; i++) 
        printf("%s\n", strings[i]); 

    free(strings);

   return; 
}




