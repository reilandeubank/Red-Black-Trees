#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cmath>

using namespace std;

template <typename K, typename V>
class Node {
    public:
    bool color;
    Node *left;
    Node *right;
    Node *p;
    K key;
    V val;
    int size;

    Node() {
        left = right = nullptr;
        color = 1;
    }
    Node(K theKey, V theVal) {
        key = theKey;
        val = theVal;
        color = 1;
        left = right = nullptr;
        size = 1;
    }
    
    ~Node() {                                               //destructor
        left = nullptr;
        right = nullptr;
    }
    void setColor(string col) {
        if (col == "black") {
            //cout << "setting " << key << " to black" << endl;
            color = 0;
        }
        else if (col == "red") {
            //cout << "setting " << key << " to red" << endl;
            color = 1;
        }
        else {
            cout << "invalid color" << endl;
        }
    }
    string getColor() {
        if (color == 0) {
            return "black";
        }
        else if (color == 1) {
            return "red";
        }
        else {
            return "invalid";
        }
    }
};

template <typename keyType, typename valueType>
class RBTree {
    private: 
        Node<keyType,valueType> *root;
        Node<keyType,valueType> *nil;
        int treeSize;

        void findPreSuc(Node<keyType,valueType> *a, Node<keyType,valueType> *&pre, Node<keyType,valueType> *&suc, keyType key) {
            {
                if (a == this->nil)  return ;
                if (a->key == key) {
                    if (a->left != this->nil) {
                        Node<keyType,valueType> *temp = a->left;
                        while (temp->right)
                            temp = temp->right;
                        pre = temp ;
                    }
                    if (a->right != this->nil) {
                        Node<keyType,valueType> *temp = a->right ;
                        while (temp->left)
                            temp = temp->left ;
                        suc = temp ;
                    }
                    return ;
                }
                if (a->key > key) {
                    suc = a ;
                    findPreSuc(a->left, pre, suc, key) ;
                }
                else {
                    pre = a ;
                    findPreSuc(a->right, pre, suc, key) ;
                }
            }
        }

        void leftRotate(Node<keyType,valueType> *x) {
            //cout << "leftRotate" << endl;
            Node<keyType,valueType> *y = new Node<keyType,valueType>();
            y->left = y->right =this->nil;
            y = x->right;
            x->right = y->left;
            if (y->left != this->nil) {
                y->left->p = x;
            }
            y->p = x-> p;
            if (x->p == this->nil) {
                this->root = y;
            }
            else if (x == x->p->left) {
                x->p->left = y;
            }
            else {
                x->p->right = y;
            }
            y->left = x;
            x->p = y;
            y->size = x->size;
            x->size = x->left->size + x->right->size + 1;
        }

        void rightRotate(Node<keyType,valueType> *x) {
            //cout << "rightRotate " << x->key << endl;
            Node<keyType,valueType> *y = new Node<keyType,valueType>();
            y->left = y->right =this->nil;
            y = x->left;
            x->left = y->right;
            if (y->right != this->nil) {
                y->right->p = x;
            }
            y->p = x->p;
            if (x->p == this->nil) {
                this->root = y;
            }
            else if (x == x->p->right) {
                x->p->right = y;
            }
            else {
                x->p->left = y;
            }
            y->right = x;
            x->p = y;
            y->size = x->size;
            x->size = x->left->size + x->right->size + 1;
        }

