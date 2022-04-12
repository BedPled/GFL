#include <iostream>
#include "graph.h"

int main() {
    graph a;

    a.addArc(1,2);
    a.addArc(3,1);
    a.addArc(2,3);
    a.addArc(4,5);
    a.addArc(5,4);
    a.addArc(3,4);
    a.addArc(2,4);
    a.addArc(2,6);
    a.addArc(5,8);
    a.addArc(8,8);
    a.addArc(7,8);
    a.addArc(6,7);
    a.addArc(7,6);

    a.ssc();



    return 0;
}
