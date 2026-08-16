#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

/*Using pragma to control structure padding and alignment */

/*Saving current alignment setting onto an internal compiler stack, 
crucial because it allows temporarily changing the alignment 
without affecting the rest of the code or other headers that might be included later*/

/*Alignment boundary set to 1 byte to avoid addition of any padding bytes and packing members tightly, 
one after the other*/
#pragma pack(push,1)

typedef struct{
    uint32_t file_id; /*tracking id*/
    uint64_t file_size_bytes; /*unsigned int for tracking large files*/
    uint16_t chunk_count; /*unsigned int for 4KB chuncks*/
    char status_flag; /*status valid, unverified */
} FileTelemetry;

/*Restoring alignment setting to before that of 'push' limiting the tightly packaged format only to FileTelemetry*/
#pragma pack(pop) /*with this the size of struct is exactly 15 bytes(4+8+2+1)*/

int export_telemetry(const char *filename, FileTelemetry *data)
{
    /*opening file in binary write mode*/
    FILE *fp; 

    fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        perror("[ERROR]The file cannot be opened");
        exit(1);
    }

    /*writing the the  raw struct directly onto the disk using fwrite*/
    size_t written = fwrite(data, sizeof(FileTelemetry),1, fp);
    
    
    fflush(fp);
    /*closing the file*/
    fclose(fp);


    return (written == 1) ? 0:-1;

}

/*using the memory address(*) instead of names like 'out_data' causes the function to work on the original data and not the copy*/
/*downside: function will not be able to modiy the original variable is needed later*/
int import_telemetry(const char *filename, FileTelemetry *out_data)
{
    /*opening file in read mode*/
    FILE *fp;

    fp = fopen(filename, "rb");
    if(fp == NULL)
    {
        perror("[ERROR] The file could not be opened in read mode");
        exit(1);
    }

    /*reading raw binary stream directly into the target struct pointer*/
    size_t read_bytes = fread(out_data,sizeof(FileTelemetry),1,fp);

    fclose(fp);

    return(read_bytes == 1)? 0:-1;
}

int main(void)
{   
    /*payload because the telemetry data is actual cargo that is distinct*/
    printf("[INFO] Executing Phoenix core payload test\n");

    FileTelemetry original_record = {
        .file_id = 9001,
        .file_size_bytes = 1048576,
        .chunk_count = 256,
        .status_flag = 'v'
    };

    /*creating variable to hold the record file of the telemetry*/
    const char *payload_path = "C:\\msys64\\ucrt64\\bin\\telemetry_record.bin";

    /*running export_telemety to save the struct to the file*/
    if (export_telemetry(payload_path, &original_record) == 0) {
        printf("[SUCCESS] Telemetry binary payload written to %s\n", payload_path);
    }

    /*Importing struct memory state back*/
    FileTelemetry imported_record;
    if (import_telemetry(payload_path, &imported_record) == 0) {
        printf("[SUCCESS] Payload imported cleanly.\n");
        printf(" -> Header ID: %u\n", imported_record.file_id);
        printf(" -> Size: %llu bytes\n", (unsigned long long)imported_record.file_size_bytes);
        printf(" -> Status Flag: %c\n", imported_record.status_flag);
    }

    return 0;

    
}