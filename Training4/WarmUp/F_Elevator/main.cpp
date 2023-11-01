#include <cstdint>
#include <iostream>
#include <vector>

int main()
{
    freopen("input.txt", "r", stdin);
    int capacity;
    int maxFlour;
    std::cin >> capacity >> maxFlour;
    int64_t time = 0;
    std::vector<int64_t> people(maxFlour + 1);
    for (int i = 1; i < maxFlour + 1; ++i) {
        int peoples;
        std::cin >> peoples;
        int trips = peoples / capacity;
        time += (int64_t)trips * 2 * i;
        people[i] = peoples % capacity;
    }
    int flour = maxFlour;
    int64_t loaded = 0;
    while (flour > 0) {
        if (people[flour] == 0) {
            flour--;
            continue;
        }
        if (loaded == 0) {
            time += 2LL * flour;
        }
        loaded += people[flour];
        if (loaded > capacity) {
            people[flour] = loaded % capacity;
            loaded = 0;
        } else {
            people[flour--] = 0;
        }
    }
    std::cout << time;
}
/*
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.math.BigInteger;

public class Task00f {

    public static void main(String[] args) throws IOException {
        var input = "input.txt";
        File file = new File(input);
        FileReader fileReader = new FileReader(file);
        try (BufferedReader reader = new BufferedReader(fileReader)) {
            String line = reader.readLine();
            int capacity = Integer.parseInt(line);
            line = reader.readLine();
            int maxFlour = Integer.parseInt(line);
            BigInteger time = BigInteger.ZERO;
            int[] people = new int[maxFlour + 1];
            for (int i = 1; i < maxFlour + 1; i++) {
                line = reader.readLine();
                int peoples = Integer.parseInt(line);
                int trips = peoples / capacity;
                time = time.add(BigInteger.valueOf((long) trips * i * 2));
                people[i] = peoples - trips * capacity;
            }
            int flour = maxFlour;
            int loaded = 0;
            while (flour > 0) {
                if (people[flour] == 0) {
                    flour--;
                    continue;
                }
                if (loaded == 0) {
                    time = time.add(BigInteger.valueOf(flour * 2L));
                }
                loaded += people[flour];
                if (loaded > capacity) {
                    people[flour] = loaded % capacity;
                    loaded = 0;
                } else {
                    people[flour--] = 0;
                }
            }
            System.out.println(time);
        }
    }

}
*/
