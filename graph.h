//
// Created by pledushka on 11.03.2022.
//

#include <iostream>

#ifndef GRAPHFORLAZARENCO_GRAPH_H
#define GRAPHFORLAZARENCO_GRAPH_H

// односвязный упорядоченный список дуг
// реализовать алгоритм сильных компонент


// удаление вершины

struct node {
    int name;
    node* next = nullptr;

    int color; // 1 - white, 2 - grey, 3 - black
    node* p = nullptr;
    int d;
    int f;

    node(int name) : name(name) {}
};

struct arc {
    arc* next = nullptr;
    node* nodeOut = nullptr;
    node* nodeIn = nullptr;

    arc(node *nodeOut, node *nodeIn) : nodeOut(nodeOut), nodeIn(nodeIn) {}
};

class graph {
    int time = 0;
    arc* head;
    node* nodes;


    int countNode () {
        node* helpNode = nodes;
        int count = 0;
        while (helpNode != nullptr) {
            count++;
            helpNode = helpNode->next;
        }
        return count;
    }


public:


    graph() {
        head = nullptr;
        nodes = nullptr;
    }

    graph(const graph &g) {
        head = nullptr;
        nodes = nullptr;

        node *gNode = g.nodes;
        node *h;

        while (gNode != nullptr) {
            h = addNode(gNode->name);
            h->p = gNode->p;
            h->f = gNode->f;
            h->d = gNode->d;
            h->color = gNode->color;

            gNode = gNode->next;
        }

        arc *gArc = g.head;

        while (gArc != nullptr) {
            addArc(gArc->nodeIn->name, gArc->nodeOut->name);

            gArc = gArc->next;
        }
    }


    ~graph() {
        arc *helpArc;
        node *helpNode;

        while (head != nullptr) {
            helpArc = head;
            head = head->next;
            delete helpArc;
        }

        while (nodes != nullptr) {
            helpNode = nodes;
            nodes = nodes->next;
            delete helpNode;
        }
    }

    node *addNode(int name) {
//        if (name >= 0) {
//            node* help = nodes;
//            node* helpPrev;
//
//            while (help != nullptr) { // проверка, что ноты ещё нет
//                if (help->name == name) {
//                    return nullptr;
//                }
//
//                helpPrev = help;
//                help = help->next;
//            }
//
//            help = new node(name);
//            if (nodes != nullptr) {
//                helpPrev->next = help;
//            } else {
//                nodes = help;
//            }
//
//            return help;
//        } else {
//            return nullptr;
//        }
        if (name >= 0) {
            if (nodes == nullptr) {
                nodes = new node(name);
                return nodes;
            }  else {
                // упорядоченная вставка
                node* prevHelp = nullptr;
                node* help = nodes;

                while (help != nullptr && help->name < name) { // идём по nodeOut
                    prevHelp = help;
                    help = help->next;
                }


                // head смотрит на следующий элемент, после вставляемого
                if (help != nullptr  && help->name == name) {
                    std::cout << "Node " << name << " already exist" << std::endl;
                    return nullptr;
                }

                node* newNode = new node(name);

                if (prevHelp == nullptr) {
                    nodes = newNode;
                } else {
                    prevHelp->next = newNode;
                }

                newNode->next = help;
                return newNode;
            }
        } else {
            return nullptr;
        }
    }

    int delNode(int name) {
        if (name < 0) {
            std::cout << "Invalid node name " << std::endl;
            return false;
        }

        node *nodeOut = getNode(name);

        if (nodeOut == nullptr) {
            std::cout << "Node does not exist" << std::endl;
            return false;
        }

        arc* helpArc = head;

        while (helpArc != nullptr) {
            delArc(helpArc->nodeOut->name, name);
            delArc(name, helpArc->nodeIn->name);
            helpArc = helpArc->next;
        }

        node* helpNode = nodes;
        node* helpNodePrev = nullptr;

        while (helpNode != nullptr) { // проверка, что ноты ещё нет
            if (helpNode->name == name) {
                break;
            }
            helpNodePrev = helpNode;
            helpNode = helpNode->next;
        }

        if (helpNodePrev == nullptr) {
            nodes = helpNode->next;
        } else {
            helpNodePrev->next = helpNode->next;
        }
        delete helpNode;
        return true;

    }

