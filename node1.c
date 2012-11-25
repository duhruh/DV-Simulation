#include <stdio.h>
#include <string.h>
#define INFINITY 99
#define NODE1 1
#define TRUE 1
#define FALSE 0

int isNeighbor1(int);
int sendToNeighbors1(int,int[]);


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

int connectcosts1[4] = { 1,  0,  1, 999 };

struct distance_table 
{
  int costs[4][4];
} dt1;

int minCost1[4];		/*The distance vector between current node and other nodes*/
int linkCost1[4];  /* link cost from the node to other nodes */
/* students to write the following two routines, and maybe some others */
int sendDV1;

rtinit1() 
{
    linkCost1[0] = 1;
    linkCost1[1] = 0;
    linkCost1[2] = 1;
    linkCost1[3] = INFINITY;

    memcpy(dt1.costs[NODE1],linkCost1,sizeof(int[4]));
    memcpy(minCost1,linkCost1,sizeof(int[4]));
    sendDV1 = FALSE;

    printdt1();
    sendToNeighbors1(NODE1,minCost1);
}


rtupdate1(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{
    if(isNeighbor1(rcvdpkt->sourceid)){
        int i;
        for(i = 0; i < 4; i++){
            if(minCost1[i] > rcvdpkt->mincost[i]){
                int possibleRoute = minCost1[rcvdpkt->sourceid]+rcvdpkt->mincost[i];
                if(possibleRoute < minCost1[i]){
                    minCost1[i] = possibleRoute;
                    sendDV1 = TRUE;
                }
            }
        }
        memcpy(dt1.costs[NODE1],minCost1,sizeof(int[4]));
        memcpy(dt1.costs[rcvdpkt->sourceid],rcvdpkt->mincost,sizeof(int[4]));
        printdt1();
    }
    if(sendDV1){
        sendToNeighbors1(NODE1,minCost1);
        sendDV1 = FALSE;
    }

}

int isNeighbor1(int sourceid){
    return linkCost1[sourceid] != INFINITY;
}
int sendToNeighbors1(int sourceid, int mincost[]){
    int i;
    for(i = 0; i < 4; i++){
       if(isNeighbor1(i) && i != sourceid) sendrtpkt(sourceid, i, mincost);
    }
}


printdt1()
{
  printf("              cost to   \n");
  printf("   D1 |    0    1     2    3 \n");
  printf("  ----|----------------------\n");
  printf("     0|  %3d   %3d   %3d  %3d\n",dt1.costs[0][0], dt1.costs[0][1], dt1.costs[0][2],dt1.costs[0][3]);
  printf("     1|  %3d   %3d   %3d  %3d\n",dt1.costs[1][0], dt1.costs[1][1], dt1.costs[1][2],dt1.costs[1][3]);
  printf("from 2|  %3d   %3d   %3d  %3d\n",dt1.costs[2][0], dt1.costs[2][1], dt1.costs[2][2],dt1.costs[2][3]);

}

linkhandler1(linkid, newcost)
  int linkid, newcost;
{
}
