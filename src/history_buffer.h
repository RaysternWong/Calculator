#ifndef history_buffer_H
#define history_buffer_H
#define LENGTH_OF_BUFFER 3

typedef struct
{
	char **buffer;
	int length;
	int currentIndex;
	int latestIndex;
	int startIndex;

}HistoryBuffer;


int previous_status;	// to indicate has already reached the oldest value in the history buffer
int next_status;		// to indicate has already pointed to the latest value in the history buffer


int readjustIndex(HistoryBuffer *hb , int index); 
HistoryBuffer *historyBufferNew(int length);
void historyBufferDel(HistoryBuffer *hb);
void historyBufferAdd(HistoryBuffer *hb, char stringtoadd[]);
char *historyBufferReadPrevious(HistoryBuffer *hb);
char *historyBufferReadNext(HistoryBuffer *hb);


#endif // history_buffer_H
