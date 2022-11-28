import java.util.*;
class Alphametic {
    private final String targetString;
    private final HashMap<Character, Integer> theMap;
    private final ArrayList<Character> characterList;
    private final ArrayList<Character> nonZeroChars;
    private String solution;

	public Alphametic(String s) {
		this.targetString = s;
		this.characterList = new ArrayList<>();
		this.nonZeroChars = new ArrayList<>();
		this.theMap = new HashMap<>();
		this.solution = solve();
	}
	public HashMap<Character, Integer> getTheMap() {
		return theMap;
	}
	public String getTargetString() {
		return targetString;
	}
	public String getSolution() {
		return solution;
	}

	private String solve() {
        String[] arr = this.targetString.split(" [\\+,=] ");
		int maxString = 0;
		for (String string : arr) {
			this.nonZeroChars.add(string.charAt(0));
			if (maxString < string.length()) {
				maxString = string.length();
			}
		}
		char[][] charMatrix = new char[arr.length][maxString];
		for (int i = 0; i < arr.length; i++) {
			char[] stringToArr = arr[i].toCharArray();
			for (int j = stringToArr.length - 1; j >= 0; j--) {
				charMatrix[i][maxString - (stringToArr.length - j)] = stringToArr[j];
				this.theMap.put(stringToArr[j], -1);
			}
		}
		for (int j = charMatrix[0].length - 1; j >= 0; j--) {
			for (int i = 0; i < charMatrix.length; i++) {
				if (Character.isAlphabetic(charMatrix[i][j])) {
					this.characterList.add(charMatrix[i][j]);
				}
				if (i == charMatrix.length - 1) {
					this.characterList.add('=');
				}
			}
        }
        
		if(this.theMap.isEmpty() || this.characterList.isEmpty())
            return "No Solution";
        if(!findAlphametics(0, 0, 0))
            return "No Solution";
			
		String solution = this.targetString;
		for (Character c : this.theMap.keySet()) {
			solution = solution.replace(c, Character.forDigit(this.theMap.get(c), 10));
		}
        return solution;
	}
	private boolean findAlphametics(int index, int sum, int token) {
		if (this.characterList.get(index + 1) == '=') {
			sum += token;
			int value = sum % 10;

			if (this.theMap.get(this.characterList.get(index)) == -1) {
				if (!this.theMap.containsValue(value) && !(this.nonZeroChars.contains(this.characterList.get(index)) && value == 0)) {
					this.theMap.put(this.characterList.get(index), value);
					if (this.characterList.size() == index + 2) {
						return sum <= 9;
					}
					if (findAlphametics(index + 2, 0, sum / 10)) {
						return true;
					}
					this.theMap.put(this.characterList.get(index), -1);
				} else {
					return false;
				}
			} else {
				if (this.theMap.get(this.characterList.get(index)) == value) {
					if (this.characterList.size() == index + 2) {
						return sum <= 9;
					}
					if (findAlphametics(index + 2, 0, sum / 10)) {
						return true;
					}
				} else {
					return false;
				}
			}
			return false;
		}

		if (this.theMap.get(this.characterList.get(index)) == -1) {
			for (int i = 0; i <= 9; i++) {
				if (!this.theMap.containsValue(i) && !(this.nonZeroChars.contains(this.characterList.get(index)) && i == 0)) {
					this.theMap.put(this.characterList.get(index), i);
					if (findAlphametics(index + 1, sum + i, token)) {
						return true;
					}
				}
			}
			this.theMap.put(this.characterList.get(index), -1);
			return false;
		} else {
			if (findAlphametics(index + 1, sum + this.theMap.get(this.characterList.get(index)), token)) {
				return true;
			}
		}
		return false;
	}
}

public class CryptArithmetic {
	public static void main(String[] args) {	
        System.out.println("Enter the alphametic equation: ");
        Scanner sc = new Scanner(System.in);
        String s = sc.nextLine();
        sc.close();

        Alphametic a = new Alphametic(s);
        System.out.println(a.getTheMap());
        System.out.println(a.getTargetString());
        System.out.println(a.getSolution());
	}
}