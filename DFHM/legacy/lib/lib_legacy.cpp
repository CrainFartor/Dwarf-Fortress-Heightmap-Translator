#include <iostream>
#include "../lib/lib_legacy.h"
#include "../lib/col.h"
#include "../lib/dat_legacy.h"
#include "../def/def_legacy.h"

int validations(int argc, char const *argv[], BMP *Heightmap, unsigned int *size, unsigned char *selected_type, unsigned char *type_i){
	int i=0, j=0;

	if(argc < 4){
		std::cout << ACR << "Error" << ACS << ": not enough arguments given" << std::endl;
		std::cout << "Correct usage is:" << std::endl;
		std::cout << "./" << ACG << "DFHM" << ACS << " <Heightmap file> <Size> <WorldGen desired preset>" << std::endl;
		std::cout << "Example: ./" << ACG << "DFHM" << ACS << " Heightmap.bmp 257 S" << std::endl;
		std::cout << "Example: ./" << ACG << "DFHM" << ACS << " Heightmap.bmp 257 Savagery" << std::endl << std::endl << std::endl;
		return -1;
	}

	*size = std::stoi(*(argv+2));

	for(i=0, j=0;i<5;i++){
		if(*size == VS[i]){
			printf("Desired world size: %d" "X" "%d" "\n", *size, *size);
			break;
		}
		else j++;
	}
	if(j >= 5){
		std::cout << ACR << "Error" << ACS << ": size: " << ACB << +size << ACS;
		std::cout << ", is not a valid DF world size" << std::endl << std::endl << std::endl;
		return -2;
	}

	for(i=0, j=0;i<6;i++){
		if( (ML[i].type == *(*(argv+3))) || (ML[i].type+CTL == *(*(argv+3))) ){
			std::cout << "Selected type: " << *(argv+3) << " matches supported type: " << ML[i].type << std::endl;
			*selected_type = ML[i].type;
			*type_i = i;
			break;
		}
		else j++;
	}
	if(j >= 6){
		std::cout << ACR << "Type" << ACS << ": " << ACB <<  *(argv+3) << ACS;
		std::cout << ", is not a valid DF world preset" << std::endl << std::endl << std::endl;
		return -3;
	}

	if (true != Heightmap->ReadFromFile(*(argv+1)) ){
		std::cout << "The was an error while trying to handle the input heightmap file" << std::endl << std::endl << std::endl;
		return -4;
	}
	else{
		std::cout << "Successfully opened file: " << *(argv+1) << std::endl;
	}

	if( HM->TellWidth() != HM->TellHeight() ){
		std::cout << ACR << "Error" << ACS << ": heightmap width is different than heightmap height, this is not supported" << std::endl;
		return -5;
	}

	if( (unsigned int)HM->TellWidth() != *size ){
		std::cout << ACR << "Error" << ACS << ": heightmap size does not correspond with desired size, this is not supported" << std::endl;
		return -6;
	}

	if( HM->TellBitDepth() != 8 ){
		std::cout << ACR << "Error" << ACS << ": heightmap bit depth is not 8, this is not supported" << std::endl;
		return -7;
	}

	return 0;
}

int	create_output(FILE **output_file, unsigned char type_i){
	*output_file = fopen(outputs[type_i], "w");

	if( *output_file == NULL ){
		std::cout << ACR << "Error" << ACS << ": failed to create/open outfile: " << outputs[type_i] << std::endl;
		return -8;
	}
	else{
		std::cout << "Successfully create/opened file: " << outputs[type_i] << std::endl;
		return 0;
	}
}
