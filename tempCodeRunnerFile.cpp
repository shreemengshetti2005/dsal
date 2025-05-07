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