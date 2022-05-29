/*
@name:invoker.h
@author: Farrrrland
@created: 2022-05-25
@modified: 2022-05-29
*/

#ifndef _INVOKER_H_
#define _INVOKER_H_

#include <stack>
#include "command.h"

class CommandInvoker {
public:
    void Execute(std::vector<std::shared_ptr<Command>> command);
    void Execute(std::shared_ptr<Command> command);
    void Undo();
    void Redo();
    CommandInvoker(std::shared_ptr<Canvas> canvas) : _canvas(canvas) {}
private:
    std::shared_ptr<Canvas> _canvas;
    std::stack<std::shared_ptr<Command>> _undoStack;
    std::stack<std::shared_ptr<Command>> _redoStack;
};

#endif