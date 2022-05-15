
typedef struct {
    int MAC;
    omnetpp::simtime_t expire;
} ARPEntry;

typedef struct {
    int port;
    omnetpp::simtime_t expire;
} SwitchEntry;
