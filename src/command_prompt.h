#ifndef command_prompt_H
#define command_prompt_H

#include "history_buffer.h"

#define ARROW_UP 			  72		// will output 2 bytes instead of 1 byte when press, first byte is  224
#define ARROW_DOWN  		  80		// will output 2 bytes instead of 1 byte when press, first byte is  224
#define ARROW_LEFT 			  75		// will output 2 bytes instead of 1 byte when press, first byte is  224
#define ARROW_RIGHT 		  77		// will output 2 bytes instead of 1 byte when press, first byte is  224
#define KEY_DELETE  		  83		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define KEY_INSERT 	 		  82		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define KEY_PAGEUP  		  73		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define KEY_PAGEDOWN 		  81		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define KEY_HOME 			  71		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define KEY_END 			  79		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define KEY_ENTER			  13		// this is not a special key, only give 1 byte which is 13
#define KEY_BACKSPACE	 	   8		// this is not a special key, only give 1 byte which is 8
#define KEY_ESCAPE			  27	
#define MAX_BUFFER_SIZE		1024		
#define ESCAPECODE1			   0	
#define ESCAPECODE2			 224	
#define NORMALCODE			 255
#define CODE_ARROWUP		 0xE048
#define CODE_ARROWDOWN		 0xE050
#define CODE_ARROWLEFT		 0xE04B
#define CODE_ARROWRIGHT		 0xE04D
#define CODE_DELETE1		 0xE053
#define CODE_DELETE2		 0x0053
#define CODE_INSERT1		 0xE052
#define CODE_INSERT2		 0x0052
#define CODE_PAGEUP1		 0xE049
#define CODE_PAGEUP2		 0x0049
#define CODE_PAGEDOWN1		 0xE051
#define CODE_PAGEDOWN2	     0x0051
#define CODE_HOME1 			 0xE047	
#define CODE_HOME2			 0x0047
#define CODE_END1 			 0xE04F
#define CODE_END2 			 0x004F		
#define CODE_ENTER			 0xFF0D		
#define CODE_BACKSPACE	 	 0xFF08		
#define CODE_ESCAPE			 0xFF1B


typedef int Keycode;
int cursor;
HistoryBuffer *hb;

extern char user_input[MAX_BUFFER_SIZE];
extern char latest_input[MAX_BUFFER_SIZE];
extern int arrow_left_right_home_status;
extern int end_of_program;

/*
\a (alert) Produces an audible or visible alert. The active
		   position shall not be changed.

\b (backspace) Moves the active position to the previous
			   position on the current line. If the active position is
			   at the initial position of a line, the behavior is
			   unspecified.

\f (form feed) Moves the active position to the initial
			   position at the start of the next logical page .

\n (new line) Moves the active position to the initial
			  position of the next line.

\r (carriage return) Moves the active position to the
					 initial position of the current line.

\t (horizontal tab) Moves the active position to the next
					horizontal tabulation position on the current line. If
					the active position is at or past the last defined
					horizontal tabulation position, the behavior is
					unspecified.

\v (vertical tab)   Moves the active position to the initial
					position of the next vertical tabulation position. If
					the active position is at or past the last defined
					vertical tabulation position, the behavior is
					unspecified.
*/



Keycode get_key_press();  				   // get key press 
Keycode is_special_key(int key_code);	   // check whether input is special key or not
Keycode user_input_interface();
void copystringtochararray(char array[] , char *string);
void mockspecialkeys(int key_code);
void check_special_keys(int key_code);
void handle_BACKSPACE();
void handle_ARROWUP();
void handle_ARROWDOWN();
void handle_ARROWLEFT();
void handle_ARROWRIGHT();
void handle_HOME();
void handle_DEL();
void handle_PAGEUP();
void handle_PAGEDOWN();
void handle_INSERT();
void handle_END();
void handle_ENTER();
int handle_ESCAPE();
void initialize_historybuffer(int length_of_buffer);
void main_command_prompt();
void movecursortoend(char array[]);
void movecharactersahead(int x, int y);
void movecharactersbackward(int endofinput);
int get_end_of_input(char array[]);
void consoleClearLine();
void printBuffer(char buffer[]);  
void printBufferTill(char buffer[], int length);

#endif // command_prompt_H
