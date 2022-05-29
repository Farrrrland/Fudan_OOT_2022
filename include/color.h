#ifndef _COLOR_H_
#define _COLOR_H_

#include <memory>

class Color {
public:
    virtual int GetColor(int) = 0;
};

class _2Color : public Color {
public:
    virtual int GetColor(int color);
    
    static std::shared_ptr<Color> Instance();
private:
    static std::shared_ptr<Color> _instance;
};

class _256Color : public Color {
public:
    virtual int GetColor(int color);
    
    static std::shared_ptr<Color> Instance();
private:
    static std::shared_ptr<Color> _instance;
};

#endif