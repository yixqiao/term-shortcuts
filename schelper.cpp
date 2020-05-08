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

#define ecout std::cout << "echo"

// using namespace std::;

void printHelp() {
  std::cout << "echo usage: sc [<command>]";
  std::cout << std::endl;
  exit(0);
}

std::string getPrevCommand() {}

int main(int argc, char *argvc[]) {
  std::string argv[argc];
  for (int i = 0; i < argc; i++) {
    argv[i] = argvc[i];
  }
  if (argc == 1) {
    printHelp();
  }
  if (argc == 2 && argv[1][0] != '-') {
    // Run command
    std::string com = argv[1];
    std::ifstream comFile("commands.txt");
    if (comFile.good()) {
      while (!comFile.eof()) {
        std::string curLine;
        std::getline(comFile, curLine);
        std::string token = curLine.substr(0, curLine.find(" "));
        if (token == com) {
          std::cout << curLine.substr(curLine.find(" ") + 1, curLine.length())
                    << std::endl;
          exit(0);
        }
      }
    }
  } else {
    if (argv[1] == "-a") {
      std::string histfile = "~/.bash_history";
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
          std::string token = curLine.substr(0, curLine.find("-"));
          std::string command =
              curLine.substr(curLine.find("-") + 1, curLine.length());
          commands.insert(std::make_pair(token, command));
        }
      }

      if (argc < 4) {
        printHelp();
      }
      if (argv[3] == "-p") {
        std::string histPath = "/home/yixuan/.bash_history";

        std::ifstream comFile(histPath);
        std::string curLine;
        std::string prevLine;
        if (comFile.good()) {
          while (!comFile.eof()) {
            prevLine = curLine;
            std::getline(comFile, curLine);
            // std::cout << curLine << std::endl;
          }
        }
        std::cout << prevLine << std::endl;
      }
    }
  }
  // ofstream myfile;
  // myfile.open("example.txt");
  // myfile << "Writing this to a file.\n";
  // myfile.close();
}
