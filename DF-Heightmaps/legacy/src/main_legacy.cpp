#include <iostream>
#include "../lib/lib_legacy.h"
#include "../lib/col.h"
#include "../def/def_legacy.h"
#include "../lib/dat_legacy.h"

int main(int argc, char const *argv[]) {

	//flow control variables
	unsigned char selected_type=0, type_i=0;
	unsigned int size=0;

	//indexation variables
	long i=0, j=0;

	//BMP processing variables
	unsigned char max_val=0, min_val=255, aux=0;
	char buffer[BFL]={0};
	unsigned int acc = 0;
	int pixel_val=0;
	BMP Heightmap;

	//output file variable
	FILE *output_file=NULL;

	if(validations(argc, argv, &Heightmap, &size, &selected_type, &type_i) != 0){
		return -1;
	}

	if(create_output(&output_file, type_i) != 0){
		return -2;
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
