#include <iostream>
#include <string.h>
#include <ctype.h>
#include "../lib/lib.h"
#include "../def/def.h"
#include "../lib/log.h"
#include "../lib/col.h"
#include "../lib/EasyBMP.h"
#include "../lib/lmg.h"

int prevalidation(int argc, char const *argv[], bool *mode){
	//program parameters: ./DFHM <mode> <size> [program instructions]
	//if mode is heightmap: ./DFHM Heightmap <size> [ <output type> <image> <output file>]
	//only the first letter of both <mode> and <output type> are parsed, they are not case sensitive
	//if mode is biome: ./DFHM Biome <size> <image> <output file>

	log::set_log_level(ALV);	//Set logging level to report only errors
	log::draw_bar('-',SBL);		//Draw first bar to encapsulate the prevalitaion messages

	if(argc<2){
		log::l(ERROR_NO_ARGS);
		return -1;
	}
	else if( 0 == validate_case_insensitive((char *)*(argv+1) ,"-h\0", 2) ){
		log::l(INSTRUCTIONS);
		return -2;
	}

	if(validate_mode(*(argv+1)) != 0){
		log::l(ERROR_BAD_MODE);
		log::ldat((char *)*(argv+1));
		return -3;
	}
	else{
		if(0 == validate_case_insensitive((char *)*(argv+1), "Heightmap", 1)){
			if(argc <5 ){
				log::l(ERROR_INSUFFICIENT_ARGUMENTS);
				return -4;
			}
			else{
				*mode = ACTIVE_MODE_HEIGHTMAP;
			}
		}
		else{
			if(argc < 4){
				log::l(ERROR_INSUFFICIENT_ARGUMENTS);
				return -5;
			}
			else{
				*mode = ACTIVE_MODE_BIOME;
			}
		}
	}

	if(validate_size(*(argv+2)) != 0){
		log::l(ERROR_BAD_SIZE);
		log::ldat((char *)*(argv+2));
		return -6;
	}

	log::ls("Successfully validatd mode, size and argument number", true);
	log::draw_bar('-',SBL);		//Draw second bar to encapsulate the prevalitaion messages
	return 0;
}

int validate_mode(const char *s){
	if((validate_case_insensitive((char *)s, "heightmap\0", 1) != 0) &&
		(validate_case_insensitive((char *)s, "biome\0", 1) != 0)) return -1;
	else return 0;
}

int validate_size(const char *s){
	unsigned int i=0;
	for(i=0;valid_sizes[i]!=0;i++){
		if(info <= log::get_log_level()) printf("comparing: %d vs %d\ti=%d\n", valid_sizes[i], atoi(s), i);
		if( (signed int)valid_sizes[i] == atoi(s) ) return 0;
	}
	return -1;
}

int validate_type(const char *s, bool warn){
	unsigned int i=0;

	for(i=0;map_list[i]!=NULL;i++){
		if( (0 == validate_case_insensitive((char *)map_list[i]->bsh_swt, (char *)s, 2))
		||	(0 == validate_case_insensitive((char *)map_list[i]->name, (char *)s, 1))){
			return 0;
		}
	}

	if(warn == true){
		log::l(ERROR_BAD_TYPE);
		log::ldat((char *)s);
	}

	return -1;
}

int validate_extension(const char *s, const char *ext){
	if( strlen(s) <= strlen(ext) ){
		log::l(ERROR_SHORT_FILE);
		log::ldat((char *)s);
		return -1;
	}
	else{
		//printf("%s\n", s+strlen(s)-strlen(ext));
		if (0 == strncmp(s+strlen(s)-strlen(ext), ext, strlen(ext))) return 0;
		else{
			log::l(ERROR_WRONG_EXTENSION);
			log::ldat((char *)s);
			return -1;
		}
	}
}

int validate_triplet(char const *argv[], int i){

	//printf("i: %d\n", i);
	//printf("(char*)*(argv+i): %s\n", (char*)*(argv+i));

	if( (*(argv+i) == NULL) || (*(argv+i+1) == NULL) ) return -1;

	if( 0 != validate_type( (char*)*(argv+i), true) ) return -2;
	if( 0 != validate_extension(*(argv+i+1), ".bmp") ) return -3;

	if( (*(argv+i+2) != NULL) ){
		if( 0 != validate_type((char*)*(argv+i+2), false) ){
			if( 0 != validate_extension(*(argv+i+2), ".txt") ){
				return -4;
			}
			else{
				return 0;
			}
		}
		else{
			log::l(NO_OUTPUT_FILE);
			return 0;
		}
		log::l(ERROR_FLOW_CONTROL);
	}
	else{
		log::l(NO_OUTPUT_FILE);
		return 0;
	}

	log::l(ERROR_FLOW_CONTROL);
	return 0;
}

int validate_case_insensitive(char *s1, char *s2, unsigned int n){
	char buf1[VBL]={0},  buf2[VBL]={0};
	int len=0;

	len = strlen(s1);
	if(strlen(s2) > (unsigned int)len) len = strlen(s2);

	bzero(buf1, VBL);
	bzero(buf2, VBL);

	strncpy(buf1, s1, VBL);
	strncpy(buf2, s2, VBL);

	for(;len>=0;len--){
		*(buf1+len) = tolower(*(buf1+len));
		*(buf2+len) = tolower(*(buf2+len));
	}

	if(strncmp(buf1, buf2, n) != 0) return -1;
	else return 0;
}

triplet *make_tripplet(char *t){
	triplet *aux=NULL;
	void *s_aux;

	if ( NULL == (aux = (triplet *)malloc( sizeof(triplet) * 1 )) ){
		log::l(ERROR_TRIP_MALLOC);
	}
	else{
		if ( NULL == (s_aux = malloc( sizeof(char) * (strlen(t)+1) )) ){
			log::l(ERROR_TRIP_MALLOC_MEMBER);
			free(aux);
			return NULL;
		}
		else{
			printf("t: %s\n", t);
			strncpy((char *)s_aux, t, strlen(t));
			aux->type = (char *)s_aux;
			printf("aux->type: %s\n", aux->type);
			return aux;
		}
	}

	log::l(ERROR_FLOW_CONTROL);
	return NULL;
}

int assemble_tripplet(triplet **trp, char *t, char *in, char *out){
	FILE *aux =NULL;

	*trp = make_tripplet(t);
	if( trp == NULL ) return -1;

	printf("trp->type: %s\n", (*trp)->type);

	if ( NULL == (aux = fopen(in, "r")) ){
		log::l(ERROR_OPEN_FILE);
		log::ldat(in);
		return -2;
	}
	else{
		printf("trp->input in at: %p\n", (*trp)->input );
		(*trp)->input = aux;
		printf("trp->input in at: %p\n", (*trp)->input );
		printf("\n\n");
	}

	if ( NULL == (aux = fopen(out, "w")) ){
		log::l(ERROR_OPEN_FILE);
		log::ldat(out);
		return -3;
	}
	else{
		printf("trp->output in at: %p\n", (*trp)->output );
		(*trp)->output = aux;
		printf("trp->output in at: %p\n", (*trp)->output );
		printf("\n\n");
	}

	return 0;
}

void print_triplet(triplet *t){
	printf("triplet:\t%s\t%p\t%p\n", t->type,t->input,t->output);
	printf("&triplet:\t%p\t%p\t%p\n", &t->type,&t->input,&t->output);
}

void free_triplet(triplet *t){
	free(t->type);
	fclose(t->input);
	fclose(t->output);
	free(t);
	return;
}
