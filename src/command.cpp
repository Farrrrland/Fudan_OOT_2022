/*
@name: command.cpp
@author: Farrrrland
@created: 2022-05-25
@modified: 2022-05-29
*/

#include <iostream>
#include "command.h"
#include "charshape.hpp"
#include "invoker.h"

/*
 Basic Command Class
*/
void Command::Execute(Coordinate) {
    Execute();
}
void Command::Undo() {
    if (!_couldUndo || !_previousCanvas) {
        exit(0);
    }
    SetExecuted(false);
    *_canvas = *_previousCanvas;
}
bool Command::CouldUndo() {
    return _couldUndo;
}
void Command::SaveState() {
    if (_couldUndo) {
        SetPreCanvas(std::make_shared<Canvas>(*_canvas));
    }
}
std::shared_ptr<Command> Command::New(CommandTypeEnum type) {
    return std::make_shared<Command>(type);
}
std::shared_ptr<Command> Command::New() {
    return std::make_shared<Command>();
}
std::shared_ptr<Command> Command::Copy() {
    return Copy(Coordinate(0, 0));
}
std::shared_ptr<Command> Command::Copy(const Coordinate& offset) {
    std::shared_ptr<Command> new_cmd = this->New();
    _executed = false;
    _previousCanvas = 0;
    return new_cmd;
}


/*
 Macro Command
*/
void MacroCommand::Execute() {
    Execute(Coordinate(0, 0));
}
void MacroCommand::Execute(Coordinate offset) {
    if (_executed) {
        exit(0);
    }
    _executed = true;
    int gray = _canvas->GetGray();
    for (auto command : _commands) {
        command->Execute(_offset + offset);
    }
    ColorCommand::New(_canvas, gray, false)->Execute();
}
void MacroCommand::SetExecuted(bool executed) {
    _executed = executed;
    for (auto command : _commands) {
        command->SetExecuted(executed);
    }
}
MacroCommand::MacroCommand(std::shared_ptr<Canvas> canvas, const std::string& name, const Coordinate& offset, std::vector<std::shared_ptr<Command>>& commands) :
    _offset(offset), _commands(commands) {
    _type = CommandTypeEnum::MACRO;
    _canvas = canvas;
    _name = name;
}
std::shared_ptr<MacroCommand> MacroCommand::New(std::shared_ptr<Canvas> canvas, const std::string& name, const Coordinate& offset, std::vector<std::shared_ptr<Command>>& commands) {
    return std::make_shared<MacroCommand>(canvas, name, offset, commands);
}
std::shared_ptr<Command> MacroCommand::Copy() {
    return Copy(_offset);
}
std::shared_ptr<Command> MacroCommand::Copy(const Coordinate& offset) {
    std::vector<std::shared_ptr<Command>> new_cmds;
    for (auto command : _commands) {
        new_cmds.push_back(command->Copy());
    }
    return std::make_shared<MacroCommand>(_canvas, _name, offset, new_cmds);
}
void MacroCommand::SetOffset(const Coordinate& offset) {
    _offset = offset;
}



/*
 Color Command
*/
void ColorCommand::Execute() {
    if (_executed) {
        exit(0);
    }
    _executed = true;
    _canvas->SetGray(_gray);
}
ColorCommand::ColorCommand(std::shared_ptr<Canvas> canvas, int gray, bool couldUndo) : _gray(gray) {
    _type = CommandTypeEnum::COLOR;
    _canvas = canvas;
    _couldUndo = couldUndo;
}
std::shared_ptr<Command> ColorCommand::New() {
    return New(_canvas, _gray, _couldUndo);
}
std::shared_ptr<ColorCommand> ColorCommand::New(std::shared_ptr<Canvas> canvas, int gray, bool couldUndo) {
    return std::make_shared<ColorCommand>(canvas, gray, couldUndo);
}