    int isNode(int name) {
        node* help = nodes;

        while (help != nullptr) { // проверка, что ноты ещё нет
            if (help->name == name) {
                return true;
            }
        }
        return false;
    }


    node *getNode(int name) {
        node* help = nodes;

        while (help != nullptr) { // проверка, что ноты ещё нет
            if (help->name == name) {
                return help;
            }
            help = help->next;
        }
        return nullptr;
    }

    int addArc(int out, int in) { //

        if (out < 0 || in < 0) {
            std::cout << "Invalid node name" << std::endl;
            return -1;
        }

        node *nodeOut = getNode(out);

        if (nodeOut == nullptr) {
            nodeOut = addNode(out);
        }

        node *nodeIn = getNode(in);

        if (nodeIn == nullptr) {
            nodeIn = addNode(in);
        }



        if (head == nullptr) {
            head = new arc(nodeOut, nodeIn);
            return 1;
        }  else {
            // упорядоченная вставка
            arc* prevHelp = nullptr;
            arc* help = head;

            while (help != nullptr && help->nodeOut < nodeOut) { // идём по nodeOut
                prevHelp = help;
                help = help->next;
            }

            while (help != nullptr && help->nodeIn < nodeIn && help->nodeOut == nodeOut) { // идём по nodeIn
                prevHelp = help;
                help = help->next;
            }

            // head смотрит на следующий элемент, после вставляемого
            if (help != nullptr && help->nodeOut == nodeOut && help->nodeIn == nodeIn) {
                std::cout << "Arc " << out << " --> " << in << " already exist" << std::endl;
                return 0;
            }

            arc* newArc = new arc(nodeOut, nodeIn);

            if (prevHelp == nullptr) {
                head = newArc;
            } else {
                prevHelp->next = newArc;
            }

            newArc->next = help;
            return 1;
        }

    }

    void print() {
        arc* help = head;
        while (help != nullptr) {
            std::cout << help->nodeOut->name<< " --> " << help->nodeIn->name << std::endl;
            help = help->next;
        }
    }

    int delArc(int out, int in){

        if (out < 0 || in < 0) {
            std::cout << "Invalid node name" << std::endl << std::endl;
            return -1;
        }

        node *nodeOut = getNode(out);
        node *nodeIn = getNode(in);

        if (nodeOut == nullptr) {
            std::cout << "Node " << out << " dose not exist" << std::endl;
            return false;
        }

        if (nodeIn == nullptr) {
            std::cout << "Node " << in << " dose not exist" << std::endl;
            return false;
        }

        if (head == nullptr) {
            return -1;
        }  else {
            // упорядоченная вставка
            arc* prevHelp = nullptr;
            arc* help = head;

            while (help != nullptr && help->nodeOut < nodeOut) { // идём по nodeOut
                prevHelp = help;
                help = help->next;
            }

            while (help != nullptr && help->nodeIn < nodeIn && help->nodeOut == nodeOut) { // идём по nodeIn
                prevHelp = help;
                help = help->next;
            }

            // head смотрит на следующий элемент, после вставляемого
            if (help != nullptr && help->nodeOut == nodeOut && help->nodeIn == nodeIn) {

                // начало списка
                if (prevHelp == nullptr) {
                    head = help->next;
                } else {
                    // середина списка
                    prevHelp->next = help->next;
                }

                // конец списка
                delete help;
                return 1;
            }

            std::cout << "Arc " << out<< " --> " << in << " dose not exist" << std::endl;
            return 0;
        }

    }

