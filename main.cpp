#include <iostream>
#include "graph.h"

int main() {
    graph a;

//    for(int i = 8; i > 0; i--) {
//        a.addNode(i);
//    }

//a.addArc(1,2);
//a.addArc(1,3);
//a.addArc(1,4);
//a.addArc(3,5);

    a.addArc(1,2);
    a.addArc(2,3);
    a.addArc(3,4);
    a.addArc(4,3);
    a.addArc(4,8);
    a.addArc(8,4);
    a.addArc(8,7);
    a.addArc(6,7);
    a.addArc(7,6);
    a.addArc(7,3);
    a.addArc(2,6);
    a.addArc(2,5);
    a.addArc(5,1);
    a.addArc(5,6);
//
//    a.addArc(1,2);
//    a.addArc(3,1);
//    a.addArc(2,3);
//    a.addArc(4,5);
//    a.addArc(5,4);
//    a.addArc(3,4);
//    a.addArc(2,4);
//    a.addArc(2,6);
//    a.addArc(5,8);
//    a.addArc(8,8);
//    a.addArc(7,8);
//    a.addArc(6,7);
//    a.addArc(7,6);

    a.ssc();

//a.BFS(a.getNode(1));

    return 0;
}
