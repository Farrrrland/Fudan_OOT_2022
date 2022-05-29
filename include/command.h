#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "canvas.h"
#include "coordinate.h"

enum CommandType {
    MACRO,
    UNDO,
    REDO,
    SHOW,
    LINE,
    TEXT,
    COLOR
};

class Command {
public:
    virtual void Execute() {};
    virtual void Execute(Coordinate);
    virtual void Undo();
    virtual bool Undoable() final;
    virtual void SaveState();

    virtual CommandType GetType() { return _type; }
    virtual std::shared_ptr<Canvas> GetCanvas() { return _canvas; }
    virtual std::string GetInfo() { return _info; }
    virtual void SetExecuted(bool executed) { _executed = executed; }
    virtual void SetPreCanvas(std::shared_ptr<Canvas> pre_canvas) { _pre_canvas = pre_canvas; }
    virtual void SetInfo(const std::string& info) { _info = info; }

    virtual std::shared_ptr<Command> New();
    static std::shared_ptr<Command> New(CommandType type);
    virtual std::shared_ptr<Command> Copy();
    virtual std::shared_ptr<Command> Copy(const Coordinate& offset);

    Command() {};
    Command(CommandType type) : _type(type) {};
protected:
    CommandType _type;
    std::shared_ptr<Canvas> _canvas;
    std::shared_ptr<Canvas> _pre_canvas;
    bool _executed = false;
    bool _undoable = true;
    std::string _info;
};

class ShowCommand : public Command {
public:
    virtual void Execute() override;

    ShowCommand(std::shared_ptr<Canvas> canvas);
    virtual std::shared_ptr<Command> New() override;
    static std::shared_ptr<ShowCommand> New(std::shared_ptr<Canvas> canvas);
};

class LineCommand : public Command {
public:
    virtual void Execute() override;
    virtual void Execute(Coordinate) override;

    LineCommand(std::shared_ptr<Canvas> canvas, Coordinate& begin, Coordinate& end);
    virtual std::shared_ptr<Command> New() override;
    static std::shared_ptr<LineCommand> New(std::shared_ptr<Canvas> canvas, Coordinate& begin, Coordinate& end);
private:
    Coordinate _begin, _end;
};

class TextCommand : public Command {
public:
    virtual void Execute() override;
    virtual void Execute(Coordinate) override;

    TextCommand(std::shared_ptr<Canvas> canvas, Coordinate& offset, const std::string& text);
    virtual std::shared_ptr<Command> New() override;
    static std::shared_ptr<TextCommand> New(std::shared_ptr<Canvas> canvas, Coordinate& offset, const std::string& text);
private:
    Coordinate _offset;
    std::string _text;
};

class ColorCommand : public Command {
public:
    virtual void Execute() override;

    ColorCommand(std::shared_ptr<Canvas> canvas, int color, bool undoable);
    virtual std::shared_ptr<Command> New() override;
    static std::shared_ptr<ColorCommand> New(std::shared_ptr<Canvas> canvas, int color, bool undoable);
private:
    int _gray;
    int _pre_gray;
};

class MacroCommand : public Command {
public:
    virtual void Execute() override;
    virtual void Execute(Coordinate) override;
    virtual void SetExecuted(bool executed) override;

    std::string GetName() { return _name; }

    MacroCommand(std::shared_ptr<Canvas> canvas, const std::string& name, const Coordinate& offset, std::vector<std::shared_ptr<Command>>& commands);
    static std::shared_ptr<MacroCommand> New(std::shared_ptr<Canvas> canvas, const std::string& name, const Coordinate& offset, std::vector<std::shared_ptr<Command>>& commands);
    std::shared_ptr<Command> Copy() override;
    std::shared_ptr<Command> Copy(const Coordinate& offset) override;
    void SetOffset(const Coordinate& offset);
private:
    std::vector<std::shared_ptr<Command>> _commands;
    Coordinate _offset;
    std::string _name;
};

#endif