    bool searchArc(int out, int in) {
        if (out < 0 || in < 0) {
            std::cout << "Invalid node name" << std::endl;
            return false;
        }

        node *nodeOut = getNode(out);
        node *nodeIn = getNode(in);

        if (nodeOut == nullptr) {
            //std::cout << "Node " << out << " dose not exist" << std::endl;
            return false;
        }

        if (nodeIn == nullptr) {
            //std::cout << "Node " << in << " dose not exist" << std::endl;
            return false;
        }


        if (head == nullptr) {
            return false;
        }  else {
            // упорядоченная вставка
            arc* prevHelp = nullptr;
            arc* help = head;

            while (help != nullptr && help->nodeOut < nodeOut) { // идём по nodeOut
                prevHelp = help;
                help = help->next;
            }

            while (help != nullptr && help->nodeIn->name < nodeIn->name && help->nodeOut->name == nodeOut->name) { // идём по nodeIn
                prevHelp = help;
                help = help->next;
            }

            // head смотрит на следующий элемент, после вставляемого
            if (help != nullptr && help->nodeOut->name == nodeOut->name && help->nodeIn->name == nodeIn->name) {
                return true;
            }

            return false;
        }
    }
///----------------------------------------------------------------
    // 1 - white, 2 - grey, 3 - black

    void dfsV (node *u) {
        time++;
        u->d = time;
        u->color = 2; // grey

        // обход вершин, в которую идёт дуга из вершины u
        arc* helpArc = head;
        while (helpArc != nullptr) {
            if (helpArc->nodeOut == u) {
                if (helpArc->nodeIn->color == 1) { // white?
                    helpArc->nodeIn->p = u;
                    dfsV(helpArc->nodeIn);
                }
            }
            helpArc = helpArc->next;
        }

        u->color = 3; // black
        time++;
        u->f = time;
    }

    void dfs() {
        node* helpNode = nodes;

        while (helpNode != nullptr) {
            helpNode->color = 1; // white
            helpNode->p = nullptr;

            helpNode = helpNode->next;
        }

        time = 0;

        helpNode = nodes;

        while (helpNode != nullptr) {
            if (helpNode->color == 1) { // white?
                dfsV(helpNode);
            }

            helpNode = helpNode->next;
        }
    }


    void ssc () {
        dfs();
        // транспонированная матрица
        graph gt(*this);
        // дфс для транспонир матрицы
        gt.dfs();
        // вывод



        node* helpNode = gt.nodes;

        while (helpNode != nullptr) {
            if (helpNode->p != nullptr) {
                std::cout << helpNode->name << " p: " << helpNode->p->name << "     f:  " << helpNode->f;
            } else {
                std::cout << helpNode->name << " p: null" << "  f:  " <<  helpNode->f;
            }
            std::cout << std::endl;
            helpNode = helpNode->next;
        }

        std::cout << std::endl;

        //сильные компоненты
        node *n1[countNode()];


        node* h= gt.nodes;

        for (int i = 0; i < countNode(); ++i) {
            n1[i] = h;
            h = h->next;
        }

        //сортировка :)

        for (int i = 0; i < countNode()-1; i++)
            for (int j = 0; j < countNode()-i-1; j++)
                if (n1[j]->f > n1[j+1]->f) {
                    node temp = *n1[j];
                    *n1[j] = *n1[j+1];
                    *n1[j+1] = temp;
                }


        for (int i = 0; i < countNode(); ++i) {

            if (n1[i]->p != nullptr) {
                std::cout << n1[i]->name;
            } else {
                std::cout << n1[i]->name;
            }
            std::cout << std::endl;
            if (i + 1 < countNode()) {
                if (n1[i]->d < n1[i + 1]->d) {
                    std::cout << std::endl;
                }
            }
        }
    }


};


#endif //GRAPHFORLAZARENCO_GRAPH_H
