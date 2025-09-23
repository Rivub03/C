#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// Configuration for a 4-way search tree (can be adjusted)
const int MAX_KEYS = 3;        // Maximum keys per node (degree - 1)
const int MIN_KEYS = 1;        // Minimum keys per node (except root)
const int DEGREE = MAX_KEYS + 1; // Degree of the tree

/**
 * Node structure for M-Way Search Tree
 * Each node can contain up to MAX_KEYS keys and MAX_KEYS+1 children
 */
struct Node {
    int count;                    // Current number of keys in the node
    int keys[MAX_KEYS];          // Array to store keys
    Node* children[DEGREE];      // Array to store child pointers
    bool is_leaf;                // Flag to indicate if node is a leaf

    Node() : count(0), is_leaf(true) {
        // Initialize all child pointers to nullptr
        for (int i = 0; i < DEGREE; i++) {
            children[i] = nullptr;
        }
    }

    ~Node() {
        // Destructor - recursively delete all non-null children
        for (int i = 0; i < DEGREE; i++) {
            if (children[i] != nullptr) {
                delete children[i];
                children[i] = nullptr;
            }
        }
    }
};

struct MWayTree {
    Node* root;

    MWayTree() {
        root = nullptr;
    }


    /**
     * Find the index where a value should be inserted or the child to follow
     * Returns the index i such that all keys[0..i-1] < val <= keys[i..count-1]
     */
    int find_key_index(Node* node, int val) {
        int i = 0;
        while (i < node->count && val > node->keys[i]) {
            i++;
        }
        return i;
    }

    /**
     * Search for a value in the subtree rooted at node
     * Returns pointer to the node containing the value, or nullptr if not found
     */
    Node* search_recursive(Node* node, int val) {
        if (node == nullptr) {
            return nullptr;
        }

        int i = find_key_index(node, val);

        // Check if the value exists in the current node
        if (i < node->count && node->keys[i] == val) {
            return node;
        }

        // If leaf node and value not found, return nullptr
        if (node->is_leaf) {
            return nullptr;
        }

        // Recursively search in the appropriate child subtree
        return search_recursive(node->children[i], val);
    }

    /**
     * Split a full child node at index child_index in parent
     * This is called when a child has MAX_KEYS keys and needs to be split
     */
    void split_child(Node* parent, int child_index) {
        Node* full_child = parent->children[child_index];
        Node* new_node = new Node();

        new_node->is_leaf = full_child->is_leaf;
        new_node->count = MIN_KEYS;

        // Copy the upper half of keys to the new node
        for (int i = 0; i < MIN_KEYS; i++) {
            new_node->keys[i] = full_child->keys[i + MIN_KEYS + 1];
        }

        // If not a leaf, copy the corresponding children
        if (!full_child->is_leaf) {
            for (int i = 0; i <= MIN_KEYS; i++) {
                new_node->children[i] = full_child->children[i + MIN_KEYS + 1];
                full_child->children[i + MIN_KEYS + 1] = nullptr; // Prevent double deletion
            }
        }

        // Reduce the key count of the original child
        full_child->count = MIN_KEYS;

        // Make space for the new child in parent
        for (int i = parent->count; i > child_index; i--) {
            parent->children[i + 1] = parent->children[i];
        }
        parent->children[child_index + 1] = new_node;

        // Make space for the median key in parent and move it up
        for (int i = parent->count - 1; i >= child_index; i--) {
            parent->keys[i + 1] = parent->keys[i];
        }
        parent->keys[child_index] = full_child->keys[MIN_KEYS];
        parent->count++;
    }

    /**
     * Insert a value into a non-full node
     * Precondition: node is not full (count < MAX_KEYS)
     */
    void insert_non_full(Node* node, int val) {
        int i = node->count - 1;

        if (node->is_leaf) {
            // Insert into leaf: shift keys and insert
            while (i >= 0 && node->keys[i] > val) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = val;
            node->count++;
        }
        else {
            // Find the child to insert into
            while (i >= 0 && node->keys[i] > val) {
                i--;
            }
            i++; // Now i is the index of the child to insert into

            // If the target child is full, split it first
            if (node->children[i]->count == MAX_KEYS) {
                split_child(node, i);
                // After splitting, decide which of the two children to insert into
                if (val > node->keys[i]) {
                    i++;
                }
            }
            insert_non_full(node->children[i], val);
        }
    }

    /**
     * Find the predecessor of a key (rightmost key in left subtree)
     */
    int get_predecessor(Node* node, int index) {
        Node* current = node->children[index];
        while (!current->is_leaf) {
            current = current->children[current->count];
        }
        return current->keys[current->count - 1];
    }

    /**
     * Find the successor of a key (leftmost key in right subtree)
     */
    int get_successor(Node* node, int index) {
        Node* current = node->children[index + 1];
        while (!current->is_leaf) {
            current = current->children[0];
        }
        return current->keys[0];
    }

