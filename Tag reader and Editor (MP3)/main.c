/****************************************** PROJECT 1 **************************************
Name: Ganesh P
Project Name: MP3 Tag Reader and Editor
Date: 28-08-25

Description: 
This project implements a command-line utility in C for reading and editing metadata (ID3v2.3 tags) in MP3 audio files.
MP3 files often contain metadata such as Title, Artist, Album, Year, Genre, and Comments stored in frames inside the ID3 header.

The goal of this project is to:
1. View existing metadata tags from an MP3 file.
2. Edit specific metadata fields (title, artist, album, year, genre, comment) without corrupting the audio content.

*********************************************************************************************/

#include<stdio.h>
#include<string.h>
#include "fun.h"
int main (int argc, char *argv[])
{
    // Minimun 3 command line arguments
    if (argc < 2){
        printf ("Error: Incorrect format of command line arguments\n");
        printf("Use \"./a.out --help\" for Help Menu\n");
        return 0;
    }

    if (strncmp(argv[1],"-v",2) == 0) {
        // Validation
        if (argc < 2) {
            printf ("Error: Incorrect format of command line arguments\n");
            printf("Use \"./a.out --help\" for Help Menu\n");
            return 0;
        }

        // Function call
        viewTagInfo (argv);

    } else if (strncmp(argv[1],"-e",2) == 0) {
        // Validation
        if (argc < 5) {
            printf ("Error: Incorrect format of command line arguments\n");
            printf("Use \"./a.out --help\" for Help Menu\n");
            return 0;
        }

        // Function call
        editTagInfo (argv);

    } else if (strncmp(argv[1],"--help",6)==0) {
        printf("INFO: Help Menu for Tag Reader and Editor:\n");
        printf("INFO: For Viewing the Tags -> ./a.out -v <filename.mp3>\n");
        printf("INFO: For Editing the Tags -> ./a.out -e <modifier> \"New_Value\" <filename.mp3>\n");
        printf("INFO: Modifier Functions:\n");
        printf("-t\tModify Title Tag\n-a\tModify Album\n-A\tModify Artist Tag\n-y\tModify Year Tag\n-g\tModify Genre\n-c\tModify Comment Tag\n");
    }
    else {
        printf("Error: Unknown option %s\n", argv[1]);
        printf("Use \"./a.out --help\" for Help Menu\n");
    }
    return 0;
}