        void insertFixUp(Node<keyType,valueType> *z) {
            //cout << "    ****    fixing up key " << z->key << " and color " << z->getColor() << ", z->p is " << z->p->getColor() << " and " << z->p->key << endl;
            if (z->p != this->nil) {
                //cout << "    ****    p is " << z->p->key << " and p->p val is " << z->p->p->key << endl;
            }
            Node<keyType,valueType> *y;
            while (z->p->getColor() == "red") {
                //cout << "inside while" << endl;
                if (z->p == z->p->p->left) {
                    //cout << "inside left if" << endl;
                    y = z->p->p->right;
                    if (y->getColor() == "red") {
                        z->p->setColor("black");
                        y->setColor("black");
                        z->p->p->setColor("red");
                        z = z->p->p;
                    }
                    else {
                        if (z == z->p->right) {
                            z = z->p;
                            leftRotate(z);
                        }
                        z->p->setColor("black");
                        z->p->p->setColor("red");
                        rightRotate(z->p->p);
                    }
                }
                else {
                    //cout << "inside right if" << endl;
                    y = z->p->p->left;
                    if (y->getColor() == "red") {
                        //cout << "in if" << endl;
                        z->p->setColor("black");
                        y->setColor("black");
                        z->p->p->setColor("red");
                        z = z->p->p;
                    }
                    else {
                        if (z == z->p->left) {
                            //cout << "in else if" << endl;
                            z = z->p;
                            rightRotate(z);
                        }
                        z->p->setColor("black");
                        z->p->p->setColor("red");
                        leftRotate(z->p->p);
                    }
                }
            }
            this->root->setColor("black");
            //cout << "    ****    done fixing up key " << z->key << " and color " << z->getColor() << ", z->p is " << z->p->getColor() << " and " << z->p->key << endl;
        }

        void deleteFixUp(Node<keyType,valueType> *x) {
            Node<keyType,valueType> *w;
            while (x != this->root && x->getColor() == "black") {
                if (x == x->p->left) {
                    w = x->p->right;
                    if (w->getColor() == "red") {
                        w->setColor("black");
                        x->p->setColor("red");
                        leftRotate(x->p);
                        w = x->p->right;
                    }
                    if (w->left->getColor() == "black" && w->right->getColor() == "black") {
                        w->setColor("red");
                        x = x->p;
                    }
                    else {
                        if (w->right->getColor() == "black") {
                            w->left->setColor("black");
                            w->setColor("red");
                            rightRotate(w);
                            w  = x->p->right;
                        }
                        w->setColor(x->p->getColor());
                        x->p->setColor("black");
                        w->right->setColor("black");
                        leftRotate(x->p);
                        x = this->root;
                    }
                }
                else {
                    w = x->p->left;
                    if (w->getColor() == "red") {
                        w->setColor("black");
                        x->p->setColor("red");
                        rightRotate(x->p);
                        w = x->p->left;
                    }
                    if (w->right->getColor() == "black" && w->left->getColor() == "black") {
                        w->setColor("red");
                        x = x->p;
                    }
                    else {
                        if (w->left->getColor() == "black") {
                            w->right->setColor("black");
                            w->setColor("red");
                            leftRotate(w);
                            w  = x->p->left;
                        }
                        w->setColor(x->p->getColor());
                        x->p->setColor("black");
                        w->right->setColor("black");
                        rightRotate(x->p);
                        x = this->root;
                    }
                }
            }
        }

        void transplant(Node<keyType,valueType> *u, Node<keyType,valueType> *v) {
            if (u->p == this->nil) {
                this->root = v;
            }
            else if (u == u->p->left) {
                u->p->left = v;
            }
            else {
                u->p->right = v;
            }
            v->p = u->p;
        }

        Node<keyType,valueType> *max(Node<keyType,valueType> *x) {
            while(x->right != this->nil) {
                x->size--;
                x = x->right;
            }
            return x;
        }

        Node<keyType,valueType> *min(Node<keyType,valueType> *x) {
            while(x->left != this->nil) {
                x = x->left;
            }
            return x;
        }

        void rbDelete(Node<keyType,valueType> *z) {
            Node<keyType,valueType> *y = z;
            Node<keyType,valueType> *x;
            string originalColor = y->getColor();
            if (z->left == this->nil) {
                x = z->right;
                z->right->size = z->size - 1;
                transplant(z, z->right);

            }
            else if (z->right == this->nil) {
                x = z->left;
                z->left->size = z->size - 1;
                transplant(z, z->left);
            }
            else {
                y = max(z->left);
                originalColor = y->getColor();
                x = y->left;
                if (y->p == z) {
                    x->p = y;
                }
                else {
                    transplant(y, y->left);
                    y->left = z->left;
                    y->left->p = y;
                }
                transplant(z, y);
                y->right = z->right;
                y->right->p = y;
                z->setColor(y->getColor());
            }
            if (originalColor == "black") {
                deleteFixUp(x);
            }
        }

