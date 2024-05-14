#include "controller.h"
#include "client.h"
#include <filesystem>
#include "utils/pathChanger.h"


int main(){
    setWorkingDirectoryToExecutablePath();
    Controller controller;
    controller.run();
}