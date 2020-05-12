#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <locale>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <vector>
#define ecout std::cout << "echo "

// using namespace std::;

std::string separator = ": ";
std::string commandFile;
const int programNameLength = 8;

void printHelp() {
  std::cout << "printf \"";
  std::cout << "s <token>\\n";
  std::cout << "s -a <token> <command>\\n";
  std::cout << "s -rm <token>\\n";
  std::cout << "s -l";
  std::cout << "\\n\"" << std::endl;
  exit(0);
}

void runCommand(int argc, std::string argv[]) {
  // Run command
  std::string com = argv[1];
  std::ifstream comFile(commandFile);
  if (comFile.good()) {
    while (!comFile.eof()) {
      std::string curLine;
      std::getline(comFile, curLine);
      std::string token = curLine.substr(0, curLine.find(separator));
      if (token == com) {
        std::cout << curLine.substr(curLine.find(separator) + 1,
                                    curLine.length())
                  << " ";
        for (int i = 2; i < argc; i++) {
          std::cout << argv[i] << " ";
        }
        std::cout << std::endl;
        exit(0);
      }
    }
  }
  ecout << "Command not found" << std::endl;
  exit(0);
}

static inline void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                  [](int ch) { return !std::isspace(ch); }));
}

void newCommand(int argc, std::string argv[]) {
  std::map<std::string, std::string> commands;

  if (argc < 4) {
    printHelp();
  }
  if (argv[2] == "-h" || argv[2] == "-a" || argv[2] == "-rm") {
    std::cout << "Reserved name" << std::endl;
    printHelp();
  }
  std::string newToken = argv[2];

  // Read commands
  std::ifstream comFile(commandFile);
  if (comFile.good()) {
    while (!comFile.eof()) {
      std::string curLine;
      std::getline(comFile, curLine);
      std::string token = curLine.substr(0, curLine.find(separator));
      if (token == newToken) {
        ecout << "Already taken" << std::endl;
        exit(0);
      }
    }
  }

  std::string newCommand = "";
  for (int i = 3; i < argc; i++) {
    newCommand += argv[i] + ((i == argc - 1) ? "" : " ");
  }
  std::ofstream commandsFile;
  commandsFile.open(commandFile, std::ios_base::app);
  commandsFile << newToken << separator << newCommand << std::endl;
  ecout << "Added: " << newToken << ": \"" << newCommand << "\"" << std::endl;
}

void removeCommand(int argc, std::string argv[]) {
  std::string removeToken = argv[2];

  std::ifstream comFile(commandFile);
  std::ofstream tmpFile("/tmp/termtmp");

  bool foundToken = false;

  if (comFile.good()) {
    while (!comFile.eof()) {
      std::string curLine;
      std::getline(comFile, curLine);
      std::string token = curLine.substr(0, curLine.find(separator));
      if (token == removeToken) {
        ecout << "Removed: \"" << curLine << "\"" << std::endl;
        foundToken = true;
      } else
        tmpFile << curLine << std::endl;
    }
  }

  if (!foundToken) {
    ecout << "Command not found" << std::endl;
    exit(0);
  }

  std::ofstream wComFile(commandFile);
  std::ifstream rTmpFile("/tmp/termtmp");

  if (rTmpFile.good()) {
    while (!rTmpFile.eof()) {
      std::string curLine;
      std::getline(rTmpFile, curLine);
      if (curLine != "")
        wComFile << curLine << std::endl;
    }
  }

  exit(0);
}

void listCommands() {
  std::cout << "cat " << commandFile << std::endl;
  exit(0);
}

std::string getPath() {
  char result[PATH_MAX];
  ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
  return std::string(result, (count > 0) ? count : 0);
}

int main(int argc, char *argvc[]) {
  commandFile = std::string(getenv("HOME")) + "/.config/term-shortcuts";

  std::string argv[argc];
  for (int i = 0; i < argc; i++) {
    argv[i] = argvc[i];
  }
  // commandFile = getPath().substr(0, getPath().length()-programNameLength) +
  // commandFile;

  if (argc == 1) {
    listCommands();
  }
  if (argv[1] == "-h") {
    printHelp();
  } else if (argv[1] == "-a") {
    newCommand(argc, argv);
  } else if (argv[1] == "-rm") {
    removeCommand(argc, argv);
  } else {
    runCommand(argc, argv);
  }
}
