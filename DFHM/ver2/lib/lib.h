#ifndef	LIBRERIAS
#define	LIBRERIAS	255

#include "../../EasyBMP/EasyBMP.h"
#include	"dat.h"

#define		VALIDATION_BUFFER_LENGTH	2048
#define		VBL	VALIDATION_BUFFER_LENGTH

#define		RED			0
#define		GREEN		1
#define		BLUE		2
#define		ALPHA		3

int	prevalidation(int argc, char const *argv[], bool *mode);

int validate_mode(const char *s);
int validate_size(const char *s);
int validate_type(const char *s);
//int validate_extension(const char *s, const char *ext);
int validate_file(const char *s);
int validate_out(const char *s);
int validate_case_insensitive(char *s1, char *s2, unsigned int n);

const map *get_map_type(char *type);
unsigned int get_type_color(const map *type);

int generate_greyscale_preset(int size, const map *type, char *input, char *output);
int generate_biome_preset(int size, char *input, char *output);
int write_biome_preset(BMP *Heightmap, int size, const map *type, char *input, FILE *output);

int generate_biome_preset();

int validate_image_size(BMP *input, int size);
int read_pixel_greyscale(BMP *Heightmap, unsigned long i, unsigned long j, bool *warn);
int read_pixel_color(BMP *Heightmap, unsigned long i, unsigned long j, unsigned int color);

#endif
