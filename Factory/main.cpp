#include <iostream>
#include <string>
#include <typeinfo>

// Typelist https://habr.com/ru/post/220217/
namespace internal {
    struct Void{};
} // internal

template<typename ...Args>
struct Typelist
{
    typedef internal::Void Head;
    typedef internal::Void Tail;
};

typedef Typelist<> EmptyTypeList;

template<typename H, typename ...T>
struct Typelist<H, T...>
{
    typedef H Head;
    typedef Typelist<T...> Tail;
};
// end of Typelist

// --------------------------------------------- Factory

template <class T>
struct ConcreteFactory {
    template <class U>
    U* Get() {
        return new T();
    }
};

// --------------------------------------------- FindInList

template <class F, class ... Args>
struct FindInList {
    typedef ConcreteFactory<internal::Void> result;
};

template <class F, class T, class ... ListArgs, class ... Args>
struct FindInList<F, Typelist<T, ListArgs...>, Args...> {
    typedef std::conditional_t <std::is_same_v<F, T>,
            ConcreteFactory<T>,
            typename FindInList<F, Typelist<ListArgs...>, Args...>::result> result;
};

template <class F, class ... Args>
struct FindInList<F, Typelist<>, Args...> {
    typedef typename FindInList<F, Args...>::result result;
};

// --------------------------------------------- GetAbstractFactory

template<size_t c1, size_t c2, typename ...Args>
struct GetAbstractFactory
{
    template <class P>
    using GetConcreteFactory = FindInList<P, Args...>;
};

// ------------------------------------------- Example

struct Apple {
    virtual void say_name() {
        std::cout << "I am Apple" << std::endl;
    }
};

struct GreenApple : Apple {
    virtual void say_name() {
        std::cout << "I am Green Apple" << std::endl;
    }};

struct Beer {
    virtual void say_name() {
        std::cout << "I am Beer" << std::endl;
    }};

struct GreenBeer : Beer {
    virtual void say_name() {
        std::cout << "I am Green Beer" << std::endl;
    }};

using MyFactoryHierarchy = GetAbstractFactory<2,2,
    Typelist<Apple, Beer>,
    Typelist<GreenApple, GreenBeer>>;


int main() {
    auto MyFactory = new MyFactoryHierarchy::GetConcreteFactory<GreenBeer>::result;
    //std::cout << typeid(*MyFactory).name() << std::endl;
    Beer* a = MyFactory->Get<Beer>();
    a->say_name();
    return 0;
}