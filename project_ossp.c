#include <stdio.h>
#include <stdlib.h>
#define max 25


//FCFS CPU SCHEDULING
void fcfscp()
{
  void findWaitingTime(int processes[], int n,int bt[], int wt[])
{
    wt[0] = 0;
    for (int  i = 1; i < n ; i++ )
        wt[i] =  bt[i-1] + wt[i-1] ;
}

void findTurnAroundTime( int processes[], int n, int bt[], int wt[], int tat[])
{
    for (int  i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];
}

void findavgTime( int processes[], int n, int bt[])
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTime(processes, n, bt, wt);
    findTurnAroundTime(processes, n, bt, wt, tat);
    printf("Processes   Burst time   Waiting time   Turn around time\n");
    for (int  i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf("   %d ",(i+1));
        printf("       %d ", bt[i] );
        printf("       %d",wt[i] );
        printf("       %d\n",tat[i] );
    }
    int s=(float)total_wt / (float)n;
    int t=(float)total_tat / (float)n;
    printf("Average waiting time = %d",s);
    printf("\n");
    printf("Average turn around time = %d ",t);
}
}

//SJFC CPU SCHEDULING
void sjfcp()
{
    int bt[20],p[20],wt[20],tat[20],i,j,n,total=0,pos,temp;
    float avg_wt,avg_tat;
    printf("Enter number of process: ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("\nnEnter Burst Time of process %d:",i+1);
        scanf("%d",&bt[i]);
        p[i]=i+1;
    }
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(bt[j]<bt[pos])
                pos=j;
        }
        temp=bt[i];
        bt[i]=bt[pos];
        bt[pos]=temp;
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
    }
    wt[0]=0;
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];

        total+=wt[i];
    }

    avg_wt=(float)total/n;
    total=0;
    printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];
        total+=tat[i];
        printf("\np%d\t\t  %d\t\t    %d\t\t\t%d",p[i],bt[i],wt[i],tat[i]);
    }
    avg_tat=(float)total/n;
    printf("\n\nAverage Waiting Time=%f",avg_wt);
    printf("\nAverage Turnaround Time=%f",avg_tat);
}


//Priority CPU SCHEDULING
void priorcp()
{
    int n;
    printf("Enter Number of Processes: ");
    scanf("%d",&n);
    int b[n],p[n],index[n];
    for(int i=0;i<n;i++)
    {
        printf("Enter Burst Time and Priority Value for Process %d: ",i+1);
        scanf("%d %d",&b[i],&p[i]);
        index[i]=i+1;
    }
    void swap(int *a,int *b)
	{
    	int temp=*a;
    	*a=*b;
    	*b=temp;
	}
    for(int i=0;i<n;i++)
    {
        int a=p[i],m=i;
        for(int j=i;j<n;j++)
        {
            if(p[j] > a)
            {
                a=p[j];
                m=j;
            }
        }
        swap(&p[i], &p[m]);
        swap(&b[i], &b[m]);
        swap(&index[i],&index[m]);
    }
    int t=0;
    printf("Order of process Execution is\n");
    for(int i=0;i<n;i++)
    {
        printf("P%d is executed from %d to %d\n",index[i],t,t+b[i]);
        t+=b[i];
    }
    printf("\n");
    printf("Process Id     Burst Time   Wait Time    TurnAround Time\n");
    int wait_time=0;
    for(int i=0;i<n;i++)
    {
        printf("P%d          \t%d         \t%d    \t      \t%d\n",index[i],b[i],wait_time,wait_time + b[i]);
        wait_time += b[i];
    }

}

