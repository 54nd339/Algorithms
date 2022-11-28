import java.util.*;
class Constants {
    static int LEFT = 0; 
    static int RIGHT = 1; 
    static boolean visited = true; 
    static boolean notVisited = false; 
    static int timeLimit = 100; 
}
class State {
    int ml, cl, mr, cr;
    int boat, side, parent;    

    public State(int ml, int cl, int mr, int cr, int boat, int side) {
        this.ml = ml; this.cl = cl;
        this.mr = mr; this.cr = cr;
        this.boat = boat;
        this.side = side;
    }
    public boolean isValid() {
        if (ml >= 0 && cl >= 0 && mr >= 0 && cr >= 0
                && (ml == 0 || ml >= cl)
                && (mr == 0 || mr >= cr))
            return true;
        return false;
    }
    public boolean isGoal() {
        if (ml == 0 && cl == 0)
            return true;
        return false;
    }

    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof State))
            return false;

        State s = (State) obj;
        return (s.cl == cl && s.ml == ml
                && s.side == side && s.cr == cr
                && s.mr == mr);
    }
    @Override
    public String toString() {
        if (side == Constants.LEFT)
            return "(" + ml + ", " + cl + ", Left, " + mr + ", " + cr + ")";
        else
            return "(" + ml + ", " + cl + ", Right, " + mr + ", " + cr + ")";
    }
    @Override
    public int hashCode() {
        int hash = 7;
        hash = 61 * hash + this.ml;
        hash = 61 * hash + this.mr;
        hash = 61 * hash + this.cl;
        hash = 61 * hash + this.cr;
        hash = 61 * hash + this.side;
        return hash;
    }
    
    List<State> getSuccessors() {
        List<State> successors = new ArrayList<>();
        if (side == Constants.LEFT) {
            for (int i = 0; i <= ml; i++) {
                for (int j = 0; j <= cl; j++) {
                    // (i == 0 || i >= j) ---> if i is 0, no check is needed. otherwise, i >= j is a must
                    if ((i + j) != 0 && ((i + j) <= boat) && (i == 0 || i >= j)) {
                        State succ = new State(ml - i, cl - j, mr + i, cr + j, boat, Constants.RIGHT);
                        if (succ.isValid()) {
                            successors.add(succ);
                            // System.out.println(succ);
                        }
                    }
                }
            }
        } else if (side == Constants.RIGHT) {
            for (int i = 0; i <= mr; i++) {
                for (int j = 0; j <= cr; j++) {

                    if ((i + j) != 0 && ((i + j) <= boat)) {
                        State succ = new State(ml + i, cl + j, mr - i, cr - j, boat, Constants.LEFT);
                        if (succ.isValid()) {
                            successors.add(succ);
                            // System.out.println(succ);
                        }
                    }
                }
            }
        }
        printAll(successors);
        return successors;
    }

    public void printAll(List<State> l) {
        for (State s : l) {
            System.out.println(s);
        }
    }
}
class BFS {
    int nodeNo;
    State[] stateArray;
    State initialState; 

    public BFS(State initialState) {
        this.initialState = initialState;
        stateArray = new State[1000005];
        nodeNo = 0;
    }

    public State getFinalState() {
        if (initialState.isGoal())
            return initialState;

        nodeNo = 0;
        Queue<State> q = new LinkedList<>();
        HashMap<State, Integer> map = new HashMap<>();

        map.put(initialState, nodeNo);
        initialState.parent = -1;
        stateArray[nodeNo] = initialState;
        q.add(initialState);

        while (!q.isEmpty()) {
            State node = q.poll();
            int index = map.get(node);
            List<State> successors = node.getSuccessors();

            for (State succ : successors) {
                if (!map.containsKey(succ)) {
                    nodeNo++;
                    succ.parent = index;
                    stateArray[nodeNo] = succ;

                    if (succ.isGoal()) 
                        return succ;
                    map.put(succ, nodeNo);
                    q.add(succ);
                }
            }
        }
        return null;
    }

    public void printPath() {
        int t = 0;
        State s = getFinalState();
        System.out.println("Number of generated nodes: " + nodeNo);

        if (s == null) {
            System.out.println("No solution found.");
            return;
        }

        String[] str = new String[100005];
        while (!s.equals(initialState)) {
            str[t++] = s.toString();
            s = stateArray[s.parent];
            // System.out.println(s);
        }
        str[t] = s.toString();
        System.out.println("BFS takes " + t + " steps.\n");

        for (int i = t; i >= 0; i--) {
            System.out.print(str[i]);
            if (i != 0) {
                System.out.print(" --> ");
            }
        }
        System.out.println("");
    }
}
public class CM {
    public static void main(String[] args) {
        State init = new State(3, 3, 0, 0, 2, Constants.LEFT);
        init.parent = -1;
        BFS bfs = new BFS(init);
        bfs.printPath();
    }
}
