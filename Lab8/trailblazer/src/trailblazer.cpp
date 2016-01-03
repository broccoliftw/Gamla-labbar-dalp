#include "costs.h"
#include "trailblazer.h"
#include <algorithm>
#include "pqueue.h"
#include <exception>
using namespace std;
bool found;

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    for (Node *node : graph.getNodeSet()){//resets whole graph
        node->resetData();
    }
    found = false;
    path = depthFirstRecursive(graph, start, end, path);

    cout << (path.size()) << endl;
    return path;
}

vector<Node*> depthFirstRecursive(BasicGraph& graph, Vertex* start, Vertex* end, vector<Vertex*> &path){
    start->setColor(GREEN);
    path.push_back(start);

    for (Node *node : graph.getNeighbors(start)){

        if (node == end){
            node->setColor(GREEN);
            found = true;
            path.push_back(node);
            return path;
        }
        if (node->getColor() == WHITE){

            depthFirstRecursive(graph,node,end, path);
            if (found){
                return path;
            }

            node->setColor(GRAY);
            path.pop_back();
        }


    }
    return path;
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    for (Node *node : graph.getNodeSet()){
        node->resetData();
    }
    vector<vector<Vertex*>> l;
    int i = 0;
    vector<Vertex*> l0;
    start->setColor(GREEN);

    for (Edge *edge : graph.getEdgeSet(start)){
        l0.push_back(edge->start); //adds to list l.
        l.push_back(l0);
        while (!l[i].empty()){
            vector <Vertex*> inner;
            for (auto element : l[i]){
                element->setColor(GREEN);// current node
                if (element == end){
                    path.push_back(element);
                    while (element->previous != nullptr){//follow pointers back to start
                        path.push_back(element->previous);
                        element = element->previous;
                    }
                    std::reverse(path.begin(),path.end());
                    return path;
                }
                for (Edge *edge2:graph.getEdgeSet(element)){
                    if (edge2->finish->getColor() == WHITE){
                        edge2->finish->setColor(YELLOW);// queue node
                        edge2->finish->previous = edge2->start;
                        inner.push_back(edge2->finish);
                    }
                    else{
                    }
                }
            }
            l.push_back(inner);
            i++;
        }
    }
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Node *> path;
    PriorityQueue<Node *> priorityQueue;
    for (Node *node : graph.getNodeSet()){ // resets graph and adds startcost as infinity
        node->resetData();
        node->cost = numeric_limits<double>::infinity();
    }

    start->cost = 0;
    priorityQueue.enqueue(start,start->cost); // enqueues the first node

    while (!priorityQueue.isEmpty()){
        Node * node = priorityQueue.dequeue();
        node->setColor(GREEN);
        if (node == end){
            path.push_back(node);
            while (node->previous != nullptr){//follow pointers back to start
                path.push_back(node->previous);
                node = node->previous;
            }
            std::reverse(path.begin(),path.end());
            return path;
        }
        for (Node *other : graph.getNeighbors(node)){
            if (other->getColor() != GREEN){
               double cost2;
              cost2 = node->cost + graph.getArc(node,other)->cost;//updates cost with 1 step
              if (cost2 < other->cost){
                  other->cost = cost2;
                  other->previous = node;

                  try{// pqueue will return error if object not in the queue already
                      priorityQueue.changePriority(other,other->cost);
                  }
                  catch(...){
                      other->setColor(YELLOW);
                      priorityQueue.enqueue(other,other->cost);

                  }
              }
            }
        }
    }
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {

    vector<Node *> path;
    PriorityQueue<Node *> priorityQueue;

    for (Node *node : graph.getNodeSet()){ // resets graph and sets startingcost as infinity
        node->resetData();
        node->cost = numeric_limits<double>::infinity();
    }

    start->cost = 0;
    priorityQueue.enqueue(start,start->heuristic(end));// enqueues first node


    while (!priorityQueue.isEmpty()){
        Node * node = priorityQueue.dequeue();
        node->setColor(GREEN);
        if (node == end){// finish
            path.push_back(node);
            while (node->previous != nullptr){//follow pointers back to start
                path.push_back(node->previous);
                node = node->previous;
            }
            std::reverse(path.begin(),path.end());
            return path;
        }
        for (Node *other : graph.getNeighbors(node)){// for every neighbor
            if (other->getColor() != GREEN){
                double cost2;
               cost2 = node->cost + graph.getArc(node,other)->cost;//updates cost with 1 step
               if (cost2 < other->cost){
                   other->cost = cost2;
                   other->previous = node;


                  try{
                      priorityQueue.changePriority(other,other->heuristic(end)+other->cost


                                                   );
                      //pqueue will return error if object not in the queue already
                  }
                  catch(...){
                      other->setColor(YELLOW);
                      priorityQueue.enqueue(other,other->heuristic(end)+other->cost);
                  }
              }
            }
        }
    }
    return path;
}
