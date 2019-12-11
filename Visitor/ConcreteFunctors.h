//
// Created by Ilya Gridasov on 10/12/2019.
//

#ifndef VISITOR_CONCRETEFUNCTORS_H
#define VISITOR_CONCRETEFUNCTORS_H

#include <iostream>
#include "functor.h"
#include "Accepter.h"
#include "Visitor.h"

class StatsParagraphFunctor: public FunctorImpl<int, Visitor*, Accepter*, int> {
public:
    typedef Paragraph AccepterType;
    typedef DocStats VisitorType;

    StatsParagraphFunctor() = default;
    [[nodiscard]] StatsParagraphFunctor* Clone() const override {
        return new StatsParagraphFunctor(*this);
    }
    int operator()(Visitor* v, Accepter* a, int args_count) override {
        a->Accept(*v);
        std::cout << "Stats Paragraph Functor done" << std::endl;
        return 0;
    }
private:
};

class StatsImageFunctor: public FunctorImpl<int, Visitor*, Accepter*, int> {
public:
    typedef Image AccepterType;
    typedef DocStats VisitorType;

    StatsImageFunctor() = default;
    [[nodiscard]] StatsImageFunctor* Clone() const override {
        return new StatsImageFunctor(*this);
    }
    int operator()(Visitor* v, Accepter* a, int args_count) override {
        a->Accept(*v);
        std::cout << "Stats Image Functor done" << std::endl;
        return 1;
    }
private:
};

#endif //VISITOR_CONCRETEFUNCTORS_H
