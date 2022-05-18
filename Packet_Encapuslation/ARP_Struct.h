
typedef struct {    // the entry in the arp table of the host, mapping destination IP to MAC addreses
    int MAC;
    omnetpp::simtime_t expire;
} ARPEntry;

typedef struct {    // the entry in the forwarding table of the Switch, mapping destination MAC to exit port
    int port;
    omnetpp::simtime_t expire;
} SwitchEntry;
