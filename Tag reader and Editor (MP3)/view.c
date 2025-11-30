#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Convert 4 bytes (big-endian) into an integer
int bytes_to_int(unsigned char bytes[4]) {
    return (bytes[0] << 24) |
           (bytes[1] << 16) |
           (bytes[2] << 8)  |
           (bytes[3]);
}

void viewTagInfo (char *argv[]) 
{
    // File name validation
    int len = strlen(argv[2]);
    if (strcmp(argv[2] + len-4,".mp3")!=0) {
        printf("Error: Only supports file with extension MP3\n");
        return;
    }

    unsigned char header[10];   // ID3 header is always 10 bytes
    FILE *fptr;
    if ((fptr = fopen(argv[2], "r")) == NULL) {
        printf("File not found\n");
        return;
    }

    // Read the 10-byte ID3 header
    if (fread(header, 1, 10, fptr) != 10) {
        printf("Error: Could not read header\n");
        fclose(fptr);
        return;
    }

    if (strncmp(header, "ID3", 3) != 0) {
        printf("No ID3 tag found\n");
        fclose(fptr);
        return;
    }

    if (header[3] != 3) {
        printf("Only ID3 v2.3 supported\n");
        fclose(fptr);
        return;
    }

    printf("\n-------------------------------------------\n");
    printf("\t MP3 TAG INFORMATION\n");
    printf("---------------------------------------------\n");

    // Now read Properties
    while (1) {
        char frame[5] = {0}; // Initial declaration 

        // Read frame ID (4 bytes)
        if (fread(frame, 1, 4, fptr) != 4) 
            break; // EOF

        if (frame[0] == 0) 
            break;  // padding
        
        // Read size (4 bytes)
        int frameSize;
        unsigned char size_of_bytes[4];  // size of frame content

        if (fread(size_of_bytes, 1, 4, fptr) != 4) 
            break;
        frameSize = bytes_to_int(size_of_bytes);

        // Skip 2 bytes flag (unused) + NULL in frame content
        fseek(fptr,3,SEEK_CUR);

        // Allocate Dynamic memory for content
        char *frameContent = malloc(frameSize);
        if (!frameContent) {
            printf("Memory allocation failed\n");
            fclose(fptr);
            return;
        }

        // Read content bytes
        fread(frameContent, 1, frameSize-1, fptr); // Till frame size -1 (removed NULL)
        frameContent[frameSize] = '\0'; // null terminate

        // Print only the required Tags
        if (strcmp(frame, "TIT2") == 0)
            printf(" Title   : %s\n", frameContent);
        else if (strcmp(frame, "TYER") == 0)
            printf(" Year    : %s\n", frameContent);
        else if (strcmp(frame, "TALB") == 0)
            printf(" Album   : %s\n", frameContent);
        else if (strcmp(frame, "TPE1") == 0)
            printf(" Artist  : %s\n", frameContent);
        else if (strcmp(frame, "TCON") == 0)
            printf(" Genre   : %s\n", frameContent);
        else if (strcmp(frame, "COMM") == 0) {
            printf(" Comment : %s\n", frameContent);
        }

        free(frameContent); // Free malloc memory
    }

    fclose(fptr);
    printf("\n✅ Successful\n");
}