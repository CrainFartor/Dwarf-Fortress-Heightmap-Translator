#ifndef	DATA
#define	DATA	240

struct s_map{
	unsigned char type;
	unsigned int s_max;
};

typedef struct s_map map;

extern const unsigned int valid_sizes[];

extern const char *outputs[];

extern const map map_list[];

#endif