        void printOrder(Node<keyType,valueType> *x, int order) {
            if (x == nullptr || x == this->nil) {
                return;
            }

            if (order == 0) {
                cout << x->key << " ";
            }
            
            printOrder(x->left, order);

            if (order == 1) {
                cout << x->key << " ";
            }

            printOrder(x->right, order);

            if (order == 2) {
                cout << x->key << " ";
            }
        }

        Node<keyType,valueType> *rbSelect(Node<keyType,valueType> *x, int i) {
            int r = x->left->size + 1;
            if (i == r) {
                return x;
            }
            else if (i < r) {
                return rbSelect(x->left, i);
            }
            else {
                return rbSelect(x->right, i - r);
            }
        }

        Node<keyType,valueType> *nodeSearch(keyType k, Node<keyType,valueType> *x) {
            //cout << "In nodeSearch" << endl;
            if (x == this->nil) {
                return this->nil;
            }
            else if (x->key == k) {
                return x;
            }
            else if (x->key > k) {
                return nodeSearch(k, x->left);
            }
            else {
                return nodeSearch(k, x->right);
            }
        }

        void destroyRecursive(Node<keyType,valueType> *node) {
            if (node != this->nil){
                destroyRecursive(node->left);
                destroyRecursive(node->right);
                delete node;
            }
        }

        void copyHelper(Node<keyType,valueType>* &copy_to, const Node<keyType,valueType>* copy_from, RBTree *a) {
            //cout << "copyTree call: "<< copy_from->key << endl;
            if (copy_from == NULL || copy_from == a->nil){
                copy_to = this->nil;
            } 
            else {
                copy_to = new Node<keyType,valueType>();
                copy_to->key = copy_from->key;
                copy_to->val = copy_from->val;
                copy_to->color = copy_from->color;
                copy_to->size = copy_from->size;
                copyHelper(copy_to->left, copy_from->left, a);
                copyHelper(copy_to->right, copy_from->right, a);
            }
        }

        void copyOP(Node<keyType,valueType> *a) {
            insert(a->key,a->val);
            if (a->left != this->nil) {
                copyOP(a->left);
            }
            if (a->right!= this->nil) {
                copyOP(a->right);
            }
        }

        void printKSmallest(Node<keyType,valueType> *a, int k, int *count) {
            if (a->left != this->nil) {
                printKSmallest(a->left, k, count);
            }
            if (*count < k) {
                (*count)++;
                cout << a->key << " ";
            }
            if (*count < k && a->right != this->nil) {
                printKSmallest(a->right, k, count);
            }
        }

    public:
        RBTree() {                                   //Default Constructor
            //cout << "default constructor" << endl;
            root = new Node<keyType,valueType>();
            nil = new Node<keyType,valueType>();
            this->nil->setColor("black");
            this->root = this->nil;
            //cout << "done with default constructor" << endl;
        }

        RBTree(keyType K[], valueType V[], int s) {
            //cout << "overloaded constructor" << endl;
            root = new Node<keyType,valueType>();
            nil = new Node<keyType,valueType>();
            this->nil->setColor("black");
            this->root = this->nil;
            //cout << "entering for loop" << endl;
            for (int i = 0; i < s; i++) {
                //cout << "inserting" << endl;
                insert(K[i],V[i]);
                //cout << "inserted " << K[i] << endl;
            }
            //cout << "done with overloaded constructor" << endl;
        } 

        ~RBTree() {
            destroyRecursive(this->root);
        }

        RBTree(RBTree &a) {
            cout << "copy 1, root is "<< a.root->key << endl;
            this->treeSize = a.treeSize;
            copyHelper(this->root, a.root, &a);
        }

