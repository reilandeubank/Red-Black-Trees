#include "RBTree.cpp"
#include <iostream>
using namespace std;

string toWord(int num);

void test1() {
    cout << endl << "+-------------------------------TEST 1-------------------------------+" << endl;
    cout << "Inserting values into the tree" << endl << endl;
    int keys[] = {6, 169, 114, 166, 7, 75, 171, 151, 88, 136, 74, 47, 12, 
                  62, 191, 192, 67, 1, 21, 141, 181, 45, 89, 175, 180, 100,
                  9, 196, 46, 14, 116, 134, 92, 51, 13, 126, 57, 121, 59, 73};
    int values[40];
    for (int i = 0; i < 40; i++)
        values[i] = i;
    RBTree<int, int> T(keys, values, 40);

    if (T.size() == 40)
        cout << "Tree is correct size" << endl;
    else
        cout << "ERROR: expected tree to be size 40, tree is size " << T.size() << " instead" << endl;
    cout << endl;

    cout << "INORDER TRAVERSAL" << endl;
    cout << "Expected:    1 6 7 9 12 13 14 21 45 46 47 51 57 59 62 67 73 74 75 88 89 92 100 114 116 121 126 134 136 141 151 166 169 171 175 180 181 191 192 196" << endl;
    cout << "Your output: ";
    T.inorder();
    cout << endl;

    cout << "PREORDER TRAVERSAL" << endl;
    cout << "Expected:    114 47 12 7 6 1 9 21 14 13 45 46 75 67 57 51 62 59 74 73 89 88 100 92 169 136 126 116 121 134 151 141 166 191 175 171 181 180 192 196" << endl;
    cout << "Your output: ";
    T.preorder();
    cout << endl;

    cout << "Testing rank and select" << endl;
    int sorted[] = {1, 6, 7, 9, 12, 13, 14, 21, 45, 46, 47, 51, 57, 59, 62,
                    67, 73, 74, 75, 88, 89, 92, 100, 114, 116, 121, 126, 134,
                    136, 141, 151, 166, 169, 171, 175, 180, 181, 191, 192, 196};
    bool passed;
    bool passed_all = true;
    for (int i = 1; i <= 40; i++) {
        passed = sorted[i - 1] == T.select(i);
        passed_all &= passed;
        if (!passed)
            cout << "ERROR: expected " << sorted[i - 1] << " from select(" << i << ") but got " << T.select(i) << endl;
        
        passed = T.rank( sorted[i - 1] ) == i;
        passed_all &= passed;
        if (!passed)
            cout << "ERROR: expected " << i << " from rank(" << sorted[i - 1] << ") but got " << T.rank( sorted[i - 1] ) << endl;
    }
    if (passed_all)
        cout << "All rank and select tests passed" << endl;
    cout << endl;

    cout << "Testing predecessor and successor" << endl;
    int predecessor = 196;
    int successor = 1;
    passed_all = true;
    for (int i = 38; i >= 0; i--) {
        predecessor = *(T.predecessor(predecessor));
        passed = predecessor == sorted[i];
        passed_all &= passed;
        if (!passed) {
            cout << "ERROR: expected " << sorted[i] << " from predecessor(" << sorted[i + 1] << ") but got " << predecessor << endl;
            predecessor = sorted[i];
        }

        successor = *(T.successor(successor));
        passed = successor == sorted[39 - i];
        passed_all &= passed;
        if (!passed) {
            cout << "ERROR: expected " << sorted[39 - i] << " from successor(" << sorted[38 - i] << ") but got " << successor << endl;
            successor = sorted[39 - i];
        }
    }
    if (passed_all)
        cout << "All predecessor and successor tests passed" << endl;
    cout << endl;

    cout << "Testing search" << endl;
    passed = true;
    cout << "Searching for 6" << endl;
    passed &= *(T.search(6)) == 0;
    if (!passed)
        cout << "Error: expected 0, got " << *(T.search(6)) << endl;
    cout << "Searching for 46" << endl;
    passed &= *(T.search(46)) == 28;
    if (!passed)
        cout << "Error: expected 28, got" << *(T.search(46)) << endl;
    cout << "Searching for 121" << endl;
    passed &= *(T.search(121)) == 37;
    if (!passed)
        cout << "Error: expected 37, got" << *(T.search(121)) << endl;
    cout << "Searching for 52, which does not exist" << endl;
    passed &= T.search(52) == NULL;
    if (!passed)
        cout << "Error: expected NULL, got" << T.search(46) << endl;
    if (passed)
        cout << "Got all expected outputs" << endl;
    cout << endl;

    int to_delete[] = {13, 62, 7, 47, 181, 175, 196, 89};
    for (int i = 0; i < 8; i++) {
        cout << "Deleting " << to_delete[i] << endl;
        if (!T.remove( to_delete[i] )) {
            cout << "ERROR: did not delete element " << to_delete[i] << ". Terminating" << endl;
            return;
        }
    }
    cout << endl;

    if (T.size() == 32)
        cout << "Tree is correct size" << endl;
    else
        cout << "ERROR: expected tree to be size 32, tree is size " << T.size() << " instead" << endl;
    cout << endl;

    cout << "INORDER TRAVERSAL" << endl;
    cout << "Expected:    1 6 9 12 14 21 45 46 51 57 59 67 73 74 75 88 92 100 114 116 121 126 134 136 141 151 166 169 171 180 191 192" << endl;
    cout << "Your output: ";
    T.inorder();
    cout << endl;

    cout << "PREORDER TRAVERSAL" << endl;
    cout << "Expected:    114 46 12 6 1 9 21 14 45 75 67 57 51 59 74 73 92 88 100 169 136 126 116 121 134 151 141 166 191 171 180 192" << endl;
    cout << "Your output: ";
    T.preorder();
    cout << endl;

    cout << "Testing rank and select" << endl;
    int sorted2[] = {1, 6, 9, 12, 14, 21, 45, 46, 51, 57, 59,
                    67, 73, 74, 75, 88, 92, 100, 114, 116, 121,
                    126, 134, 136, 141, 151, 166, 169, 171, 180, 191, 192};
    passed;
    passed_all = true;
    for (int i = 1; i <= 32; i++) {
        passed = sorted2[i - 1] == T.select(i);
        passed_all &= passed;
        if (!passed)
            cout << "ERROR: expected " << sorted2[i - 1] << " from select(" << i << ") but got " << T.select(i) << endl;
        
        passed = T.rank( sorted2[i - 1] ) == i;
        passed_all &= passed;
        if (!passed)
            cout << "ERROR: expected " << i << " from rank(" << sorted2[i - 1] << ") but got " << T.rank( sorted2[i - 1] ) << endl;
    }
    if (passed_all)
        cout << "All rank and select tests passed" << endl;
    cout << endl;

    cout << "Testing predecessor and successor" << endl;
    predecessor = 192;
    successor = 1;
    passed_all = true;
    for (int i = 30; i >= 0; i--) {
        predecessor = *(T.predecessor(predecessor));
        passed = predecessor == sorted2[i];
        passed_all &= passed;
        if (!passed) {
            cout << "ERROR: expected " << sorted2[i] << " from predecessor(" << sorted2[i + 1] << ") but got " << predecessor << endl;
            predecessor = sorted2[i];
        }

        successor = *(T.successor(successor));
        passed = successor == sorted2[31 - i];
        passed_all &= passed;
        if (!passed) {
            cout << "ERROR: expected " << sorted2[31 - i] << " from successor(" << sorted2[30 - i] << ") but got " << successor << endl;
            successor = sorted2[31 - i];
        }
    }
    if (passed_all)
        cout << "All predecessor and successor tests passed" << endl;
    cout << endl;

    cout << "Testing boundary cases for predecessor and successor" << endl;
    passed = true;
    cout << "Looking for the successor of the largest key" << endl;
    passed &= T.successor(192) == NULL;
    if (!passed)
        cout << "ERROR: expected null from successor(192) but got something else" << endl;
    cout << "Looking for the predecessor of the smallest key" << endl;
    passed &= T.predecessor(1) == NULL;
    if (!passed)
        cout << "ERROR: expected null from predecessor(1) but got something else" << endl;
    cout << "Looking for the successor of a key that does not exist" << endl;
    passed &= T.successor(36) == NULL;
    if (!passed)
        cout << "ERROR: expected null from successor(36) but got something else" << endl;
    cout << "Looking for the predecessor of a key that does not exist" << endl;
    passed &= T.predecessor(71) == NULL;
    if (!passed)
        cout << "ERROR: expected null from predecessor(71) but got something else" << endl;
    if (passed)
        cout << "Got all expected outputs" << endl;
    cout << endl;


    cout << "Trying to delete a node not in the tree" << endl;
    if (!T.remove(69))
        cout << "Got expected output" << endl;
    else
        cout << "ERROR: unexpected output from remove function with node not in the tree" << endl;
    cout << "+--------------------------------------------------------------------+" << endl << endl;
}

