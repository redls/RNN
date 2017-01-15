package partIIProject;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class CheckParsedTrees {
	private final static String FILE_READER_PATH_CORRECT_TREES = 
			"/home/laura/Part II Project/partIIProject/RNN/stanfordSentimentTreebank/STree.txt";
	
	private final static String FILE_READER_PATH_COMPUTED_TREES = 
			"/home/laura/Part II Project/partIIProject/RNN/PreprocessedDatasetSentences.txt";
	
	public static void main(String args[]) {
		FileReader frCorrectTrees;
		FileReader frComputedTrees;
		int k = 0;
		try {
			frCorrectTrees = new FileReader(FILE_READER_PATH_CORRECT_TREES);
			frComputedTrees = new FileReader(FILE_READER_PATH_COMPUTED_TREES);
			BufferedReader brCorrectTrees = new BufferedReader(frCorrectTrees);
			BufferedReader brComputedTrees = new BufferedReader(frComputedTrees);
			String originalLine;
			String computedLine;
			while ((originalLine = brCorrectTrees.readLine()) != null) {
				computedLine = brComputedTrees.readLine();
				if (!originalLine.equals(computedLine)) {
					System.out.println("Wrong computation: ");
					System.out.println(computedLine);
					System.out.println(originalLine);
					k++;
				}
			}
			brCorrectTrees.close();
			brComputedTrees.close();
			System.out.println("***** " + k);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
