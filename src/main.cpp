#include <iostream>
#include "../lib/lib.h"
#include "../lib/log.h"
#include "../lib/col.h"
#include "../lib/EasyBMP.h"
#include "../def/def.h"
#include "../lib/dat.h"

lll log::log_level=none;

int main(int argc, char const *argv[]) {
	bool active_mode = false;
	unsigned int i=0;
	triplet *trip=NULL;;

	argv[argc] = NULL;	//Ensure that argv[] is NULL terminated

	if( 0 != prevalidation(argc, argv, &active_mode) ) return -1;

	if( active_mode == ACTIVE_MODE_HEIGHTMAP ){
		if( 0 == validate_triplet(argv, 3+i) ){
			if(0 == assemble_tripplet(&trip, (char *)*(argv+3+i), (char *)*(argv+3+i+1), (char *)*(argv+3+i+2)) ){
				print_triplet(trip);
				printf("HOLA\n");
			}
			else{
				printf("UY\n");
			}
		}
		else{
		}
	}
	else{
	}

	return 0;
}
