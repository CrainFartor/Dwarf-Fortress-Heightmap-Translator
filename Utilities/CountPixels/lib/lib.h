#ifndef	LIBRERIAS
#define	LIBRERIAS	255

#include "../lib/EasyBMP/EasyBMP.h"
#include "../def/def.h"

int get_pixel_count(BMP *im, RGBApixel pix);

bool compare_pixel(RGBApixel pixel1, RGBApixel pixel2);
bool check_pixel(BMP *im, int i, int j, RGBApixel pix);

bool prevalidation(int argc, char const *argv[], BMP *Map, RGBApixel *pix);

bool validate_switch(const char *s1, const char *s2);
bool validate_case_insensitive(const char *s1, const char *s2, unsigned int n);
bool is_number(char *arg);

#endif
