#include "filter.h"
#include <stdio.h>
#include <stdlib.h>

int compfunc(const void *a, const void *b)
{
  return ( *(int*)a - *(int*)b );
}

void frame(int winSize, int xMin, int xMax, int yMin, int yMax, int i, int width, int height, int *minJ, int *maxJ, int *minK, int *maxK)
{
      /*Top and left of box cut off*/
      if (xMin < 0 && yMin < 0)
      {
         *minJ = 0;
         *maxJ = xMax;
         *minK = 0;
         *maxK = yMax;
      }
      /*Top of box cut off*/
      else if (xMax < width && yMin < 0)
      {
         *minJ = xMin;
         *maxJ = xMax;
         *minK = 0;
         *maxK = yMax;
      }

      /*Top and right of box cut off*/
      else if (xMax >= width && yMin < 0)
      {
         *minJ = xMin;
         *maxJ = width - 1;
         *minK = 0;
         *maxK = yMax;
      }

      /*Left of box cut off only*/
      else if (xMin < 0 && yMin >= 0)
      {
         *minJ = 0;
         *maxJ = xMax;
         *minK = yMin;
         *maxK = yMax;
      }

      /*Right of box is cut off*/
      else if (xMax >= width && yMax < height)
      {
         *minJ = xMin;
         *maxJ = width - 1;
         *minK = yMin;
         *maxK = yMax;
      }
      /*Left and bottom of box is cut off*/
      else if (xMin < 0 && yMax >= height)
      {
         *minJ = 0;
         *maxJ = xMax;
         *minK = yMin;
         *maxK = height - 1;
      }
      /*bottom only is cut off*/
      else if (xMax < width && yMax >= height)
      {
         *minJ = xMin;
         *maxJ = xMax;
         *minK = yMin;
         *maxK = height - 1;
      }

      /*bottom and right is cut off*/
      else if (xMax >= width && yMax >= height)
      {
         *minJ = xMin;
         *maxJ = width - 1;
         *minK = yMin;
         *maxK = height - 1;
      }
}

RGB *denoiseImage(int width, int height, const RGB *image, int n, filter f)
{
   int denom, winSize = (n/2), minJ, maxJ, minK, maxK, xMin, xMax, yMin, yMax;
   int k, j, i = 0;
   int winArea = n*n;
   int size = width*height;
   RGB* p = malloc((width*height)*sizeof(RGB));

   if (f == MEAN)
   {
   int aveR, aveG, aveB;
      while(i < size)
      {
         aveR = 0;
         aveG = 0;
         aveB = 0;
         denom = 0;

         xMin = i%width - winSize;
         xMax = i%width + winSize;
         yMin = i/width - winSize;
         yMax = i/width + winSize;

      /*None of box is cut off*/
      if (xMin >= 0 && xMax < width && yMin >=0 && yMax < height)
      {
        minJ = xMin;
        maxJ = xMax;
        minK = yMin;
        maxK = yMax;
      }

      else
         frame(winSize, xMin, xMax, yMin, yMax, i, width, height, &minJ, &maxJ, &minK, &maxK);

         for (j = minJ; j <= maxJ; j++)
         {
            for (k = minK; k <= maxK; k++)
            {
               aveR += image[j+(width*k)].r;
               aveG += image[j+(width*k)].g;
               aveB += image[j+(width*k)].b;
               denom++;
            }
         }
         p[i].r = aveR/denom;
         p[i].g = aveG/denom;
         p[i].b = aveB/denom;
         i++;
      }
   }
   else if (f == MEDIAN)
   {
      int medR[winArea], medG[winArea], medB[winArea];
      while (i < size)
      {
         denom = 0;

         xMin = i%width - winSize;
         xMax = i%width + winSize;
         yMin = i/width - winSize;
         yMax = i/width + winSize;

      /*None of box is cut off*/
      if (xMin >= 0 && xMax < width && yMin >=0 && yMax < height)
      {
         minJ = xMin;
         maxJ = xMax;
         minK = yMin;
         maxK = yMax;
      }
      else
         frame(winSize, xMin, xMax, yMin, yMax, i, width, height, &minJ, &maxJ, &minK, &maxK);

         for (j = minJ; j <= maxJ; j++)
         {
            for (k = minK; k <= maxK; k++)
            {
               medR[denom] = image[j+(width*k)].r;
               medG[denom] = image[j+(width*k)].g;
               medB[denom] = image[j+(width*k)].b;
               denom++;
            }
         }
         qsort(medR, winArea, sizeof(medR[0]), compfunc);
         qsort(medG, winArea, sizeof(medG[0]), compfunc);
         qsort(medB, winArea, sizeof(medB[0]), compfunc);

         p[i].r = medR[(winArea)/2];
         p[i].g = medG[(winArea)/2];
         p[i].b = medB[(winArea)/2];
         i++;
      }
   }
   return p;
}

