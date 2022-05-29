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
    std::stack<std::shared_ptr<Command>> _undo_stack;
    std::stack<std::shared_ptr<Command>> _redo_stack;
    std::shared_ptr<Canvas> _canvas;
};

#endif