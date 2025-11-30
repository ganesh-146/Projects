#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Convert int to 4 bytes (big-endian)
void int_to_bytes(int val, unsigned char bytes[4]) {
    bytes[0] = (val >> 24) & 0xFF;
    bytes[1] = (val >> 16) & 0xFF;
    bytes[2] = (val >> 8) & 0xFF;
    bytes[3] = val & 0xFF;
}

// Convert 4 bytes (big-endian) to int --> Function already present in view.c
int bytes_to_int(unsigned char bytes[4]);

void editTagInfo(char *argv[]) {
    // File name validation
    int len = strlen(argv[4]);
    if (strcmp(argv[4] + len - 4, ".mp3") != 0) {
        printf("Error: Only supports file with extension MP3\n");
        return;
    }

    // Validating Year value (Accept only Int value)
    if(strcmp(argv[2],"-y")==0){
        for(int i=0;argv[3][i];i++){
            if(!(argv[3][i]>='0' && argv[3][i]<='9')){
                printf("Year should be in Integer\n");
                return;
            }
        }
    }

    FILE *fptr1;
    if ((fptr1 = fopen(argv[4], "rb")) == NULL) {
        printf("File not found\n");
        return;
    }

    FILE *fptr2;
    if ((fptr2 = fopen("output.mp3", "wb")) == NULL) {
        printf("Error: Could not create output\n");
        fclose(fptr1);
        return;
    }

    unsigned char header[10];
    if (fread(header, 1, 10, fptr1) != 10) {
        printf("Error: Could not read header\n");
        fclose(fptr1);
        fclose(fptr2);
        return;
    }

    // Write header to output
    fwrite(header, 1, 10, fptr2);

    // Map command-line flag to frame ID
    char *frameToEdit = NULL;
    if (strcmp(argv[2], "-t") == 0) frameToEdit = "TIT2"; // Title
    else if (strcmp(argv[2], "-a") == 0) frameToEdit = "TPE1"; // Artist
    else if (strcmp(argv[2], "-A") == 0) frameToEdit = "TALB"; // Album
    else if (strcmp(argv[2], "-y") == 0) frameToEdit = "TYER"; // Year
    else if (strcmp(argv[2], "-c") == 0) frameToEdit = "COMM"; // Comments
    else if (strcmp(argv[2], "-g") == 0) frameToEdit = "TCON"; // Genre
    else {
        printf("Error: Unsupported option %s\n", argv[2]);
        fclose(fptr1);
        fclose(fptr2);
        return;
    }

    char *newValue = argv[3];
    int newValueLen = strlen(newValue);

    // Process frames
    while (1) {
        char frame[5] = {0};
        if (fread(frame, 1, 4, fptr1) != 4) 
            break; // end of tags
        if (frame[0] == 0) 
            break; // padding

        unsigned char sizeBytes[4];
        if (fread(sizeBytes, 1, 4, fptr1) != 4) 
            break;
        int frameSize = bytes_to_int(sizeBytes);

        unsigned char flags[2];
        if (fread(flags, 1, 2, fptr1) != 2) 
            break;

        char *frameContent = malloc(frameSize);
        if (!frameContent) {
            printf("Memory allocation failed\n");
            break;
        }
        fread(frameContent, 1, frameSize, fptr1);

        if (strcmp(frame, frameToEdit) == 0) {
            // Write new frame
            fwrite(frame, 1, 4, fptr2);

            unsigned char newSizeBytes[4];
            int frameDataLen = newValueLen + 1; // +1 for encoding byte
            int_to_bytes(frameDataLen, newSizeBytes);
            fwrite(newSizeBytes, 1, 4, fptr2);

            fwrite(flags, 1, 2, fptr2);

            // Write encoding + new string
            unsigned char encoding = 0; // ISO-8859-1
            fwrite(&encoding, 1, 1, fptr2);
            fwrite(newValue, 1, newValueLen, fptr2);

            printf("✅ Updated %s\n", frameToEdit);
        } else {
            // Copy original frame
            fwrite(frame, 1, 4, fptr2);
            fwrite(sizeBytes, 1, 4, fptr2);
            fwrite(flags, 1, 2, fptr2);
            fwrite(frameContent, 1, frameSize, fptr2);
        }

        free(frameContent);
    }

    // Copy rest of MP3 (audio data) 1KB at a time for faster copy
    unsigned char buffer[1024];
    int n;
    while ((n = fread(buffer, 1, sizeof(buffer), fptr1)) > 0) {
        fwrite(buffer, 1, n, fptr2);
    }

    fclose(fptr1);
    fclose(fptr2);

    // Replace original file by removing original file and renaming the new file
    if (remove(argv[4]) != 0) {
        printf("Error deleting original file");
        return;
    }
    if (rename("output.mp3", argv[4]) != 0) {
        printf("Error renaming output file");
        return;
    }

    printf("Tag updated successfully in %s\n", argv[4]);
}

