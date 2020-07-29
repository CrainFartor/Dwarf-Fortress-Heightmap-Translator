#include "dat.h"

const unsigned int valid_sizes[5]={
	17,
	33,
	65,
	129,
	257
};

const char *outputs[6]={
	"Elevation.txt",
	"Rainfall.txt",
	"Temperature.txt",
	"Drainage.txt",
	"Volcanism.txt",
	"Savagery.txt"
};

const map map_list[6]={
	{'E',		400},
	{'R',		100},
	{'T',		170},
	{'D',		100},
	{'V',		100},
	{'S',		100}
};
