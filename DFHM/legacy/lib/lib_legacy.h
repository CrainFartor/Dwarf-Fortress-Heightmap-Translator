#ifndef	LIBRERIAS
#define	LIBRERIAS	255
#include "../../EasyBMP/EasyBMP.h"

int validations(int argc, char const *argv[], BMP *Heightmap, unsigned int *size, unsigned char *selected_type, unsigned char *type_i);
int	create_output(FILE **output_file, unsigned char type_i);

#endif
