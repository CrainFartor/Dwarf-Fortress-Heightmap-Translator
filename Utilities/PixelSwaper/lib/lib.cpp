#include "../lib/lib.h"

bool change_pixel_color_to_closest(BMP *Input, BMP *Output, int i, int j, int size, RGBApixel *color_to_change){
	int l=0;
	RGBApixel new_pixel;
	RGBApixel aux = {0, 0, 0, 0};
	const RGBApixel empty = {0, 0, 0, 0};

	aux = Input->GetPixel(i,j);

	if(false == compare_pixel(&aux, color_to_change)){
		return true;
	}

	for(l=0;l<size;l++){
		new_pixel = square_nonmatching_search(Input, color_to_change, l, i, j, size);
		if(false == compare_pixel(&new_pixel, (RGBApixel *)&empty)) break;
	}

	if(true == compare_pixel(&new_pixel, (RGBApixel *)&empty)){
		return false;
	}
	else{
		if(false == Output->SetPixel(i, j, new_pixel)) return false;
		else return true;
	}
}

RGBApixel square_nonmatching_search(BMP *Heightmap, RGBApixel *pixel, int radius, int i, int j, int size){
	RGBApixel empty = {0, 0, 0, 0};
	RGBApixel aux = {0, 0, 0, 0};
	int l_i=0, l=0, t_i=0, t=0;
	bool flow_l=false, flow_t=false;

	l_i = (i-radius >= 0) ? i-radius : 0;
	t_i = (j-radius >= 0) ? j-radius : 0;

	for(l=l_i;true!=flow_l;l++){
		flow_t=false;
		for(t=t_i;true!=flow_t;t++){
			aux = Heightmap->GetPixel(l,t);
			if( true != compare_pixel( &aux, pixel  ) ){
				return aux;
			}
			flow_t = end_reached(t, j, radius, size);
		}
		flow_l = end_reached(l, i, radius, size);
	}
	return empty;
}

bool end_reached(int current, int start, int radius, int size){
	if( (current >= size-1) || (current >= start + radius) ) return true;
	else return false;
}

bool compare_pixel(RGBApixel *pixel1, RGBApixel *pixel2){
	if((pixel1->Red == pixel2->Red)
	&& (pixel1->Blue == pixel2->Blue)
	&& (pixel1->Green == pixel2->Green)
	&& (pixel1->Alpha == pixel2->Alpha)) return true;
	else return false;
}

void pb(char c, int l){
	int i=0;
	for(i=0;i<l;i++) putchar(c);
	putchar('\n');
}

bool prevalidation(int argc, char const *argv[], BMP *Map, RGBApixel *pix){
	const RGBApixel black_pixel={0,0,0,255};
	bool file_open = false;

	if((argc < 2) || ((argc >= 2) && (validate_case_insensitive("-H\0",argv[1], 2) == true))){
		printf("This program changes the color of a pixel that matches the specifed RGBA values to the color of the closest non-matching pixel\n\n");
		printf("Usage: ./PixelSwaper <input file> [<Red> <Green> <Blue> [<Alpha>]]\n\n");
		printf("The [<Alpha>] argument is entirely optional and if you do not specify an alpha value the program will default to 255, note that most .bmp files do not support alpha values\n\n");
		printf("If no [<Red> <Green> <Blue>] values are specified the program will default to looking for black pixels (0,0,0,255)\n\n");
		printf("Note that if you provide a color that is not present on the file, the program will still generate an output\n\n");
		return false;
	}

	file_open = Map->ReadFromFile(argv[1]);
	if(file_open == false){
		printf("Failed to open file: %s\n", argv[1]);
		return false;
	}

	if(argc >= 5){
		if(true == is_number((char *)argv[2])) pix->Red = atoi(argv[2]);
		else return false;

		if(true == is_number((char *)argv[3])) pix->Green = atoi(argv[3]);
		else return false;

		if(true == is_number((char *)argv[4])) pix->Blue = atoi(argv[4]);
		else return false;

		if(argc >= 6) pix->Alpha = (true == is_number((char *)argv[5])) ? atoi(argv[5]) : 255;
		else pix->Alpha = 255;
	}
	else{
		printf("Not enough arguments guven for [<Red> <Green> <Blue> [<Alpha>]], The program will deafult to looking for black pixels\n");
		pix->Red = black_pixel.Red;
		pix->Green = black_pixel.Green;
		pix->Blue = black_pixel.Blue;
		pix->Alpha = black_pixel.Alpha;
	}

	return true;
}

bool validate_switch(const char *s1, const char *s2){
	char aux[3]={'-','\0','\0'};

	strncat(aux, s2, 1);

	if((0 == validate_case_insensitive(s1, s2, 1)) ||
 	(0 == validate_case_insensitive(s1, aux, 2))){
		return true;
	}
	else{
		return false;
	}
}

bool validate_case_insensitive(const char *s1, const char *s2, unsigned int n){
	char buf1[VBL]={0},  buf2[VBL]={0};
	int len=0;

	len = strlen(s1);
	if(strlen(s2) > (unsigned int)len) len = strlen(s2);

	bzero(buf1, VBL);
	bzero(buf2, VBL);

	strncpy(buf1, s1, VBL);
	strncpy(buf2, s2, VBL);

	for(;len>=0;len--){
		*(buf1+len) = tolower(*(buf1+len));
		*(buf2+len) = tolower(*(buf2+len));
	}

	if(strncmp(buf1, buf2, n) != 0) return false;
	else return true;
}

bool is_number(char *arg){
	unsigned int i=0;
	for(i=0;*(arg+i) != '\0';i++){
		if(isdigit(*(arg+i)) == 0){
			printf("This argument is not a number: %s\n", arg);
			return false;
		}
	}
	return true;
}
