#include <sys/wait.h>
#include <unistd.h>
#include <string>

auto main() -> int {
    int fd[2];  // fd[0] - read; fd[1] - write
    // create pipe and check if it was created
    if (pipe(fd) == -1) {
        return 1;
    }

    // create the process
    int id = fork();

    if (id == -1) {  // fork error
        return 2;
    } else if (id == 0) {  // child
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);

        execlp("./calc", "./calc", NULL);

        return 3;
    } else {  // parent
        close(fd[0]);
        char c;

        while (read(STDIN_FILENO, &c, sizeof(char)) > 0) {
            if (c == '\n') {
                break;  // stop reading if \n
            }
            if (write(fd[1], &c, sizeof(char)) == -1) {
                return 5;
            }
        }

        close(fd[1]);

        int status;
        waitpid(0, &status, 0);  // wait child process finish

        if (status != 0)
            return 6;
    }

    return 0;
}