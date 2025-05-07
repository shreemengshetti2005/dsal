#include <iostream>
#include <stack>
using namespace std;

class Node {
public:
    int val;
    Node* left, *right;

    Node(int v) {
        val = v;
        left = right = nullptr;
    }
};

class BST {
public:
    Node* root;

    BST() {
        root = nullptr;
    }

    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->val)
            node->left = insert(node->left, val);
        else
            node->right = insert(node->right, val);
        return node;
    }

    int height(Node* node) {
        if (!node) return 0;
        return max(height(node->left), height(node->right)) + 1;
    }

    int findMin(Node* node) {
        if (!node) return -1;
        while (node->left) node = node->left;
        return node->val;
    }

    int findMax(Node* node) {
        if (!node) return -1;
        while (node->right) node = node->right;
        return node->val;
    }

    void mirror(Node* node) {
        if (!node) return;
        swap(node->left, node->right);
        mirror(node->left);
        mirror(node->right);
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->val << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (!node) return;
        cout << node->val << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->val << " ";
    }

    void preorderIterative(Node* node) {
        if (!node) return;
        stack<Node*> st;
        st.push(node);
        while (!st.empty()) {
            Node* curr = st.top(); st.pop();
            cout << curr->val << " ";
            if (curr->right) st.push(curr->right);
            if (curr->left) st.push(curr->left);
        }
        cout << endl;
    }

    void postorderIterative(Node* node) {
        if (!node) return;
        stack<Node*> st1, st2;
        st1.push(node);
        while (!st1.empty()) {
            Node* curr = st1.top(); st1.pop();
            st2.push(curr);
            if (curr->left) st1.push(curr->left);
            if (curr->right) st1.push(curr->right);
        }
        while (!st2.empty()) {
            cout << st2.top()->val << " ";
            st2.pop();
        }
        cout << endl;
    }

    bool search(Node* node, int val) {
        if (!node) return false;
        if (val == node->val) return true;
        if (val < node->val)
            return search(node->left, val);
        else
            return search(node->right, val);
    }

    Node* deleteNode(Node* node, int val) {
        if (!node) return nullptr;
        if (val < node->val) {
            node->left = deleteNode(node->left, val);
        } else if (val > node->val) {
            node->right = deleteNode(node->right, val);
        } else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* successor = node->right;
            while (successor->left) successor = successor->left;
            node->val = successor->val;
            node->right = deleteNode(node->right, successor->val);
        }
        return node;
    }

    int countLeaves(Node* node){
        if(!node) return 0;
        if(!node->left && !node->right) return 1;
        return countLeaves(node->left)+ countLeaves(node->right);
    }

    int countInternal(Node* node){
        if(!node || (!node->left && !node->right)) return 0;
        return countInternal(node->left) +countInternal(node->right)+1;
        
    }
    Node* copyRec(Node* node) {
        if (!node) return nullptr;
        Node* newNode = new Node(node->val);
        newNode->left = copyRec(node->left);
        newNode->right = copyRec(node->right);
        return newNode;
    }

    void eraseTreeRec(Node*& node) {
        if (!node) return;
        eraseTreeRec(node->left);
        eraseTreeRec(node->right);
        delete node;
        node = nullptr;
    }
};

int main() {
    BST tree;
    int choice, val;

    while (true) {
        cout << "\n=== MENU ===\n";
        cout << "1. Insert\n2. Height\n3. Min & Max\n4. Mirror\n5. Search\n";
        cout << "6. Inorder\n7. Preorder (rec)\n8. Postorder (rec)\n";
        cout << "9. Preorder (iter)\n10. Postorder (iter)\n";
        cout << "11. Delete\n12. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                tree.root = tree.insert(tree.root, val);
                break;
            case 2:
                cout << "Height: " << tree.height(tree.root) << endl;
                break;
            case 3:
                cout << "Min: " << tree.findMin(tree.root) << ", Max: " << tree.findMax(tree.root) << endl;
                break;
            case 4:
                tree.mirror(tree.root);
                cout << "Tree mirrored.\n";
                break;
            case 5:
                cout << "Enter value to search: ";
                cin >> val;
                cout << (tree.search(tree.root, val) ? "Found\n" : "Not Found\n");
                break;
            case 6:
                cout << "Inorder: ";
                tree.inorder(tree.root);
                cout << endl;
                break;
            case 7:
                cout << "Preorder (recursive): ";
                tree.preorder(tree.root);
                cout << endl;
                break;
            case 8:
                cout << "Postorder (recursive): ";
                tree.postorder(tree.root);
                cout << endl;
                break;
            case 9:
                cout << "Preorder (iterative): ";
                tree.preorderIterative(tree.root);
                break;
            case 10:
                cout << "Postorder (iterative): ";
                tree.postorderIterative(tree.root);
                break;
            case 11:
                cout << "Enter value to delete: ";
                cin >> val;
                tree.root = tree.deleteNode(tree.root, val);
                cout << "Node deleted (if existed).\n";
                break;
            case 12:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
