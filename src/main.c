#include "main.h"
#include <stdio.h>



int main()
{
	int length_of_historybuffer=5;
	
	initialize_historybuffer(length_of_historybuffer);
	printf(">>");
	
	while(end_of_program != 1)
	{
		main_command_prompt();
	}
	
	historyBufferDel(hb);
}

