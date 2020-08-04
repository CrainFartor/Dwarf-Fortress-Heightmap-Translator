#ifndef		LOG_MESSAGES
#define		LOG_MESSAGES	100
#include "../lib/log.h"	//included for definition of enum type lll

struct s_log_message{
	lll level;
	const unsigned int i;
	const char *msg;
}typedef log_message;

extern const log_message *logging_messages[];

extern const log_message error_no_args;
extern const log_message error_bad_mode;
extern const log_message error_bad_size;
extern const log_message error_bad_type;
extern const log_message error_trip_malloc;
extern const log_message error_trip_malloc_member;
extern const log_message error_insufficient_arguments;
extern const log_message error_flow_control;
extern const log_message instructions;
extern const log_message error_open_file;
extern const log_message error_short_file;
extern const log_message error_wrong_extension;
extern const log_message no_output_file;
extern const log_message warn_bad_triplet;
extern const log_message warn_bad_pixel;
extern const log_message error_bad_image_size;

#define		LMGS						logging_messages

#define		ERROR_NO_ARGS										0
#define		ERROR_BAD_MODE									1
#define		ERROR_BAD_SIZE									2
#define		ERROR_INSUFFICIENT_ARGUMENTS		3
#define		ERROR_BAD_TYPE									4
#define		ERROR_TRIP_MALLOC								6
#define		ERROR_TRIP_MALLOC_MEMBER				7
#define		ERROR_OPEN_FILE									8
#define		ERROR_WRONG_EXTENSION						9
#define		ERROR_SHORT_FILE								10
#define		NO_OUTPUT_FILE									11
#define		WARN_BAD_PIXEL									12
#define		WARN_BAD_TRIPLET								13
#define		ERROR_BAD_IMAGE_SIZE						14
//#define
//#define

#define		INSTRUCTIONS										20

#define		ERROR_FLOW_CONTROL							50

#endif
