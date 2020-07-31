#ifndef	LIBRERIAS
#define	LIBRERIAS	255

#include	"dat.h"

#define		VALIDATION_BUFFER_LENGTH	2048
#define		VBL	VALIDATION_BUFFER_LENGTH

int	prevalidation(int argc, char const *argv[], bool *mode);

int validate_mode(const char *s);
int validate_size(const char *s);
int validate_type(const char *s);
//int validate_extension(const char *s, const char *ext);
int validate_file(const char *s);
int validate_out(const char *s);
int validate_case_insensitive(char *s1, char *s2, unsigned int n);

#endif
