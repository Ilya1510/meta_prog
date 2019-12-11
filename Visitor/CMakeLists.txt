cmake_minimum_required(VERSION 3.15)
project(Visitor)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp typelist.h functor.h Visitor.h Accepter.h VisitFactory.h ConcreteFunctors.h)