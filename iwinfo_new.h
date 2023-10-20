#include <inttypes.h>
#include <netinet/if_ether.h>
#include <linux/nl80211.h>

int nl80211_init(const char *ifname, int *phyid, char *mac_addr, enum nl80211_iftype *type);

