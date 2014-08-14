#include "command_prompt.h"
#include "history_buffer.h"
#include <stdio.h>
#include <malloc.h>
#include "get_ch.h"
#include "putch.h"


char user_input[MAX_BUFFER_SIZE];
char latest_input[MAX_BUFFER_SIZE];
int arrow_left_right_home_status;
int end_of_program;		//indicator for end of the program


/*  To check for the input is special key or not
 *	Input  :
 *			 key_code is the ascii code of the input
 *  Return :
 *			 modified key_code of the input will be return
 * 			 modified key_code will be in 2 bytes format
 */
Keycode is_special_key(int key_code)
{
	int upper_byte , lower_byte;
	
	if ( key_code == ESCAPECODE1 || key_code == ESCAPECODE2)
		{
			upper_byte = (key_code<<8);
			lower_byte = get_character();
			key_code = (upper_byte|lower_byte);
			if ( key_code != CODE_ARROWUP && key_code != CODE_ARROWDOWN && key_code != CODE_ARROWLEFT && key_code != CODE_ARROWRIGHT && 
				 key_code != CODE_DELETE1 && key_code != CODE_DELETE2 && key_code != CODE_INSERT1 && key_code != CODE_INSERT2 && 
				 key_code != CODE_PAGEUP1 && key_code != CODE_PAGEUP2 && key_code != CODE_PAGEDOWN1 && key_code != CODE_PAGEDOWN2 &&
				 key_code != CODE_HOME1   && key_code != CODE_HOME2   && key_code != CODE_END1 		&& key_code != CODE_END2)
				return 0;
			else	
				return key_code;
		}
	else if( key_code == KEY_ENTER || key_code == KEY_BACKSPACE || key_code == KEY_ESCAPE)
		{
			upper_byte = (NORMALCODE<<8);
			lower_byte = key_code;
			key_code = (upper_byte|lower_byte);
			return key_code;
		}
	else
		return 0;
}




/*  To get a single key input
 *  Return :
 *			 ascii code of the input will be return
 * 			
 */
Keycode get_key_press()
{
	int	  key_code;  
		
	key_code = get_character();
	return key_code;
}




/*  Get a string input store it inside a buffer and display it on screen, stop when special key is entered 
 *  Return :
 *			 key code of the special key will be return
 * 			
 */
Keycode user_input_interface()
{
	int status,key_code;
	
	while(1)
	{
		key_code = get_key_press();
		status = is_special_key(key_code);
		if (status != 0)		// status !=0 means special character input	
		{
			if(status == CODE_ENTER);
			{
				if ( status == CODE_ARROWDOWN || status == CODE_ARROWUP);
				else
					copystringtochararray(latest_input, "");
			}
			return status;
		}
		if(user_input[cursor] == '\0')
			user_input[cursor+1]='\0';
			
		user_input[cursor] = key_code;
		put_character(user_input[cursor]);
				
		if(arrow_left_right_home_status != 1)	//if arrow left, arrow right and HOME are not press previously
		{
			cursor++;
			user_input[cursor] = '\0';
		}
		else
		{
			cursor++;
			arrow_left_right_home_status=0;
		}
			
		copystringtochararray(latest_input,user_input);
	}
}




/* The real main command prompt which
 * will be use and seen by user
 */
void main_command_prompt()
{
	int keycode =  user_input_interface();
	check_special_keys(keycode);

}




void check_special_keys(int key_code)
{
	switch ( key_code)
	{
		case (CODE_ARROWUP):
				handle_ARROWUP();
				break;
		
		case (CODE_ARROWDOWN):
				handle_ARROWDOWN();
				break;
		
		case (CODE_ARROWLEFT):
				handle_ARROWLEFT();
				break;
		
		case (CODE_ARROWRIGHT):
				handle_ARROWRIGHT();
				break;
		
		case (CODE_HOME1):
				handle_HOME();
				break;
		
		case (CODE_HOME2):
				handle_HOME();
				break;
				
		case (CODE_DELETE1):
				handle_DEL();
				break;
				
		case (CODE_DELETE2):
				handle_DEL();
				break;
		
		case (CODE_PAGEUP1):
				handle_PAGEUP();
				break;
		
		case (CODE_PAGEUP2):
				handle_PAGEUP();
				break;
		
		case (CODE_PAGEDOWN1):
				handle_PAGEDOWN();
				break;
		
		case (CODE_PAGEDOWN2):
				handle_PAGEDOWN();
				break;
		
		case (CODE_INSERT1):
				handle_INSERT();
				break;
		
		case (CODE_INSERT2):
				handle_INSERT();
				break;
				
		case (CODE_END1):
				handle_END();
				break;
		
		case (CODE_END2):
				handle_END();
				break;
				
		case (CODE_ENTER):
				handle_ENTER();
				break;
		
		case (CODE_ESCAPE):
				handle_ESCAPE();
				break;
		case (CODE_BACKSPACE):
				handle_BACKSPACE();
				break;
	}
}




//adjust the cursor to the end of the user input
void movecursortoend(char array[])
{
	int i=0;
	
	while ( array[i] != '\0')
	{
		i++;
	}
	
	cursor = i;
}



