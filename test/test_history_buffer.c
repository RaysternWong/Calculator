#include "unity.h"
#include "history_buffer.h"

char latest_input[1024];

void setUp(void)
{
	previous_status = 0;
	next_status = 0;
}

void tearDown(void)
{
}

void test_HistoryBufferNew_given_3_should_allocate_HistoryBuffer_object_with_a_buffer_of_3(void)
{
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);
	TEST_ASSERT_EQUAL( 0 , hb->currentIndex);
	TEST_ASSERT_EQUAL( 0 , hb->latestIndex);
	TEST_ASSERT_EQUAL( 0 , hb->startIndex);
	TEST_ASSERT_EQUAL( 3 , hb->length);
	historyBufferDel(hb);
}


void test_readjustIndex_when_index_is_equal_or_greater_than_length_should_return_0()
{
	int index = 3;
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);
	
	index = readjustIndex(hb , index);
	TEST_ASSERT_EQUAL( 0 ,index);
}


void test_readjustIndex_when_index_is_neg_1_should_return_length_minus_1()
{
	int index = -1;
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);

	index = readjustIndex(hb , index);
	TEST_ASSERT_EQUAL( hb->length-1 ,index);
}


void test_historyBufferAdd_given_123_latestIndex_should_get_1_startIndex_is_0()
{
	
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);
	
	historyBufferAdd(hb, "123");

	TEST_ASSERT_EQUAL(0 , hb->startIndex);
	TEST_ASSERT_EQUAL(1 , hb->latestIndex);
	TEST_ASSERT_EQUAL_STRING( "123" , *(hb->buffer)	);
	TEST_ASSERT_EQUAL_STRING( "123" , hb->buffer[hb->startIndex]	);
	TEST_ASSERT_EQUAL_STRING( NULL , hb->buffer[hb->latestIndex]	);
    historyBufferDel(hb);
}


void test_historyBufferAdd_given_123_and_abc_should_get_latestIndex_is_2_startIndex_is_0()
{
	
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);
	
	historyBufferAdd(hb, "123");
	historyBufferAdd(hb, "abc");

	TEST_ASSERT_EQUAL_STRING("123", *(hb->buffer)	);
	TEST_ASSERT_EQUAL_STRING("abc", *(hb->buffer+1)	);
	TEST_ASSERT_EQUAL(0 , hb->startIndex);
	TEST_ASSERT_EQUAL(2 , hb->latestIndex);
	TEST_ASSERT_EQUAL_STRING( "123" , hb->buffer[hb->startIndex]	);
	TEST_ASSERT_EQUAL_STRING( NULL , hb->buffer[hb->latestIndex]	);
    historyBufferDel(hb);
}


void test_historyBufferAdd_given_123_abc_456_should_get_latestIndex_is_0_startIndex_is_1()
{
	
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);
	
	historyBufferAdd(hb, "123");
	historyBufferAdd(hb, "abc");
	historyBufferAdd(hb, "456");

	TEST_ASSERT_EQUAL_STRING("123", *hb->buffer);
	TEST_ASSERT_EQUAL_STRING("abc", *(hb->buffer+1) );
	TEST_ASSERT_EQUAL_STRING("456", *(hb->buffer+2) );
	TEST_ASSERT_EQUAL(0 , hb->startIndex);
	TEST_ASSERT_EQUAL(0 , hb->latestIndex);
	TEST_ASSERT_EQUAL_STRING( "123" , hb->buffer[hb->startIndex]	);
	TEST_ASSERT_EQUAL_STRING( "123" , hb->buffer[hb->latestIndex]	);
    historyBufferDel(hb);
}


void test_historyBufferAdd_given_123_abc_456_789_should_get_latestIndex_is_1_startIndex_is_1()
{
	
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);
	
	historyBufferAdd(hb, "123");
	historyBufferAdd(hb, "abc");
	historyBufferAdd(hb, "456");
	historyBufferAdd(hb, "789");

	TEST_ASSERT_EQUAL_STRING("789", *(hb->buffer)	);
	TEST_ASSERT_EQUAL_STRING("abc", *(hb->buffer+1)	);
	TEST_ASSERT_EQUAL_STRING("456", *(hb->buffer+2)	);
	TEST_ASSERT_EQUAL(1, hb->startIndex);
	TEST_ASSERT_EQUAL(1 , hb->latestIndex);
	TEST_ASSERT_EQUAL_STRING( "abc" , hb->buffer[hb->latestIndex]	);
	TEST_ASSERT_EQUAL_STRING( "abc" , hb->buffer[hb->startIndex]	);
    historyBufferDel(hb);
}


