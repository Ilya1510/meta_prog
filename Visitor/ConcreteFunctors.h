//
// Created by Ilya Gridasov on 10/12/2019.
//

#ifndef VISITOR_CONCRETEFUNCTORS_H
#define VISITOR_CONCRETEFUNCTORS_H

#include <iostream>
#include "functor.h"
#include "Accepter.h"
#include "Visitor.h"
#include <cassert>

class DocStats;

class StatsParagraphFunctor: public FunctorImpl<
        int,
        const DocStats&,
        const Paragraph&,
        int> {
public:
    StatsParagraphFunctor() = default;
    [[nodiscard]] StatsParagraphFunctor* Clone() const override {
        return new StatsParagraphFunctor(*this);
    }
    int operator()(const DocStats& docStats, const Paragraph& paragraph, int args_count) override {
        std::cout << "Stats Paragraph Functor done" << std::endl;
        return 0;
    }
    void CheckArgs(const DocStats& docStats, const Paragraph& paragraph, int args_count) override {
        if (args_count != 0) {
            std::cout << "Args count for StatsParagraphFunctor should be 0" << std::endl;
            assert(args_count == 0);
        }
    }
private:
};

class StatsImageFunctor: public FunctorImpl<
        int,
        const DocStats&,
        const Image&,
        int> {
public:
    StatsImageFunctor() = default;
    [[nodiscard]] StatsImageFunctor* Clone() const override {
        return new StatsImageFunctor(*this);
    }
    int operator()(const DocStats& docStats, const Image& image, int args_count) override {
        std::cout << "Stats Image Functor done" << std::endl;
        return 1;
    }
    void CheckArgs(const DocStats& docStats, const Image& image, int args_count) override {
        if (args_count != 0) {
            std::cout << "Args count for StatsImageFunctor should be 0" << std::endl;
            assert(args_count == 0);
        }
    }
private:
};

#endif //VISITOR_CONCRETEFUNCTORS_H
