#include <stdio.h>
#include <gd.h>
#include <string.h>
#include <omp.h>

int main() {
	char *input_file = "a1.png";
	char *output_file = "a2.png";

	int num_threads = 2;
	
	File *fp = fopen(input,"r");
    
    if(fp == NULL)
    {
        printf("file not found")
        return -1;
    }

	gdImagePtr img = gdImageCreateFromPng(fp);
	int width = gdImageSX(img);
	int height = gdImageSY(img);
	
	int red,green,blue,color,combined,x,y;
	double t1 = omp_get_wtime();
	
	#pragma omp parallel for private(y, color, red, green, blue, combined)
	for(x=0; x<width; x++) 
	{
	    #pragma omp critical
	    {
			for(y=0; y<height; y++) 
			{
				color = gdImageGetPixel(img, x, y);
				red   = gdImageRed(img, color);
				green = gdImageGreen(img, color);
				blue  = gdImageBlue(img, color);
				combined = 0.3*red + 0.59*green + 0.11*blue;
				color = gdImageColorAllocate(img, combined, combined, combined);
				gdImageSetPixel(img, x, y, color);
	        }
	    }
	}
	double t2 = omp_get_wtime();
	
	fp = fopen(output,"w");
	if(fp == NULL) 
	{
		printf("Error opening output file %s\n", output_file);
		return 1;
	}
	
	gdImagePng(img, fp);
	gdImageDestroy(img);
	fclose(fp);

	printf("File Size: %dx%d\n", width, height);
	printf("Time Taken: %.3lfms\n",(t2 - t1) * 1000);
	return 0;
}