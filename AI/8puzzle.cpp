#include <bits/stdc++.h>
using namespace std;
#define N 3
vector<vector<int>> goal(N, vector<int>(N, 0));
vector<vector<int>> init(N, vector<int>(N, 0));
vector<char> moves{'U', 'D', 'L', 'R'};

class Puzzle {
    pair<int, int> blank = {0, 0};
public:
    vector<vector<int>> state{N, vector<int>(N, 0)};
    Puzzle() { state = init; }
    Puzzle(vector<vector<int>> &state) {
        this->state = state;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (state[i][j] == 0)
                    blank = {i, j};
            }
        }
    }

    bool moveBlank(char dir) {
        if (dir == 'U' && blank.first != 0) {
            swap(state[blank.first][blank.second], state[blank.first - 1][blank.second]);
            blank.first--;
            return true;
        }
        if (dir == 'D' && blank.first != N-1) {
            swap(state[blank.first][blank.second], state[blank.first + 1][blank.second]);
            blank.first++;
            return true;
        }
        if (dir == 'L' && blank.second != 0) {
            swap(state[blank.first][blank.second], state[blank.first][blank.second - 1]);
            blank.second--;
            return true;
        }
        if (dir == 'R' && blank.second != N-1) {
            swap(state[blank.first][blank.second], state[blank.first][blank.second + 1]);
            blank.second++;
            return true;
        }
        return false;
    }
    void print() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << state[i][j] << " ";
            cout << endl;
        }
    }
};
class Node {
    Node *parent;
    int level;
public:
    Puzzle node;
    Node() = default;
    Node(Puzzle p, Node *par, int lvl) {
        node = p;
        parent = par;
        level = lvl;
    }
    // Get the successors of the node
    queue<Node *> getChildren() {
        queue<Node *> succs;
        for (char dir : moves) {
            Puzzle succ = node;
            if (succ.moveBlank(dir)) {   
                cout << "\nMove : " << dir << endl;
                Node* newNode = new Node(succ, this, level + 1); 
                succs.push(newNode);
                (succs.back())->node.print();
            }
        }
        return succs;
    }
    // Print the path from the root to the goal node
    void printPath() {
        if (this->level == 0) {
            node.print(); cout << endl;
            return;
        }
        else
            this->parent->printPath();
        node.print();
        cout << endl;
    }
};

class Search {
    Node root;
public:
    static int count;
    Search() {
        root = Node(Puzzle(init), NULL, 0);
    }
    // Search for the goal state
    bool DLS(Node *root, int depth) {
        // check(*root);
        if (depth == 0) {
            if (root->node.state == goal) {
                cout << "\nFound Solution Path :" << endl;
                root->printPath();
                return true;
            }
            return false;
        }
        
        cout << "\nExamining State : " << endl;
        root->node.print();
        queue<Node *> succs = root->getChildren();
        count += succs.size();
        while (!succs.empty()) {
            Node *n = succs.front();
            succs.pop();
            if (DLS(n, depth - 1))
                return true;
        }
        return false;
    }
    void IDS() {
        int depth = 0; bool flag = false;
        while (true) {
            count = 0;
            if (DLS(&root, depth++)) {
                cout << "Solution Found at depth : " << (depth-1) << endl;
                flag = true;
            }
            cout << "No. of nodes at depth " << (depth-1) << " : " << count << endl;
            if (flag) break;
        }
    }
};
int Search::count = 0;
int main() {
    cout << "Enter the initial state of the puzzle :" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cin >> init[i][j];
    }
    cout << "Enter the goal state of the puzzle: " << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cin >> goal[i][j];
    }
    Search s;
    s.IDS();
    return 0;
}
/*
Initial State of the puzzle :
1 2 3
5 6 0
7 8 4
Goal State of the puzzle :
1 2 3
5 8 6
0 7 4
*/