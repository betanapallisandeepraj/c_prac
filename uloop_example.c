#include <libubox/uloop.h>
#include <libubox/utils.h>
#include <unistd.h>
#include <stdio.h>  // Add this line

void stdin_cb(struct uloop_fd *u, unsigned int events) {
    char buf[128];
    ssize_t len;
    printf("callback function started\n");
    len = read(u->fd, buf, sizeof(buf));
    if (len < 0) {
        perror("read");
        return;
    }

    buf[len] = '\0';
    printf("Read from stdin: %s\n", buf);
}

int main(void) {
    struct uloop_fd stdin_fd = {
        .fd = STDIN_FILENO,
        .cb = stdin_cb,
    };

    uloop_init();
    uloop_fd_add(&stdin_fd, ULOOP_READ);

    printf("Waiting for input...\n");
    uloop_run();
    uloop_done();

    return 0;
}

