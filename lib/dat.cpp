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
	&map_temparature,
	&map_drainage,
	&map_volcanism,
	&map_savagery,
	NULL
};

const map map_elevation{
	"Elevation\0",
	"[PS_EL\0",
	"-E\0",
	0,
	400,
	"elevation.txt\0"
};
const map map_rainfall{
	"Rainfall\0",
	"[PS_RF\0",
	"-R\0",
	1,
	100,
	"rainfall.txt\0"
};
const map map_temparature{
	"Temperature\0",
	"[PS_TP\0",
	"-T\0",
	2,
	170,
	"temperature.txt\0"
};
const map map_drainage{
	"Drainage\0",
	"[PS_DR\0",
	"-D\0",
	3,
	100,
	"drainage.txt\0"
};
const map map_volcanism{
	"Volcanism\0",
	"[PS_VL\0",
	"-V\0",
	4,
	100,
	"volcanism.txt\0"
};
const map map_savagery{
	"Savagery\0",
	"[PS_SV\0",
	"-S\0",
	5,
	100,
	"savagery.txt\0"
};
