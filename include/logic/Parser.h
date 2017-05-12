#pragma once

class Parser {
/* GRAMMAR: 
 * IMP = DISJ {'->' IMP}
 * DISJ = CONJ {'|' DISJ} 
 * CONJ = NEG {'&' CONJ}
 * NEG = {!}PAR
 * PAR = (DISJ) | VAR
 * VAR = {a..z | A..Z}
 */
private:
    int t;
    void gt() {
        do {
            t = std::cin.get();
        } 
        while ( isspace(t));
    }
public:
    std::shared_ptr<Formula> var() {
        //std::cout << "VAR" << std::endl;
        if (((t >= 'a') && (t <= 'z')) || ((t >= 'A') && (t <= 'Z'))) {
            std::shared_ptr<VariableFormula> ret(new VariableFormula(t));
            gt();
            return ret;
        }
        else {
            throw ParseException("Incorrect!");
        }
    }
    std::shared_ptr<Formula> par() {
        if (t != '(') {
            return var();
        }
        else {
            gt();
            auto ret = disj();
            if (t != ')') {
                throw ParseException("Incorrect!");
            }
            gt();
            return ret;
        }
    }
    std::shared_ptr<Formula> neg() {
        //std::cout << "NEG" << std::endl;
        if (t == '!') { 
            gt();
            std::shared_ptr<NegationFormula> ret(new NegationFormula(neg()));
            return ret;
        }
        auto ret = par();
        return ret;
    }
    std::shared_ptr<Formula> conj() {
        //std::cout << "CONJ" << std::endl;
        auto tmp = neg();
        if (t == '&') {
            std::shared_ptr<ConjunctionFormula> ret(new ConjunctionFormula());
            ret->add(tmp);
            while (t == '&') {
                gt();
                ret->add(conj());
            }
            return ret;
        }
        else {
            return tmp;
        }
    }
    std::shared_ptr<Formula> disj() {
        //std::cout << "DISJ" << std::endl;
        auto tmp = conj();
        if (t == '|') {
            std::shared_ptr<DisjunctionFormula> ret(new DisjunctionFormula());
            ret->add(tmp);
            while (t == '|') {
                gt();
                ret->add(disj());
            }
            return ret;
        }
        else {
            return tmp;
        }
    }
    std::shared_ptr<Formula> parse() {
        gt();
        auto ret = disj();
        if (!std::cin.eof()) {
            throw ParseException("Incorrect!");
        }
        return ret;    
    }
};