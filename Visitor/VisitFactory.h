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
    template <class... Args>
    auto Go(Visitor*, Accepter*, int args_count, Args... args);
};

template <class... Args>
class FindFunctor {
public:
    template <class V, class A>
    static auto find(V v, A a) {
        return Functor<int, Visitor*, Accepter*, int>();
    }
};

template <class F, class... Args>
class FindFunctor<Typelist<F, Args...>> {
public:
    template <class V, class A>
    static auto find(V* v, A *a) {
        if (dynamic_cast<typename F::VisitorType*>(v) && dynamic_cast<typename F::AccepterType*>(a)) {
            return Functor<int, Visitor*, Accepter*, int>(std::shared_ptr<F>(new F()));
        } else {
            return FindFunctor<Typelist<Args...>>::find(v, a);
        }
    }
};

template <class VisitorsList, class AcceptersList, class FunctorsList>
template <class... Args>
auto VisitFactory<VisitorsList, AcceptersList, FunctorsList>::Go(Visitor* v, Accepter* a, int args_count, Args... args) {
    auto foundFunctor = FindFunctor<FunctorsList>::find(v, a);
    return foundFunctor(v, a, args_count, args...);
}

#endif //VISITOR_VISITFACTORY_H
