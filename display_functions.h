#ifndef DISPLAY_FUNCTIONS_H
#define DISPLAY_FUNCTIONS_H 

/* Display how to pass CLA */
void display_error()
{
        printf("\n-----------------------------------------------------------\n");
        printf("ERROR : ./a.out : INVALID ARGUMENTS\n");
        printf("Usage : \n");
        printf("To view please pass like : ./a.out -v mp3filename.mp3\n");  
        printf("To edit please pass like : ./a.out -e -t/-a/-A/-m/-y/-c  changing_text  mp3filename.mp3\n");    
        printf("To get help pass like : ./a.out --help\n"); 
        printf("-----------------------------------------------------------\n\n");
        exit(0);
}

/* Display --help */
void display_help()
{
        printf("\n------------------------HELP MENU----------------------------------\n\n");
        printf("1. -v -> to view mp3 file contents\n");
        printf("2. -e -> to edit mp3 file contents\n");
        printf("\t\t 2.1 -t -> to edit song title\n");
        printf("\t\t 2.2 -A -> to edit artist name\n");
        printf("\t\t 2.3 -a -> to edit album name\n");
        printf("\t\t 2.4 -y -> to edit year\n");
        printf("\t\t 2.5 -m -> to edit content\n");
        printf("\t\t 2.6 -c -> to edit comment\n");
        printf("\n-----------------------------------------------------------\n\n");
        exit(0);
}
#endif
