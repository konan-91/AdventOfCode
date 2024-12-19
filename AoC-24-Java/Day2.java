import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public static class SafeReports {
    public int std_reports;
    public int sbl_reports;

    public SafeReports(int std_reports, int sbl_reports) {
        this.std_reports = std_reports;
        this.sbl_reports = sbl_reports;
    }
}

public static boolean safetyCheck(int[] report) {
    boolean asc = true;
    boolean desc = true;

    for (int i = 1; i < report.length; i++) {
        int diff = report[i] - report[i - 1];
        if (Math.abs(diff) < 1 || Math.abs(diff) > 3) {
            return false;  // Invalid step size
        }
        if (diff <= 0) asc = false;   // Not increasing
        if (diff >= 0) desc = false;  // Not decreasing
    }

    return asc || desc;
}

public static SafeReports noSafeReports(Path path) throws IOException {
    int std_reports = 0, sbl_reports = 0;
    try (BufferedReader reader = Files.newBufferedReader(path)) {
        String line;

        while ((line = reader.readLine()) != null) {
            String[] split_line = line.split(" ");
            int[] report = new int[split_line.length];

            for (int i = 0; i < split_line.length; i++) {
                report[i] = Integer.parseInt(split_line[i]); // Converting strings to ints
            }

            if (safetyCheck(report)) {
                std_reports++;
            } else {
                int[][] combinations = new int[report.length][report.length - 1];

                // Iterate through report skipping one value, append vals to combinations[i][idx]
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

    return new SafeReports(std_reports, std_reports + sbl_reports);
}

public static void main() throws IOException {
    SafeReports result = noSafeReports(Path.of("day_2/input.txt"));
    System.out.printf("Safe Reports: %d\nTotal safe reports: %d", result.std_reports, result.sbl_reports);
}
