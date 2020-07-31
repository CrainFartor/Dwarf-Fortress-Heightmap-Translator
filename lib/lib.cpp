#include <iostream>
#include <string.h>
#include <ctype.h>
#include "../lib/lib.h"
#include "../def/def.h"
#include "../lib/log.h"
#include "../lib/col.h"
#include "../lib/EasyBMP.h"
#include "../lib/lmg.h"

int prevalidation(int argc, char const *argv[], bool *mode){
	//program parameters: ./DFHM <mode> <size> [program instructions]
	//if mode is heightmap: ./DFHM Heightmap <size> [ <output type> <image> <output file>]
	//only the first letter of both <mode> and <output type> are parsed, they are not case sensitive
	//if mode is biome: ./DFHM Biome <size> <image> <output file>

	log::set_log_level(ALV);	//Set logging level to report only errors
	log::draw_bar('-',SBL);		//Draw first bar to encapsulate the prevalitaion messages

	if(argc<2){
		log::l(ERROR_NO_ARGS);
		return -1;
	}
	else if( 0 == validate_case_insensitive((char *)*(argv+1) ,"-h\0", 2) ){
		log::l(INSTRUCTIONS);
		return -2;
	}

	if(validate_mode(*(argv+1)) != 0){
		log::l(ERROR_BAD_MODE);
		log::ldat((char *)*(argv+1));
		return -3;
	}
	else{
		if(0 == validate_case_insensitive((char *)*(argv+1), "Heightmap", 1)){
			if(argc <5 ){
				log::l(ERROR_INSUFFICIENT_ARGUMENTS);
				return -4;
			}
			else{
				*mode = ACTIVE_MODE_HEIGHTMAP;
			}
		}
		else{
			if(argc < 3){
				log::l(ERROR_INSUFFICIENT_ARGUMENTS);
				return -5;
			}
			else{
				*mode = ACTIVE_MODE_BIOME;
			}
		}
	}

	if(validate_size(*(argv+2)) != 0){
		log::l(ERROR_BAD_SIZE);
		log::ldat((char *)*(argv+2));
		return -6;
	}

	if(*mode == ACTIVE_MODE_HEIGHTMAP){
		if(validate_type(*(argv+3)) != 0){
			log::l(ERROR_BAD_TYPE);
			log::ldat((char *)*(argv+3));
			return -7;
		}
		if(validate_file(*(argv+4)) != 0){
			log::l(ERROR_OPEN_FILE);
			log::ldat((char *)*(argv+4));
			return -8;
		}
		if(validate_out(*(argv+5)) != 0){
			log::l(NO_OUTPUT_FILE);
		}
	}
	else{
		if(validate_file(*(argv+3)) != 0){
			log::l(ERROR_OPEN_FILE);
			log::ldat((char *)*(argv+3));
			return -9;
		}
		if(validate_out(*(argv+4)) != 0){
			log::l(NO_OUTPUT_FILE);
		}
	}

	log::ls("Successfully validatd mode, size and argument number", true);
	log::draw_bar('-',SBL);		//Draw second bar to encapsulate the prevalitaion messages
	return 0;
}

int validate_out(const char *s){	return (s != NULL) ? 0 : -1;	}

int validate_mode(const char *s){
	if((validate_case_insensitive((char *)s, "heightmap\0", 1) != 0) &&
		(validate_case_insensitive((char *)s, "biome\0", 1) != 0)) return -1;
	else return 0;
}

int validate_size(const char *s){
	unsigned int i=0;
	for(i=0;valid_sizes[i]!=0;i++){
		if( (signed int)valid_sizes[i] == atoi(s) ) return 0;
	}
	return -1;
}

int validate_type(const char *s){
	unsigned int i=0;

	for(i=0;map_list[i]!=NULL;i++){
		if( (0 == validate_case_insensitive((char *)map_list[i]->bsh_swt, (char *)s, 2))
		||	(0 == validate_case_insensitive((char *)map_list[i]->name, (char *)s, 1))){
			return 0;
		}
	}

	return -1;
}

int validate_file(const char *s){
	FILE *fpaux = NULL;
	if( NULL == (fpaux = fopen(s, "r")) ){
		return -1;
	}
	else{
		fclose(fpaux);
		return 0;
	}
}
/*
int validate_extension(const char *s, const char *ext){
	if( strlen(s) <= strlen(ext) ){
		log::l(ERROR_SHORT_FILE);
		log::ldat((char *)s);
		return -1;
	}
	else{
		//printf("%s\n", s+strlen(s)-strlen(ext));
		if (0 == strncmp(s+strlen(s)-strlen(ext), ext, strlen(ext))) return 0;
		else{
			log::l(ERROR_WRONG_EXTENSION);
			log::ldat((char *)s);
			return -1;
		}
	}
}
*/
int validate_case_insensitive(char *s1, char *s2, unsigned int n){
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

	if(strncmp(buf1, buf2, n) != 0) return -1;
	else return 0;
}

int validate_image_size(BMP *input, int size){

	if( (input->TellHeight() != size) || (input->TellWidth() != size) ){
		log::l(ERROR_BAD_IMAGE_SIZE);
		return -1;
	}

	return 0;
}

const map *get_map_type(char *type){
	unsigned int i=0;

	for(i=0;map_list[i]!=NULL;i++){
		if( (0 == validate_case_insensitive((char *)map_list[i]->bsh_swt, type, 2))
		||	(0 == validate_case_insensitive((char *)map_list[i]->name, type, 1))){
			return map_list[i];
		}
	}

	log::l(ERROR_FLOW_CONTROL);
	return NULL;
}

