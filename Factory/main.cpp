#include <iostream>
#include <string>
#include <typeinfo>

// ------------------------------------------ Typelist https://habr.com/ru/post/220217/
namespace internal {
    struct Void{};
} // internal

template<typename ...Args>
struct Typelist{};

// ------------------------------------------ TypeExists in Typelist
template <typename TList, typename T> struct TypeExists;

template <typename T, typename... Tail>
struct TypeExists<Typelist<T, Tail...>, T> {
    static constexpr bool result = true;
};

template <typename Head, typename... Tail, typename T>
struct TypeExists<Typelist<Head, Tail...>, T> {
    static constexpr bool result = TypeExists<Typelist<Tail...>, T>::result;
};

template <typename T>
struct TypeExists<Typelist<>, T> {
    static constexpr bool result = false;
};

// ------------------------------------------ FindDerived in Typelist
template <typename TList, typename T> struct FindDerived;

template <typename F, typename... Tail, typename T>
struct FindDerived<Typelist<F, Tail...>, T> {
    typedef std::conditional_t<std::is_base_of_v<T, F>,
            F, typename FindDerived<Typelist<Tail...>, T>::result> result;
};

template <typename T>
struct FindDerived<Typelist<>, T> {
    typedef internal::Void result;
};

// end of Typelist

// --------------------------------------------- Factory

template <class T>
struct ConcreteFactory;

template <class ... ListArgs>
struct ConcreteFactory<Typelist<ListArgs...>> {
    template <class U>
    U* Get() {
        typedef typename FindDerived<Typelist<ListArgs...>, U>::result T;
        return new T();
    }
};

// --------------------------------------------- FindInList

template <class F, class ... Args>
struct FindInList {
    typedef ConcreteFactory<Typelist<internal::Void>> result;
};

template <class F, class ... ListArgs, class ... Args>
struct FindInList<F, Typelist<ListArgs...>, Args...> {
    typedef std::conditional_t<TypeExists<Typelist<ListArgs...>, F>::result,
            ConcreteFactory<Typelist<ListArgs...>>,
            typename FindInList<F, Args...>::result> result;
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
    auto GreenFactory = new MyFactoryHierarchy::GetConcreteFactory<GreenBeer>::result;
    Beer* green_beer = GreenFactory->Get<Beer>();
    green_beer->say_name(); // I am Green Beer
    Apple* green_apple = GreenFactory->Get<Apple>();
    green_apple->say_name(); // I am Green Apple
    return 0;
}