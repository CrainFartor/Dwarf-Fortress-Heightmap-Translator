#ifndef	LIBRERIAS
#define	LIBRERIAS	255

#include	"dat.h"

#define		VALIDATION_BUFFER_LENGTH	2048
#define		VBL	VALIDATION_BUFFER_LENGTH

int	prevalidation(int argc, char const *argv[], bool *mode);

int validate_mode(const char *s);
int validate_size(const char *s);
int validate_type(const char *s, bool warn);
int validate_extension(const char *s, const char *ext);
int validate_triplet(char const *argv[], int i);
int validate_case_insensitive(char *s1, char *s2, unsigned int n);


triplet *make_tripplet(char *t);
int  assemble_tripplet(triplet **trp, char *t, char *in, char *out);
void free_triplet(triplet *t);
void print_triplet(triplet *t);

#endif
