#pragma once
#include <string>
#include <iostream>
#include "UI.h"
class MainController;

class StreamUI: public UI {
    const std::string ERR_MSG = "Неожиданный конец ввода!";
protected:
    std::istream &input_stream;
    std::ostream &output_stream;
public:
    StreamUI(std::istream &, std::ostream &);
    StreamUI(std::istream &, std::ostream &, MainController *);
    void msg(std::string) override;
    void err(std::string) override;
    bool inp(std::string &) override;
    bool inp(int &) override;
    bool inp(char &) override;
    void ignore() override;
};