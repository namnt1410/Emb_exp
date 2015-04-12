#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/fcntl.h>

#define FIFO_FILE_PATH "myfifo"
#define BUFF_SIZE 256

int main()
{
    int fifoFd;
    char buf[BUFF_SIZE];

    /* open, read, and display the message from the FIFO */
    fifoFd = open(FIFO_FILE_PATH, O_RDONLY);
    read(fifoFd, buf, BUFF_SIZE);
    printf("Received: %s\n", buf);

    close(fifoFd);
    unlink(FIFO_FILE_PATH);

    return 0;
}
