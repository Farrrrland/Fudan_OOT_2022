#include <fstream>
#include <iostream>
#include "board.h"
#include "draw.h"
#include "command.h"
#include "parser.h"
#include "invoker.h"

void run(int argc, char** argv) {
    int gscale = 2, gray = 0;
    char* file_name;
    if (argc == 2) {
        file_name = argv[1];
        
    } else if(argc != 4) {
        std::cout << "ERROR: Command Not Defined" << std::endl;
        return; 
    } else if (argv[1][1] == 'g') {
        gscale = atoi(argv[2]);
        file_name = argv[3];
    } else {
        std::cout << "ERROR: Paratetor " << argv[1] << " Not Defined" << std::endl;
        return; 
    }

    std::shared_ptr<Board> board = std::make_shared<Board>(50, gscale);
    std::string script;
    std::string line;
    std::fstream fin(file_name);

    while (getline(fin, line)) {
        if (line.length() < 2 || line[0] != '/' || line[1] != '/') {
            script += line;
        }
    }

    CommandParser parser;
    std::vector<std::shared_ptr<Command>> cmds = parser.ParseCommands(board, script);
    CommandInvoker invoker(board);
    invoker.Execute(cmds);
}