/*
 Line Command
*/
void LineCommand::Execute() {
    Execute(Coordinate(0, 0));
}
void LineCommand::Execute(Coordinate offset) {
    if (_executed) {
        exit(0);
    }
    _executed = true;
    // Use bresenham's line algorithm to draw lines
    int dx = _end.x() - _begin.x();
    int dy = _end.y() - _begin.y();
    if (abs(dx) >= abs(dy)) {
        if (dy < 0) {
            std::swap(_begin, _end);
            dx = -dx;
            dy = -dy;
        }
        for (int x = _begin.x(), y = _begin.y(), e = -x, aug = _begin.x() < _end.x() ? 1 : -1; ; x += aug) {
            _canvas->Plot(offset + Coordinate(x, y));
            e += 2 * dy;
            if (e > 0) {
                e -= abs(2 * dx), y++;
            }
            if (x == _end.x()) {
                break;
            }
        }
    } else {
        if (dx < 0) {
            std::swap(_begin, _end);
            dx = -dx;
            dy = -dy;
        }
        for (int x = _begin.x(), y = _begin.y(), e = -y, aug = _begin.y() < _end.y() ? 1 : -1; ; y += aug) {
            _canvas->Plot(offset + Coordinate(x, y));
            e += 2 * dx;
            if (e > 0) {
                e -= abs(2 * dy), x++;
            }
            if (y == _end.y()) {
                break;
            }
        }
    }
}
LineCommand::LineCommand(std::shared_ptr<Canvas> canvas, Coordinate& begin, Coordinate& end) : _begin(begin), _end(end) {
    _type = CommandTypeEnum::LINE;
    _canvas = canvas;
}
std::shared_ptr<Command> LineCommand::New() {
    return New(_canvas, _begin, _end);
}
std::shared_ptr<LineCommand> LineCommand::New(std::shared_ptr<Canvas> canvas, Coordinate& begin, Coordinate& end) {
    return std::make_shared<LineCommand>(canvas, begin, end);
}


/*
 Text Command
*/
void TextCommand::Execute() {
    Execute(Coordinate(0, 0));
}
void TextCommand::Execute(Coordinate offset) {
    if (_executed) {
        exit(0);
    }
    _executed = true;

    Coordinate cur = offset + Coordinate(_offset.x() + 1, _offset.y());;
    for (auto c : _text) {
        std::vector<int> mat = GetCharShape(c);
        int n = mat.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                if (mat[i]&(1<<j)) {
                    _canvas->Plot(Coordinate(cur.x() + n - j - 1, cur.y() + n - i - 1));
                }
        }
        cur = Coordinate(cur.x() + n + 1, cur.y());
    }
}
TextCommand::TextCommand(std::shared_ptr<Canvas> canvas, Coordinate& offset, const std::string& text) : _offset(offset), _text(text) {
    _type = CommandTypeEnum::TEXT;
    _canvas = canvas;
}
std::shared_ptr<Command> TextCommand::New() {
    return New(_canvas, _offset, _text);
}
std::shared_ptr<TextCommand> TextCommand::New(std::shared_ptr<Canvas> canvas, Coordinate& offset, const std::string& text) {
    return std::make_shared<TextCommand>(canvas, offset, text);
}


/*
 Show Command
*/
void ShowCommand::Execute() {
    if (_executed) {
        exit(0);
    }
    _executed = true;
    int size = _canvas->GetSize();
    std::vector<std::vector<int>>* canvas = _canvas->GetCanvas();
    for (int j = size - 1; j >= 0; j--) {
        for (int i = 0; i < size; i++) {
            if (i) {
                std::cout << " ";
            }
            std::cout << (*canvas)[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
ShowCommand::ShowCommand(std::shared_ptr<Canvas> canvas) {
    _type = CommandTypeEnum::SHOW;
    _couldUndo = false;
    _canvas = canvas;
}
std::shared_ptr<Command> ShowCommand::New() {
    return New(_canvas);
}
std::shared_ptr<ShowCommand> ShowCommand::New(std::shared_ptr<Canvas> canvas) {
    return std::make_shared<ShowCommand>(canvas);
}
