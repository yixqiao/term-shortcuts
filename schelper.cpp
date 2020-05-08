#include <array>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#define ecout std::cout << "echo "

// using namespace std::;

std::string separator = ": ";

void printHelp() {
  ecout << "usage: sc [<command>]" << std::endl;
  exit(0);
}

void runCommand(int argc, std::string argv[]) {
  // Run command
  std::string com = argv[1];
  std::ifstream comFile("commands.txt");
  if (comFile.good()) {
    while (!comFile.eof()) {
      std::string curLine;
      std::getline(comFile, curLine);
      std::string token = curLine.substr(0, curLine.find(separator));
      if (token == com) {
        std::cout << curLine.substr(curLine.find(separator) + 1,
                                    curLine.length())
                  << std::endl;
        exit(0);
      }
    }
  }
}

void newCommand(int argc, std::string argv[]) {
  std::map<std::string, std::string> commands;

  if (argv[2].find("-") != std::string::npos) {
    std::cout << "Commands cannot contain the character \"-\"." << std::endl
              << std::endl;
    printHelp();
  }
  std::string newToken = argv[2];

  // Read commands
  std::ifstream comFile("commands.txt");
  if (comFile.good()) {
    while (!comFile.eof()) {
      std::string curLine;
      std::getline(comFile, curLine);
      std::string token = curLine.substr(0, curLine.find(separator));
      if (token == newToken) {
        ecout << "This token is already taken!" << std::endl;
        exit(0);
      }
    }
  }

  if (argc < 4) {
    printHelp();
  }

  if (argv[3] == "-p") {
    std::string histPath = std::string(getenv("HOME")) + "/.bash_history";

    std::ifstream comFile(histPath);
    std::string curLine;
    std::string lastCommand;
    if (comFile.good()) {
      while (!comFile.eof()) {
        lastCommand = curLine;
        std::getline(comFile, curLine);
        // std::cout << curLine << std::endl;
      }
    }
    std::ofstream commandsFile;
    commandsFile.open("commands.txt", std::ios_base::app);
    commandsFile << newToken << separator << lastCommand << std::endl;
    ecout << "Write successful: " << newToken << ": \"" << lastCommand << "\""
          << std::endl;
  } else {
    std::string newCommand = "";
    for (int i = 3; i < argc; i++) {
      newCommand += argv[i] + ((i == argc - 1) ? "" : " ");
    }
    std::ofstream commandsFile;
    commandsFile.open("commands.txt", std::ios_base::app);
    commandsFile << newToken << separator << newCommand << std::endl;
    ecout << "Write successful: " << newToken << ": \"" << newCommand << "\""
          << std::endl;
  }
}

void removeCommand(int argc, std::string argv[]) {
  std::string removeToken = argv[2];

  std::ifstream comFile("commands.txt");
  std::ofstream tmpFile("tmp");

  if (comFile.good()) {
    while (!comFile.eof()) {
      std::string curLine;
      std::getline(comFile, curLine);
      std::string token = curLine.substr(0, curLine.find(separator));
      if (token == removeToken)
        ecout << "Removed " << curLine << std::endl;
      else
        tmpFile << curLine << std::endl;
    }
  }

  std::ofstream wComFile("commands.txt");
  std::ifstream rTmpFile("tmp");

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

void listCommands(int argc, std::string argv[]) {
  std::cout << "cat "
            << "commands.txt" << std::endl;
}

int main(int argc, char *argvc[]) {
  std::string argv[argc];
  for (int i = 0; i < argc; i++) {
    argv[i] = argvc[i];
  }
  if (argc == 1) {
    printHelp();
  }
  if (argc == 2 && argv[1][0] != '-') {
    runCommand(argc, argv);
  } else if (argv[1] == "-a") {
    newCommand(argc, argv);
  } else if (argv[1] == "-r") {
    removeCommand(argc, argv);
  } else if (argv[1] == "-l") {
    listCommands(argc, argv);
  }
}