#include <iostream>
#include "invoker.h"

void CommandInvoker::Execute(std::vector<std::shared_ptr<Command>> cmds) {
    for (auto cmd : cmds) {
        CommandTypeEnum type = cmd->GetType();
        if (type == MACRO) {
            std::cout << "Execute Macro Command: " + std::dynamic_pointer_cast<MacroCommand>(cmd)->GetName() << std::endl;
            Execute(cmd);
        } else if (type == CommandTypeEnum::UNDO) {
            std::cout << "Execute Undo Command" << std::endl;
            Undo();
        } else if (type == CommandTypeEnum::REDO) {
            std::cout << "Execute Redo Command" << std::endl;
            Redo();
        } else {
            std::cout << "Execute Command: " + cmd->GetInfo() << std::endl;
            Execute(cmd);
        }

        if (type == CommandTypeEnum::COLOR) {
            std::cout << std::endl;
        } else {
            Execute(ShowCommand::New(_canvas));
        }
    }
}

void CommandInvoker::Execute(std::shared_ptr<Command> command) {
    if (command->CouldUndo()) command->SaveState();
    command->Execute();
    if (command->CouldUndo()) {
        while (!_redo_stack.empty()) _redo_stack.pop();
        _undo_stack.push(command);
    }
}

void CommandInvoker::Undo() {
    if (_undo_stack.empty()) return;
    std::shared_ptr<Command> cmd = _undo_stack.top();
    _undo_stack.pop();
    cmd->Undo();
    _redo_stack.push(cmd);
}

void CommandInvoker::Redo() {
    if (_redo_stack.empty()) return;
    std::shared_ptr<Command> cmd = _redo_stack.top();
    _redo_stack.pop();
    cmd->Execute();
    _undo_stack.push(cmd);
}
