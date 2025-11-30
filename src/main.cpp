#include <iostream>
#include <thread>   // for std::this_thread::sleep_for
#include <chrono>   // for std::chrono::seconds
#include <unistd.h> // for fork()

#include "include/FileWatch.hpp" // FileWatch header (github.com/ThomasMonkman/FileWatch)

// Message to professional c++ devs: I'm sorry that you have to look at this abomination.
// using namespace std; // Avoiding this for clarity. I guess.

void handle_errors_Unistd(pid_t pidT)
{
    if (pidT < 0)
    {
        // Error handling for fork failure
        perror("fork failed");
    }
    else if (pidT > 0)
    {
        // Parent process exits
    }

    if (setsid() < 0)
    {
        // Error handling for setsid failure
        perror("setsid failed");
    }

    if (chdir("/") < 0)
    {
        perror("chdir failed");
    }
}

int main(int argc, char *argv[])
{

    std::string watchFile = "/etc/mtab";
    std::string command;
    std::string watchFolder = "/usr/share/";
    auto last_run = std::chrono::steady_clock::now() - std::chrono::seconds(1); // To prevent two runs at file change in linux.

    /*
        FileWatch on Linux (using inotify) or on other platforms often triggers multiple events for a single edit.
            * Example: when you save a file in an editor like vim or VSCode:
            * One event for IN_MODIFY (file content changed)
            * Another event for IN_CLOSE_WRITE (file closed after writing)
            * This ultimately results in the command being executed multiple times for a single logical change.
            * It was a pain to fix this bug :(
    */

    for (int i = 1; i < argc; ++i)
    {                              // Start from i=1 to skip program name
        std::string arg = argv[i]; // Convert to std::string for easier manipulation

        if (arg == "--background" && (i + 1) < argc)
        {
            pid_t pid = fork();
            handle_errors_Unistd(pid);

            // Close standard file descriptors
            close(STDIN_FILENO);
            close(STDOUT_FILENO);
            close(STDERR_FILENO);

            // Redirect to /dev/null or log files
            open("/dev/null", O_RDWR); // stdin
            open("/dev/null", O_RDWR); // stdout
            open("/dev/null", O_RDWR); // stderr
            i++;                       // Increment i
        }

        if (arg == "--logfile" && (i + 1) < argc)
        {
            const char *logFilePath = argv[i + 1];
            freopen(logFilePath, "a", stdout); // Redirect stdout to log file
            freopen(logFilePath, "a", stderr); // Redirect stderr to log file
            i++;                               // Increment i
        }

        if (arg == "--watchfile" && (i + 1) < argc)
        {
            // Use the next argument as the file to watch
            std::string fileToWatch = argv[i + 1];
            watchFile = fileToWatch; // for global acess if needed.
            std::cout << "Watching file: " << fileToWatch << std::endl;
            i++; // Increment i
        }

        if (arg == "--watchfolder" && (i + 1) < argc)
        {
            std::string folderToWatch = argv[i + 1];
            watchFolder = folderToWatch; // For global access if needed.
            std::cout << "Watching Folder: " << folderToWatch << std::endl;
        }

        if (arg == "--help")
        {
            std::cout << "Usage: " << argv[0] << " [--background] [--logfile <path>] [--watchfile <path>] [--help]\n";
            std::cout << "--background       Run the program as a background daemon.\n";
            std::cout << "--command <cmd>    Command to execute on file change (in quotes).\n";
            std::cout << "--watchfolder <path> Specify the folder to watch changes in.";
            std::cout << "--logfile <path>   Specify a log file to redirect output.\n";
            std::cout << "--watchfile <path> Specify the file to watch for changes.\n";
            std::cout << "--help             Display this help message.\n";
            return 0;
        }

        if (arg == "--command" && (i + 1) < argc)
        { // Command that is executed on file change (in "")
            std::string commandToExecute = argv[i + 1];
            command = commandToExecute;
            i++; // Increment i
        }
    }

    filewatch::FileWatch<std::string> folderWatch(
        watchFolder, // path to the folder
        [&command, &last_run](const std::string &path, const filewatch::Event change_type)
        {
            if (change_type == filewatch::Event::modified)
            {

                auto now = std::chrono::steady_clock::now();
                auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_run).count();

                if (diff > 500)
                { // debounce: avoid double-trigger

                    system(command.c_str());
                    std::cout << "Executed command: " << command
                              << " due to modification in: " << path << std::endl;

                    last_run = now;
                }
            }
        });

    filewatch::FileWatch<std::string> fileWatch(
        watchFile,
        [&command, &last_run](const std::string &path, const filewatch::Event change_type)
        {
            if (change_type == filewatch::Event::modified)
            {
                auto now = std::chrono::steady_clock::now();
                auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_run).count();
                if (diff > 500)
                { // only run if more than 500ms passed
                    system(command.c_str());
                    std::cout << "Executed command: " << command << " due to change in file: " << path << std::endl;
                    last_run = now;
                }
            }
        });

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
