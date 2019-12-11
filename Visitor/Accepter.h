//
// Created by Ilya Gridasov on 10/12/2019.
//

#ifndef VISITOR_ACCEPTER_H
#define VISITOR_ACCEPTER_H

#include "Visitor.h"
#include <string>
#include <utility>

class Visitor;

class Accepter { //! Accepter
public:
    virtual void Accept(Visitor&) = 0;
};

class Paragraph : public Accepter { //! Concrete Accepter
public:
    void Accept(Visitor& v) override {
        return v.Visit(*this);
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

class Image : public Accepter { //! Concrete Accepter
public:
    void Accept(Visitor& v) override {
        return v.Visit(*this);
    }
};

class DocStats : public Visitor { //! Concrete Visitor
public:
    void Visit(const Paragraph& paragraph) override {
        words_count_ += paragraph.words_count();
    }

    void Visit(const Image&) override {
        images_count_ += 1;
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