void test2() {
    cout << endl << "+-------------------------------TEST 2-------------------------------+" << endl;
    cout << "Creating tree with 5 000 000 nodes. Should take a couple seconds maximum" << endl;
    RBTree<int, int> T;
    for (int i = 1; i <= 5000000; i++)
        T.insert(i, i);
    cout << "Created" << endl;
    cout << endl;

    cout << "Testing rank, select, search. Should take a couple seconds maximum" << endl;
    bool passed = true;
    for (int i = 1; i <= 5000000; i++) {
        passed &= T.rank(i) == i;
        if (!passed)
            cout << "ERROR: expected " << i << " from rank(" << i << ") but got " << T.rank(i) << endl;
        passed &= T.select(i) == i;
        if (!passed)
            cout << "ERROR: expected " << i << " from select(" << i << ") but got " << T.select(i) << endl;
        passed &= *(T.search(i)) == i;
        if (!passed)
            cout << "ERROR: expected " << i << " from search(" << i << ") but got " << *(T.search(i)) << endl;
    }
    if (passed)
        cout << "All tests passed" << endl;
    cout << endl;

    cout << "Testing successor. Should take a couple seconds maximum" << endl;
    passed = true;
    int successor = 1;
    for (int i = 2; i <= 5000000; i++) {
        successor = *(T.successor(successor));
        passed &= successor == i;
        if (!passed)
            cout << "ERROR: expected " << i << " from successor(" << i - 1 << ") but got " << successor << endl;
    }
    if (passed)
        cout << "All tests passed" << endl;
    cout << "+--------------------------------------------------------------------+" << endl << endl;
}

