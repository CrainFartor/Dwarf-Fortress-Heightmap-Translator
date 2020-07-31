#include "../lib/col.h"			//terminal color defines
#include "../lib/lmg.h"			//header for this file
#include <cstddef>					//included for definition of NULL

const log_message *logging_messages[]{
	&error_no_args,
	&error_bad_mode,
	&error_bad_size,
	&error_bad_type,
	&error_trip_malloc,
	&error_trip_malloc_member,
	&error_insufficient_arguments,
	&error_flow_control,
	&error_open_file,
	&error_short_file,
	&error_open_file,
	&no_output_file,
	&error_wrong_extension,
	&instructions,
	&warn_bad_triplet,
	&warn_bad_pixel,
	&error_bad_image_size,
	NULL
};

const log_message error_bad_image_size{
	error,
	ERROR_BAD_IMAGE_SIZE,
	ACR "ERROR" ACS ": Image size does not match selected size, remember that non square map sizes are not supported\0"
};

const log_message warn_bad_pixel{
	warn,
	WARN_BAD_PIXEL,
	ACY "WARNING" ACS ": Pixel has non matching RGB values, this is not intended in single type mode, a plain avarage of all 3 colors will be used insted.\0"
};

const log_message no_output_file{
	info,
	NO_OUTPUT_FILE,
	ACY "NOTICE" ACS ": No output file specified, the program will use the default output file.\0"
};

const log_message error_no_args{
	error,
	ERROR_NO_ARGS,
	ACR "ERROR" ACS ": No arguments given, use -h for information on how to use the program\0"
};

const log_message error_bad_mode{
	error,
	ERROR_BAD_MODE,
	ACR "ERROR" ACS ": Invalid mode selected\0"
};

const log_message error_bad_size{
	error,
	ERROR_BAD_SIZE,
	ACR "ERROR" ACS ": Invalid size selected\0"
};

const log_message error_insufficient_arguments{
	error,
	ERROR_INSUFFICIENT_ARGUMENTS,
	ACR "ERROR" ACS ": Not enough arguments given for selected mode\0"
};

const log_message error_bad_type{
	error,
	ERROR_BAD_TYPE,
	ACR "ERROR" ACS ": Invalid type selected\0"
};

const log_message error_trip_malloc{
	error,
	ERROR_TRIP_MALLOC,
	ACR "ERROR" ACS ": Failed to allocate memory for triplet\0"
};

const log_message error_trip_malloc_member{
	error,
	ERROR_TRIP_MALLOC_MEMBER,
	ACR "ERROR" ACS ": Failed to allocate memory for triplet member\0"
};

const log_message error_flow_control{
	error,
	ERROR_FLOW_CONTROL,
	ACR "ERROR" ACS ": Programming error: somehow a function has reached a point where it was not supposed to ever reach\0"
};

const log_message error_open_file{
	error,
	ERROR_OPEN_FILE,
	ACR "ERROR" ACS ": could not open file\0"
};

const log_message error_short_file{
	error,
	ERROR_SHORT_FILE,
	ACR "ERROR" ACS ": filename lenght is too short wich indicates either a file name just \".<extension>\" or an outright invalid argument\0"
};

const log_message warn_bad_triplet {
	warn,
	WARN_BAD_TRIPLET,
	ACY "WARNING" ACS ": failed to validate triplet, this and all following triplets will be ignored\0"
};

const log_message error_wrong_extension{
	error,
	ERROR_WRONG_EXTENSION,
	ACR "ERROR" ACS ": the file extension of the file does not correspond to the expected file extension for this argument\0"
};

const log_message instructions{
	error,
	INSTRUCTIONS,
	ACG "DFHM - Dwarf fortress heightmap translator" ACS "\n\n"
	ACB "General usage" ACS ": ./DFHM <mode> <size> [program instructions]" "\n"
	"Available modes: Heightmap (or simply H) --- Biome (or simply B) -- only the first letter of the mode argument is evaluated \n\n"

	ACC "Heightmap usage" ACS ": ./DFHM Heightmap <size> <output type> <image> <output file>\n"
	"Where <size> is a supported DF world size and <output type> <image> <output file> are the program inputs and outputs"
	"you can skip the <output file> member, the program will use the default output in such case\n"
	"Supported sizes: 17 33 65 129 257, preset generation of non square maps is not supported\n\n"
	"To specify a type you can either write the whole name or use a switch only the first letter will be evaluated in either case:\n\n"
	"Valid types:\t<Full type>\t<Switch>\n"
	"\t\tElevation\t-E\n"
	"\t\tRainfall\t-R\n"
	"\t\tTemperature\t-T\n"
	"\t\tDrainage\t-D\n"
	"\t\tVolcanism\t-V\n"
	"\t\tSavagery\t-S\n\n"
	"The input image can be any 8bit-depth .bmp, but the program expects a file where all pixels R, G and B values are the same per pixel (a greyscale image)\n"
	"Example heightmap usage: ./DFHM Heightmap 257 Elevation image1.bmp Altitude.txt\n\n"

	ACG "Biome usage" ACS ": ./DFHM Biome <size> <Image> <output file>\n"
	"Where <size> is a supported DF world size and <output type> <image> <output file> are the program inputs and outputs"
	"you can skip the <output file> member, the program will use the default output in such case\n"
	"Supported sizes: 17 33 65 129 257, preset generation of non square maps is not supported\n\n"
	"The input image can be any 8bit-depth .bmp file but it is meant to be use with images where pixel data corresponds in the following manner:\n"
	ACR "RED\t" ACS " corresponds to the temperature scale\n"
	ACB "BLUE\t" ACS " corresponds to the rainfall scale\n"
	ACG "GREEN\t" ACS " corresponds to the drainage scale\n"
	"Example biome usage: ./DFHM Biome 65 biomes.bmp presets.txt"
	"\0"
};
