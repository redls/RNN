package partIIProject;

public class ParsedTree {
	int value;
	String word;
	ParsedTree left;
	ParsedTree right;
	
	ParsedTree() {
		value = -1;
		word = "";
		left = null;
		right = null;
	}
	
	ParsedTree(int value) {
		this.value = value;
		word = "";
		left = null;
		right = null;
	}
	
	ParsedTree(int value, String word) {
		this.value = value;
		this.word = word;
		left = null;
		right = null;
	}
	
	ParsedTree(String word) {
		this.value = -1;
		this.word = word;
		left = null;
		right = null;
	}
	
	void setLeftTree(ParsedTree tree) {
		left = tree;
	}
	
	void setRightTree(ParsedTree tree) {
		right = tree;
	}
	
	void printTree() {
		if (left != null) left.printTree();
		if (value != -1 || !word.equals("")) System.out.println(value + word); 
		if (right != null) right.printTree();
	}
	
	int max(int a, int b) {
		if (a > b) return a;
		return b;
	}
	
	int setValuesForLeaves(int startValue) {
		if (left == null || right == null) {
			value = startValue;
			return value + 1;
		}
		int maxNumberOnLeft = left.setValuesForLeaves(startValue);
		int maxNumberOnRight = right.setValuesForLeaves(maxNumberOnLeft);
		//value = maxNumberOnRight;
		return maxNumberOnRight;
	}
	
	int setValuesForInnerNodes(int n) {
		if (left == null || right == null) {
			return value;
		}
		int maxNumberOnRight = right.setValuesForInnerNodes(n);
		int maxNumberOnLeft = left.setValuesForInnerNodes(max(n, maxNumberOnRight));
		
		value = max(maxNumberOnLeft, max(n,maxNumberOnRight)) + 1;
		return value;
	}
	
	// Returns the maximum value contained in the leaves.
	int getMaxValueOfLeavesInTree() {
		if (left == null && right == null) return value;
		return right.getMaxValueOfLeavesInTree();
	}
	
	int updateInnerNodes() {
		int maxValue = getMaxValueOfLeavesInTree();
		return this.setValuesForInnerNodes(maxValue);
	}
	void updateArray(int[] a) {
		if (left == null || right == null) {
			return;
		}
		int leftChild = left.value;
		a[leftChild - 1] = value;
		left.updateArray(a);
		int rightChild = right.value;
		a[rightChild - 1] = value;
		right.updateArray(a);
	}
	
	int[] parentPointerRepresentation() {
		int numberOfNodes = this.value;
		int[] a = new int[numberOfNodes];
		a[numberOfNodes - 1] = 0;
		this.updateArray(a);
		return a;
	}
}
