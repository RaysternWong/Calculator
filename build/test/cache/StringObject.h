





typedef struct

{

 char *string;

 int startindex;

 int length;

}String;



String *stringNew();

void StringTrim(String *str, char StringChar[]);

String *stringRemoveWordContaining (String *str , char *ContainSet);

String *stringRemoveWordNotContaining (String *str , char *notContainSet);

int StringCharAt(String *str , int relativePos);
