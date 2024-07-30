#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <net/if.h>
#include <linux/nl80211.h>
#include <netlink/netlink.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/ctrl.h>
#include <netlink/msg.h>
#include <netlink/attr.h>

static int error_handler(struct sockaddr_nl *nla, struct nlmsgerr *err, void *arg) {
    int *ret = arg;
    *ret = err->error;
    return NL_STOP;
}

static int finish_handler(struct nl_msg *msg, void *arg) {
    int *ret = arg;
    *ret = 0;
    return NL_SKIP;
}

static int ack_handler(struct nl_msg *msg, void *arg) {
    int *ret = arg;
    *ret = 0;
    return NL_STOP;
}

int channel_to_frequency(int channel) {
    if (channel >= 1 && channel <= 14) {
        return 2407 + channel * 5;
    } else if (channel >= 36 && channel <= 165) {
        return 5000 + (channel - 36) * 5 + 5000;
    } else {
        return -1; // Invalid channel
    }
}

void switch_channel(const char *iface, int channel) {
    struct nl_sock *sock = nl_socket_alloc();
    if (!sock) {
        perror("Unable to allocate netlink socket");
        return;
    }

    if (genl_connect(sock)) {
        perror("Unable to connect to netlink");
        nl_socket_free(sock);
        return;
    }

    int driver_id = genl_ctrl_resolve(sock, "nl80211");
    if (driver_id < 0) {
        perror("nl80211 interface not found");
        nl_socket_free(sock);
        return;
    }

    int ifindex = if_nametoindex(iface);
    if (ifindex == 0) {
        perror("Unable to find interface index");
        nl_socket_free(sock);
        return;
    }

    int frequency = channel_to_frequency(channel);
    if (frequency == -1) {
        fprintf(stderr, "Invalid channel: %d\n", channel);
        nl_socket_free(sock);
        return;
    }

    struct nl_msg *msg = nlmsg_alloc();
    if (!msg) {
        perror("Unable to allocate netlink message");
        nl_socket_free(sock);
        return;
    }

    genlmsg_put(msg, 0, 0, driver_id, 0, 0, NL80211_CMD_SET_WIPHY, 0);

    nla_put_u32(msg, NL80211_ATTR_IFINDEX, ifindex);
    nla_put_u32(msg, NL80211_ATTR_WIPHY_FREQ, frequency);
    nla_put_u32(msg, NL80211_ATTR_WIPHY_CHANNEL_TYPE, NL80211_CHAN_NO_HT);

    int ret = nl_send_auto(sock, msg);
    if (ret < 0) {
        perror("Unable to send netlink message");
        nlmsg_free(msg);
        nl_socket_free(sock);
        return;
    }

    int err = 1;
    struct nl_cb *cb = nl_cb_alloc(NL_CB_DEFAULT);
    if (!cb) {
        perror("Unable to allocate netlink callback");
        nlmsg_free(msg);
        nl_socket_free(sock);
        return;
    }

    nl_cb_err(cb, NL_CB_CUSTOM, error_handler, &err);
    nl_cb_set(cb, NL_CB_FINISH, NL_CB_CUSTOM, finish_handler, &err);
    nl_cb_set(cb, NL_CB_ACK, NL_CB_CUSTOM, ack_handler, &err);

    while (err > 0) {
        ret = nl_recvmsgs(sock, cb);
        if (ret < 0) {
            perror("Error receiving netlink messages");
            break;
        }
    }

    nl_cb_put(cb);
    nlmsg_free(msg);
    nl_socket_free(sock);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <interface> <channel>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *iface = argv[1];
    int channel = atoi(argv[2]);

    switch_channel(iface, channel);

    return 0;
}

