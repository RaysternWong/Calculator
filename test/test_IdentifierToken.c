#include "unity.h"
#include "IdentifierToken.h"

void setUp(void)
{
}

void tearDown(void)
{
}

/*#1
 * Test create new identifier token given identifier ABC
 * should store ABC inside identifierNew
 */
void test_identifierNew_given_ABC_should_store_inside_identifierNew(void)
{
	Identifier *identifier = identifierNew("ABC");
	
	TEST_ASSERT_NOT_NULL(identifier);
	TEST_ASSERT_EQUAL(IDENTIFIER_TOKEN , identifier->type);
	TEST_ASSERT_EQUAL_STRING("ABC" , identifier->name);
	
	identifierDel(identifier);
}