//
// Created by Ilya Gridasov on 10/12/2019.
//

#ifndef VISITOR_VISITOR_H
#define VISITOR_VISITOR_H

#include <iostream>
#include "Accepter.h"
#include "functor.h"

template <class R, class... Args>
class Accepter;
class Paragraph;
class Image;

template <class R, class... Args>
class Visitor { //! Visitor
public:
    virtual R Visit(const Paragraph&, Args... args) = 0;
    virtual R Visit(const Image&, Args... args) = 0;
};

#endif //VISITOR_VISITOR_H
