//
// Created by Ilya Gridasov on 10/12/2019.
//

#ifndef VISITOR_VISITOR_H
#define VISITOR_VISITOR_H

#include <iostream>
#include "Accepter.h"
#include "functor.h"

class Accepter;
class Paragraph;
class Image;

class Visitor { //! Visitor
public:
    virtual void Visit(const Paragraph&) = 0;
    virtual void Visit(const Image&) = 0;
};

#endif //VISITOR_VISITOR_H
