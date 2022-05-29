#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include <map>
#include <algorithm>
#include "command.h"

#include <iostream>

class CommandParser {
public:
    std::vector<std::shared_ptr<Command>> ParseCommands(std::shared_ptr<Canvas> canvas, std::string& str);
private:
    void RegisterMacroCommand(std::string& cmd, std::shared_ptr<Canvas> canvas);
    std::shared_ptr<Command> GetCommand(std::string& cmd, std::shared_ptr<Canvas> canvas);
    std::shared_ptr<Command> GetMacroCommand(std::string& cmd, const Coordinate& offset);
    std::map<std::string, std::shared_ptr<MacroCommand>> _macro_table;
};


std::vector<std::string> SplitCommand(const std::string& cmd) {
    std::vector<std::string> cmds;
    bool inmacro = false;
    bool instring = false;
    for (int l = 0, r = 0, undo, redo; l < cmd.length(); r++) {
        if (r - l == 0) {
            undo = cmd[r] == 'u';
            redo = cmd[r] == 'r';
        } else if (r - l == 1) {
            undo += cmd[r] == 'n';
            redo += cmd[r] == 'e';
        } else if (r - l == 2) {
            undo += cmd[r] == 'd';
            redo += cmd[r] == 'd';
        } else if (r - l == 3) {
            undo += cmd[r] == 'o';
            redo += cmd[r] == 'o';
        }

        if (cmd[r] == '"') instring ^= 1; 
        if (instring) continue;
        
        if (cmd[r] == '}') {
            cmds.push_back(cmd.substr(l, r - l + 1));
            l = r + 1;
            inmacro = false;
        } else if (cmd[r] == '#') {
            inmacro = true;
        } else if (!inmacro && (cmd[r] == ')' || undo == 4 || redo == 4)) {
            cmds.push_back(cmd.substr(l, r - l + 1));
            l = r + 1;
        }
    }
    return cmds;
}

std::vector<std::string> TrimCommand(const std::string& cmd) {
    std::vector<std::string> res;
    int l = 0, r = 0;
    while (r < cmd.length() && cmd[r] != '(') r++;
    res.push_back(cmd.substr(l, r));
    l = ++r;
    while (r < cmd.length()) {
        if (cmd[r] == ',' || cmd[r] == ')') {
            res.push_back(cmd.substr(l, r - l));
            l = r + 1;
        }
        r++;
    }
    return res;
}

std::vector<std::shared_ptr<Command>> CommandParser::ParseCommands(std::shared_ptr<Canvas> canvas, std::string& str) {
    std::vector<std::shared_ptr<Command>> res;

    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());

    std::vector<std::string> cmds = SplitCommand(str);
    
    for (std::string cmd : cmds) {
        if (cmd[0] == '#') {
            RegisterMacroCommand(cmd, canvas);
        } else {
            std::shared_ptr<Command> command = GetCommand(cmd, canvas);
            command->SetInfo(cmd);
            res.push_back(command);
        }
    }

    return res;
}

void CommandParser::RegisterMacroCommand(std::string& cmd, std::shared_ptr<Canvas> canvas) {
    int len = cmd.length();
    int l, r;
    for (int i = 1; i < len; i++) {
        if (cmd[i] == '{') l = i;
        if (cmd[i] == '}') r = i;
    }
    std::vector<std::string> strs = SplitCommand(cmd.substr(l + 1, r - l - 1));
    std::vector<std::shared_ptr<Command>> cmds;
    for (std::string str : strs) {
        cmds.push_back(GetCommand(str, canvas));
    }
    std::string name = cmd.substr(1, l - 1); 
    _macro_table[name] = MacroCommand::New(canvas, name, Coordinate(0, 0), cmds);
}

std::shared_ptr<Command> CommandParser::GetMacroCommand(std::string& cmd, const Coordinate& offset) {
    return _macro_table[cmd]->Copy(offset);
}

std::shared_ptr<Command> CommandParser::GetCommand(std::string& cmd, std::shared_ptr<Canvas> canvas) {
    std::vector<std::string> tokens = TrimCommand(cmd);
    if (tokens[0] == "color") {
        return ColorCommand::New(canvas, atoi(tokens[1].c_str()), true);
    } else if (tokens[0] == "line") {
        Coordinate p1 = Coordinate(atoi(tokens[1].c_str()), atoi(tokens[2].c_str()));
        Coordinate p2 = Coordinate(atoi(tokens[3].c_str()), atoi(tokens[4].c_str()));
        return LineCommand::New(canvas, p1, p2);
    } else if (tokens[0] == "text") {
        Coordinate p = Coordinate(atoi(tokens[1].c_str()), atoi(tokens[2].c_str()));
        return TextCommand::New(canvas, p, tokens[3].substr(1, tokens[3].size() - 2));
    } else if (tokens[0] == "undo") {
        return Command::New(CommandType::UNDO);
    } else if (tokens[0] == "redo") {
        return Command::New(CommandType::REDO);
    } else {
        Coordinate p = Coordinate(atoi(tokens[1].c_str()), atoi(tokens[2].c_str()));
        if (tokens[0][0] == '!') tokens[0] = tokens[0].substr(1, cmd.size() - 1);
        return GetMacroCommand(tokens[0], p);
    }
}

#endif