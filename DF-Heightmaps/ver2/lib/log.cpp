#include "../def/def.h"
#include <iostream>
#include "lmg.h"
#include "col.h"
#include "log.h"

void log :: set_log_level(lll val){
	if((val > none)||(val < error)){
		CO << "Invalid logging level:" << val << EL;
	}
	else{
		log_level = val;
	}
}

lll log :: get_log_level(void){ return log_level; }

void log :: l(unsigned int warn_i){
	unsigned int i = 0;

	for(i=0;LMGS[i]!=NULL;i++){
		if( LMGS[i]->i == warn_i ) break;
	}
	if(LMGS[i] == NULL){
		CO << ACR "ERROR" ACS ": Could not find log message with index: " << warn_i << EL;
		return;
	}

	if( LMGS[i]->level <= log_level ){
		CO << LMGS[i]->msg << EL;
	}
}

void log :: ls(char * s, bool el){
	if( log_level >= info ) CO << s;
	if( el == true ) CO << EL;
}

void log :: ldat(char * s){
	if( log_level >= info ){
		ls((char *) "The line:\t", false);
		CO << s;
		ls((char *) "\tWas not recognized as valid for the expected parameter", true);
		CO << EL;
	}
}

void log :: draw_bar(char c, unsigned int l){
	unsigned int i=0;
	if( log_level < none ){
		for(i=0;i<l;i++) CO << c;
		CO << EL;
	}
}
