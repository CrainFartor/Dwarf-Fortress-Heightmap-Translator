#include <cstddef>
#include "dat.h"

const unsigned int valid_sizes[]{
	17,
	33,
	65,
	129,
	257,
	0
};

const map *map_list[]{
	&map_elevation,
	&map_rainfall,
	&map_elevation,
	&map_drainage,
	&map_volcanism,
	&map_savagery,
	NULL
};

const map map_elevation{
	"Elevation\0",
	"-E\0",
	0,
	400,
	"elevation.txt\0"
};
const map map_rainfall{
	"Rainfall\0",
	"-R\0",
	1,
	100,
	"rainfall.txt\0"
};
const map map_temparature{
	"Temperature\0",
	"-T\0",
	2,
	170,
	"temperature.txt\0"
};
const map map_drainage{
	"Drainage\0",
	"-D\0",
	3,
	100,
	"drainage.txt\0"
};
const map map_volcanism{
	"Volcanism\0",
	"-V\0",
	4,
	100,
	"volcanism.txt\0"
};
const map map_savagery{
	"Savagery\0",
	"-S\0",
	5,
	100,
	"savagery.txt\0"
};