        RBTree& operator=(RBTree &a) {
            cout << "copy 2" << endl;
            if (this != &a) {
                Node<keyType,valueType> *b = a.root;
                this->root->size = b->size;
                this->root->p = this->nil;
                this->root->key = b->key;
                this->root->val = b->val;
                this->root->setColor(b->getColor());
                if (b->left != this->nil) {
                    copyOP(b->left);
                }
                if (b->right!= this->nil) {
                    copyOP(b->right);
                }
            }
            this->treeSize = a.treeSize;
            return *this;
        }

        void insert(keyType k, valueType v) {
            Node <keyType,valueType> *z = new Node<keyType,valueType>(k,v);
            z->left = z->right = this->nil;
            Node<keyType,valueType> *y = this->nil;
            Node<keyType,valueType> *x = this->root;

            while (x != this->nil) {
                y = x;
                y->size++;
                if (z->key < x->key) {
                    x = x->left;
                }
                else
                 x = x->right;
            }

            z->p = y;

            if (y == this->nil) {
                this->root = z;
            }
            else if (z->key < y->key) {
                y->left = z;
            }
            else y->right = z;
            z->left = z->right = this->nil;
            z->setColor("red");
            //cout << "inserted " << z->key << endl;
            insertFixUp(z);
            treeSize++;
            //cout << "fixed " << z->key << endl;
        }

        int remove(keyType k) {
            //cout << "removing " << k << endl;
            Node<keyType,valueType> *curr = this->root;
            while(k != curr->key) {
                if (k < curr->key) {
                    //cout << k << " is less than " << curr->key << endl;
                    curr->size--;
                    curr = curr->left;
                }
                else if (k > curr->key) {
                    curr->size--;
                    //cout << k << " is less than " << curr->key << endl;
                    curr = curr->right;
                }
                if (curr == this->nil) {
                    //cout << k << " is not found"<< endl;
                    return 0;
                }
            }
            rbDelete(curr);
            treeSize--;
            return 1;
        }

        int rank (keyType k) {
            //cout << "rank" << endl;
            Node<keyType,valueType> *x = nodeSearch(k, this->root);
            int r = x->left->size + 1;
            Node<keyType,valueType> *y = x;
            while (y != this->root) {
                if (y == y->p->right) {
                    r = r + y->p->left->size + 1;
                }
                y = y->p;
            }
            return r;
        }

        keyType select(int pos) {
            return rbSelect(this->root, pos)->key;
        }

        keyType *successor(keyType k) {
            /*Node<keyType,valueType> *pre, *suc;
            findPreSuc(this->root, pre, suc, k);
            if (suc != this->nil) {
                return &(suc->key);
            }
            else {
                return NULL;
            }*/
            //cout << "successor" << endl;
            if (rank(k)+1 >= treeSize) {
                return NULL;
            } 
            return &(rbSelect(this->root,rank(k)+1)->key);
        }

        keyType *predecessor(keyType k) {
            /*Node<keyType,valueType> *pre, *suc;
            findPreSuc(this->root, pre, suc, k);
            if (pre != this->nil) {
                return &(pre->key);
            }
            else {
                return NULL;
            }*/
            //cout << "predecessor" << endl;
            if (rank(k) == 1) {
                return NULL;
            }
            return &(rbSelect(this->root,rank(k)-1)->key);
        }

        valueType *search(keyType k) {
            //cout << "Searching " << k << endl;
            Node<keyType,valueType> *x = nodeSearch(k, this->root);
            if (x == this->nil) {
                return NULL;
            }
            else {
                return &(x->val);
            }
        }

        int size() {
            return treeSize;
        }

        void preorder() {
            printOrder(this->root, 0);
            cout << endl;
        }
        
        void inorder() {
            printOrder(this->root, 1);
            cout << endl;
        }

        void postorder() {
            printOrder(this->root, 2);
            cout << endl;
        }

        void printk(int k) {
            int count = 0;
            printKSmallest(this->root, k, &count);
            cout << endl;
        }
};