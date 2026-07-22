  #include <stdio.h> 
  #include <stdlib.h> 
  #include <stdint.h> //for fixed width integer types like unit64_t 

  //struct definition using typedef
  typedef struct{
    uint32_t file_id; /*tracking id*/
    uint64_t file_size_bytes; /*unsigned int for tracking large files*/
    uint16_t chunk_count; /*unsigned int for 4KB chuncks*/
    char status_flag; /*status valid, unverified */
  } FileTelemetry; 

  int main(void)
  {
    printf("[INFO] Initializing phoenix core Telemetry type registry\n");

    //declaring variable for our struct 
    FileTelemetry sample_file; 

    //populating struct members 
    sample_file.file_id = 1001; 
    sample_file.file_size_bytes = 1048576 /*1MB*/; 
    sample_file.status_flag = 'v'; 
    sample_file.chunk_count = 256; /*256 chunks of 4096 bytes are required for 1 MB*/

    printf("The file id is: %u \n",sample_file.file_id);
    printf("The file size in bytes is: %llu\n", sample_file.file_size_bytes);
    printf("The status of the file is: %c\n",sample_file.status_flag);
    printf("The chunk count is: %u\n",sample_file.chunk_count);

    //Memory analysis printout: 
    printf("\n Structure memory footprint analysis\n"); 
    printf("Total size of 'File Telemtry' Struct in RAM: %zu bytes\n",sizeof(FileTelemetry));

    return 0;


  }