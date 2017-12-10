#include<sys/resource.h>
#include<unistd.h>

double getTime() {           
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  struct timeval time;
  time = usage.ru_utime;
  return time.tv_sec+time.tv_usec/1e6;
}

	
        
    
    
    
    

