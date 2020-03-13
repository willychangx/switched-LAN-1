#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <unistd.h>
#include <fcntl.h>

#include "main.h"
#include "net.h"
#include "man.h"
#include "host.h"
#include "packet.h"
#include "switch.h"

#define TENMILLISEC 10000
#define MAXTABLE 100

struct forwarding_table {
	int dst[MAXTABLE];
	int valid[MAXTABLE];
	struct net_port *port[MAXTABLE];
};

void switch_main(int host_id)
{
int sent=0;
int found=0;
struct net_port *p;
struct forwarding_table *fwdtable;
struct packet *in_packet;
int node_port_num;
struct net_port *switch_port;
struct net_port *node_port_list;
struct net_port **node_port;
struct man_port_at_host *man_port;
int n;

fwdtable = (struct forwarding_table *) malloc(sizeof(struct forwarding_table));

for(int f=0; f<MAXTABLE; f++){
	fwdtable->dst[f] = 0;
}

man_port = net_get_host_port(host_id);
node_port_list = net_get_port_list(host_id);

node_port_num = 0;
for (p=node_port_list; p!=NULL; p=p->next){
	node_port_num++;
}

node_port = (struct net_port **)
	malloc(node_port_num*sizeof(struct net_port *));

p = node_port_list;
for(int k=0; k < node_port_num; k++) {
	node_port[k] = p;
	p = p->next;
}

while(1) {
	found = 0; sent = 0;
	for (int k=0; k < node_port_num; k++) {
		in_packet = (struct packet *) malloc(sizeof(struct packet));
		n = packet_recv(node_port[k], in_packet);
		if(n > 0) {
			for(int i=0; i<100; i++){
				if(fwdtable->valid[i]){
					if(fwdtable->dst[i] == in_packet->dst){
						packet_send(fwdtable->port[i], in_packet);
						sent = 1;
					}
					if(fwdtable->dst[i] == in_packet->src) found=1;
				}
			}
			if(!sent){
				for(int q=0; q < node_port_num; q++) {
					if(q != k)
						packet_send(node_port[q], in_packet);
				}
			}
			if(!found){
				for(int i=0; i<100; i++){
					if(fwdtable->valid[i] == 0) {
						fwdtable->valid[i] = 1;
						fwdtable->dst[i] = in_packet->src;
						fwdtable->port[i] = node_port[k];
					}
				}
			}
		}
		usleep(TENMILLISEC);
	}
}
}
