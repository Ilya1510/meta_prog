//
// Created by Ilya Gridasov on 10/12/2019.
//

#ifndef VISITOR_FUNCTOR_H
#define VISITOR_FUNCTOR_H


#include <memory>
#include "typelist.h"

template <typename R, class... Args>
class FunctorImpl;

template <typename R, class... Args>
class Functor {
public:
    Functor() = default;
    Functor(const Functor&) = default;
    Functor& operator=(const Functor&) = default;
    explicit Functor(std::shared_ptr<FunctorImpl<R, Args...>> spImpl)
            : spImpl_(spImpl) {};

    R operator()(Args... args) {
        return (*spImpl_)(args...);
    }
    virtual void CheckArgs(Args... args) {
        return spImpl_->CheckArgs(args...);
    }

    template <class Fun>
    Functor (const Fun& fun, bool fromFunction);
private:
    typedef FunctorImpl<R, Args...> Impl;
    std::shared_ptr<Impl> spImpl_;
};

template <typename R, class... Args>
class FunctorImpl
{
public:
    virtual R operator()(Args... args) = 0;
    virtual FunctorImpl* Clone() const = 0;
    virtual void CheckArgs(Args... args) = 0;
    virtual ~FunctorImpl() = default;
};

//! Example - FunctorHandler
template <typename Fun, class ResultType, class... Args>
class FunctorHandler: public FunctorImpl<
        ResultType,
        Args...> {
public:
    FunctorHandler(const Fun& fun) : fun_(fun) {}
    FunctorHandler* Clone() const {
        return new FunctorHandler(*this);
    }
    ResultType operator()(Args... args){
        return fun_(args...);
    }
    void CheckArgs(Args... args) {}
private:
    Fun fun_;
};

template <typename R, class... Args>
template <typename Fun>
Functor<R, Args...>::Functor(const Fun& fun, bool fromFunction)
        : spImpl_(new FunctorHandler<Fun, R, Args...>(fun)) {
}


#endif //VISITOR_FUNCTOR_H
