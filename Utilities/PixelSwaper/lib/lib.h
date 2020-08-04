#ifndef	LIBRERIAS
#define	LIBRERIAS	255

#include "../lib/EasyBMP/EasyBMP.h"
#include "../def/def.h"

bool change_pixel_color_to_closest(BMP *Input, BMP *Output, int i, int j, int size, RGBApixel *color_to_change);
RGBApixel square_nonmatching_search(BMP *Heightmap, RGBApixel *pixel, int radius, int i, int j, int size);
bool compare_pixel(RGBApixel *pixel1, RGBApixel *pixel2);
bool end_reached(int current, int start, int radius, int size);

bool prevalidation(int argc, char const *argv[], BMP *Map, RGBApixel *pix);

bool validate_case_insensitive(const char *s1, const char *s2, unsigned int n);
bool validate_switch(const char *s1, const char *s2);
bool is_number(char *arg);

void pb(char c, int l);

#endif