//buffer no overwrite
void test_historyBufferReadPrevious_given_1plus6_should_return_1plus6_when_read_once()
{
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);
	
	historyBufferAdd(hb, "1+6");
	char *string_return = historyBufferReadPrevious(hb);
	TEST_ASSERT_EQUAL(0, hb->currentIndex);
	TEST_ASSERT_EQUAL_STRING("1+6", string_return);
	historyBufferDel(hb);
	
}


//buffer no overwrite
void test_historyBufferReadPrevious_given_1plus6_should_return_1plus6_when_read_twice()
{
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);
	char *string_return;
	
	historyBufferAdd(hb, "1+6");
	string_return = historyBufferReadPrevious(hb);
	TEST_ASSERT_EQUAL(0, hb->currentIndex);
	TEST_ASSERT_EQUAL_STRING("1+6", string_return);
	string_return = historyBufferReadPrevious(hb);
	TEST_ASSERT_EQUAL(0, hb->currentIndex);
	TEST_ASSERT_EQUAL_STRING("1+6", string_return);
	historyBufferDel(hb);
}


//buffer no overwrite
void test_historyBufferReadPrevious_given_empty_and_latest_input_is_1plus6_should_return_1plus6_when_read()
{
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);
	char *string_return;
	latest_input[0] = '1';
	latest_input[1] = '+';
	latest_input[2] = '6';
	
	string_return = historyBufferReadPrevious(hb);
	TEST_ASSERT_EQUAL_STRING("1+6", string_return);

	historyBufferDel(hb);
}


//buffer no overwrite
void test_historyBufferReadPrevious_1plus6_2plus8_given_should_return_2plus8_1plus6_when_read_twice()
{
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);
	char *string_return;
	
	// Add
	historyBufferAdd(hb, "1+6");
	historyBufferAdd(hb, "2+8");
	
	string_return = historyBufferReadPrevious(hb);	
	TEST_ASSERT_EQUAL(1, hb->currentIndex);
	TEST_ASSERT_EQUAL_STRING("2+8", string_return);
	string_return = historyBufferReadPrevious(hb);
	TEST_ASSERT_EQUAL(0, hb->currentIndex);
	TEST_ASSERT_EQUAL_STRING("1+6", string_return);
	historyBufferDel(hb);
}



//buffer overwrite
void test_historyBufferReadPrevious_1plus6_2plus8_3plus4_5minus4_should_return_5minus4_3plus4_2plus8_when_read_thrice_and_2plus8_when_read_fourth_time()
{
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);
	char *string_return;
		
	historyBufferAdd(hb, "1+6");
	historyBufferAdd(hb, "2+8");
	historyBufferAdd(hb, "3+4");
	historyBufferAdd(hb, "5-4");
	
	string_return = historyBufferReadPrevious(hb);
	TEST_ASSERT_EQUAL_STRING("5-4", string_return);
	TEST_ASSERT_EQUAL(0, hb->currentIndex);
	string_return = historyBufferReadPrevious(hb);
	TEST_ASSERT_EQUAL(2, hb->currentIndex);
	TEST_ASSERT_EQUAL_STRING("3+4" , string_return);
	string_return = historyBufferReadPrevious(hb);
	TEST_ASSERT_EQUAL(1, hb->currentIndex);
	TEST_ASSERT_EQUAL_STRING("2+8", string_return);
	string_return = historyBufferReadPrevious(hb);
	TEST_ASSERT_EQUAL(1, hb->currentIndex);
	TEST_ASSERT_EQUAL_STRING("2+8", string_return);
	
	historyBufferDel(hb);
}



void test_historyBufferReadNext_given_1plus6_2plus3_4plus5_should_return_2plus3_4plus5_when_read_next_twice()
{
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);

	char *string_return;

	historyBufferAdd(hb, "1+6");
	historyBufferAdd(hb, "2+3");
	historyBufferAdd(hb, "4+5");
	
	string_return = historyBufferReadPrevious(hb);
	string_return = historyBufferReadPrevious(hb);
	string_return = historyBufferReadPrevious(hb);
	string_return = historyBufferReadNext(hb);
	TEST_ASSERT_EQUAL(1, hb->currentIndex);	
	TEST_ASSERT_EQUAL_STRING("2+3" , string_return);
	string_return = historyBufferReadNext(hb);
	TEST_ASSERT_EQUAL(2, hb->currentIndex);	
	TEST_ASSERT_EQUAL_STRING("4+5" , string_return);
	historyBufferDel(hb);
}



