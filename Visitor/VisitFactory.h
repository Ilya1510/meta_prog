//
// Created by Ilya Gridasov on 10/12/2019.
//

#ifndef VISITOR_VISITFACTORY_H
#define VISITOR_VISITFACTORY_H

#include "typelist.h"
#include "Visitor.h"
#include "Accepter.h"
#include "ConcreteFunctors.h"

template <class VisitorsList, class AcceptersList, class FunctorsList>
class VisitFactory {
public:
    template <class... Args, class R, class... ArgsVA>
    auto Go(Visitor<R, ArgsVA...>*, Accepter<R, ArgsVA...>*, int args_count, Args... args);
};

template <class VisitorsList, class AcceptersList, class FunctorsList>
template <class... Args, class R, class... ArgsVA>
auto VisitFactory<VisitorsList, AcceptersList, FunctorsList>::Go(
        Visitor<R, ArgsVA...>* v,
        Accepter<R, ArgsVA...>* a,
        int args_count, Args... args) {
    return a->Accept(*v, args_count, args...);
}

#endif //VISITOR_VISITFACTORY_H
