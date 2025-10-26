#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Course {
    std::string code;
    std::string title;
    std::vector<std::string> prereqs;
};

struct Node {
    Course course;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(const Course& c) : course(c), left(nullptr), right(nullptr) {}
};

class CourseBST {
public:
    // Constructor initializes an empty BST
    CourseBST() : root(nullptr) {}
    // Destructor cleans up all nodes
    ~CourseBST() { clear(root); }

    // Insert a course into the BST
    void insert(const Course& c) { root = insertRec(root, c); }
    // Print all courses in alphanumeric order
    void printInOrder() const { inOrder(root); }
    // Find a course by code
    Course* find(const std::string& code) const { return findRec(root, code); }
    // Remove a course by code
    bool remove(const std::string& code) { bool removed = false; root = removeRec(root, code, removed); return removed; }
    // Display a single course with its prerequisites
    void displaySingleCourse(const std::string& code) const {
        Course* c = find(code);
        if (!c) {
            std::cout << "Course not found: " << code << '\n';
            return;
        }
        std::cout << c->code << ", " << c->title << '\n';
        if (!c->prereqs.empty()) {
            std::cout << "Prerequisites: ";
            for (size_t i = 0; i < c->prereqs.size(); ++i) {
                if (i) std::cout << "; ";
                Course* prereq = find(c->prereqs[i]);
                if (prereq) {
                    std::cout << prereq->code << ", " << prereq->title;
                } else {
                    std::cout << c->prereqs[i] << " (title not found)";
                }
            }
            std::cout << '\n';
        } else {
            std::cout << "No prerequisites.\n";
        }
    }

private:
    Node* root;

    // Helper function to insert a course into the BST recursively
    Node* insertRec(Node* node, const Course& c) {
        if (!node) return new Node(c);
        if (c.code < node->course.code) node->left = insertRec(node->left, c);
        else if (c.code > node->course.code) node->right = insertRec(node->right, c);
        else node->course = c; // replace/update existing
        return node;
    }

    // Helper function to print courses in alphanumeric order
    void inOrder(Node* node) const {
        if (!node) return;
        inOrder(node->left);
        std::cout << node->course.code << ": " << node->course.title;
        std::cout << '\n';
        inOrder(node->right);
    }

    // Helper function to clear all nodes in the BST
    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    // Helper function to find a course by code recursively
    Course* findRec(Node* node, const std::string& code) const {
        if (!node) return nullptr;
        if (code == node->course.code) return &node->course;
        if (code < node->course.code) return findRec(node->left, code);
        return findRec(node->right, code);
    }

    // Helper function to remove a course by code recursively
    Node* removeRec(Node* node, const std::string& code, bool& removed) {
        if (!node) return nullptr;
        if (code < node->course.code) node->left = removeRec(node->left, code, removed);
        else if (code > node->course.code) node->right = removeRec(node->right, code, removed);
        else {
            removed = true;
            if (!node->left) {
                Node* right = node->right;
                delete node;
                return right;
            } else if (!node->right) {
                Node* left = node->left;
                delete node;
                return left;
            } else {
                Node* succParent = node;
                Node* succ = node->right;
                while (succ->left) {
                    succParent = succ;
                    succ = succ->left;
                }
                node->course = succ->course;
                if (succParent != node) succParent->left = removeRec(succParent->left, succ->course.code, removed);
                else succParent->right = removeRec(succParent->right, succ->course.code, removed);
            }
        }
        return node;
    }
};

static inline std::string trim(const std::string& s) {
    const char* ws = " \t\r\n";
    size_t start = s.find_first_not_of(ws);
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(ws);
    return s.substr(start, end - start + 1);
}

static std::vector<std::string> splitCSVLine(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ',')) {
        tokens.push_back(trim(token));
    }
    return tokens;
}

int main() {
    CourseBST bst;
    bool loaded = false;
    std::string filename;
    std::cout << "Enter course file name: ";
    std::getline(std::cin, filename);
    filename = trim(filename);
    if (filename.empty()) {
        std::cerr << "No filename provided.\n";
        return 1;
    }

    while (true) {
        // Display menu options
        std::cout << "\nMenu:\n";
        std::cout << "1. Load course data\n";
        std::cout << "2. Print all courses\n";
        std::cout << "3. Print course details\n";
        std::cout << "9. Exit\n";
        std::cout << "Choose option: ";
        std::string input;
        std::getline(std::cin, input);
        if (input.empty()) {
            std::cout << "Error: No input provided. Please enter a menu option.\n";
            continue;
        }
        // Validate menu input is an integer and within allowed options
        int opt = 0;
        try {
            opt = std::stoi(input);
        } catch (...) {
            std::cout << "Error: Invalid input. Please enter a number (1, 2, 3, or 9).\n";
            continue;
        }
        if (opt != 1 && opt != 2 && opt != 3 && opt != 9) {
            std::cout << "Invalid option. Please enter 1, 2, 3, or 9.\n";
            continue;
        }
        if (opt == 1) {
            if (loaded) {
                std::cout << "Data already loaded.\n";
                continue;
            }
            std::ifstream infile(filename);
            if (!infile) {
                std::cerr << "Failed to open file: " << filename << '\n';
                continue;
            }
            std::string line;
            // Read and insert courses from file
            while (std::getline(infile, line)) {
                line = trim(line);
                if (line.empty()) continue;
                if (line.size() >= 2 && line[0] == '/' && line[1] == '/') continue;
                if (line.size() >= 1 && line[0] == '#') continue;
                auto tokens = splitCSVLine(line);
                if (tokens.size() < 2) continue;
                Course c;
                c.code = tokens[0];
                c.title = tokens[1];
                for (size_t i = 2; i < tokens.size(); ++i) {
                    if (!tokens[i].empty()) c.prereqs.push_back(tokens[i]);
                }
                bst.insert(c);
            }
            loaded = true;
            std::cout << "Course data loaded.\n";
        } else if (opt == 2) {
            if (!loaded) {
                std::cout << "Please load course data first (Option 1).\n";
                continue;
            }
            std::cout << "\nCourses (alphanumeric order):\n";
            bst.printInOrder();
        } else if (opt == 3) {
            if (!loaded) {
                std::cout << "Please load course data first (Option 1).\n";
                continue;
            }
            std::cout << "Enter course code to display: ";
            std::getline(std::cin, input);
            input = trim(input);
            if (input.empty()) {
                std::cout << "Error: No course code entered.\n";
                continue;
            }
            bst.displaySingleCourse(input);
        } else if (opt == 9) {
            std::cout << "Exiting.\n";
            break;
        }
    }
    return 0;
}