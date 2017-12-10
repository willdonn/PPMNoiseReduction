#include "filter.h"
#include <stdio.h>

void writePPM(const char *file, int width, int height, int max, const RGB *image)
{
   int i, j;
   int index = 0;
   FILE *fp;

   fp = fopen(file, "wb");

   fprintf(fp, "%c%c\n", 'P', '3');
   fprintf(fp, "%d %d\n", width, height);
   fprintf(fp, "%d\n", max);

   for(i = 0; i < height; i++)
   {
      for(j = 0; j < width; j++)
      {
         fprintf(fp, "%hhu %hhu %hhu ", image[index].r, image[index].g, image[index].b);
         index++;
      }
      fprintf(fp, "\n");
   }
   fprintf(fp,"\n");
   fclose(fp);

}

