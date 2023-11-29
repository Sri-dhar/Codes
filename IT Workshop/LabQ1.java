import java.io.*;
import java.util.*;

public class LabQ1 {
    public static void main(String[] args) throws IOException {
        if (args.length != 2) {
            System.out.println("Usage: java DisplayCommonWords file1.txt file2.txt");
            return;
        }

        Map<String, Set<Integer>> file1Words = getWords(args[0]);
        Map<String, Set<Integer>> file2Words = getWords(args[1]);

        System.out.println("The following words are common in both files with the following details:");
        for (String word : file1Words.keySet()) {
            if (file2Words.containsKey(word)) {
                System.out.println(word + ": length " + word.length() + ", appeared in " + file1Words.get(word) + " line of " + args[0] + " and " + file2Words.get(word) + " line in " + args[1]);
            }
        }
    }

    private static Map<String, Set<Integer>> getWords(String filename) throws IOException {
        Map<String, Set<Integer>> words = new HashMap<>();
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line;
            int lineNumber = 1;
            while ((line = reader.readLine()) != null) {
                for (String word : line.split("\\s+")) {
                    words.computeIfAbsent(word, k -> new HashSet<>()).add(lineNumber);
                }
                lineNumber++;
            }
        }
        return words;
    }
}