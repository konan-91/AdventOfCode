// Advent Of Code 2024, Day 2.
// https://adventofcode.com/2024/day/2

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.List;

public static boolean safetyCheck(int[] report) {
    boolean asc = true;
    boolean desc = true;

    for (int i = 1; i < report.length; i++) {
        int diff = report[i] - report[i - 1];
        if (Math.abs(diff) < 1 || Math.abs(diff) > 3) {
            return false;
        }
        if (diff <= 0) asc = false;
        if (diff >= 0) desc = false;
    }

    return asc || desc;
}

public static List<Integer> noSafeReports(Path path) throws IOException {
    int std_reports = 0, sbl_reports = 0;
    try (BufferedReader reader = Files.newBufferedReader(path)) {
        String line;

        while ((line = reader.readLine()) != null) {
            String[] split_line = line.split(" ");
            int[] report = new int[split_line.length];

            for (int i = 0; i < split_line.length; i++) {
                report[i] = Integer.parseInt(split_line[i]);
            }

            if (safetyCheck(report)) {
                std_reports++;
            } else {
                int[][] combinations = new int[report.length][report.length - 1];
                for (int i = 0; i < report.length; i++) {
                    int idx = 0;
                    for (int j = 0; j < report.length; j++) {
                        if (j == i) {
                            continue;
                        }
                        combinations[i][idx] = report[j];
                        idx++;
                    }
                }

                for (var combo : combinations) {
                    if (safetyCheck(combo)) {
                        sbl_reports++;
                        break;
                    }
                }
            }
        }
    }

    return Arrays.asList(std_reports, std_reports + sbl_reports);
}

public static void main() throws IOException {
    List<Integer> result = noSafeReports(Path.of("AoC-24/input_files/day_02/input.txt"));
    System.out.printf("Safe Reports: %d\nTotal safe reports: %d", result.get(0), result.get(1));
}
