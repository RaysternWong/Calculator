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


int previous_status;
int next_status;


int readjustIndex(HistoryBuffer *hb , int index); 
HistoryBuffer *historyBufferNew(int length);
void historyBufferDel(HistoryBuffer *hb);
void historyBufferAdd(HistoryBuffer *hb, char stringtoadd[]);
char *historyBufferReadPrevious(HistoryBuffer *hb);
char *historyBufferReadNext(HistoryBuffer *hb);


#endif // history_buffer_H
