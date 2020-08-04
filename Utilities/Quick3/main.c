#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define	VBL	2048

int validate_case_insensitive(const char *s1, const char *s2, unsigned int n);
int validate_switch(const char *s1, const char *s2);

int main(int argc, char const *argv[]) {
	int smax=0, val=0, i=0;

	if(argc <= 1){
		printf("Usage: ./Q3 <type> <value>\n");
		printf("Valid types:\n"
		"-E : Elevation\n"
		"-T : Temperature\n"
		"-R : Rainfall\n"
		"-D : Drainage\n"
		"-S : Savagery\n"
		"-V : Volcanism\n");
		return -10;
	}

	if((0 == validate_switch(argv[1], "r\0"))	||
		(0 == validate_switch(argv[1], "d\0"))	||
		(0 == validate_switch(argv[1], "v\0"))	||
		(0 == validate_switch(argv[1], "s\0"))	){
		smax = 100;
	}
	else if (0 == validate_switch(argv[1], "e\0")){
		smax = 400;
	}
	else if (0 == validate_switch(argv[1], "t\0")){
		smax = 170;
	}
	else if (0 == validate_switch(argv[1], "h\0")){
		printf("Usage: ./Q3 <type> <value>\n");
		printf("Valid types:\n"
		"-E : Elevation\n"
		"-T : Temperature\n"
		"-R : Rainfall\n"
		"-D : Drainage\n"
		"-S : Savagery\n"
		"-V : Volcanism\n");
		return 1;
	}
	else{
		printf("No valid switch given use: -H for info on how to use the program\n");
		return -1;
	}

	if(argv[2] == NULL){
		printf("No value given, imposible to make conversion\n");
		return -56;
	}

	for(i=0;(*(argv[2]+i)) != '\0';i++){
		if(isdigit(*(argv[2]+i)) == 0){
			printf("The third argument must be a number\n");
			return -2;
		}
	}

	val = atoi(argv[2]);

	if( (val < 0) || (val > smax)){
		printf("the value: %d is not valid for the given type\n", val);
		return -3;
	}

	printf("Value on a scale of 0 to 255:\t%d\n", ((val*255)/smax));

	return 0;
}

int validate_switch(const char *s1, const char *s2){
	char aux[3]={'-','\0','\0'};

	strncat(aux, s2, 1);

	if((0 == validate_case_insensitive(s1, s2, 1)) ||
 	(0 == validate_case_insensitive(s1, aux, 2))){
		return 0;
	}
	else{
		return -1;
	}
}

int validate_case_insensitive(const char *s1, const char *s2, unsigned int n){
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