    /**
     * Merge child at index with its right sibling
     * Used during deletion when both child and sibling have minimum keys
     */
    void merge_children(Node* parent, int index) {
        Node* left_child = parent->children[index];
        Node* right_child = parent->children[index + 1];

        // Move the separator key from parent to left child
        left_child->keys[left_child->count] = parent->keys[index];
        left_child->count++;

        // Copy keys from right child to left child
        for (int i = 0; i < right_child->count; i++) {
            left_child->keys[left_child->count] = right_child->keys[i];
            left_child->count++;
        }

        // Copy children from right child to left child (if not leaves)
        if (!left_child->is_leaf) {
            for (int i = 0; i <= right_child->count; i++) {
                left_child->children[left_child->count - right_child->count + i - 1] = right_child->children[i];
                right_child->children[i] = nullptr; // Prevent double deletion
            }
        }

        // Remove the separator key from parent and shift everything left
        for (int i = index; i < parent->count - 1; i++) {
            parent->keys[i] = parent->keys[i + 1];
        }

        // Shift children pointers left
        for (int i = index + 1; i < parent->count; i++) {
            parent->children[i] = parent->children[i + 1];
        }
        parent->children[parent->count] = nullptr; // Clear the last pointer

        parent->count--;

        // Now safely delete the right child (its children pointers are nulled)
        delete right_child;
    }

    /**
     * Borrow a key from the left sibling through the parent
     */
    void borrow_from_left(Node* parent, int index) {
        Node* child = parent->children[index];
        Node* left_sibling = parent->children[index - 1];

        // Make space for the new key in child
        for (int i = child->count - 1; i >= 0; i--) {
            child->keys[i + 1] = child->keys[i];
        }

        // If not a leaf, make space for the new child pointer
        if (!child->is_leaf) {
            for (int i = child->count; i >= 0; i--) {
                child->children[i + 1] = child->children[i];
            }
            // Move the rightmost child from left sibling
            child->children[0] = left_sibling->children[left_sibling->count];
            left_sibling->children[left_sibling->count] = nullptr;
        }

        // Move separator key from parent to child
        child->keys[0] = parent->keys[index - 1];
        child->count++;

        // Move the rightmost key from left sibling to parent
        parent->keys[index - 1] = left_sibling->keys[left_sibling->count - 1];
        left_sibling->count--;
    }

    /**
     * Borrow a key from the right sibling through the parent
     */
    void borrow_from_right(Node* parent, int index) {
        Node* child = parent->children[index];
        Node* right_sibling = parent->children[index + 1];

        // Move separator key from parent to child
        child->keys[child->count] = parent->keys[index];
        child->count++;

        // If not a leaf, move the leftmost child from right sibling
        if (!child->is_leaf) {
            child->children[child->count] = right_sibling->children[0];
        }

        // Move the leftmost key from right sibling to parent
        parent->keys[index] = right_sibling->keys[0];

        // Shift keys and children in right sibling
        for (int i = 0; i < right_sibling->count - 1; i++) {
            right_sibling->keys[i] = right_sibling->keys[i + 1];
        }
        if (!right_sibling->is_leaf) {
            for (int i = 0; i < right_sibling->count; i++) {
                right_sibling->children[i] = right_sibling->children[i + 1];
            }
            right_sibling->children[right_sibling->count] = nullptr;
        }

        right_sibling->count--;
    }

    /**
     * Ensure that the child at index has at least MIN_KEYS+1 keys
     * This is called before descending into a child during deletion
     */
    void fix_child(Node* parent, int index) {
        Node* child = parent->children[index];

        // If child already has enough keys, no need to fix
        if (child->count > MIN_KEYS) {
            return;
        }

        // Try to borrow from left sibling
        if (index > 0 && parent->children[index - 1] != nullptr &&
            parent->children[index - 1]->count > MIN_KEYS) {
            borrow_from_left(parent, index);
            return;
        }

        // Try to borrow from right sibling
        if (index < parent->count && parent->children[index + 1] != nullptr &&
            parent->children[index + 1]->count > MIN_KEYS) {
            borrow_from_right(parent, index);
            return;
        }

        // Must merge with a sibling
        if (index > 0) {
            // Merge with left sibling
            merge_children(parent, index - 1);
        }
        else {
            // Merge with right sibling
            merge_children(parent, index);
        }
    }

