"""code will execute only if the file's integrity can be cryptographically verified via chunked binary streams """

import hashlib #built in hashing library
import sys #to interact via command line interface
import os #to read file paths

def calculate_sha256(file_path): 
    """Memory bounded file streaming,
    reads a file in fixed 4096-byte blocks"""

    #initializing an empty sha256 hashing engine
    sha256_hash = hashlib.sha256()

    #checking if the path is an actual physical file path
    if not os.path.isfile(file_path):
        print(f"[WARNING] No such file path exists!")
        return None
    
    try: 
        with open(file_path, 'rb') as file:
            #Start a loop to stream the hardware blocks
            while True:
                #Reads exactly 4096 from drive to the RAM
                byte_block = file.read(4096)

                #if 'byte_block' is empty, break out of the loop early 
                if not byte_block:
                    break

                #feed this specific chunk into the hashing engine 
                sha256_hash.update(byte_block)

        return sha256_hash.hexdigest()
            
    except PermissionError:
        print(f"[WARNING] Insufficient privileges to read system frame, {file_path}")
        return None


if __name__ == "__main__":
    #if the user did not supply a target file path in terminal arguments, stop execution
    if len(sys.argv) < 2: 
        print("[MESSAGE] Usage: python telemetry_hub.py <file_path>")
        sys.exit(1)
    
    #Extract the target file path provided by the user
    target_path = sys.argv[1]
    
    #Execute function to capture resulting cryptographic signature string 
    digest = calculate_sha256(target_path)
    
    #If a valid signature was successfully computed display it
    if digest: 
        print(f"Python Engine Integrity Signature: {digest}")