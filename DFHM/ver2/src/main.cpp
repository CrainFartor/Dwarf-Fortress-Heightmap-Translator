#include <iostream>
#include "../lib/lib.h"
#include "../lib/log.h"
#include "../lib/col.h"
#include "../def/def.h"
#include "../lib/dat.h"
#include "../lib/lmg.h"

lll log::log_level=none;

int main(int argc, char const *argv[]) {
	bool active_mode = false;
	char *input = NULL;
	char *output = NULL;
	int size=0;
	const map *type=NULL;

	argv[argc] = NULL;	//Ensure that argv[] is NULL terminated

	if( 0 != prevalidation(argc, argv, &active_mode) ) return -1;

	if( active_mode == ACTIVE_MODE_HEIGHTMAP ){
		size = atoi((char *)*(argv+2));
		type = get_map_type((char *)*(argv+3));
		input = (char *)*(argv+4);
		output = (char *)*(argv+5);

		if (0 == generate_greyscale_preset(size, type, input, output)) return 0;
		else return -2;
	}
	else{
		size = atoi((char *)*(argv+2));
		input = (char *)*(argv+3);
		output = (char *)*(argv+4);

		if (0 == generate_biome_preset(size, input, output)) return 0;
		else return -3;
	}

	return 0;
}
