#include <iostream>

#include "functor.h"
#include "typelist.h"
#include "Accepter.h"
#include "VisitFactory.h"
#include "ConcreteFunctors.h"

#include <iostream>
// Для небольших программ на С++ можно применять
// директиву using
using namespace std;
// Определяем тестируемый функтор
struct TestFunctor
{
    void operator()(int i, double d) {
        cout << "TestFunctor::operator()(" << i << ", " << d << ") called. \n";
    }
};

int main() {
    //! Test for Functor usage with functions
    TestFunctor f;
    Functor<void, int, double> cmd(f, true);
    cmd(4, 4.5); // TestFunctor::operator()(4, 4.5) called.

    //! Test for Visitor Architecture usage
    Accepter** arr = new Accepter*[5];
    arr[0] = new Image();
    arr[1] = new Paragraph("hello world!");
    arr[2] = new Paragraph("Hi! There!");
    arr[3] = new Image();
    arr[4] = new Image();

    DocStats statsVisitor;
    for (int i = 0; i < 5; ++i) {
        arr[i]->Accept(statsVisitor);
    }
    statsVisitor.DisplayStats(); // Words count = 4 Images count = 3

    //! Test for VisitFactory
    VisitFactory<Typelist<DocStats>,
                 Typelist<Paragraph, Image>,
                 Typelist<StatsParagraphFunctor, StatsImageFunctor>> visitFactory;

    visitFactory.Go(&statsVisitor, arr[3], 0);
    statsVisitor.DisplayStats(); // Words count = 4 Images count = 4

    visitFactory.Go(&statsVisitor, arr[2], 0);
    statsVisitor.DisplayStats(); // Words count = 6 Images count = 3
}