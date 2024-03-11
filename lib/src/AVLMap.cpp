//
// Created by Raymond Tsai on 10/25/23.
//

#include "../include/AVLMap.h"

//used for testing the AVLMap.h file, not the function to run entire program
int main() {
    AVLMap<char, int>* avlMapTest = new AVLMap<char, int>();
    /*
    // LL CASE WORKS
    avlMapTest->insert('a', 1);
    avlMapTest->insert('b', 2);
    avlMapTest->insert('c', 3);
    avlMapTest->insert('d', 4);
    avlMapTest->insert('e', 5);
     */

    // RR CASE WORKS
    /*
    avlMapTest->insert('e', 5);
    avlMapTest->insert('d', 4);
    avlMapTest->insert('c', 3);
    avlMapTest->insert('b', 2);
    avlMapTest->insert('a', 1);
    */

    // RL CASE WORKS
    /*
    avlMapTest->insert('a', 1);
    avlMapTest->insert('c', 3);
    avlMapTest->insert('b', 2);
     */

    // LR CASE WORKS
    avlMapTest->insert('c', 3);
    avlMapTest->insert('a', 1);
    avlMapTest->insert('b', 2);

    avlMapTest->printAllElements();
}
