#include "history_buffer.h"
#include "command_prompt.h"
#include <malloc.h>	 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char latest_input[1024];

/*
 * Initialize the historybuffer
 *
 *Input :
 *					length is the length of the buffer
 */
HistoryBuffer *historyBufferNew(int length)
{
	HistoryBuffer *historyBuffer;
	historyBuffer = malloc(sizeof(HistoryBuffer));
	historyBuffer->buffer = calloc(sizeof(char*), length);
	historyBuffer->length = length;
	historyBuffer->currentIndex = 0;
	historyBuffer->latestIndex	= 0;
	historyBuffer->startIndex	= 0;
	return historyBuffer;
}


/*
 *	To free the buffer memory
 */
void historyBufferDel(HistoryBuffer *hb)
{
	free(hb);
}



/*
 * Add a new value into the history buffer
 *
 *Input :
 *					Pointer hb is the pointer which pointed to the HistoryBuffer structure
 *					stringtoadd is the string to be added into the HistoryBuffer
 *
 */
void historyBufferAdd(HistoryBuffer *hb, char stringtoadd[])
{
	if ( hb->buffer[hb->latestIndex] != NULL)
		free(hb->buffer[hb->latestIndex]);
	
	if( hb->latestIndex == hb->startIndex)
	{
		if(hb->startIndex == hb->length-1)
			hb->startIndex = 0;
		else if( hb->buffer[hb->startIndex] == NULL);
		else
			hb->startIndex++;
	}
	
	hb->buffer[hb->latestIndex++] = strdup(stringtoadd);
	hb->latestIndex = readjustIndex(hb , hb->latestIndex);
	hb->currentIndex = hb->latestIndex;
}



/*
 * Re-adjust the index of the history buffer
 *
 *Input :
 *					Pointer hb is the pointer which pointed to the HistoryBuffer structure
 *					index is the variable of index that pass into the function
 *
 */
int readjustIndex(HistoryBuffer *hb , int index)
{
	if (index >= hb->length)
		return 0;
	else if( index < 0 )	
		return hb->length-1;
	else
		return index;
}



/*
 * Return the previous string in history buffer 
 *
 *Input :
 *					Pointer hb is the pointer which pointed to the HistoryBuffer structure
 *	
 *Return :
 *					The latest string that stored in the historyBuffer
 *
 */
char *historyBufferReadPrevious(HistoryBuffer *hb)
{
	int latest = hb->latestIndex;
	latest = readjustIndex(hb , latest-1);
	
	if (previous_status == 1)
		return hb->buffer[hb->startIndex];
	
	hb->currentIndex--;
		
	if( hb->currentIndex < 0	&&	hb->buffer[hb->startIndex] == NULL)
	{
		hb->currentIndex = 0;
		return latest_input;
	}
	
	hb->currentIndex = readjustIndex(hb , hb->currentIndex);
	
	if ( hb->currentIndex != latest)	// if the currentIndex is not pointed to latest, then reset the next status to 0
		next_status = 0;
	else	
		next_status = 1;
	
	if( hb->currentIndex == hb->startIndex)
		previous_status = 1;
	
	return hb->buffer[hb->currentIndex];	
}



/*
 * Return the next string in history buffer 
 *
 *Input :
 *					Pointer hb is the pointer which pointed to the HistoryBuffer structure
 *	
 *Return :
 *					The next string that stored in the historyBuffer
 *
 */
char *historyBufferReadNext(HistoryBuffer *hb)
{
	previous_status = 0;  //clear the status to 0 to indicate its not at the end of buffer anymore
	int latest = hb->latestIndex;
	
	if ( next_status == 1)
	{
		hb->currentIndex = hb->latestIndex;
		return latest_input;
	}
	
	if(hb->buffer[hb->startIndex] == NULL || hb->buffer[hb->currentIndex] == NULL)
		return latest_input;

	hb->currentIndex++;
	
	latest = readjustIndex(hb , latest-1);
	hb->currentIndex = readjustIndex(hb , hb->currentIndex);
	
	if (hb->currentIndex == latest)
		next_status = 1;
	
	return hb->buffer[hb->currentIndex];
}