void test_historyBufferReadNext_given_1plus6_2plus3_4plus5_should_return_4plus5_when_currentIndex_is_at_4plus5()
{
	HistoryBuffer *hb = historyBufferNew(LENGTH_OF_BUFFER);

	char *string_return;

	historyBufferAdd(hb, "1+6");
	historyBufferAdd(hb, "2+3");
	historyBufferAdd(hb, "4+5");
	latest_input[0] = '0';
	latest_input[1] = '+';
	latest_input[2] = '6';
	
	string_return = historyBufferReadPrevious(hb);
	string_return = historyBufferReadPrevious(hb);
	string_return = historyBufferReadPrevious(hb);
	string_return = historyBufferReadNext(hb);		
	
	TEST_ASSERT_EQUAL_STRING("2+3" , string_return);
	TEST_ASSERT_EQUAL(1, hb->currentIndex);
	string_return = historyBufferReadNext(hb);
	TEST_ASSERT_EQUAL(2, hb->currentIndex);		
	TEST_ASSERT_EQUAL_STRING("4+5" , string_return);
	string_return = historyBufferReadNext(hb);	
	TEST_ASSERT_EQUAL_STRING("0+6" , string_return);
	historyBufferDel(hb);
}





/*  Given input string of 1+2	2+4	  3+6	4+8	  5+10  11-4   12*3 	and the size of buffer is 5 
 *	latest should be pointed to 12*3	after adding all the strings into historybuffer
 *	Read previous 3 times should get 5+10
 *	Read next 2 times should get 12*3
 *	Read previous one time should get 11-4
 *	Read next one time should get 12*3
 *	Read previous 4 times should get 3+6
 *	Read next 2 times should get 5+10
 */
void test_historyBufferReadNext_and_historyBufferReadPrevious()
{	
	HistoryBuffer *hb = historyBufferNew(5);

	char string1[] = "1+2";
	char string2[] = "2+4";
	char string3[] = "3+6";
	char string4[] = "4+8";
	char string5[] = "5+10";
	char string6[] = "11-4";
	char string7[] = "12*3";
	char *string_return;
	
	//add 7 times expect hb->latest to be 3+6
	historyBufferAdd(hb, string1);
	historyBufferAdd(hb, string2);
	historyBufferAdd(hb, string3);
	historyBufferAdd(hb, string4);
	historyBufferAdd(hb, string5);
	historyBufferAdd(hb, string6);
	historyBufferAdd(hb, string7);
	TEST_ASSERT_EQUAL(hb->startIndex , hb->latestIndex);
		
		
	//read previous 3 times expect 5+10
	string_return = historyBufferReadPrevious(hb);
	string_return = historyBufferReadPrevious(hb);
	string_return = historyBufferReadPrevious(hb);
	TEST_ASSERT_EQUAL_STRING(string5 , string_return);
		
		
	//read next 2 times expect 12*3
	string_return = historyBufferReadNext(hb);
	string_return = historyBufferReadNext(hb);
	TEST_ASSERT_EQUAL_STRING(string7 , string_return);
	
	//read previous one time expect 11-4
	string_return = historyBufferReadPrevious(hb);
	TEST_ASSERT_EQUAL_STRING(string6 , string_return);
	
	//read next one time expect 12*3
	string_return = historyBufferReadNext(hb);
	TEST_ASSERT_EQUAL_STRING(string7 , string_return);
		
	//read previous 4 times expect 3+6
	string_return = historyBufferReadPrevious(hb);
	string_return = historyBufferReadPrevious(hb);
	string_return = historyBufferReadPrevious(hb);
	string_return = historyBufferReadPrevious(hb);
	TEST_ASSERT_EQUAL_STRING(string3 , string_return);
		
	//read next 2 times expect	5+10
	string_return = historyBufferReadNext(hb);
	string_return = historyBufferReadNext(hb);
	TEST_ASSERT_EQUAL_STRING(string5 , string_return);
			
	historyBufferDel(hb);
}
