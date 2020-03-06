

struct forwarding_table {
	int valid[100];
	int dst[100];
	//struct net_port *port[100];
};

void switch_main(int host_id);
