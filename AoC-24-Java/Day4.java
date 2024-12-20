import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

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

public static int countXmas(String path) {
    char[][] input = fileToArray(path);
    int xmasCount = 0;
/*
    // Check rows for XMAS
    for (var line : input) {
        System.out.println(line);
        for (int i = 0; i < line.length - 4; i++) {
            if (line[i] == 'X') { // FIX THIS SECTION! COMPARE NEXT 3 VALS AT ONCE.
                if (line[i+1: i+4] == "MAS") {
                    xmasCount++;
                }
            } else if (line[i] == 'S') {
                if (line[i+1: i+4] == "AMX") {
                    xmasCount++;
                }
            }
        }
    }

    // Check columns for XMAS
    for (int i = 0; i < input[0].length; i++) {
        for (int j = 0; j < input.length - 4; j++) {
            if (input[j][i] == 'X') {
                if (input[j+1: j+4] == "MAS") {
                    xmasCount++;
                }
            } else if (input[j][i] == 'S') {
                if (input[j+1: j+4][i] == "AMX") {
                    xmasCount++;
                }
            }
        }
    }
 */

    // TODO: create a new char[][] by rotating input[][] 90 degrees. Wrap below in loop which uses both as input.

    // TODO: Convert arrays of chars to strings (or get them as strings) for substring comparisons ("XMAS").

    // Starting at bottom left corner and getting diagonals
    for (int i = 4; i <= input.length; i++) {
        int start = input.length - i;
        int j = 0;
        List<Character> diagonal = new ArrayList<>();

        // Iterate through diagonal
        while (start != input.length) {
            diagonal.add(input[start][j]);
            start++;
            j++;
        }

        System.out.println(diagonal);
    }

    // Same as before, but starting from top right corner and ending before middle
    for (int i = 4; i <= input.length - 1; i++) {
        int start = input.length - i;
        int j = 0;
        List<Character> diagonal = new ArrayList<>();

        // Iterate through diagonal
        while (start != input.length) {
            diagonal.add(input[j][start]);
            start++;
            j++;
        }

        System.out.println(diagonal);
    }

    return 0;
}

public static void main() {
    System.out.println("Hello, Advent of Code day 4!");
    System.out.println(countXmas("AoC-24-Java/input_files/day_4/input.txt"));
}