void consoleClearLine()
{
	int i;
	
	printf("\r");
	for(i=0; i<79;i++)
	{
		printf(" ");
	}
	printf("\r");
}




void printBuffer(char buffer[])
{
	printf("%s", buffer);
}




void printBufferTill(char buffer[], int length)
{
	int i;
	
	printf("\r");
	
	for(i=0; i<length;i++)
	{
		printf("%c", buffer[i]);
	}
}




void movecharactersahead(int x, int y)
{
	while(1)
	{
		user_input[cursor+x] = user_input[cursor+y];
		x++;
		y++;
		if(user_input[cursor+y] == '\0')
		{
			user_input[cursor+x] = '\0';
			break;
		}
	}
}




void movecharactersbackward(int endofinput)
{
	int y=0,x=1;
	
	while(1)
	{
		user_input[endofinput+x] = user_input[endofinput-y];
		if(user_input[endofinput-y] == user_input[cursor])
		{
			user_input[cursor] = get_key_press();
			if(user_input[cursor] != '\0')
				cursor++;
			break;
		}
		x--;
		y++;
	}
}



//get the index of the end of the input
int get_end_of_input(char array[])
{
	int j=0,length=0;
	
	while ( array[j] != '\0')
	{
		length++;
		j++;
	}
	return length;
}





/*  To perform backspace
 * 			
 */
void handle_BACKSPACE()
{
	int j=0 , endofinput;
	
	if(user_input[cursor] == '\0')
	{
		endofinput = get_end_of_input(user_input);
		user_input[endofinput-1] = '\0';
		cursor--;
	
		if(cursor < 0)
			cursor=0;
	}
	else
	{
		if(cursor != 0)
		{
			movecharactersahead(-1, 0);
			cursor--;
			if(cursor < 0)
				cursor=0;
		}
	}
	
	copystringtochararray(latest_input , user_input);
	consoleClearLine();
	printBuffer(user_input);
	printBufferTill(user_input,cursor);
}




// To initialize for the historybuffer
void initialize_historybuffer(int length_of_buffer)
{
	hb = historyBufferNew(length_of_buffer);
}




//copy the content of a given string to char array
void copystringtochararray(char array[] , char *string)
{
	int i;
	
	for( i=0 ; string[i] != '\0' ; i++)
	{
		array[i] = string[i];
	}
	array[i] = '\0';
}




/* To perform enter
 *
 */
void handle_ENTER()
{
	historyBufferAdd(hb, user_input);
	consoleClearLine();
	copystringtochararray(user_input,"");
	printBuffer(user_input);
	previous_status = 0;
	cursor = 0;		// has to reinitialize length of input to 0 to get new input correctly
}




/* To perform arrow up
 *
 */
void handle_ARROWUP()
{

	char *temp = historyBufferReadPrevious(hb);
	copystringtochararray(user_input, temp);
	movecursortoend(user_input);
	consoleClearLine();
	printBuffer(user_input);
}




/* To perform arrow down
 *
 */
void handle_ARROWDOWN()
{
	char *temp = historyBufferReadNext(hb);
	copystringtochararray(user_input, temp);
	movecursortoend(user_input);
	consoleClearLine();
	printBuffer(user_input);
}




void handle_ARROWRIGHT()
{
	arrow_left_right_home_status=1;
	
	if( user_input[cursor] != '\0')
		cursor++;
		
	printBufferTill(user_input,cursor);
}



void handle_ARROWLEFT()
{
	arrow_left_right_home_status=1;
	
	if(cursor != 0)
		cursor--;
		
	printBufferTill(user_input,cursor);
}





void handle_HOME()
{
	cursor = 0;
	arrow_left_right_home_status = 1;
	printBufferTill(user_input,cursor);
}




void handle_DEL()
{
	if(user_input[cursor+1] == '\0')
		user_input[cursor] = '\0';
	else
		movecharactersahead(0, 1);
		
	copystringtochararray(latest_input , user_input);
	consoleClearLine();
	printBuffer(user_input);
	printBufferTill(user_input,cursor);
}




void handle_PAGEDOWN()
{
	if( hb->buffer[hb->startIndex] == NULL);
	else
	{
		int index = hb->latestIndex;
		index = readjustIndex(hb , index-1);
		copystringtochararray(user_input, hb->buffer[index]);
	}
	movecursortoend(user_input);
	consoleClearLine();
	printBuffer(user_input);
}





void handle_PAGEUP()
{
	if( hb->buffer[hb->startIndex] == NULL);
	else
	{
		int index = hb->startIndex;
		copystringtochararray(user_input, hb->buffer[index]);
	}
	previous_status = 1;
	movecursortoend(user_input);
	consoleClearLine();
	printBuffer(user_input);
}




void handle_INSERT()
{
	int endofinput;
	
	endofinput = get_end_of_input(user_input);
	movecharactersbackward(endofinput);
	copystringtochararray(latest_input , user_input);
	consoleClearLine();
	printBuffer(user_input);
	printBufferTill(user_input,cursor);
}



void handle_END()
{
	movecursortoend(user_input);
	printBufferTill(user_input,cursor);
}



int handle_ESCAPE()
{
	end_of_program = 1;
	return end_of_program;
}