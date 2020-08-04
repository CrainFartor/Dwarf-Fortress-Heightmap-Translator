#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include "../lib/EasyBMP/EasyBMP.h"
#include "../lib/lib.h"
#include "../def/def.h"

int main(int argc, char const *argv[]) {
	BMP Map;
	BMP *Map_New;
	
	RGBApixel pixel={0,0,0,0};

	int i=0,j=0;

	if( false == prevalidation(argc, argv, &Map, &pixel) ) return -1;

	printf("Please wait while the program processes the image\n");
	Map_New = new BMP(Map);

	for(i=0;i<Map_New->TellHeight();i++){
		for(j=0;j<Map_New->TellWidth();j++){
			if(false == change_pixel_color_to_closest(&Map, Map_New, i, j, Map_New->TellHeight(), &pixel)){
				printf("The whole image is nothing but that color\n");
				printf("No output will be generated\n");
				return -2;
			}
		}
	}

	printf("Finished processing image please wait while the program writes the output file\n");

	Map_New->WriteToFile("output.bmp");

	printf("Finished writting file\n");

	return 0;
}
