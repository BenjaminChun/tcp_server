# tcp_server

base_directory to be exposed is ./file_sys

requirements:
- Read file (pathname, offset, number of bytes)
- Insert Content to file (pathname, offset, sequence of bytes)
- Monitor updates (pathname, length of interval) -> callback endpoint that allows client to register
    - Have a hashmap that maps file -> list of machines that register to it
    - So every change invoking api call will check hashmap before returning message
        - If not empty list
        - Iterate thru list check if callback in list is expired
        - If not then execute callback
- List files in directory (directory_path)
- Remove Content of File (pathname, offset, sequence of bytes)- ‘abcdefg’ [pathname, remove at offset 2, number of bytes 2] -> ‘adefg’

Fault tolerance:
- At least once (only reliable for idempotent ops)
    - No record of duplicate requests
    - If a request is reached, just execute it as instructed and return request
- At most once
    - Records responses
    - If request is repeated (check message-id+machine-id -> requestId), resend recorded response

TODO:
find out the stat behavior and extract wtv is needed, metadata of file -> what is required?