unsigned int get_type_color(const map *type){
	if( validate_case_insensitive((char *)type->bsh_swt, "-T", 2) == 0) return RED;
	if( validate_case_insensitive((char *)type->bsh_swt, "-R", 2) == 0) return BLUE;
	if( validate_case_insensitive((char *)type->bsh_swt, "-D", 2) == 0) return GREEN;
	if( validate_case_insensitive((char *)type->bsh_swt, "-S", 2) == 0) return ALPHA;

	log::l(ERROR_FLOW_CONTROL);
	return 100;
}

int generate_greyscale_preset(int size, const map *type, char *input, char *output){
	BMP Heightmap;
	bool pixel_warn = false;
	unsigned long i=0, j=0;
	int pixel_val=0;
	FILE *output_fp=NULL;
	char buffer[BFL]={0};

	if (true != Heightmap.ReadFromFile(input) ){
		log::l(ERROR_OPEN_FILE);
		return -1;
	}
	else{
		log::ls("The input file was recognized as a .bmp file",true);
	}
	if(output == NULL){
		output = (char *)type->default_output;
	}

	if( NULL == (output_fp = fopen(output, "w")) ){
		log::l(ERROR_OPEN_FILE);
		printf("file: %s\n", output);
		return -2;
	}

	if(0 != validate_image_size(&Heightmap, size) ) return -1;

	for(i=0;i<(unsigned long)size;i++){
		for(j=0;j<(unsigned long)size;j++){
			pixel_val = read_pixel_greyscale(&Heightmap, i, j, &pixel_warn);
			pixel_val = (type->scale_max * pixel_val) / MRV;
			if(pixel_warn == true){
				printf("pixel: %ld, %ld\n", i, j);
				log::l(WARN_BAD_PIXEL);
			}
			if(j == 0) fwrite(type->ps_start, sizeof(char), 6, output_fp);

			if( validate_case_insensitive((char *)type->bsh_swt, "-T", 2) == 0) pixel_val -= 30;

			bzero(buffer,BFL);
			sprintf(buffer, "%d", pixel_val);

			fwrite(":\0\0", sizeof(char), 1, output_fp);
			fwrite(buffer, sizeof(char), strlen(buffer), output_fp);

			if(j>=(unsigned long)size-1)	fwrite("]\n\0\0", sizeof(char), 2, output_fp);
		}
	}

	fclose(output_fp);
	return 0;
}

int generate_biome_preset(int size, char *input, char *output){
	BMP Heightmap;
	FILE *output_fp=NULL;
	unsigned int i=0;

	const map *type[]{
		&map_rainfall,
		&map_temparature,
		&map_drainage,
		&map_savagery,
		NULL
	};


	if (true != Heightmap.ReadFromFile(input) ){
		log::l(ERROR_OPEN_FILE);
		return -1;
	}
	else{
		log::ls("The input file was recognized as a .bmp file",true);
	}
	if(output == NULL){
		output = "preset.txt\0";
	}

	if( NULL == (output_fp = fopen(output, "w")) ){
		log::l(ERROR_OPEN_FILE);
		printf("file: %s\n", output);
		return -2;
	}

	if(0 != validate_image_size(&Heightmap, size) ) return -1;

	for(i=0;i<4;i++){
		write_biome_preset(&Heightmap, size, type[i], input, output_fp);
	}

	fclose(output_fp);
	return 0;
}

int write_biome_preset(BMP *Heightmap, int size, const map *type, char *input, FILE *output){
	bool pixel_warn = false;
	unsigned long i=0, j=0;
	int pixel_val=0;
	char buffer[BFL]={0};

	unsigned int color = get_type_color(type);

	for(i=0;i<(unsigned long)size;i++){
		for(j=0;j<(unsigned long)size;j++){
			pixel_val = read_pixel_color(Heightmap, i, j, color);
			pixel_val = (type->scale_max * pixel_val) / MRV;
			if(pixel_warn == true){
				printf("pixel: %ld, %ld\n", i, j);
				log::l(WARN_BAD_PIXEL);
			}
			if(j == 0) fwrite(type->ps_start, sizeof(char), 6, output);

			if( validate_case_insensitive((char *)type->bsh_swt, "-T", 2) == 0) pixel_val -= 30;

			bzero(buffer,BFL);
			sprintf(buffer, "%d", pixel_val);

			fwrite(":\0\0", sizeof(char), 1, output);
			fwrite(buffer, sizeof(char), strlen(buffer), output);

			if(j>=(unsigned long)size-1)	fwrite("]\n\0\0", sizeof(char), 2, output);
		}
	}

	return 0;
}

int read_pixel_greyscale(BMP *Heightmap, unsigned long i, unsigned long j, bool *warn){
	unsigned long acc=0;
	RGBApixel	pixel;

	pixel = Heightmap->GetPixel(i,j);

	if((pixel.Red != pixel.Blue) || (pixel.Red != pixel.Green) || (pixel.Blue != pixel.Green) ){
		*warn = true;
		acc = (pixel.Red + pixel.Blue + pixel.Green)/3;
		return acc;
	}
	else{
		*warn = false;
		return pixel.Red;
	}
}

int read_pixel_color(BMP *Heightmap, unsigned long i, unsigned long j, unsigned int color){
	RGBApixel	pixel;

	pixel = Heightmap->GetPixel(i,j);

	switch (color) {
		case RED:
			return pixel.Red;
		break;

		case GREEN:
			return pixel.Green;
		break;

		case BLUE:
			return pixel.Blue;
		break;

		case ALPHA:
			return pixel.Alpha;
		break;

		default:
			log::l(ERROR_FLOW_CONTROL);
			return -200;
		break;
	}
}
