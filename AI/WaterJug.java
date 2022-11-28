import java.util.*;
class Jug {
    float capacity, current;
    static String transfer[] = {"1->2", "2->1", "1->3", "3->1", "2->3", "3->2"};
    Jug(float capacity, float current) {
        this.capacity = capacity;
        this.current = current;
    }
    void pour(Jug j) {
        float amount = Math.min(current, j.capacity - j.current);
        this.current -= amount;
        j.current += amount;
    }
    static boolean move(Node node, String move) {
        Jug j1 = node.j1, j2 = node.j2, j3 = node.j3;
        if(move.equals("1->2")) {
            j1.pour(j2); return true;
        }
        if(move.equals("2->1")) {
            j2.pour(j1); return true;
        }
        if(move.equals("1->3")) {
            j1.pour(j3); return true;
        }
        if(move.equals("3->1")) {
            j3.pour(j1); return true;
        }
        if(move.equals("2->3")) {
            j2.pour(j3); return true;
        }
        if(move.equals("3->2")) {
            j3.pour(j2); return true;
        }
        return false;
    }
}
class Node{
    Jug j1, j2, j3;
    Node parent; int depth;
    Node(Jug j1, Jug j2, Jug j3, Node parent, int depth) {
        this.j1 = j1;
        this.j2 = j2;
        this.j3 = j3;
        this.parent = parent;
        this.depth = depth;
    }
    Node copy() {
        return new Node(new Jug(j1.capacity, j1.current), new Jug(j2.capacity, j2.current), new Jug(j3.capacity, j3.current), parent, depth);
    } 
    @Override
    public String toString() {
        return j1.current + " " + j2.current + " " + j3.current;
    }

    boolean isGoal() {
        float goal = j1.capacity/2;
        return j1.current == goal && j2.current == goal && j3.current == 0;
    }
    
    Queue<Node> generateNodes(HashMap<String, Boolean> visited) {
        Queue<Node> q = new LinkedList<Node>();
        for (int i = 0; i < 6; i++) {
            Node temp = this.copy();
            if(Jug.move(temp, Jug.transfer[i]) && visited.get(temp.toString()) == null) {
                System.out.println("Move : " + Jug.transfer[i]); 
                System.out.println(temp.toString());
                temp.parent = this; q.add(temp);
            }
        }
        System.out.println(); return q;
    }
    
    void printPath() {
        if(this.parent == null)
            System.out.println("Solution Path : ");
        else
            this.parent.printPath();
        System.out.println(this.toString());
    }
}
class Search {
    static int count;
    static void BFS(Jug j1, Jug j2, Jug j3) {
        HashMap<String, Boolean> visited = new HashMap<>();
        Queue<Node> q = new LinkedList<>();
        q.add(new Node(j1, j2, j3, null, 0));

        while(!q.isEmpty()) {
            Node node = q.poll();
            if (node.isGoal()) {
                node.printPath();
                return;
            }
            
            String key = node.toString();
            if (visited.get(key) != null) continue;
            System.out.println("\nExaming Node : "+key);
            visited.put(key, true); count++;

            Queue<Node> temp = node.generateNodes(visited);
            while(!temp.isEmpty()) q.add(temp.poll());
        }

        System.out.println("No Solution Found.");
    }
    static boolean DLS(Node node, int limit, HashMap<String, Boolean> visited) {
        if (node.isGoal()) {
            node.printPath();
            return true;
        }
        if (node.depth == limit) return false;
        String key = node.toString();
        if (visited.get(key) != null) return false;
        System.out.println("\nExaming Node : "+key);
        visited.put(key, true); count++;

        Queue<Node> temp = node.generateNodes(visited);
        while(!temp.isEmpty()) {
            if(DLS(temp.poll(), limit, visited)) return true;
        }
        return false;
    }
    static void IDDFS(Jug j1, Jug j2, Jug j3) {
        HashMap<String, Boolean> visited = new HashMap<>();
        for (int i = 0; i < 100; i++) {
            count = 0;
            if(DLS(new Node(j1, j2, j3, null, 0), i, visited)) {
                System.out.println("Nodes Examined : "+count);
                return;
            }
        }
        System.out.println("No Solution Found.");
    }
}

public class WaterJug {
    public static void main(String[] args) {
        System.out.println("Enter 3 capacities : ");
        Scanner sc = new Scanner(System.in);
        float a = sc.nextFloat();
        float b = sc.nextFloat();
        float c = sc.nextFloat();
        Jug j1 = new Jug(a, a);
        Jug j2 = new Jug(b, 0);
        Jug j3 = new Jug(c, 0);

        Search.count = 0;
        Search.BFS(j1, j2, j3);
        System.out.println("No. of nodes created while BFS : " + Search.count);

        Search.count = 0;
        Search.IDDFS(j1, j2, j3);
        System.out.println("No. of nodes created while IDS : " + Search.count);
        sc.close();
    }
}