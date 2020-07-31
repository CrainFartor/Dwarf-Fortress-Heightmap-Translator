#include <iostream>
#include "../lib/lib.h"
#include "../lib/log.h"
#include "../lib/col.h"
#include "../lib/EasyBMP.h"
#include "../def/def.h"
#include "../lib/dat.h"
#include "../lib/lmg.h"

lll log::log_level=none;

int main(int argc, char const *argv[]) {
	bool active_mode = false;

	argv[argc] = NULL;	//Ensure that argv[] is NULL terminated

	if( 0 != prevalidation(argc, argv, &active_mode) ) return -1;

	if( active_mode == ACTIVE_MODE_HEIGHTMAP ){

	}
	else{
	}

	return 0;
}
