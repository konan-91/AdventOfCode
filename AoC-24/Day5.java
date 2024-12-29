// Advent Of Code 2024, Day 5.
// https://adventofcode.com/2024/day/5

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;

public static List<List<Integer>> getRules(Path path) {
    List<List<Integer>> rules = new ArrayList<>();
    String line;

    try (BufferedReader br = Files.newBufferedReader(path)) {
        while ((line = br.readLine()) != null) {
            if (line.isEmpty()) {
                break;
            }

            String[] parts = line.split("\\|");
            if (parts.length == 2) {
                int num1 = Integer.parseInt(parts[0].trim());
                int num2 = Integer.parseInt(parts[1].trim());
                rules.add(Arrays.asList(num1, num2));
            }
        }
    } catch (IOException e) {
        throw new RuntimeException(e);
    }

    return rules;
}

public static List<List<Integer>> getArrays(Path path) {
    List<List<Integer>> arrays = new ArrayList<>();
    boolean atArrays = false;
    String line;

    try (BufferedReader br = Files.newBufferedReader(path)) {
        while ((line = br.readLine()) != null) {
            if (line.isEmpty()) {
                atArrays = true;
                continue;
            }

            if (atArrays) {
                List<Integer> lineArray = new ArrayList<>();
                String[] parts = line.split(",");
                for (String part : parts) {
                    lineArray.add(Integer.parseInt(part.trim()));
                }

                arrays.add(lineArray);
            }
        }
    } catch (IOException e) {
        throw new RuntimeException(e);
    }

    return arrays;
}

public static Map<Integer, List<Integer>> getRulesMap(Path path) {
    Map<Integer, List<Integer>> rulesMap = new HashMap<>();
    List<List<Integer>> rulesList = getRules(path);
    for (List<Integer> rule : rulesList) {
        rulesMap.computeIfAbsent(rule.get(0), _ -> new ArrayList<>()).add(rule.get(1));
    }

    return rulesMap;
}

public static List<Integer> sumUpdates(Path path){
    int middleValSum = 0;
    int middleValSumOrdered = 0;

    Map<Integer, List<Integer>> rulesMap = getRulesMap(path);
    List<List<Integer>> arraysList = getArrays(path);
    List<List<Integer>> invalidArraysList = new ArrayList<>();

    outer: // Verify arrays do not break rules, sum middle values
    for (var array : arraysList) {
        for (int i = array.size() - 1; i > 0; i--) {
            List<Integer> illegalVals = rulesMap.get(array.get(i));
            for (int j = i; j >= 0; j--) {
                if (illegalVals.contains(array.get(j))) {
                    invalidArraysList.add(array);
                    continue outer;
                }
            }
        }

        middleValSum += array.get(array.size() / 2);
    }

    // Order invalid arrays then sum middle values
    for (var array : invalidArraysList) {
        for (int i = array.size() - 1; i > 0; i--) {
            int j = i - 1;
            while (j >= 0) {
                if (rulesMap.get(array.get(i)).contains(array.get(j))) {
                    int iCopy = array.get(i); // Swap values at pointers
                    array.set(i, array.get(j));
                    array.set(j, iCopy);
                    j = i - 1;
                    continue;
                }

                j--;
            }
        }

        middleValSumOrdered += array.get(array.size() / 2);
    }

    return Arrays.asList(middleValSum, middleValSumOrdered);
}

public static void main() {
    Path path = Path.of("AoC-24/input_files/day_5/input.txt");
    List<Integer> result = sumUpdates(path);
    System.out.printf("Sum of middle values from valid  %d%n", result.get(0));
    System.out.printf("Sum of middle values from ordered invalid lines: %d%n", result.get(1));
}
