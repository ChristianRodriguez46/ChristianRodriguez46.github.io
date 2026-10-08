#include <iostream>
#include <string>

using namespace std;

struct Node
{
    int value;
    Node *left;
    Node *right;
};

class BST
{
    private:
        int count;
        Node *root;

        Node *create(int value)
        {
            Node *newNode = new Node;
            newNode->value = value;
            newNode->left = NULL;
            newNode->right = NULL;
            count++;
            return newNode;
        }

        void add_node(Node *subtreeroot, int value)
        {
            if (subtreeroot->value != value)
            {
                if (value < subtreeroot->value) //L    Go to the left subtree
                {
                    if (subtreeroot->left != NULL)
                        add_node(subtreeroot->left, value);
                    else
                        subtreeroot->left = create(value);      // Create a new node on the left
                }
                else //R    Go to the right subtree
                {
                    if (subtreeroot->right != NULL)
                        add_node(subtreeroot->right, value);
                    else
                        subtreeroot->right = create(value);     // Create a new node on the right
                }
            }
        }


        void show_node(Node *subtreeroot)
        {
            if (subtreeroot != NULL)
            {
                show_node(subtreeroot->left);
                cout << subtreeroot->value << " ";
                show_node(subtreeroot->right);
            }
        };

        void destroy_node(Node *node)
        {
            if (node != NULL)
            {
                destroy_node(node->left);   //L
                destroy_node(node->right);  //R
            }

            delete node;    //V
            count--;

        };

        Node *find_node(Node *subtreeroot, int value)
        {
            if (subtreeroot == NULL || subtreeroot->value == value)
                return subtreeroot;

            if (value < subtreeroot->value)
                return find_node(subtreeroot->left, value);
            else
                return find_node(subtreeroot->right, value);
        };

    public:
        BST()
        {
            root = NULL;
            count = 0;
        };

        ~BST()
        {
            destroy_node(root);
        };

        // Public member function to access the count
        int getCount()
        {
            return count;
        }

        void add(int item)
        {
            if (root == NULL)
                root = create(item);
            else
                add_node(root, item);
        };

        bool find(int value)
        {
            return find_node(root, value) != NULL;
        };

        bool delete_node(int value)
        {
            bool found = false;
            Node *temp = root;
            Node *parent = NULL;

            while (!found && temp != NULL)
            {
                if (value == temp->value)
                {
                    found = true;
                }
                else if (value < temp->value)
                {
                    parent = temp;
                    temp = temp->left;
                }
                else if (value > temp->value){
                    parent = temp;
                    temp = temp->right;
                }
            }

            if (found)
            {
                if (temp->left != NULL && temp->right != NULL)
                {
                    Node *replacement = temp->right;
                    while (replacement->left != NULL)
                    {
                        parent = replacement;
                        replacement = replacement->left;
                    }
                    temp->value = replacement->value;
                    temp = replacement;
                }

                Node *subtree = (temp->right != NULL) ? temp->right : temp->left;
                
                // Node *subtree = temp->right;

                // if (subtree == NULL)
                //     subtree = temp->left;

                if (temp->value < parent->value)
                {
                    parent->left = subtree;
                }
                else
                {
                    parent->right = subtree;
                }
                
                count--;        // when this node is deleted, something has to take its place. 
                delete temp;
                // count--;        // when this node is deleted, something has to take its place. 
                return true;
            }
            else
                return false;
        };

        friend void show(BST &bst);
};


void show(BST &bst)
{
    bst.show_node(bst.root);
    cout << endl;
}


int main()
{
    BST bst;
    int values[25] = {23, 117, 45, 19, 7, 13, 17, 40, 9, 11, 93, 49, 35, 8, 3, 10, 22, 77, 16, 6, 51, 57, 55, 90, 31};

    // Fill up the BST object
    for (int i = 0; i < 25; ++i)
    {
        bst.add(values[i]);
    }

    // Display the contents of the BST
    cout << "Contents of the BST: ";
    show(bst);
    cout << endl;

    // Ask the user to enter a new integer value
    int newValue;
    cout << "Enter a new integer value: ";
    cin >> newValue;

    // Add the new value into the BST object
    bst.add(newValue);

    // Display the contents of the BST again
    cout << "Contents of the BST after adding " << newValue << ": ";
    show(bst);

    // Display the count of nodes in the BST
    cout << "Count of nodes in the BST: " << bst.getCount() << endl << endl;

    // Ask the user to search for a value
    int searchValue;
    cout << "Enter a value to search in the BST: ";
    cin >> searchValue;

    // Check if the value was found
    if (bst.find(searchValue))
    {
        cout << "Value " << searchValue << " found in the BST." << endl << endl;

        // Ask the user if the value should be deleted
        char choice;
        cout << "Do you want to delete the value? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y')
        {
            // Delete the matching node
            if (bst.delete_node(searchValue))
            {
                cout << "Value " << searchValue << " deleted from the BST." << endl << endl;
                // Display the tree to confirm its deletion
                cout << "Contents of the BST after deletion: ";
                show(bst);
                cout << "Count of nodes in the BST: " << bst.getCount() << endl;
            }
            else
            {
                cout << "Failed to delete the value from the BST." << endl;
            }
        }
    }
    else
    {
        cout << "Value " << searchValue << " not found in the BST." << endl;
    }

    return 0;
}
