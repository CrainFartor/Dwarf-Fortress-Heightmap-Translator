#ifndef	DATA
#define	DATA	240

#include <cstdio>

struct s_map{
	const char 						*name;
	const char 						*ps_start;
	const char						*bsh_swt;
	const unsigned int		i;
	const unsigned int		scale_max;
	const char						*default_output;
}typedef map;

extern const unsigned int valid_sizes[];
extern const map					*map_list[];
extern const map 					map_elevation;
extern const map 					map_rainfall;
extern const map 					map_temparature;
extern const map 					map_drainage;
extern const map 					map_volcanism;
extern const map 					map_savagery;

#endif