//RR CPU SCHEDULING
void rrcp()
{
	int i, NOP, sum=0,count=0, y, quant, wt=0, tat=0, at[10], bt[10], temp[10];
	float avg_wt, avg_tat;
	printf(" Total number of process in the system: ");
	scanf("%d", &NOP);
	y = NOP;
	for(i=0; i<NOP; i++)
	{
		printf("\n Enter the Arrival and Burst time of the Process[%d]\n", i+1);
		printf(" Arrival time is: \t");
		scanf("%d", &at[i]);
		printf(" \nBurst time is: \t");
		scanf("%d", &bt[i]);
		temp[i] = bt[i];
	}
	printf("Enter the Time Quantum for the process: \t");
	scanf("%d", &quant);
	printf("\n Process No \t\t Burst Time \t\t TAT \t\t Waiting Time ");
	for(sum=0, i = 0; y!=0; )
	{
	if(temp[i] <= quant && temp[i] > 0)
	{
		sum = sum + temp[i];
	 	temp[i] = 0;
		 count=1;
	}
	else if(temp[i] > 0)
	{
		temp[i] = temp[i] - quant;
		sum = sum + quant;
	}
	if(temp[i]==0 && count==1)
	{
		y--;
		printf("\nProcess No[%d] \t\t %d\t\t\t\t %d\t\t\t %d", i+1, bt[i], sum-at[i], sum-at[i]-bt[i]);
		wt = wt+sum-at[i]-bt[i];
		tat = tat+sum-at[i];
		count =0;
	}
	if(i==NOP-1)
	{
		i=0;
	}
	else if(at[i+1]<=sum)
	{
		i++;
	}
	else
	{
		i=0;
	}
	}
	avg_wt = wt * 1.0/NOP;
	avg_tat = tat * 1.0/NOP;
	printf("\n Average Turn Around Time: \t%f", avg_wt);
	printf("\n Average Waiting Time: \t%f", avg_tat);

}

//Multilevel queue CPU SCHEDULING
void mqcp()
{
	int p[20],bt[20], su[20], wt[20],tat[20],i, k, n, temp;
	float wtavg, tatavg;
	printf("Enter the number of processes:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
	p[i] = i;
	printf("Enter the Burst Time of Process%d:", i+1);
	scanf("%d",&bt[i]);
	printf("System/User Process (0/1) ? ");
	scanf("%d", &su[i]);
	}
	for(i=0;i<n;i++)
		for(k=i+1;k<n;k++)
		if(su[i] > su[k])
		{
			temp=p[i];
			p[i]=p[k];
			p[k]=temp;
			temp=bt[i];
			bt[i]=bt[k];
			bt[k]=temp;
			temp=su[i];
			su[i]=su[k];
			su[k]=temp;
		}
	wtavg = wt[0] = 0;
	tatavg = tat[0] = bt[0];
	for(i=1;i<n;i++)
	{
	wt[i] = wt[i-1] + bt[i-1];
	tat[i] = tat[i-1] + bt[i];
	wtavg = wtavg + wt[i];
	tatavg = tatavg + tat[i];
	}
	printf("\nPROCESS\t\t SYSTEM/USER PROCESS \tBURST TIME\tWAITING TIME\tTURNAROUND TIME");
	for(i=0;i<n;i++)
	printf("\n%d \t\t %d \t\t %d \t\t %d \t\t %d ",p[i],su[i],bt[i],wt[i],tat[i]);
	printf("\nAverage Waiting Time is --- %f",wtavg/n);
	printf("\nAverage Turnaround Time is --- %f",tatavg/n);

}

