import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

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

    // Check rows for XMAS
    for (var line : input) {
        System.out.println(line);
        for (int i = 0; i < line.length; i++) {
            // if S found
            // check for AMX
            // if X found
            // check for MAS

        }
    }

    // Check columns for XMAS


    // Check crosses for XMAS
    // check ↘ for XMAS and SMAS
    // rotate matrix 90 degrees and check again
    // this covers everything!

    // OR check for XMAS and SMAS ↙, which is the same as rotating the matrix
    // more code but more efficient also.

    return 0;
}

public static void main() {
    System.out.println("Hello, Advent of Code day 4!");
    System.out.println(countXmas("day_4/input.txt"));
}
