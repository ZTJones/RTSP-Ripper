#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

using std::cout; using std::endl;
using std::filesystem::directory_iterator;

namespace fs = std::filesystem;

void encodeOnLoop(bool* running, std::string inputAddress) // Encodes an RTSP stream to mp4, and it just don't stop... Unless a flag is lifted.
{
    std::string seconds = "30";
    std::string cameraAddress = inputAddress;
    std::string fileNameBase = "streamCap";
    std::string outputFormat = ".mp4";
    int loop = 0;

    while (*running) {
        // Need to 
        std::string ffmpegCommand = "ffmpeg -rtsp_transport udp -t " + seconds + " -i " + cameraAddress + " " + fileNameBase + std::to_string(loop) + outputFormat;
        system(ffmpegCommand.c_str());
        
        loop++;
    }
}

int main(int argc, char* argv[])
{
    bool ready = false;
    std::string path = ".";

    

    // std::string inputAddress = argv[0];

    while (true) { // A bit of quick logic to create a folder to work with.
        for (const auto & file : fs::directory_iterator(path))
        {
            if (file.path() == ".//TempTest") { // checking to see if there's a folder called TempTest
                cout << "Found the test folder." << endl;
                fs::current_path(file.path());
                ready = true;
                break;
            }
        }
        if (!ready) {
            fs::create_directory(fs::current_path().string() + "\\TempTest");
        }
        if (ready) {
            break;
        }
    }

    std::string switchCommand = "cd " + fs::current_path().string();
    system(switchCommand.c_str());

    // Okay, so we're grabbing a 30 second clip from a streamed video... ip camera.
    // What now?
    // Let's think about this... We want to do a few things.  
    // 1: encode video from an RTSP stream into mp4 videos, repeatedly
    // 2: upload those videos to Azure blob storage
    // 3: then clean up those files on the local system.
    // That means that we're going to want a loop... and maybe a few other things.
    // Like multithreading.
    
    bool continueRunning = true;
    char inputChar;

    if (argc < 2) {
        cout << "You need to provide the camera address as a parameter." << endl;
        return 0;
    }
    // This is where we're calling the new thread
    std::thread ffmpegLoop(encodeOnLoop, &continueRunning, argv[1]); // We're running encodeOnLoop in a separate thread to prevent blocking our input.
    while (true)
    {

        cout << "Stop process?  y/n" << endl;
        std::cin >> inputChar; // While the encoding loop is running, you can interrupt it at any time by typing 'y' and hitting enter.
        if (inputChar == 'y') {
            continueRunning = false;
            // while (!finalLoop);
            ffmpegLoop.join(); // Once you've signaled that you'd like to stop, we wait for the extra thread to finish it's encoding job.
            break;
        }
    }

    
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
