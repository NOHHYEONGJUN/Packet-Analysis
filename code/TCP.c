#pragma once
#include "TCP.h"
void ParseTCP(uchar* base, uint len)
{
    TCPHeader* th = (TCPHeader*)base;
    printf("\n★★★★★    TCP header  ★★★★★\n");
    printf("\n\tsrc port : %u\n", ntohs(th->src_port));
    printf("\tdest port : %u\n", ntohs(th->dst_port));
    printf("\tseq no : %u\n", ntohl(th->seqno));
    printf("\tack no : %u\n", ntohs(th->ackno));
    printf("\t");
    if (th->syn) { printf("SYN "); }
    if (th->ack) { printf("ACK "); }
    if (th->fin) { printf("FIN "); }
    if (th->rst) { printf("RST "); }
    if (th->psh) { printf("PSH "); }
    if (th->urg) { printf("URG "); }
    printf("\n");
    printf("\twindow size : %u\n", ntohs(th->winsize));
    printf("\turg pointer : %u\n", ntohs(th->upoint));
}
