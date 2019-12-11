//
// Created by Ilya Gridasov on 10/12/2019.
//

#ifndef VISITOR_ACCEPTER_H
#define VISITOR_ACCEPTER_H

#include "Visitor.h"
#include "ConcreteFunctors.h"
#include <string>
#include <utility>

template <class R, class... Args>
class Accepter { //! Accepter
public:
    virtual R Accept(Visitor<R, Args...>&, Args... args) = 0;
};

class Paragraph : public Accepter<int, int> { //! Concrete Accepter
public:
    int Accept(Visitor<int, int>& v, int args_count) override {
        return v.Visit(*this, args_count);
    }
    explicit Paragraph(std::string text)
        : text_(std::move(text)) {
    }
    unsigned int words_count() const {
        unsigned int cur_count = 0;
        char prev = ' ';
        for (auto c: text_) {
            if (c != ' ' && prev == ' ') {
                cur_count += 1;
            }
            prev = c;
        }
        return cur_count;
    }

private:
    std::string text_;
};

class Image : public Accepter<int, int> { //! Concrete Accepter
public:
    int Accept(Visitor<int, int>& v, int args_count) override {
        return v.Visit(*this, args_count);
    }
};

class DocStats : public Visitor<int, int> { //! Concrete Visitor
public:
    int Visit(const Paragraph& paragraph, int args_count) override {
        words_count_ += paragraph.words_count();
        //auto foundFunctor = FindFunctor<FunctorsList, int, Visitor*, Accepter*, int, Args...>::find(v, a);
        auto functor = Functor<int, const DocStats&, const Paragraph&, int>(std::shared_ptr<StatsParagraphFunctor>(new StatsParagraphFunctor()));
        functor.CheckArgs(*this, paragraph, args_count);
        return functor(*this, paragraph, args_count);
    }

    int Visit(const Image& image, int args_count) override {
        images_count_ += 1;
        auto functor = Functor<int, const DocStats&, const Image&, int>(std::shared_ptr<StatsImageFunctor>(new StatsImageFunctor()));
        functor.CheckArgs(*this, image, args_count);
        return functor(*this, image, args_count);
    }

    void DisplayStats() const {
        std::cout << "Words count = " << words_count_ << " " <<
                  "Images count = " << images_count_ << std::endl;
    }

private:
    unsigned int words_count_ = 0;
    unsigned int images_count_ = 0;
};


#endif //VISITOR_ACCEPTER_H
