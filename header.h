#ifndef TAGS_H
#define TAGS_H
enum tags
{
	t=14, A=67, a=110, y=129, m=144, c=185		
};

struct store
{
    char *file_name;
    char *change_text;
}store;

union f
{
    unsigned int f1; 
    unsigned char f2[4];
}f;

#endif

void display_error();
void display_help();
void view();

