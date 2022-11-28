import java.util.*;
class Input {
    static Scanner sc = new Scanner(System.in);
}
class Puzzle {
    int mat[][] = new int[3][3];
    int empty_pos[] = {0, 0};
    static char move[] = {'U', 'D', 'L', 'R'};
    static Puzzle copy(Puzzle p) { // copy constructor
        Puzzle q = new Puzzle();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                q.mat[i][j] = p.mat[i][j];
            }
        }
        q.empty_pos[0] = p.empty_pos[0];
        q.empty_pos[1] = p.empty_pos[1];
        return q;
    }
    void setInit() {    // set the initial state of the puzzle
        System.out.println("Enter the initial state of the puzzle :");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++){
                mat[i][j] = Input.sc.nextInt();
                if(mat[i][j] == 0) {
                    empty_pos[0] = i;
                    empty_pos[1] = j;
                }
            }
        }
    }
    void swap(int i, int j, int k, int l) {
        int temp = mat[i][j];
        mat[i][j] = mat[k][l];
        mat[k][l] = temp;
    }
    boolean move(char move) {   // Move the empty position
        if(move == 'U' && empty_pos[0] != 0) {  // Up
            swap(empty_pos[0], empty_pos[1], empty_pos[0] - 1, empty_pos[1]);
            empty_pos[0]--; return true;
        }
        if(move == 'D' && empty_pos[0] != 2) {  // Down
            swap(empty_pos[0], empty_pos[1], empty_pos[0] + 1, empty_pos[1]);
            empty_pos[0]++; return true;
        }
        if(move == 'L' && empty_pos[1] != 0) { // Left
            swap(empty_pos[0], empty_pos[1], empty_pos[0], empty_pos[1] - 1);
            empty_pos[1]--; return true;
        }
        if(move == 'R' && empty_pos[1] != 2) { // Right
            swap(empty_pos[0], empty_pos[1], empty_pos[0], empty_pos[1] + 1);
            empty_pos[1]++; return true;
        }
        return false;
    }
    void printState() { // Print the state of the puzzle
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                System.out.print(mat[i][j] + " ");
            System.out.println();
        }
        System.out.println();
    }
}
class Node {
    Puzzle state;   // state of the puzzle
    Node parent;    // parent of the node
    int depth;      // depth of the node
    static int goal[][] = new int[3][3];
    Node(Puzzle state, Node parent, int depth) {
        this.state = state;
        this.parent = parent;
        this.depth = depth;
    }
    static void setGoalState() {    // Get Goal State
        System.out.println("Enter the goal state of the puzzle :");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                goal[i][j] = Input.sc.nextInt();
        }
    }
    // Get the possible moves from the current node state
    Queue<Node> generateNodes() {
        Queue<Node> q = new LinkedList<Node>();
        for (int i = 0; i < 4; i++) {
            Puzzle temp = Puzzle.copy(this.state);
            if(temp.move(Puzzle.move[i])) {
                // System.out.println("Move : " + Puzzle.move[i]); 
                Node newNode = new Node(temp, this, this.depth + 1);
                /*newNode.state.printState();*/ q.add(newNode);
            }
        }
        /*System.out.println();*/ return q;
    }
    // Print the path from the initial state to the goal state
    void printPath() {
        if(this.parent == null)
            System.out.println("\nSolution Path : ");
        else
            this.parent.printPath();
        this.state.printState();
    }
}
class Search {
    static int count;
    static void BFS(Node root) {
        Queue<Node> q = new LinkedList<Node>();
        q.add(root);
        while(!q.isEmpty()) {
            Node temp = q.poll();
            if(Arrays.deepEquals(temp.state.mat, Node.goal)) {
                temp.printPath();
                return;
            }

            // System.out.println("Examining State : ");
            // root.state.printState();
            Queue<Node> nodes = temp.generateNodes();
            count += nodes.size();
            while(!nodes.isEmpty())
                q.add(nodes.remove());
        }
    }
    static boolean DLS(Node root, int depth) {
        if(depth == 0) {
            if(Arrays.deepEquals(root.state.mat, Node.goal)) {
                root.printPath();
                return true;
            }
            return false;
        }
        // System.out.println("Examining State : ");
        // root.state.printState();
        Queue<Node> q = root.generateNodes();
        Search.count += q.size();
        while(!q.isEmpty()) {
            Node temp = q.remove();
            if(DLS(temp, depth - 1))
                return true;
        }
        return false;
    }
    static void IDS(Node root) {
        int depth = 0;
        while(true) {
            boolean flag = Search.DLS(root, depth++);
            System.out.println("\nNo. of Nodes created at Depth " + depth + " : " + (Search.count+1));
            if(flag) break; Search.count = 0; 
        }
        System.out.println("Solution Found at depth : " + depth);
    }
    static void Astar(Node root) {
        PriorityQueue<Node> q = new PriorityQueue<Node>(new Comparator<Node>() {
            @Override
            public int compare(Node o1, Node o2) {
                int h1 = 0, h2 = 0;
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if(o1.state.mat[i][j] != Node.goal[i][j])
                            h1++;
                        if(o2.state.mat[i][j] != Node.goal[i][j])
                            h2++;
                    }
                }
                return (h1 + o1.depth) - (h2 + o2.depth);
            }
        });
        q.add(root);
        while(!q.isEmpty()) {
            Node temp = q.poll();
            if(Arrays.deepEquals(temp.state.mat, Node.goal)) {
                temp.printPath();
                return;
            }
            // System.out.println("Examining State : ");
            // root.state.printState();
            Queue<Node> nodes = temp.generateNodes();
            count += nodes.size();
            while(!nodes.isEmpty())
                q.add(nodes.remove());
        }
    }
}
public class Game {
    public static void main(String[] args) {
        Puzzle p = new Puzzle();
        p.setInit(); Node.setGoalState();

        Search.count = 0;
        Search.BFS(new Node(p, null, 0));
        System.out.println("No. of Nodes created while BFS : " + Search.count);

        Search.count = 0;
        Search.IDS(new Node(p, null, 0));
        System.out.println("No. of Nodes created while IDS : " + Search.count);

        Search.count = 0;
        Search.Astar(new Node(p, null, 0));
        System.out.println("No. of Nodes created while A* Search : " + Search.count);
    }
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