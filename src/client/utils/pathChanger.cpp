#include "pathChanger.h"



void setWorkingDirectoryToExecutablePath() {
#ifdef _WIN32
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    std::filesystem::path exe_path(path);
    std::filesystem::path exe_dir = exe_path.parent_path();
    std::filesystem::current_path(exe_dir);
#elif __APPLE__
    char path[1024];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0) {
        std::filesystem::path exe_path(path);
        std::filesystem::path exe_dir = exe_path.parent_path();
        std::filesystem::current_path(exe_dir);
    } else {
        std::cerr << "Buffer size for _NSGetExecutablePath is too small; should be " << size << std::endl;
    }
#endif
}