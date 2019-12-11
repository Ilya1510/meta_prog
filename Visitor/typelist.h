//
// Created by Ilya Gridasov on 10/12/2019.
//

#include <typeinfo>

#ifndef VISITOR_TYPELIST_H
#define VISITOR_TYPELIST_H

// ------------------------------------------ Typelist https://habr.com/ru/post/220217/
namespace internal {
    struct Void{};
    struct NullType{};
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

////////////////////////////////////////////////////////////////////////////////
// TypeAt
// @param TList     Typelist
// @param index     position of Type to get
// ::result         Type from Typelist at specified index.
////////////////////////////////////////////////////////////////////////////////
template <typename TList, unsigned int index> struct TypeAt;

template <>
struct TypeAt<Typelist<>, 0> {
    using result = internal::NullType;
};

template <typename Head, typename... Tail>
struct TypeAt<Typelist<Head, Tail...>, 0> {
    using result = Head;
};

template <typename Head, typename... Tail, unsigned int i>
struct TypeAt<Typelist<Head, Tail...>, i> {
    using result = typename TypeAt<Typelist<Tail...>, i - 1>::result;
};

// end of Typelist

#endif //VISITOR_TYPELIST_H
