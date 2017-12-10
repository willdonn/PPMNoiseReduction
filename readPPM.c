#include "filter.h"
#include <stdio.h>
#include <stdlib.h>

RGB *readPPM(const char *file, int *width, int *height, int *max)
{
   char format[2];
   FILE *image;
   if(!(image = fopen(file, "rb")))
   {
      printf("File could not be found\n");
      exit(1);
   }

   fscanf(image, "%c%c", &format[0], &format[1]);
   if ((format[0] != 'P' && format[0] != 'p') || format[1] != '3')
   {
      printf("Invalid file format\n");
      exit(1);
   }

   fscanf(image, "%d %d\n", width, height);
   fscanf(image, "%d\n", max);

   RGB* p = malloc(((*height)*(*width))*sizeof(RGB));
   int i = 0;

   while(fscanf(image, "%hhu%hhu%hhu", &(p[i].r), &(p[i].g), &(p[i].b)) != EOF)
   {
      i++;
   }
   fclose(image);
   return p;
}

