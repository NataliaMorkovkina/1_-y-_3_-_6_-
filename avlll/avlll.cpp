#include <iostream>
#include <chrono>

class node {
public:
    int data;
    int height;
    node* left;
    node* right;
    node(int k) {
        height = 1;
        data = k;
        left = NULL;
        right = NULL;
    }
};

int height(node* root) {
    if (root == NULL) return 0;
    return root->height;
}
node* rightRotation(node* root) {
    node* newhead = root->left;
    root->left = newhead->right;
    newhead->right = root;
    root->height = 1 + std::max(height(root->left), height(root->right));
    newhead->height = 1 + std::max(height(newhead->left), height(newhead->right));
    return newhead;
}

node* leftRotation(node* root) {
    node* newhead = root->right;
    root->right = newhead->left;
    newhead->left = root;
    root->height = 1 + std::max(height(root->left), height(root->right));
    newhead->height = 1 + std::max(height(newhead->left), height(newhead->right));
    return newhead;
}

void inorderUtil(node* root, bool last) {
    if (root == NULL) return;
    inorderUtil(root->left, false);
    std::cout << root->data << (last && root->right == NULL ? "\n" : " -> ");
    inorderUtil(root->right, last);
}

node* insertUtil(node* root, int x) {
    if (root == NULL) {
        node* temp = new node(x);
        return temp;
    }
    if (x < root->data) root->left = insertUtil(root->left, x);
    else if (x > root->data) root->right = insertUtil(root->right, x);
    root->height = 1 + std::max(height(root->left), height(root->right));
    int bal = height(root->left) - height(root->right);
    if (bal > 1) {
        if (x < root->left->data) {
            return rightRotation(root);
        }
        else {
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }
    }
    else if (bal < -1) {
        if (x > root->right->data) {
            return leftRotation(root);
        }
        else {
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }
    }
    return root;
}
node* removeUtil(node* root, int x) {
    if (root == NULL) return NULL;
    if (x < root->data) {
        root->left = removeUtil(root->left, x);
    }
    else if (x > root->data) {
        root->right = removeUtil(root->right, x);
    }
    else {
        node* r = root->right;
        if (root->right == NULL) {
            node* l = root->left;
            delete(root);
            root = l;
        }
        else if (root->left == NULL) {
            delete(root);
            root = r;
        }
        else {
            while (r->left != NULL) r = r->left;
            root->data = r->data;
            root->right = removeUtil(root->right, r->data);
        }
    }
    if (root == NULL) return root;
    root->height = 1 + std::max(height(root->left), height(root->right));
    int bal = height(root->left) - height(root->right);
    if (bal > 1) {
        if (height(root->left) >= height(root->right)) {
            return rightRotation(root);
        }
        else {
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }
    }
    else if (bal < -1) {
        if (height(root->right) >= height(root->left)) {
            return leftRotation(root);
        }
        else {
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }
    }
    return root;
}
node* searchUtil(node* root, int x) {
    if (root == NULL) return NULL;
    int k = root->data;
    if (k == x) return root;
    if (k > x) return searchUtil(root->left, x);
    return searchUtil(root->right, x);
}

class avlTree {
private:
    node* root = NULL;

public:
    void insert(int x) {
        root = insertUtil(root, x);
    }

    void remove(int x) {
        root = removeUtil(root, x);
    }

    node* search(int x) {
        return searchUtil(root, x);
    }

    void inorder() {
        inorderUtil(root, true);
        std::cout << '\n';
    }

private:
    int h(node* r) {
        if (r->left == NULL && r->right == NULL)
            return 1;
        if (r->left != NULL && r->right == NULL)
            return h(r->left) + 1;
        if (r->left == NULL && r->right != NULL)
            return h(r->right) + 1;
        return std::max(h(r->left), h(r->right)) + 1;
    }

public:
    int h() {
        return h(root);
    }
};
int main() {
    avlTree tree;

    auto start = std::chrono::high_resolution_clock::now();

    /*for (int i = 0; i < 500; i++)
    {
        int t = i;

        tree.insert(t);
    }*/

    for (int i = 0; i < 500; i++) {
        int t = rand()%500;
        // std::cout << t << ' ';
        tree.insert(t);
    }

    std::cout << '\n';

    tree.inorder();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    std::cout << "t" << duration.count() * 1000 << "\n";

    std::cout << '\n';
    

    std::cout << tree.h() << '\n';
}