#include <iostream>
#include <stdlib.h>
#include "../lib/EasyBMP/EasyBMP.h"
#include "../lib/lib.h"
#include "../def/def.h"

int main(int argc, char const *argv[]) {
	BMP Map;
	RGBApixel usr_pixel={0,0,0,0};

	if( true == prevalidation(argc, argv, &Map, &usr_pixel) ){
		printf("Amount of pixels of color: %d %d %d %d\nAmount: %d\n", usr_pixel.Red, usr_pixel.Green, usr_pixel.Blue, usr_pixel.Alpha,
		get_pixel_count(&Map, usr_pixel));
		return 0;
	}
	else{
		return -1;
	}
}
