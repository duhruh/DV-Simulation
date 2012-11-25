#include <stdio.h>
#include <string.h>
#define INFINITY 99
#define NODE2 2
#define TRUE 1
#define FALSE 0

int isNeighbor2(int);
int sendToNeighbors2(int,int[]);

extern struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };

extern int TRACE;
extern int YES;
extern int NO;
extern float clocktime;

struct distance_table 
{
  int costs[4][4];
} dt2;

int minCost2[4];		/*The distance vector between current node and other nodes*/
int linkCost2[4];  /* link cost from the node to other nodes */
/* students to write the following two routines, and maybe some others */
int sendDV2;

void rtinit2() 
{
    linkCost2[0] = 3;
    linkCost2[1] = 1;
    linkCost2[2] = 0;
    linkCost2[3] = 2;

    memcpy(dt2.costs[NODE2],linkCost2,sizeof(int[4]));
    memcpy(minCost2,linkCost2,sizeof(int[4]));
    sendDV2 = FALSE;

    printdt2();
    sendToNeighbors2(NODE2,minCost2);

}


void rtupdate2(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{
    if(isNeighbor2(rcvdpkt->sourceid)){
        int i;
        for(i = 0; i < 4; i++){
            if(minCost2[i] > rcvdpkt->mincost[i]){
                int possibleRoute = minCost2[rcvdpkt->sourceid]+rcvdpkt->mincost[i];
                if(possibleRoute < minCost2[i]){
                    minCost2[i] = possibleRoute;
                    sendDV2 = TRUE;
                }
            }
        }
        memcpy(dt2.costs[NODE2],minCost2,sizeof(int[4]));
        memcpy(dt2.costs[rcvdpkt->sourceid],rcvdpkt->mincost,sizeof(int[4]));
        printdt2();
    }
    if(sendDV2){
        sendToNeighbors2(NODE2,minCost2);
        sendDV2 = FALSE;
    }

}

int isNeighbor2(int sourceid){
    return linkCost2[sourceid] != INFINITY;
}
int sendToNeighbors2(int sourceid, int mincost[]){
    int i;
    for(i = 0; i < 4; i++){
       if(isNeighbor2(i) && i != sourceid) sendrtpkt(sourceid, i, mincost);
    }
}


printdt2()
{
  printf("              cost to   \n");
  printf("   D2 |    0    1     2    3 \n");
  printf("  ----|----------------------\n");
  printf("     0|  %3d   %3d   %3d  %3d\n",dt2.costs[0][0], dt2.costs[0][1], dt2.costs[0][2],dt2.costs[0][3]);
  printf("     1|  %3d   %3d   %3d  %3d\n",dt2.costs[1][0], dt2.costs[1][1], dt2.costs[1][2],dt2.costs[1][3]);
  printf("from 2|  %3d   %3d   %3d  %3d\n",dt2.costs[2][0], dt2.costs[2][1], dt2.costs[2][2],dt2.costs[2][3]);
  printf("     3|  %3d   %3d   %3d  %3d\n",dt2.costs[3][0], dt2.costs[3][1], dt2.costs[3][2],dt2.costs[3][3]);
}


linkhandler2(linkid, newcost)   
  int linkid, newcost;
{
}
