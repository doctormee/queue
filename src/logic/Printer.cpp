#include "Printer.h"
#include <iostream>
#include "Rule.h"
#include "ConjunctionPredicate.h"
#include "Term.h"
#include "DisjunctionPredicate.h"
#include "NegationPredicate.h"
#include "ImplicationPredicate.h"
#include "Specialist.h"
#include "Constants.h"
void Printer::visit(const Term &term) {
    Field field = term.get_field();
    Sign sign = term.get_sign();
    auto value = term.get_value();
    switch (field) {
        case Field::ALL: {
            out += "ALL ";
            return;
        }
        case Field::AGE: {
            out += "age ";
            break;
        }
        case Field::HEIGHT: {
            out += "height ";
            break;
        }
        case Field::WEIGHT: {
            out += "weight ";
            break;
        }
        case Field::GENDER: {
            out += "gender ";
            break;
        }
        default: {
            throw std::logic_error("Некорректное условие!");
        }
    }
    switch (sign) {
        case Sign::LESS: {
            out += "< ";
            break;
        }
        case Sign::LESSEQ: {
            out += "<= ";
            break;
        }
        case Sign::EQ: {
            out += "= ";
            break;
        }
        case Sign::MOREEQ: {
            out += ">= ";
            break;
        }
        case Sign::MORE: {
            out += "> ";
            break;
        }
        case Sign::NOTEQ: {
            out += "!= ";
            break;
        }
        default: {
            throw std::logic_error("Некорректное условие!");
        }
    }
    if (field == Field::GENDER) {
        if (value == 'M') {
            out += 'M';
        } else if (value == 'F') {
            out += 'F';
        } else {
            throw std::logic_error("Некорректное условие!");
        }
    } else {
        out += std::to_string(term.get_value());
    }
}
void Printer::visit(const ConjunctionPredicate &pred) {
    for (auto i = pred.begin(); i != pred.end(); ++i) {
        out += "( ";
        (*i)->accept(*this);
        out += " ) ";
        if ( (i + 1) != pred.end()) {
            out += "& ";
        }
    }
}
void Printer::visit(const DisjunctionPredicate &pred) {
    for (auto i = pred.begin(); i != pred.end(); ++i) {
        out += "( ";
        (*i)->accept(*this);
        out += " ) ";
        if ( (i + 1) != pred.end()) {
            out += "| ";
        }
    }
}
void Printer::visit(const NegationPredicate &pred) {
    out += "!( ";
    pred.predicate().accept(*this);
    out += " ) ";
}
void Printer::visit(const ImplicationPredicate &pred) {
    for (auto i = pred.begin(); i != pred.end(); ++i) {
        out += "( ";
        (*i)->accept(*this);
        out += " ) ";
        if ( (i + 1) != pred.end()) {
            out += "-> ";
        }
    }
}
void Printer::flush() {
    out.clear();
}
std::string Printer::str() {
    return out;
}
void Printer::visit(const Specialist &spec) {
    bool correct = false;
    out = spec.get_name() + " " + spec.get_surname() + " ";
    for (auto j = 0; j < spec.size(); ++j) {
        correct = true;
        out += spec.get_service(j) + " ";
    }
    if (!correct) {
        throw std::logic_error("Невозможный специалист!");
    }
    out.pop_back();
    out += '\n';
}