    /**
     * Delete a key from the subtree rooted at node
     * This is the main recursive deletion function
     */
    void delete_recursive(Node* node, int val) {
        if (node == nullptr) {
            return; // Key not found
        }

        int i = find_key_index(node, val);
        bool found = (i < node->count && node->keys[i] == val);

        if (node->is_leaf) {
            // Case 1: Key is in a leaf node
            if (found) {
                // Shift keys to remove the target key
                for (int j = i; j < node->count - 1; j++) {
                    node->keys[j] = node->keys[j + 1];
                }
                node->count--;
            }
            // If not found in leaf, key doesn't exist in tree
        }
        else {
            // Node is internal
            if (found) {
                // Case 2: Key is in an internal node
                Node* left_child = node->children[i];
                Node* right_child = node->children[i + 1];

                if (left_child->count > MIN_KEYS) {
                    // Case 2a: Left child has extra keys, replace with predecessor
                    int predecessor = get_predecessor(node, i);
                    node->keys[i] = predecessor;
                    delete_recursive(left_child, predecessor);
                }
                else if (right_child->count > MIN_KEYS) {
                    // Case 2b: Right child has extra keys, replace with successor
                    int successor = get_successor(node, i);
                    node->keys[i] = successor;
                    delete_recursive(right_child, successor);
                }
                else {
                    // Case 2c: Both children have minimum keys, merge them
                    merge_children(node, i);
                    delete_recursive(node->children[i], val);
                }
            }
            else {
                // Case 3: Key is not in this internal node, must be in a child
                // Ensure child has enough keys before descending
                if (i <= node->count && node->children[i] != nullptr) {
                    fix_child(node, i);

                    // After potential merging, find the correct child again
                    int new_i = find_key_index(node, val);
                    if (new_i < node->count && node->keys[new_i] == val) {
                        // The key moved up during merge, delete it from current node
                        delete_recursive(node, val);
                    }
                    else {
                        // Continue searching in the appropriate child
                        delete_recursive(node->children[new_i], val);
                    }
                }
            }
        }
    }

    /**
     * Print the tree structure recursively (helper for print_tree)
     */
    void print_level_order() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }

        queue<Node*> q;
        q.push(root);

        cout << "Tree structure (level order):" << endl;
        while (!q.empty()) {
            int level_size = q.size();

            for (int i = 0; i < level_size; i++) {
                Node* current = q.front();
                q.pop();

                cout << "[ ";
                for (int j = 0; j < current->count; j++) {
                    cout << current->keys[j];
                    if (j < current->count - 1) cout << ", ";
                }
                cout << " ] ";

                // Add children to queue for next level
                if (!current->is_leaf) {
                    for (int j = 0; j <= current->count; j++) {
                        if (current->children[j] != nullptr) {
                            q.push(current->children[j]);
                        }
                    }
                }
            }
            cout << endl;
        }
    }
    /*Public search interface
        * Returns true if value is found, false otherwise
        * /
        bool search(int val) {
        return search_recursive(root, val) != nullptr;
    }

    /**
     * Public insert interface
     * Inserts a value into the tree, maintaining m-way search tree properties
     */
    void insert(int val) {
        // Don't insert duplicates
        if (search_recursive(root, val)) {
            cout << "Value " << val << " already exists in the tree." << endl;
            return;
        }

        if (root == nullptr) {
            // Create the first node
            root = new Node();
            root->keys[0] = val;
            root->count = 1;
            return;
        }

        // If root is full, create a new root and split
        if (root->count == MAX_KEYS) {
            Node* new_root = new Node();
            new_root->is_leaf = false;
            new_root->children[0] = root;
            split_child(new_root, 0);
            root = new_root;
        }

        insert_non_full(root, val);
    }

    /**
     * Public delete interface
     * Removes a value from the tree while maintaining m-way search tree properties
     */
    void remove(int val) {
        if (root == nullptr) {
            cout << "Cannot delete from empty tree." << endl;
            return;
        }

        delete_recursive(root, val);

        // If root becomes empty after deletion, make its only child the new root
        if (root->count == 0) {
            Node* old_root = root;
            if (root->is_leaf) {
                root = nullptr; // Tree becomes empty
            }
            else {
                root = root->children[0];
                old_root->children[0] = nullptr; // Prevent recursive deletion
            }
            delete old_root;
        }
    }

    /**
     * Print the entire tree structure
     */
    void print_tree() {
        print_level_order();
    }

    /**
     * Check if the tree is empty
     */
    bool is_empty() {
        return root == nullptr;
    }
};

int main() {
    MWayTree tree;

    cout << "=== M-Way Search Tree Demo ===" << endl;
    cout << "Using " << DEGREE << "-way tree (max " << MAX_KEYS << " keys per node)" << endl << endl;

    // Test insertions
    cout << "--- Testing Insertions ---" << endl;
    vector<int> values = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };

    for (int val : values) {
        cout << "Inserting " << val << "..." << endl;
        tree.insert(val);
    }

    cout << "\nTree after insertions:" << endl;
    tree.print_tree();

    // Test searches
    cout << "\n--- Testing Searches ---" << endl;
    for (int val : {30, 75, 100, 5}) {
        cout << "Searching for " << val << ": "
            << (tree.search_recursive(tree.root, val) ? "Found" : "Not Found") << endl;
    }

    // Test deletions
    cout << "\n--- Testing Deletions ---" << endl;
    vector<int> to_delete = { 30, 70, 40, 60 };

    for (int val : to_delete) {
        cout << "\nDeleting " << val << "..." << endl;
        tree.remove(val);
        cout << "Tree after deletion:" << endl;
        tree.print_tree();
    }

    // Final verification
    cout << "\n--- Final Verification ---" << endl;
    cout << "Remaining values in tree:" << endl;
    for (int val : values) {
        if (tree.search_recursive(tree.root, val)) {
            cout << val << " ";
        }
    }
    cout << endl;



    return 0;
}