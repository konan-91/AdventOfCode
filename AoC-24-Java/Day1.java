import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public static int getAbsDiff(List<String> locations) {
    List<Integer> list1 = new ArrayList<>();
    List<Integer> list2 = new ArrayList<>();

    for (String location : locations) {
        String[] split = location.split("\\s+");
        list1.add(Integer.parseInt(split[0]));
        list2.add(Integer.parseInt(split[1]));
    }

    list1.sort(null);
    list2.sort(null);

    int sum = 0;
    for (int i = 0; i < list1.size(); i++) {
        sum += Math.abs(list1.get(i) - list2.get(i));
    }
    return sum;
}

public static int getSimilarity(List<String> locations) {
    List<Integer> list1 = new ArrayList<>();
    List<Integer> list2 = new ArrayList<>();

    for (String location : locations) {
        String[] split = location.split("\\s+");
        list1.add(Integer.parseInt(split[0]));
        list2.add(Integer.parseInt(split[1]));
    }

    Map<Integer, Integer> freq_dict = new HashMap<>();
    for (Integer num : list1) {
        freq_dict.put(num, 0);
    }
    for (Integer num : list2) {
        freq_dict.put(num, freq_dict.getOrDefault(num, 0) + 1);
    }

    int sum = 0;
    for (Integer num : list1) {
        sum += num * freq_dict.get(num);
    }
    return sum;
}

public static void main() throws IOException {
    List<String> locations = Files.readAllLines(Path.of("day_1/input.txt"));

    System.out.printf("Sum: %d%n", getAbsDiff(locations));
    System.out.printf("Similarity: %d%n", getSimilarity(locations));
}
