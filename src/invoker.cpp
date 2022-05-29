/*
@name:invoker.cpp
@author: Farrrrland
@created: 2022-05-25
@modified: 2022-05-29
*/

#include <iostream>
#include "invoker.h"

void CommandInvoker::Execute(std::vector<std::shared_ptr<Command>> commands) {
    for (auto command : commands) {
        CommandTypeEnum type = command->GetType();
        if (type == MACRO) {
            std::cout << "Execute Macro Command: " + std::dynamic_pointer_cast<MacroCommand>(command)->GetName() << std::endl;
            Execute(command);
        } else if (type == CommandTypeEnum::UNDO) {
            std::cout << "Execute Undo Command" << std::endl;
            Undo();
        } else if (type == CommandTypeEnum::REDO) {
            std::cout << "Execute Redo Command" << std::endl;
            Redo();
        } else {
            std::cout << "Execute Command: " + command->GetInfo() << std::endl;
            Execute(command);
        }
        if (type == CommandTypeEnum::COLOR) {
            std::cout << std::endl;
        } else {
            Execute(ShowCommand::New(_canvas));
        }
    }
}
void CommandInvoker::Execute(std::shared_ptr<Command> command) {
    if (command->CouldUndo()) {
        command->SaveState();
    }
    command->Execute();
    if (command->CouldUndo()) {
        while (!_redoStack.empty()) {
            _redoStack.pop();
        }
        _undoStack.push(command);
    }
}
void CommandInvoker::Undo() {
    if (_undoStack.empty()) {
        return;
    }
    std::shared_ptr<Command> command = _undoStack.top();
    _undoStack.pop();
    command->Undo();
    _redoStack.push(command);
}
void CommandInvoker::Redo() {
    if (_redoStack.empty()) {
        return;
    }
    std::shared_ptr<Command> command = _redoStack.top();
    _redoStack.pop();
    command->Execute();
    _undoStack.push(command);
}