void test3() {
    cout << endl << "+-------------------------------TEST 3-------------------------------+" << endl;
    cout << "Testing delete for memory leaks" << endl;
    cout << "You can monitor memory usage in task manager. Should take somewhere around 20 MB" << endl;
    RBTree<int, int> *T;
    for (int i = 0; i < 100; i++) {
        T = new RBTree<int, int>();
        for (int i = 1; i <= 500000; i++)
            T->insert(i, i);
        delete T;
    }
    cout << "If this test ran in less than 10 seconds with memory usage sitting around a constant value, you shouldn't have any memory leaks" << endl;
    cout << "+--------------------------------------------------------------------+" << endl << endl;
}

void test4() {
    cout << endl << "+-------------------------------TEST 4-------------------------------+" << endl;
    cout << "Testing red black tree as a dictionary between ints and words" << endl;
    cout << "Storing ints between 0 and 9999 as keys and their corresponding english spellings as values" << endl;
    RBTree<int, string> T;
    for (int i = 0; i < 10000; i++)
        T.insert(i, toWord(i));
    cout << "Tree built" << endl << endl;

    cout << "Testing search" << endl;
    bool passed = true;
    for (int i = 100; i < 3000; i++) {
        if (! (passed &= *(T.search(i)) == toWord(i)))
            cout << "ERROR: expected " << toWord(i) << " from search(" << i << ") but got " << *(T.search(i)) << endl;
    }
    if (passed)
        cout << "All tests passed" << endl;
    cout << "+--------------------------------------------------------------------+" << endl << endl;
}

void test5() {
    cout << endl << "+-------------------------------TEST 5-------------------------------+" << endl;
    cout << "Creating tree T" << endl;
    RBTree<int, int> T;
    for (int i = 0; i < 40; i++)
        T.insert(i, i);
    cout << "Built tree T" << endl << endl;

    cout << "Testing copy constructor" << endl;
    RBTree<int, int> R = T;
    cout << "Copied T to R" << endl;
    for (int i = 35; i < 40; i++) {
        cout << "removing " << i << endl;
        R.remove(i);
    }
    for (int i = 13; i < 16; i++)
        R.remove(i);
    cout << "Deleted elements from R" << endl;
    cout << "T inorder traversal" << endl;
    cout << "Expected:    0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39" << endl;
    cout << "Your output: ";
    T.inorder();
    cout << "R inorder traversal" << endl;
    cout << "Expected:    0 1 2 3 4 5 6 7 8 9 10 11 12 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34" << endl;
    cout << "Your output: ";
    R.inorder();
    cout << endl;

    cout << "Testing copy assignment operator" << endl;
    RBTree<int, int> G;
    for (int i = 0; i < 500; i++)
        G.insert(500 - i, i);
    cout << "Created tree G and inserted values into it" << endl;
    cout << "Assigning G to T" << endl;
    G = T;
    cout << "Deleting elements from G" << endl;
    for (int i = 1; i < 7; i++)
        G.remove(i);
    for (int i = 24; i < 33; i++)
        G.remove(i);
    cout << "T inorder traversal" << endl;
    cout << "Expected:    0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39" << endl;
    cout << "Your output: ";
    T.inorder();
    cout << "G inorder traversal" << endl;
    cout << "Expected:    0 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 33 34 35 36 37 38 39" << endl;
    cout << "Your output: ";
    G.inorder();
    cout << "+--------------------------------------------------------------------+" << endl << endl;
}

string toWord(int num) {
    string ones[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    string two_digit[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    string tens[] = {"", "", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    int temp = num;
    int num_digits = 0;
    while (temp != 0) {
        temp /= 10;
        num_digits++;
    }
    if (num_digits <= 1)
        return ones[num];
    if (num < 20)
        return two_digit[num % 10];
    if (num_digits == 2)
        return tens[num / 10] + " " + ((num % 10 == 0) ? "" : ones[num % 10]);
    if (num_digits == 3)
        return ones[num / 100] + " hundred " + ((num % 100 == 0) ? "" : toWord(num % 100));
    if (num_digits == 4)
        return ones[num / 1000] + " thousand " + ((num % 1000 == 0) ? "" : toWord(num % 1000));
    return "";
}

int main(int argc, char **argv) {
    int test = atoi(argv[1]);
    switch (test) {
        case 1:
            test1();
            break;
        case 2:
            test2();
            break;
        case 3:
            test3();
            break;
        case 4:
            test4();
            break;
        case 5:
            test5();
            break;
        default:
            cout << "Invalid selection" << endl;
    }
}
