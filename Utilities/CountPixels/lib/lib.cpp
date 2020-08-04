#include "../lib/lib.h"

bool compare_pixel(RGBApixel pixel1, RGBApixel pixel2){
	if((pixel1.Red == pixel2.Red)
	&& (pixel1.Blue == pixel2.Blue)
	&& (pixel1.Green == pixel2.Green)
	&& (pixel1.Alpha == pixel2.Alpha)) return true;
	else return false;
}

bool check_pixel(BMP *im, int i, int j, RGBApixel pix){
	RGBApixel pix_aux;
	pix_aux = im->GetPixel(i,j);
	if( true == compare_pixel(pix_aux, pix) ) return true;
	return false;
}

int get_pixel_count(BMP *im, RGBApixel pix){
	int i=0, j=0, amount=0;
	for(i=0;i<im->TellWidth();i++){
		for(j=0;j<im->TellHeight();j++){
			if(check_pixel(im,i,j, pix) == true) amount++;
		}
	}
return amount;
}

bool prevalidation(int argc, char const *argv[], BMP *Map, RGBApixel *pix){
	const RGBApixel black_pixel={0,0,0,255};
	bool file_open = false;

	if((argc < 2) || ((argc >= 2) && (validate_case_insensitive("-H\0",argv[1],2) == true))){
		printf("This program count the amount of pixels of a specified color\n\n");
		printf("Usage: ./CountPixel <input file> [<Red> <Green> <Blue> [<Alpha>]]\n\n");
		printf("The [<Alpha>] argument is entirely optional and if you do not specify an alpha value the program will default to 255, note that most .bmp files do not support alpha values\n\n");
		printf("If no [<Red> <Green> <Blue>] values are specified the program will default to looking for black pixels (0,0,0,255)\n\n");
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
