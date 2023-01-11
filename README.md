# RTSP-Ripper
This program uses ffmpeg to ingest an RTSP feed and turn it into uniform mp4 videos.

## Current function
Takes a camera address, checks for then creates an empty folder, then records 30 second chunks of video to mp4s. You can interrupt the process by typing 'y,' which will signal to the thread running ffmpeg that this is its last loop.

## TO DO
* integrate Azure Blob Storage
* upload blobs to storage
* delete local mp4 chunks
