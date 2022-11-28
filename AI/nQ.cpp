#include <bits/stdc++.h>
using namespace std;

class Queen {
    int x, y;
public:
    Queen(int x, int y) {
        this->x = x;
        this->y = y;
    }
    int getX() { return x; }
    int getY() { return y; }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    int walkUp(int n) {     // takes one step up on the board
        if(x > 0) {
            --x; return 1;
        }
        return 0;
    }
    int walkDown(int n) {   // takes one step down on the board
        if(x < n-1) {
            ++x; return 1;
        }
        return 0;
    }
};

class State {
    vector<Queen> queens; // list of queens on the board
    int n; // dimension of the board
public:
    State() {}
    State(int dim) {
        n = dim;
        srand (time(NULL)); //initialize random seed
        // initial configuration for the queens on the board
        for(int i = 0; i < n; i++) {
            Queen q(rand() % n, i);
            if((int)queens.size() < n)
                queens.push_back(q);
        }
    }
    int getN() { return n; }
    vector<Queen> getQueens();

    vector<State> getSuccessors() {
        vector<State> successors;
        for(int i = 0; i < n; i++) {
            int x = queens[i].getX();
            int y = queens[i].getY();
            
            // each queen walks up on the board as much as it can
            while(queens[i].walkUp(n) != 0)
                successors.push_back(*this);
            // initial position is set back
            queens[i].setX(x);
            queens[i].setY(y);
            
            // each queen walks down on the board as much as it can
            while(queens[i].walkDown(n) != 0)
                successors.push_back(*this);
            // initial position is set back
            queens[i].setX(x);
            queens[i].setY(y);
        }
        return successors;
    }
    State bestSuccessor() {
        vector<State> successors = getSuccessors();
        int noSucc = successors.size();
        vector<int> bestSuccessors;
        int min_attacks = n*n; // number of attacks for best successor
        for(int i = 0; i < noSucc; i++) {
            int attacks = successors[i].number_of_attacks();
            if(attacks < min_attacks) { // finds a new minimum
                min_attacks = attacks;
                bestSuccessors.clear(); // starts vector again
                bestSuccessors.push_back(i); // adds new minimum
            }
            else if(attacks == min_attacks) // finds the same minimum again
                bestSuccessors.push_back(i); // adds to list of best successors
        }
        // chooses random state from possible best states
        srand (time(NULL)); // initialize random seed
        int min_index = rand() % (int)bestSuccessors.size();
        return successors[bestSuccessors[min_index]];
    }
    int number_of_attacks() {   // number of possible attacks between 2 queens
        // variable for counting number of attacks in rows
        int attacks_in_rows = 0;
        int queens_by_row[n];
        for(int i = 0; i < n; i++)
            queens_by_row[i] = 0;
        // variable for counting number of attacks in diagonals
        int attacks_in_diag = 0;
        int queens_by_diagonal[2*n-1], queens_by_diagonal_2[2*n-1];
        for(int i = 0; i < 2*n-1; i++) {
            queens_by_diagonal[i] = 0;
            queens_by_diagonal_2[i] = 0;
        }
        // counting number of queens
        for(int i = 0; i < n; i++) {
            int x = queens[i].getX();
            int y = queens[i].getY();
            ++queens_by_row[x]; // in each row
            ++queens_by_diagonal[x+y]; // in each antidiagonal direction
            ++queens_by_diagonal_2[n-1+y-x]; // in each main diagonal direction
        }
        
        // number of attacks in rows
        for(int i = 0; i < n; i++)
            if(queens_by_row[i] > 1)
                attacks_in_rows += queens_by_row[i] - 1;
        // number of attacks in diagonals
        for(int i = 0; i < 2*n-1; i++) {
            if(queens_by_diagonal[i] > 1)
                attacks_in_diag += queens_by_diagonal[i] - 1;
            if(queens_by_diagonal_2[i] > 1)
                attacks_in_diag += queens_by_diagonal_2[i] - 1;
        }
        return attacks_in_diag + attacks_in_rows;
    }
    void print() {
        char board[n][n];
        // filling board with underlines
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                board[i][j] = '_';
        // filling board with its queens
        for(int i = 0; i < n; i++)
            board[queens[i].getX()][queens[i].getY()] = 'Q';
        // actually printing
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                cout << board[i][j] << (j == n-1 ? "\n" : " ");
        cout << endl;
    }
};

State Hillclimb(State current) {
    int iteration = 1; // counts number of iterations
    while(true) { // unless an error occurs, the program always find a solution
        current.print();
        State next = current.bestSuccessor();
        if(current.number_of_attacks() <= next.number_of_attacks()) {
            cout << "\nNumber of iterations: " << iteration << endl;
            return current;
        }
        current = next;
        ++iteration;
    }
    // in case of error
    return State(-1);
}

int main() {
    cout << "Choose the board's dimension: ";
    int dim; cin >> dim;
    State initial_state(dim);
    State solution = Hillclimb(initial_state);
    // if it doesn't find solution, then get a new random initial state and try again
    int random = 1;
    while(solution.number_of_attacks() > 0) {
        cout << "Random initial state " << random << endl;
        State initial_state(dim);
        solution = Hillclimb(initial_state);
        ++random;
    }
    cout << "\nSolution:\n" << endl;
    if(solution.getN() == -1)
        cout << "Error" << endl;
    else
        solution.print();
    return 0;
}