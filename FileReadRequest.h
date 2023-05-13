// Author: Mark Blinder
// FileReadRequest struct, holds process id (PID) and name of file (fileName)

#include <string>

struct FileReadRequest {
        int PID{0};
        std::string fileName{""};
    };