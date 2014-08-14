#include "main.h"




int main()
{
	int length_of_historybuffer=5;
	
	initialize_historybuffer(length_of_historybuffer);
	 
	while(end_of_program != 1)
	{
		main_command_prompt();
	}
}

