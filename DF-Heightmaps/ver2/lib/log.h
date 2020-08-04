#ifndef	LOG
#define	LOG	220

enum log_level_list{error=0,warn=1,info=2,none=3};
typedef enum log_level_list		lll;

class log{
public:
	static void							set_log_level(lll val);
	static lll							get_log_level(void);

	static void							l(unsigned int warn_i);
	static void							ls(char * s, bool el);
	static void							ldat(char * s);
	static void							draw_bar(char c, unsigned int l);
private:
	log(){}

	static lll 							log_level;
};

#endif
