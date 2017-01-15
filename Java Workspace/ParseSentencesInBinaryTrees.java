package partIIProject;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.StringReader;
import java.util.List;

import edu.stanford.nlp.trees.Tree;
import edu.stanford.nlp.parser.lexparser.TreeBinarizer;
import edu.stanford.nlp.ling.CoreLabel;
import edu.stanford.nlp.process.TokenizerFactory;
import edu.stanford.nlp.parser.lexparser.LexicalizedParser;
import edu.stanford.nlp.process.CoreLabelTokenFactory;
import edu.stanford.nlp.process.PTBTokenizer;
import edu.stanford.nlp.process.Tokenizer;
import edu.stanford.nlp.parser.lexparser.TreeBinarizer;
import edu.stanford.nlp.trees.TreeCoreAnnotations.BinarizedTreeAnnotation;

public class ParseSentencesInBinaryTrees {
	private final static String PCG_MODEL = "edu/stanford/nlp/models/lexparser/englishPCFG.ser.gz";        

    private final TokenizerFactory<CoreLabel> tokenizerFactory = PTBTokenizer.factory(new CoreLabelTokenFactory(), "invertible=true");

    private final static LexicalizedParser parser = LexicalizedParser.loadModel(PCG_MODEL);
    
	private final static String FILE_READER_PATH = 
			"/home/laura/Part II Project/partIIProject/RNN/stanfordSentimentTreebank/SOStr.txt";
	
//	private final static String FILE_WRITER_PATH = 
//			"/home/laura/Part II Project/partIIProject/RNN/PreprocessedDatasetSentences.txt";
//	
//	 public Tree parse(String str) {                
//	        List<CoreLabel> tokens = tokenize(str);
//	        Tree tree = parser.apply(tokens);
//	        return tree;
//	    }
//	 
//	   private List<CoreLabel> tokenize(String str) {
//	        Tokenizer<CoreLabel> tokenizer =
//	            tokenizerFactory.getTokenizer(
//	                new StringReader(str));    
//	        return tokenizer.tokenize();
//	    }
	
	private static void printTree(Tree t) {
		int n = t.numChildren();
	//	System.out.println("*" + t.nodeString());
		List<Tree> children = t.getChildrenAsList();
		//System.out.println(children.size());
		for(Tree i: children) {
			printTree(i);
			
		}
	}
	
	private static ParsedTree createTree(Tree binaryTree) {
		List<Tree> children = binaryTree.getChildrenAsList();
		if(children.size() == 0) {
			ParsedTree newTree = new ParsedTree(binaryTree.label().value());
			return newTree;
		}
		if(children.size() == 1) return createTree(children.get(0));
		ParsedTree newTree = new ParsedTree();
		newTree.left = createTree(children.get(0));
		newTree.right = createTree(children.get(1));
		return newTree;
	}
	 
	public static void main(String args[]) {
		FileReader fr;
		FileWriter fw;
		TreeBinarizer parserBinarized = new TreeBinarizer(parser.getTLPParams().headFinder(), parser.treebankLanguagePack(), 
                false, false, 0, false, false, 0.0, false, true, true);
		String processedLine = "";
		try {
			fr = new FileReader(FILE_READER_PATH);
			//fw = new FileWriter(FILE_WRITER_PATH);
			BufferedReader br = new BufferedReader(fr);
			//BufferedWriter bw = new BufferedWriter(fw);
			String originalLine;
			int k = 0;
			while ((originalLine = br.readLine()) != null) {
//				processedLine = originalLine;
//				processedLine = originalLine.replaceAll("\\|", " ");
//				Tree tree = parser.parse(processedLine); 
//				Tree binarizedTree = parserBinarized.transformTree(tree);
//				ParsedTree t = createTree(binarizedTree);
//			    t.setValuesForLeaves(1);
//			    t.updateInnerNodes();
//			    int[] a = t.parentPointerRepresentation();
//			    String treeString = "" + a[0];
//			    for(int i = 1; i < a.length; i++) treeString = treeString + "|" +a[i];
			//	bw.write(treeString);
			//	bw.newLine();
				k++;
				
				System.out.println("k=" + k);
			}
			//bw.close();
			//fw.close();
		} catch (IOException e) {
			System.out.println("Errooor");
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		processedLine = "One of the best movies of the year .";
		 //Parser parser = new Parser(); 
	     Tree tree = parser.parse(processedLine); 
	     System.out.println(tree);
	     printTree(tree);
	     
	     Tree secondTree = parserBinarized.transformTree(tree);
	     ParsedTree t = createTree(secondTree);
	    // secondTree.
	     System.out.println("*****");
	     System.out.println(secondTree);
	     System.out.println("*****");
	     t.setValuesForLeaves(1);
	     System.out.println("++++++");
	     t.printTree();
	     t.updateInnerNodes();
	     System.out.println("*****");
	     t.printTree();
	     int[] a = t.parentPointerRepresentation();
	     //System.out.println(t);
	     System.out.println("*****");
	     for(int i = 0; i < a.length; i++) System.out.print(a[i] + " ");
	}
}