//FCFS Disk SCHEDULING
void fcfs()
{
    printf("\t\t\tFCFS\n\n");
    int queue[20],n,head,i,j,dist=0,diff;
    printf("Enter the size of queue request: ");
    scanf("%d",&n);
    printf("Enter the queue of disk positions to be read: ");
    for (i = 1; i <= n; i++){
        scanf("%d", &queue[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    queue[0] = head;
    for (j=0;j<=n-1;j++)
    {
        diff=abs(queue[j + 1]-queue[j]);
        dist+= diff;
        }
    printf("\nTotal distance is %d\n", dist);
    printf("Seek Sequence is\n");
	for (int i = 0; i < n; i++){
		printf(" -> %d",queue[i]);
	}
	printf("\n\n");
}

//SSTF Disk SCHEDULING
void sstf()
{
    printf("\t\t\tSSTF\n\n");
    int i,n,k,queue[50],mov=0,head,index[50],min,a[50],j=0,mini,cp1;
    printf("Enter the size of queue request: ");
    scanf("%d",&n);
    printf("Enter the queue of disk positions to be read: ");
    for(i=0;i<n;i++)
    {
        scanf("%d",&queue[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d",&head);
    cp1=head;
    for(k=0;k<n;k++)
    {
    for(i=0;i<n;i++)
    {
        index[i]=abs(head-queue[i]);
    }
    min=index[0];
    mini=0;
    for(i=1;i<n;i++)
    {
        if(min>index[i])
        {
            min=index[i];
            mini=i;
        }
    }
    a[j]=queue[mini];
    j++;
    head=queue[mini];
    queue[mini]=999;
    }
    printf("Sequence is : ");
    printf("%d",cp1);
    mov=mov+abs(cp1-a[0]);
    printf(" -> %d",a[0]);
    for(i=1;i<n;i++)
    {
        mov=mov+abs(a[i]-a[i-1]);
        printf("%d -> ",a[i]);
    }
    printf("\n");
    printf("Total head movement = %d\n",mov);
}

//SCAN Disk SCHEDULING
void scan()
{
    printf("\t\t\tSCAN\n\n");
    int queue[100],i,j,n,TotalHeadMoment=0,initial,size,move;
    printf("Enter total disk size: ");
    scanf("%d",&size);
    printf("Enter the size of queue request: ");
    scanf("%d",&n);
    printf("Enter the queue of disk positions to be read: ");
    for(i=0;i<n;i++)
     scanf("%d",&queue[i]);
    printf("Enter initial head position: ");
    scanf("%d",&initial);
    printf("Enter the head movement direction for Right 1 and for left 0: ");
    scanf("%d",&move);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(queue[j]>queue[j+1])
            {
                int temp;
                temp=queue[j];
                queue[j]=queue[j+1];
                queue[j+1]=temp;
            }
        }
    }
    int index;
    for(i=0;i<n;i++)
    {
        if(initial<queue[i])
        {
            index=i;
            break;
        }
    }
    if(move==1)
    {
        for(i=index;i<n;i++)
        {
            TotalHeadMoment=TotalHeadMoment+abs(queue[i]-initial);
            initial=queue[i];
        }
        TotalHeadMoment=TotalHeadMoment+abs(size-queue[i-1]-1);
        initial = size-1;
        for(i=index-1;i>=0;i--)
        {
             TotalHeadMoment=TotalHeadMoment+abs(queue[i]-initial);
             initial=queue[i];
        }
    }
    else
    {
        for(i=index-1;i>=0;i--)
        {
            TotalHeadMoment=TotalHeadMoment+abs(queue[i]-initial);
            initial=queue[i];
        }
        TotalHeadMoment=TotalHeadMoment+abs(queue[i+1]-0);
        initial =0;
        for(i=index;i<n;i++)
        {
             TotalHeadMoment=TotalHeadMoment+abs(queue[i]-initial);
             initial=queue[i];
        }
    }
    printf("Total head movement is %d",TotalHeadMoment);
}

//C-SCAN Disk SCHEDULING
void c_scan()
{
    printf("\t\t\tC-SCAN\n\n");
    int queue[100],i,j,n,TotalHeadMoment=0,initial,size,move;
    printf("Enter total disk size: ");
    scanf("%d",&size);
    printf("Enter the size of queue request: ");
    scanf("%d",&n);
    printf("Enter the queue of disk positions to be read: ");
    for(i=0;i<n;i++)
     scanf("%d",&queue[i]);
    printf("Enter initial head position: ");
    scanf("%d",&initial);
    printf("Enter the head movement direction for Right 1 and for left 0: ");
    scanf("%d",&move);
    for(i=0;i<n;i++)
    {
        for( j=0;j<n-i-1;j++)
        {
            if(queue[j]>queue[j+1])
            {
                int temp;
                temp=queue[j];
                queue[j]=queue[j+1];
                queue[j+1]=temp;
            }
        }
    }
    int index;
    for(i=0;i<n;i++)
    {
        if(initial<queue[i])
        {
            index=i;
            break;
        }
    }
    if(move==1)
    {
        for(i=index;i<n;i++)
        {
            TotalHeadMoment=TotalHeadMoment+abs(queue[i]-initial);
            initial=queue[i];
        }
        TotalHeadMoment=TotalHeadMoment+abs(size-queue[i-1]-1);
        TotalHeadMoment=TotalHeadMoment+abs(size-1-0);
        initial=0;
        for( i=0;i<index;i++)
        {
             TotalHeadMoment=TotalHeadMoment+abs(queue[i]-initial);
             initial=queue[i];
        }
    }
   else
    {
        for(i=index-1;i>=0;i--)
        {
            TotalHeadMoment=TotalHeadMoment+abs(queue[i]-initial);
            initial=queue[i];
        }
        TotalHeadMoment=TotalHeadMoment+abs(queue[i+1]-0);
        TotalHeadMoment=TotalHeadMoment+abs(size-1-0);
        initial =size-1;
        for(i=n-1;i>=index;i--)
        {
             TotalHeadMoment=TotalHeadMoment+abs(queue[i]-initial);
             initial=queue[i];
        }
    }
    printf("Total head movement is %d",TotalHeadMoment);
}


//Look Disk SCHEDULING
void look()
{
    printf("\t\t\tLOOK\n\n");
    int queue[100],i,j,n,TotalHeadMoment=0,initial,size,move;
    printf("Enter total disk size: ");
    scanf("%d",&size);
    printf("Enter the size of queue request: ");
    scanf("%d",&n);
    printf("Enter the queue of disk positions to be read: ");
    for(i=0;i<n;i++)
     scanf("%d",&queue[i]);
    printf("Enter initial head position: ");
    scanf("%d",&initial);
    printf("Enter the head movement direction for Right 1 and for left 0: ");
    scanf("%d",&move);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(queue[j]>queue[j+1])
            {
                int temp;
                temp=queue[j];
                queue[j]=queue[j+1];
                queue[j+1]=temp;
            }
        }
    }
    int index;
    for(i=0;i<n;i++)
    {
        if(initial<queue[i])
        {
            index=i;
            break;
        }
    }
   if(move==1)
    {
        for(i=index;i<n;i++)
        {
            TotalHeadMoment=TotalHeadMoment+abs(queue[i]-initial);
            initial=queue[i];
        }

        for(i=index-1;i>=0;i--)
        {
             TotalHeadMoment=TotalHeadMoment+abs(queue[i]-initial);
             initial=queue[i];

        }
    }
    else
    {
        for(i=index-1;i>=0;i--)
        {
            TotalHeadMoment=TotalHeadMoment+abs(queue[i]-initial);
            initial=queue[i];
        }

        for(i=index;i<n;i++)
        {
             TotalHeadMoment=TotalHeadMoment+abs(queue[i]-initial);
             initial=queue[i];

        }
    }
    printf("Total head movement is %d",TotalHeadMoment);
}

//C-LOOK Disk SCHEDULING
void c_look(){
    printf("\t\t\tC-LOOK\n\n");
    int queue[100],i,j,n,TotalHeadMoment=0,initial,size,move;
    printf("Enter total disk size: ");
    scanf("%d",&size);
    printf("Enter the size of queue request: ");
    scanf("%d",&n);
    printf("Enter the queue of disk positions to be read: ");
    for(i=0;i<n;i++)
    scanf("%d",&queue[i]);
    printf("Enter initial head position: ");
    scanf("%d",&initial);
    printf("Enter the head movement direction for Right 1 and for left 0: ");
    scanf("%d",&move);
    for(i=0;i<n;i++)
    {
        for( j=0;j<n-i-1;j++)
        {
            if(queue[j]>queue[j+1])
            {
                int temp;
                temp=queue[j];
                queue[j]=queue[j+1];
                queue[j+1]=temp;
            }
        }
    }
    int index;
    for(i=0;i<n;i++)
    {
        if(initial<queue[i])
        {
            index=i;
            break;
        }
    }
   if(move==1)
    {
        for(i=index;i<n;i++)
        {
            TotalHeadMoment=TotalHeadMoment+abs(queue[i]-initial);
            initial=queue[i];
        }
        for( i=0;i<index;i++)
        {
             TotalHeadMoment=TotalHeadMoment+abs(queue[i]-initial);
             initial=queue[i];
        }
    }
   else
    {
        for(i=index-1;i>=0;i--)
        {
            TotalHeadMoment=TotalHeadMoment+abs(queue[i]-initial);
            initial=queue[i];
        }
        for(i=n-1;i>=index;i--)
        {
             TotalHeadMoment=TotalHeadMoment+abs(queue[i]-initial);
             initial=queue[i];
        }
    }
    printf("Total head movement is %d",TotalHeadMoment);
}

//First Fit Memory allocation
void ft()
{
    printf("\t\tFirst Fit\n");
    int bsize[25], psize[25], bno, pno, flags[25], allocation[25], i, j;
    for(i = 0; i < 10; i++)
        {
            flags[i] = 0;
            allocation[i] = -1;
        }
    printf("Enter number of blocks: ");
    scanf("%d", &bno);
    for(i = 0; i < bno; i++){
            printf("Enter size of block %d : ",i+1);
            scanf("%d", &bsize[i]);
        }

    printf("\nEnter number of processes: ");
    scanf("%d", &pno);
    for(i = 0; i < pno; i++){
            printf("Enter size of process %d : ",i+1);
            scanf("%d", &psize[i]);
        }
    for(i = 0; i < pno; i++)
    for(j = 0; j < bno; j++)
    if(flags[j] == 0 && bsize[j] >= psize[i])
        {
    allocation[j] = i;
    flags[j] = 1;
    break;
        }
    printf("\nBlock no.\tBlock size\t\tProcess no.\t\tProcess size");
    for(i = 0; i < bno; i++)
    {
        printf("\n%d\t\t\t%d\t\t", i+1, bsize[i]);
        if(flags[i] == 1)
            printf("\t%d\t\t\t%d",allocation[i]+1,psize[allocation[i]]);
        else
            printf("Not allocated");
    }
}


//Best Fit Memory Allocation
void bt()
{
    printf("\t\tBest Fit\n");
    int fragment[20],b[20],p[20],i,j,nb,np,temp,lowest=9999;
    static int barray[20],parray[20];
    printf("\nEnter the number of blocks:");
    scanf("%d",&nb);
    for(i=1;i<=nb;i++)
    {
        printf("Enter size of block %d : ",i);
        scanf("%d",&b[i]);
    }
    printf("\nEnter the number of processes:");
    scanf("%d",&np);
    for(i=1;i<=np;i++)
    {
        printf("Enter size of block %d : ",i);
        scanf("%d",&p[i]);
    }
    for(i=1;i<=np;i++)
    {
        for(j=1;j<=nb;j++)
        {
            if(barray[j]!=1)
            {
            temp=b[j]-p[i];
            if(temp>=0)
                if(lowest>temp)
                    {
                    parray[i]=j;
                    lowest=temp;
                    }
                }
            }
            fragment[i]=lowest;
            barray[parray[i]]=1;
            lowest=10000;
    }
    printf("\nProcess_no\tProcess_size\tBlock_no\tBlock_size\tFragment");
    for(i=1;i<=np && parray[i]!=0;i++)
    printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",i,p[i],parray[i],b[parray[i]],fragment[i]);
    }


//Worst Fit Memory Allocation
void wt()
{
    printf("\t\tWorst Fit\n");
    int frag[max],b[max],f[max],i,j,nb,nf,temp,highest=0;
    static int bf[max],ff[max];

    printf("\nEnter the number of blocks: ");
    scanf("%d",&nb);

    for(i=1;i<=nb;i++)
    {
        printf("Enter size of block %d : ",i);
        scanf("%d",&b[i]);
    }
    printf("\nEnter the number of files: ");
    scanf("%d",&nf);

    for(i=1;i<=nf;i++)
    {
        printf("Enter size of file %d : ",i);
        scanf("%d",&f[i]);
    }
    for(i=1;i<=nf;i++)
    {
        for(j=1;j<=nb;j++)
        {
            if(bf[j]!=1)
            {
            temp=b[j]-f[i];
            if(temp>=0)
            if(highest<temp)
                {
                ff[i]=j;
                highest=temp;
                }
            }
        }
    frag[i]=highest;
    bf[ff[i]]=1;
    highest=0;
    }
    printf("\nFile_no:\tFile_size :\tBlock_no:\tBlock_size:\tFragement");
    for(i=1;i<=nf;i++)
    printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",i,f[i],ff[i],b[ff[i]],frag[i]);
}

//CPU SCHEDULING
void cpu()
{
    int choice;
        printf("\t\tCPU SCHEDULING\n");
        printf("1.SJF\n");
        printf("2.FCFS\n");
        printf("3.RR\n");
        printf("4.MULTILEVEL QUEUES\n");
        printf("5.PRIORITY SCHEDULING\n");
        printf("6. Exit  \n");
        printf("Enter your choice :  ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
               sjfcp();
               break;
            case 2:
               fcfscp();
               break;
            case 3:
                rrcp();
                break;
            case 4:
                mqcp();
                break;
            case 5:
                priorcp();
                break;
            case 6:
            printf("\n\t\t\tEnding!\n\n");
            exit(0);
        }

}

//Disk Scheduling
void disk()
{
    int choice;
        printf("\t\tDISK SCHEDULING\n");
        printf("1. FCFS  \n");
        printf("2. SSTF \n");
        printf("3. SCAN\n");
        printf("4. C-SCAN\n");
        printf("5. LOOK\n");
        printf("6. C-LOOK\n");
        printf("7. Exit\n\n\n");
        printf("Enter your choice :  ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            fcfs();
            break;
        case 2:
            sstf();
            break;
        case 3:
            scan();
            break;
        case 4:
            c_scan();
            break;
        case 5:
            look();
            break;
        case 6:
            c_look();
            break;
        case 7:
            printf("\n\t\t\tEnding!\n\n");
            exit(0);
}
}

//Memory allocation
void memory()
{
    int choice;
        printf("\t\tMemory Allocation\n");
        printf("1. First Fit  \n");
        printf("2. Best Fit \n");
        printf("3. Worst Fit\n");
        printf("4. Exit  \n");
        printf("Enter your choice :  ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            ft();
            break;
        case 2:
            bt();
            break;
        case 3:
            wt();
            break;
        case 4:
            printf("\n\t\t\tEnding!\n\n");
            exit(0);
        }
}

//Driver code
int main()
{
    printf("\n\n\t\tProcess Scheduling Simulator\n\n\n");
    int choice;
        printf("1. CPU Scheduling  \n");
        printf("2. Disk Scheduling \n");
        printf("3. Memory Allocation \n");
        printf("4. Exit  \n");
        printf("Enter your choice :  ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            cpu();
            break;
        case 2:
            disk();
            break;
        case 3:
            memory();
            break;
        case 4:
            printf("\n\t\t\tEnding!\n\n");
            exit(0);
        }
return 0;
}
