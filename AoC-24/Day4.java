// Advent Of Code 2024, Day 4.

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;
import java.util.stream.Collectors;

public static char[][] fileToArray(String path) {
    char[][] input = new char[140][140];

    try (BufferedReader reader = Files.newBufferedReader(Path.of(path))) {
        String line;
        int j = 0;
        while ((line = reader.readLine()) != null) {
            for (int i = 0; i < line.length(); i++) {
                input[j][i] = line.charAt(i);
            }
            j++;
        }
    } catch (IOException e) {
        e.printStackTrace();
        System.out.println("Error opening file!");
    }

    return input;
}

public static List<String> getWordSearch(String path) {
    char[][] input = fileToArray(path);
    int size = input.length;
    int length = input[0].length;

    // Getting rows and columns
    List<String> wordSearch = Arrays.stream(input)
            .map(String::new)
            .collect(Collectors.toCollection(ArrayList::new));
    for (int i = 0; i < length; i++) {
        StringBuilder col = new StringBuilder(size);
        for (char[] chars : input) {
            col.append(chars[i]);
        }
        wordSearch.add(col.toString());
    }

    // Create new matrix rotated 90 degrees for full diagonal coverage
    char[][] inputRotated = new char[size][length];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            inputRotated[j][size - i - 1] = input[i][j];
        }
    }

    List<char[][]> inputList = new ArrayList<>();
    inputList.add(input);
    inputList.add(inputRotated);

    for (var matrix : inputList) {
        // Getting diagonals from LHS to BOTTOM
        for (int i = 4; i <= size; i++) {
            int j = 0;
            int start = size - i;
            StringBuilder diagonal = new StringBuilder(size);
            while (start != size) {
                diagonal.append(matrix[start][j]);
                start++;
                j++;
            }

            wordSearch.add(diagonal.toString());
        }

        // Getting diagonals from TOP to RHS
        for (int i = 4; i <= size - 1; i++) {
            int start = size - i;
            int j = 0;
            StringBuilder diagonal = new StringBuilder(size);
            while (start != size) {
                diagonal.append(matrix[j][start]);
                start++;
                j++;
            }

            wordSearch.add(diagonal.toString());
        }
    }

    return wordSearch;
}

public static int getXmasCount(String path) {
    int xmasCount = 0;
    List<String> wordSearch = getWordSearch(path);

    for (String str : wordSearch) {
        int index = 0;
        while ((index = str.indexOf("XMAS", index)) != -1) {
            xmasCount++;
            index += "XMAS".length();
        }
        index = 0;
        while ((index = str.indexOf("SAMX", index)) != -1) {
            xmasCount++;
            index += "SAMX".length();
        }
    }

   return xmasCount;
}

public static int getXofMasCount(String path) {
    int XofMasCount = 0;
    char[][] input = fileToArray(path);

    // Verify 4 corners of X contain 2 M's & 2 S's
    for (int i = 1; i < input.length - 1; i++) {
        for (int j = 1; j < input[1].length - 1; j++) {
            if (input[i][j] == 'A') {
                Set<Character> chars = new HashSet<>();
                chars.add(input[i + 1][j + 1]);
                chars.add(input[i - 1][j - 1]);

                if (chars.size() != 2 || !chars.contains('M') || !chars.contains('S')) {
                    continue;
                }

                chars.clear();
                chars.add(input[i + 1][j - 1]);
                chars.add(input[i - 1][j + 1]);

                if (chars.size() == 2 && chars.contains('M') && chars.contains('S')) {
                    XofMasCount++;
                }
            }
        }
    }

    return XofMasCount;
}

public static void main() {
    System.out.printf("XMAS count: %d%n", getXmasCount("AoC-24/input_files/day_4/input.txt"));
    System.out.printf("X of MAS count: %d%n", getXofMasCount("AoC-24/input_files/day_4/input.txt"));
}
