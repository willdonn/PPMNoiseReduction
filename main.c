#include "filter.h"
#include <stdlib.h>
#include <stdio.h>
extern double getTime();

int main(int argc, char *argv[])
{
   if (argc != 5)
      printf("Incorrect number of arguments: 4 expected, %d passed.\n", argc);
   else
   {
      if (*argv[4] != 'A' && *argv[4] != 'M')
      {
         printf("Invalid filter\n");
         exit(1);
      }

      int width, height, max;
      int winSize = atoi(argv[3]);
      RGB* PixelArray;

      printf("\nReading file %s\n", argv[1]);

      double time = getTime();
      PixelArray = readPPM(argv[1], &width, &height, &max);
      time = getTime() - time;
      printf("***   %s read   in %.1e seconds\n", argv[1], time);

      if (*argv[4] == 'A')
      {
         time = getTime();
         printf("\nProcessing %d x %d image using %d x %d window and mean filter...\n", width, height, winSize, winSize);
         PixelArray = denoiseImage(width, height, PixelArray, winSize, MEAN);
         time = getTime() - time;
         printf("***   image processed in %.1e seconds\n", time);
      }
      else if (*argv[4] == 'M')
      {
         time = getTime();
         printf("\nProcessing %d x %d image using %d x %d window and median filter...\n", width, height, winSize, winSize);
         PixelArray = denoiseImage(width, height, PixelArray, winSize, MEDIAN);
         time = getTime() - time;
         printf("***   image processed in %.1e seconds\n", time);
      }


      printf("\nWriting file %s\n", argv[2]);
      time = getTime();
      writePPM(argv[2], width, height, max, PixelArray);
      time = getTime() - time;
      printf("***   %s written in %.1e seconds\n\n", argv[2], time);
   }
   return 0;

}
