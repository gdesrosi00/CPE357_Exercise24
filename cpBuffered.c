#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "memmon.h"

void displayUsage()
{
   fprintf(stderr, "Usage: cpBuffered bufsize fromfile tofile\n");
   exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
   int bufsize = 0;
   int wfd, rfd;
   void *buffer;
   ssize_t bytesRead;
   if(argc != 4)
      displayUsage();
   if ((sscanf(argv[1], " %d", &bufsize)) == EOF)
      displayUsage();
   rfd = open(argv[2], O_RDONLY);
   wfd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
   buffer = malloc(sizeof(char) * bufsize);
   while((bytesRead = read(rfd, buffer, bufsize)) != 0)
      write(wfd, buffer, bytesRead);
   close(rfd);
   close(wfd);
   free(buffer);
   printf("Number of Allocations: %u\n", memAllocs());
   printf("   Current Allocation: %u\n", memCurrent());
   printf("      Peak Allocation: %u\n", memPeak());
   return EXIT_SUCCESS;
}
