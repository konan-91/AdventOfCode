import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

private static final int NUM_LENGTH = 3;
private static final int NUM_COUNT = 2;

public static int mulCheck(String str, int i) {
    // Increment i to check for "mul(", "x", ",", "y", ")"
    if (i + NUM_LENGTH > str.length() || !str.substring(i, i + 4).equals("mul(")) {
        return -1;
    }

    i += 4;
    int[] nums = new int[NUM_COUNT];

    for (int x = 0; x < NUM_COUNT; x++) {
        StringBuilder num = new StringBuilder();
        // Collect digits into a string until reaching a non-digit character
        while (i < str.length() && Character.isDigit(str.charAt(i))) {
            num.append(str.charAt(i++));
            if (num.length() > NUM_LENGTH) {
                break;
            }
        }

        // Returning if "," is not after num1, or ")" after num2
        if (x == 0 && (i >= str.length() || str.charAt(i) != ',')) {
            return -6;
        } else if (x == 1 && (i >= str.length() || str.charAt(i) != ')')) {
            return -8;
        }

        nums[x] = Integer.parseInt(num.toString()); // Convert StringBuilder to string, then to an int
        i++; // Increment i to start of next number, or to end of mul(x,y)_
    }

    return nums[0] * nums[1];
}

public static int mulCounter(Path path) {
    // Reading program instructions into memory
    String instructions;
    try {
        instructions = Files.readString(path);
    } catch (IOException e) {
        e.printStackTrace();
        return -1;
    }

    // Looking for "mul(x,y)" in string, and do()/don't()'s
    int sum = 0, i = 0;
    boolean mulCheckEnabled = true;

    while (i < instructions.length() - 7) {
        // mulCheckSwitch = true; // uncomment this line for puzzle 1 result
        if (mulCheckEnabled) {
            if (instructions.charAt(i) == 'm') {
                int res = mulCheck(instructions, i);
                if (res > 0) {
                    sum += res; // mul(x,y) was valid, skip ahead
                    i += 8;
                } else {
                    i += Math.abs(res); // was not valid, skip ahead
                }
            } else {
                i++;
            }
        } else if (instructions.startsWith("do()", i)) {
            mulCheckEnabled = true; // enable mulCheck()
            i += 4;
        } else {
            i++; // Do nothing if check is disabled
        }

        // Check if mulCheck() should be disabled
        if (instructions.startsWith("don't()", i)) {
            mulCheckEnabled = false;
            i += 7;
        }
    }

    return sum;
}

public static void main() {
    int answer = mulCounter(Path.of("AoC-24-Java/input_files/day_3/input.txt"));
    System.out.printf("%nSum of Multiplications: %d%n", answer);
}
