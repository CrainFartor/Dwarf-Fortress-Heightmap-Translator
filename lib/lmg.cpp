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
	NULL
};

const log_message no_output_file{
	info,
	NO_OUTPUT_FILE,
	ACY "NOTICE" ACS ": No output file specified for this triplet, the program will use the default output file.\n"
	"If you are trying to generate multiple heightmaps for this type the output of this triplet may be overriden\0"
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
	ACC "Heightmap usage" ACS ": ./DFHM Heightmap <size> [<image> <output type> <output file>]\n"
	"Where <size> is a supported DF world size and [<output type> <image> <output file>] is a triplet of \"linked\" arguments "
	"you can skip the <output file> member, all triplets after the first none matching or incomplete triplet will be ignored\n"
	"Supported sizes: 17 33 65 129 257, preset generation of non square maps is not supported\n\n"
	"All <image> arguments " ACR "MUST" ACS " end with .bmp, all <output> arguments " ACR "MUST" ACS " end with .txt\n"
	"Example heightmap usage: ./DFHM Heightmap 257 Elevation image1.bmp Altitude.txt Rainfaill image2.bmp\n\n"
	ACG "Biome usage" ACS ": ./DFHM Biome <size> <Image> <output file>\n"
	"the <image> argument " ACR "MUST" ACS " end with .bmp, the <output> argument " ACR "MUST" ACS " end with .txt\n"
	"The input image can be any 8bit-depth .bmp file but it is meant to be use with images where pixel data corresponds in the following manner:\n"
	ACR "RED\t" ACS " corresponds to the temperature scale\n"
	ACB "BLUE\t" ACS " corresponds to the rainfall scale\n"
	ACG "GREEN\t" ACS " corresponds to the drainage scale\n"
	ACM "ALPHA\t" ACS " corresponds to the savagery scale\n\n"
	"Example biome usage: ./DFHM Biome 65 biomes.bmp presets.txt"
	"\0"
};