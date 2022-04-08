/*

Name	 	:	MK MOOSA KASIM
Date		:	08-04-2022
Description	:	To view and edit the mp3 file such as album, singer, year, comment
etc. Here we are using ID3v2.3 editor
Input		:	./a.out -v sample.mp3
Output		:	

---------------------------SELECTED VIEW DETAILS--------------------------

--------------------------------------------------------------------------

		MP3 TAG READER AND EDITOR FOR ID3V2

--------------------------------------------------------------------------
TITLE		:	Sunny_Sunny
ARTIST		:	Yo_Yo_Honey_Singh
ALBUM		:	Yariya
YEAR		:	2015
MUSIC		:	Bollywood Music - [SongsPk.CC]
COMMENT		:	engDownloaded From SongsPk.CC
---------------------------------------------------------------------------

----------------------DETAILS DISPLAYED SUCCESSFULLY-----------------------


*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"header.h"
#include"display_functions.h"

int main(int argc, char *argv[])
{
		int i=0;
		/* CLA input validation */
		if(argc == 1)
				display_error();

		if(!(strcmp(argv[1],"--help")))		// strcmp returns 0 - equal
				display_help();

		if(!strcmp(argv[1],"-v"))
		{
				FILE *fptr;
				fptr = fopen(argv[2],"r");
				if(fptr == NULL )
				{	
						printf("ERROR : File reading is not present\n");
						return 0;
				}
				else
				{	
						/* Check 1st 3bytes are ID3 */
						char *id3 ="ID3";
						for(i=0; i<3; i++)
								if(id3[i] != fgetc(fptr))
								{
										printf("Header ID is not present\n");
										return 0;
								}

						/* Check next 2 bytes are 03 00 */	
						int arr[]={0x03,0x00};
						for(i=0; i<2; i++)
								if(arr[i] != fgetc(fptr))
								{
										printf("Version is not present\n");
										return 0;
								}

						/* Check passed file is .mp3 */
						if((strcmp(strrchr(argv[2],'.') ,".mp3")))
						{
								printf("Passed file has no .mp3 extension\n");
								return 0;
						}

						/* Print file tags */
						printf("\n---------------------------SELECTED VIEW DETAILS--------------------------\n");
						printf("\n--------------------------------------------------------------------------\n");
						printf("\n\t\tMP3 TAG READER AND EDITOR FOR ID3V2\n");
						printf("\n--------------------------------------------------------------------------\n");
						printf("TITLE\t\t:\t");
						view(argv[2]);
						printf("ARTIST\t\t:\t");
						view(argv[2]);
						printf("ALBUM\t\t:\t");
						view(argv[2]);
						printf("YEAR\t\t:\t");
						view(argv[2]);
						printf("MUSIC\t\t:\t");
						view(argv[2]);
						printf("COMMENT\t\t:\t");
						view(argv[2]);
						printf("---------------------------------------------------------------------------\n");
						printf("\n----------------------DETAILS DISPLAYED SUCCESSFULLY-----------------------\n\n");
				}
		}


		/* Edit file */

		if(!(strcmp(argv[1],"-e")))		// strcmp returns 0 - equal
		{	
				FILE *file_title;

				/* store CLA data */
				store.file_name=argv[4];
				store.change_text=argv[3];
				file_title = fopen(argv[4],"r+");
				if(file_title == NULL)
				{
						printf(" Given file %s is not possible to edit\n",argv[4]);
						return 0;
				}

				/* move file pointer given tag location */
				switch(argv[2][1])
				{	
						case 't': fseek(file_title,t,SEEK_SET); break;
						case 'A': fseek(file_title,A,SEEK_SET); break;
						case 'a': fseek(file_title,a,SEEK_SET); break;
						case 'y': fseek(file_title,y,SEEK_SET); break;
						case 'm': fseek(file_title,m,SEEK_SET); break;
						case 'c': fseek(file_title,c,SEEK_SET); break;
				}

				/* read size of a tag */

				if((argv[2][1]) != ('t'))
						fseek(file_title,4,SEEK_CUR);		

				for(i=(4-1); i>=0; i--)
				{
						f.f2[i] = fgetc(file_title);
				}

				/* write a new tag */

				if((argv[2][1]) != ('y'))
						for(i=0;i<f.f1;i++)
						{
								if(i >= 4 + strlen(store.change_text) )
								{
										fputc('\0',file_title);	
										continue;
								}
								fwrite(&argv[2][i],1,1,file_title);

						}

				/* for editing year tag data only */

				else if((argv[2][1]) == ('y'))
				{
						char year[4];
						strcpy(year,store.change_text);
						fseek(file_title,139,SEEK_SET);		
						for(i=0;i<f.f1;i++)
						{
							fwrite(&year[i],1,1,file_title);
						}
				}			

				/* erasing last two characters of music and comment tag */

				if(argv[2][1]=='m' || argv[2][1] == 'c')
				{
					fseek(file_title,183,SEEK_SET);		
					fputc('\0',file_title);	
					fseek(file_title,184,SEEK_SET);		
					fputc('\0',file_title);	
					fseek(file_title,224,SEEK_SET);		
					fputc('\0',file_title);	
					fseek(file_title,225,SEEK_SET);		
					fputc('\0',file_title);	
				}
		}
}

void view(char file_name[])
{
		int i=0;
		static int num=14;
		FILE *fptr;
		fptr = fopen(file_name,"r");
		if(fptr == NULL )
		{	
				printf("ERROR : File reading is not present\n");
				return ;
		}

		/* Read frame header */	
		rewind(fptr);
		fseek(fptr,10,SEEK_SET);
		char first[5]=" ";
		for(i=0; i<4; i++)
		{
				first[i]=fgetc(fptr);
				//fread(&[i,1,1,fptr]);
		}

		fseek(fptr,num,SEEK_SET);

		/*storing title size */	
		if(num!=14)
				fseek(fptr,4,SEEK_CUR);		// skip flag
		for(i=(4-1); i>=0; i--)
		{
				f.f2[i]=fgetc(fptr);
		}	
		int len = f.f1;				//0x2F

		/* To read a title */
		fseek(fptr,2,SEEK_CUR);		// skip flag
		char title[len+1];			

		fread(title,len,1,fptr);
		title[len]='\0';
		for(i=0;i<(len);i++)
				fwrite(&title[i],1,1,stdout);
		printf("\n");

		num = (int) ftell(fptr);
}
