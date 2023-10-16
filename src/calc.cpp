#include <fcntl.h>
#include <unistd.h>
#include <string>

auto main() -> int {
    int outputd;
    outputd = open("output.txt", O_RDWR | O_CREAT, 0666);
    std::string s = "0";
    char ch;
    int sum = 0;

    while (read(STDIN_FILENO, &ch, ch!='\n')) {
        if ( ch == ' '){
         sum += std::stoi(s);
         s = "";
        }
        else
         s += ch;
    }
    sum+=std::stoi(s);

    std::string sum_str = std::to_string(sum);

    char output[100];
    sprintf(output, "The sum is: %d", sum);

    if (write(outputd, &output, 13 + sum_str.length()) == -1) {
        return 1;
    }
}
