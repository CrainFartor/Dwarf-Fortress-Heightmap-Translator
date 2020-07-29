#include <iostream>
#include "../lib/lib.h"
#include "../lib/col.h"
#include "../lib/EasyBMP.h"
#include "../def/def.h"
#include "../lib/dat.h"

int main(int argc, char const *argv[]) {

	long i=0, j=0;
	unsigned int size=0;
	unsigned char selected_type=0, type_i=0;
	BMP Heightmap;
	unsigned char max_val=0, min_val=255, aux=0;
	unsigned int acc = 0;
	int pixel_val=0;
	FILE *output_file=NULL;
	char buffer[BFL]={0};

	if(argc < 4){
		std::cout << ACR << "Error" << ACS << ": not enough arguments given" << std::endl;
		std::cout << "Correct usage is:" << std::endl;
		std::cout << "./" << ACG << "DFHM" << ACS << " <Heightmap file> <Size> <WorldGen desired preset>" << std::endl << std::endl << std::endl;
		return -1;
	}

	size = std::stoi(*(argv+2));

	for(i=0, j=0;i<5;i++){
		if(size == VS[i]){
			printf("Desired world size: %d" "X" "%d" "\n", size, size);
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
			selected_type = ML[i].type;
			type_i = i;
			break;
		}
		else j++;
	}
	if(j >= 6){
		std::cout << ACR << "Type" << ACS << ": " << ACB <<  *(argv+3) << ACS;
		std::cout << ", is not a valid DF world preset" << std::endl << std::endl << std::endl;
		return -3;
	}

	if (true != Heightmap.ReadFromFile(*(argv+1)) ){
		std::cout << "The was an error while trying to handle the input heightmap file" << std::endl << std::endl << std::endl;
		return -4;
	}
	else{
		std::cout << "Successfully opened file: " << *(argv+1) << std::endl;
	}

	if( HM.TellWidth() != HM.TellHeight() ){
		std::cout << ACR << "Error" << ACS << ": heightmap width is different than heightmap height, this is not supported" << std::endl;
		return -5;
	}

	if( (unsigned int)HM.TellWidth() != size ){
		std::cout << ACR << "Error" << ACS << ": heightmap size does not correspond with desired size, this is not supported" << std::endl;
		return -6;
	}

	if( HM.TellBitDepth() != 8 ){
		std::cout << ACR << "Error" << ACS << ": heightmap bit depth is not 8, this is not supported" << std::endl;
		return -7;
	}

	//std::cout << "Image is: " << +HM.TellWidth() << "x" << +HM.TellHeight() << " with a bit deph of: " << +HM.TellBitDepth() << std::endl;

	output_file = fopen(outputs[type_i], "w");

	if( output_file == NULL ){
		std::cout << ACR << "Error" << ACS << ": failed to create/open outfile: " << outputs[type_i] << std::endl;
		return -8;
	}
	else{
		std::cout << "Successfully create/opened file: " << outputs[type_i] << std::endl;
	}

	for(i=0;i<HM.TellWidth();i++){
		for(j=0;j<HM.TellHeight();j++){
			if( (HM(i,j)->Red != HM(i,j)->Blue) || (HM(i,j)->Red != HM(i,j)->Green) || (HM(i,j)->Blue != HM(i,j)->Green)  ){
				std::cout << ACY << "Warning" << ACS ", pixel: X: " << i << " Y: " << j << ' ';
				std::cout << "does not have all 3 colors with equal values, the program will now use an avarage of all 3" << std::endl;
				acc = (HM(i,j)->Red + HM(i,j)->Blue + HM(i,j)->Green)/3 ;
				aux = acc;
			}
			else{
				aux = HM(i,j)->Red;
			}

			if( HM(i,j)->Alpha != 255 ){
				std::cout << ACY << "Warning" << ACS ", pixel: X: " << i << " Y: " << j << ' ';
				std::cout << "does not have an alpha value of 255, the program ignores alpha values, if you intended the alpha to do something, it won't, if you "
				"didn't intend the alpha to do anything then you can ignore this warning" << std::endl;
			}

			max_val = (aux > max_val) ? aux : max_val;
			min_val = (aux < min_val) ? aux : min_val;

			pixel_val = (ML[type_i].s_max * aux) / MRV;

			if(j==0){
				switch(selected_type){
					case 'E':
						fwrite("[PS_EL\0\0", sizeof(char), 6, output_file);
					break;

					case 'R':
						fwrite("[PS_RF\0\0", sizeof(char), 6, output_file);
					break;

					case 'T':
						fwrite("[PS_TP\0\0", sizeof(char), 6, output_file);
					break;

					case 'D':
						fwrite("[PS_DR\0\0", sizeof(char), 6, output_file);
					break;

					case 'V':
						fwrite("[PS_VL\0\0", sizeof(char), 6, output_file);
					break;

					case 'S':
						fwrite("[PS_SV\0\0", sizeof(char), 6, output_file);
					break;

					default:
						std::cout << ACR << "Error" << ACS << ": Something went wrong when trying to process data for output file" << std::endl;
						return -10;
					break;
				}
			}

			if(selected_type == 'T')	pixel_val-=30;

			bzero(buffer,BFL);
			sprintf(buffer, "%d", pixel_val);

			fwrite(":\0\0", sizeof(char), 1, output_file);

			fwrite(buffer, sizeof(char), strlen(buffer), output_file);

			if(j>=size-1)	fwrite("]\n\0\0", sizeof(char), 2, output_file);

			/*printf("Pixel (R G B): %d, %d, %d", HM(i,j)->Red , HM(i,j)->Blue , HM(i,j)->Green);
			printf(" Alpha: %d \n", HM(i,j)->Alpha);*/
		}
	}

	std::cout << "max: " << +max_val << " min: " << +min_val << std::endl;

	fclose(output_file);

	return 0;
}
