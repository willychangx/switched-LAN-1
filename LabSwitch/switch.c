#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <unistd.h>

#include "main.h"
#include "net.h"
#include "man.h"
#include "host.h"
#include "packet.h"
#include "switch.h"

#define TENMILLISEC 10000
void switch_main(int host_id)
{
int sent=0;
int found=0;
struct net_port *p;
struct forwarding_table *ft;
struct packet *in_packet;
int node_port_num;
struct net_port *switch_port;
struct net_port *node_port_list;
struct net_port **node_port;
int n;

for(int i=0; i<100; i++){
	printf("am i here\n");
	ft->valid[i] = 0;
	printf("how many\n");
}
printf("hell\n");
/*node_port_list = net_get_port_list(host_id);
printf("help\n");
node_port_num = 0;
for (p=node_port_list; p!=NULL; p=p->next){
	node_port_num++;
}
printf("node_port_num: %d\n", node_port_num);

p = node_port_list;
for(int k=0; k < node_port_num; k++) {
	node_port[k] = p;
	p = p->next;
}

while(1) {
	printf("working\n");
	found = 0; sent = 0;
	for (int k=0; k < node_port_num; k++) {
		in_packet = (struct packet *) malloc(sizeof(struct packet));
		n = packet_recv(node_port[k], in_packet);

		if(n > 0) {
			for(int i=0; i<100; i++){
				if(ft->valid[i]){
					if(ft->dst[i] == in_packet->dst){
						packet_send(ft->port[i], in_packet);
						sent = 1;
					}
					if(ft->dst[i] == in_packet->src) found=1;
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
					if(ft->valid[i] == 0) {
						ft->valid[i] = 1;
						ft->dst[i] = in_packet->src;
						ft->port[i] = node_port[k];
					}
				}
			}
		}
		usleep(TENMILLISEC);
	}
}*/
}
