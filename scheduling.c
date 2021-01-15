/*@Programmed By - Lokesh Kumar Nahata
 * REG NO. - 1841017158
 * BRANCH - CSIT A
 * SECTION - A
 * SEMESTER - 5 th
 * Session		: 2020-2021
 * Admission Batch	: 2018
 * **********************************
 * END TERM PROJECT 
 * CPU SCHEDULING
 * DESIGN OF OPERATING SYSTEMS (CSE 4049)
 * DATE - 15/01/2021
  **/

#include <stdio.h>
#include <stdlib.h>
#define MAX 100
//structure for roundrobin
struct times
{
	   int p,art,but,wtt,tat,rnt;
};
//structure for sjf
struct sjf
{
	       int bt,at,wt,st,pno,tt,cbt;
};

void sjf();
void srtf();
int iscomplite(struct sjf arr[],int n);
void gantt_chart(struct sjf arr[],int p[],int n,int nop);
int get(struct sjf arr[],int t,int n);
void round_robin();
void sortart(struct times a[],int pro);
void  print_gantt_chart_fcfs(int pid[], int burst_time[],int turnaround_time[],int waiting_time[],int n);

//fcfs scheduling
void fcfs()
{
     int pid[MAX],burst_time[MAX],wait_time[MAX],tat_time[MAX],arr_time[MAX];
     int i,j,n;
     int total_wait_time= 0, total_tat_time = 0;
	//no. of process
	printf("Enter total number of process: ");
	 scanf("%d", &n);
	 printf("Enter burst time for each process:\n");
	 for(i=0; i<n; i++)
	 {
		 pid[i] = i+1;
		 printf("P[%d] : ", i+1);
		 scanf("%d", &burst_time[i]);
		wait_time[i] = tat_time[i] = 0;
	 }
		printf("Enter process arrival time: \n");
		 for(i=0; i<n; i++)
	 	 {
	       	printf("P[%d] : ", i+1);
		 scanf("%d", &arr_time[i]);
		 }
	  // calculate waiting time and turnaround time
	   tat_time[0] =burst_time[0];
	        for(i=1; i<n; i++) 
		{
			wait_time[i] =wait_time[i-1] + burst_time[i-1];
		tat_time[i] = wait_time[i] + burst_time[i];
		}
		
		// print gantt chart
		printf("\n");
		 printf("          GANTT CHART          \n");
		 printf("          ***********          \n");
		  print_gantt_chart_fcfs(pid,burst_time, tat_time,wait_time, n);
// calculate sum of waiting time and sum of turnaround time
	for (i=0; i<n; i++)
	{
		  total_wait_time += wait_time[i] - arr_time[i];
		  total_tat_time += tat_time[i] - arr_time[i];
	}
	//print chart
	printf("\n");
	printf("|*****|************|**************|*****************|\n");
	printf("| PID | Burst Time | Waiting Time | Turnaround Time |\n");
	printf("|*****|************|**************|*****************|\n");
	for (i=0; i<n;i++)
	{
	printf("| %2d  |     %2d     |      %2d      |        %2d       |\n", pid[i], burst_time[i],wait_time[i] - arr_time[i], tat_time[i] - arr_time[i] );
         printf("|*****|************|**************|*****************|\n");
	}
	printf("\n");
	//print results
	printf ("Average Waiting Time      : %-2.2lf\n",(double)total_wait_time / (double) n);
	printf ("Average Turnaround Time   : %-2.2lf\n",(double)total_tat_time / (double) n);
	printf ("Average Response Time      : %-2.2lf\n",(double)total_wait_time / (double) n);
}

//gantt chart for fcfs

void print_gantt_chart_fcfs(int pid[], int burst_time[],int turnaround_time[],int waiting_time[],int n)
{
	int i,j;
	//print top line
	printf(" ");
	for(i=0; i<n; i++)
       	{
		for(j=0; j<burst_time[i]; j++)
		       	printf("--");
		printf(" ");
	}
	printf("\n|");
	//print process id 
	for(i=0; i<n; i++) {
		for(j=0; j<burst_time[i] - 1; j++)
		       	printf(" ");
		printf("P%d", pid[i]);
		for(j=0; j<burst_time[i] - 1; j++) printf(" ");
		printf("|");
	}
	printf("\n ");
	//bottom bar
	for(i=0; i<n; i++) {
		for(j=0; j<burst_time[i]; j++)
		       	printf("--");
		printf(" ");
	}
	printf("\n");
	//timeline
	printf("0");
	for(i=0; i<n; i++) {
		for(j=0; j<burst_time[i]; j++)
		       	printf("  ");
		if(turnaround_time[i] > 9)
		       	printf("\b");
	        printf("%d", turnaround_time[i]);
	}
printf("\n");	
}

//Shortest job first scheduling

void sjf()
{
	int pid[MAX],burst_time[MAX],waiting_time[MAX],arr_time[MAX],tat[MAX];
	int n,i,j,k=0,last;
	int t1,t2,t3,total_waiting_time = 0,total_tat_time = 0;
       	printf("Enter total number of process: ");
	scanf("%d", &n);
	printf("Enter burst time for each process:\n");
	for(i=0; i<n; i++)
	{
		pid[i] = i+1;
		printf("P[%d] : ", i+1);
		scanf("%d", &burst_time[i]);
	}
	printf("Enter process arrival time: \n");
	for(i=0; i<n; i++)
	{
		printf("P[%d] : ", i+1);
		scanf("%d", &arr_time[i]);
	}

	//sorting process by burst time
	for (i=0;i<n-1;i++)
	{
		for(j=0;j<n-1-i;j++)
		{
			if (burst_time[j] > burst_time[j+1])
			{
				t1 = burst_time[j];
				burst_time[j] = burst_time[j+1];
				burst_time[j+1] = t1;

				t2 = pid[j] ;
				pid[j] = pid[j+1];
				pid[j+1] = t2;

				t3 = arr_time[j];
				arr_time[j] = arr_time[j+1];
				arr_time[j+1] = t3;
			}
		}
	}
	//calculating waiting time , turnaround time , response time	
	waiting_time[0] = 0;
	for (i=1;i<n;i++)
	{
		waiting_time[i] = waiting_time[i-1] + burst_time[i-1]; 
		total_waiting_time += waiting_time[i];
	}
	for (i = 0;i<n;i++)
		total_waiting_time = total_waiting_time - arr_time[i];
	

    //	Gantt chart
    last = burst_time[n-1] + (n == 1 ? 0 : waiting_time[n-1]);
    //top bar 
    printf(" ");
    for (i=0;i<n;i++)
    {
	    for(j=0; j<burst_time[i]; j++) 
		    printf("--");
	    printf(" ");
    }
    printf("\n|");
	             // middle position
         for(i=0; i<n; i++) {
		 for(j=0; j<burst_time[i]-1; j++) 
			 printf(" ");
		 printf("p%d", pid[i]);
		 for(j=0; j<burst_time[i]-1; j++)
			 printf(" ");
		 printf("|");
	 }
	 printf("\n ");
 // bottom bar
	 for(i=0; i<n; i++) {
		 for(j=0; j<burst_time[i]; j++)
			 printf("--");
		 printf(" ");
	 }
 	printf("\n");
	//print timeline
	int minus = 0;
	for(i=0; i<n; i++) {
		if(waiting_time[i]>9)
			printf(" ");
		printf("%d",waiting_time[i]);
		tat[k] = waiting_time[i];
		k = k+1;
		if(waiting_time[i]>9){
			minus = 1;
		}
		if(i+1 == n )  
			if (last>9) 
				minus = 1;
		for(j=0; j<burst_time[i]-minus; j++) 
			printf("  ");
	}
	if(last>9)
		printf(" ");
	printf("%d\n", last);
	tat[k] = last;

	for (i=1;i<=n;i++)
	{
		total_tat_time = total_tat_time + tat[i] - arr_time[i-1];
	}
	// printing average and details  
	 printf("\n");
	 printf("|*****|************|**************|*****************|\n");
	 printf("| PID | Burst Time | Waiting Time | Turnaround Time |\n");
	 printf("|*****|************|**************|*****************|\n");
	 for (i=0; i<n;i++)
	 {
 printf("| %2d  |     %2d     |      %2d      |        %2d       |\n", pid[i], burst_time[i],waiting_time[i] - arr_time[i], tat[i+1] - arr_time[i] );
	 printf("|*****|************|**************|*****************|\n");
	 }
	 printf("\n");
	 //print results
        printf ("Average Waiting Time      : %-2.2lf\n",(double)total_waiting_time / (double) n);
        printf ("Average Turnaround Time   : %-2.2lf\n",(double)total_tat_time / (double) n);
       printf ("Average Response Time      : %-2.2lf\n",(double)total_waiting_time / (double) n);
}

// sorting process on the basis of arrival time for roundrobin scheduling

void sortart(struct times a[],int pro)
{
	int i,j;
	struct times temp;
	//sorting arrival time basis
	for(i=0;i<pro;i++)
	{
		for(j=i+1;j<pro;j++)
		{
			if(a[i].art > a[j].art)
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
	return;
}
//round robin function
void round_robin()
{
	int i,j,pro,time,remain,flag=0,ts,sum=0,sum1=0;
        struct times a[100];
        float avgwt=0,avgtt=0,avgrt=0;
        printf("Enter Number Of Processes : ");
        scanf("%d",&pro);
        remain=pro;
	 printf("Enter arrival time and Burst time for Process : \n");
        for(i=0;i<pro;i++)
	{
	printf(" P%d : ",i);
	scanf("%d%d",&a[i].art,&a[i].but);
	a[i].p = i;
	a[i].rnt = a[i].but;
	}
        sortart(a,pro);
	//input quantum number
        printf("Enter Time Slice OR Quantum Number : ");
        scanf("%d",&ts);
	
	//Gantt Chart
	printf("\n");
	printf("          GANTT CHART          ");
	printf("\n          ***********          ");
	printf("\n0");
	for(time=0,i=0;remain!=0;)
	{
		if(a[i].rnt<=ts && a[i].rnt>0)
		{
			time = time + a[i].rnt;
			printf(" | P%d | %d",a[i].p,time);
			a[i].rnt=0;
		flag=1;
		}
              else if(a[i].rnt > 0)
	      {
		      a[i].rnt = a[i].rnt - ts;
		      time = time + ts;
		      printf(" | P%d | %d",a[i].p,time);
	      }
	      //calculating waiting time and turnaround time
	      if(a[i].rnt==0 && flag==1)
	      {
		      remain--;
		      a[i].tat = time-a[i].art;
		      a[i].wtt = time-a[i].art-a[i].but;
		      avgwt = avgwt + time-a[i].art-a[i].but;
		      avgtt = avgtt + time-a[i].art;
		      flag=0;
	      }
              if(i==pro-1)
		      i=0;
	      else if(a[i+1].art <= time)
		      i++;
	      else
		      i=0;
	}
	//print results 
        printf("\n\n\n");
	printf("|*****|**************|************|**************|*****************|\n");
	printf("| PID | Arrival Time | Burst Time | Waiting Time | Turnaround Time |\n");
	printf("|*****|**************|************|**************|*****************|\n");
       for(i=0;i<pro;i++)
       {
        printf("| P%d  |     %2d       |     %2d     |      %2d      |        %2d       |\n",a[i].p,a[i].art,a[i].but,a[i].wtt,a[i].tat);
       	 printf("|*****|**************|************|**************|*****************|\n");
       }
       avgwt = avgwt/pro;
       avgtt = avgtt/pro;
       printf("Average Waiting Time      : %.2f\n",avgwt);
       printf("Average Turnaround Time   : %.2f\n",avgtt); 

       //calculating response time
 	for(i=1;i<pro;i++)
	{
	   if ( a[i].but >=2)
		   sum = sum + ts;
	   else
		   sum = sum + a[i].but;
	   sum1 = sum1 + sum;
	}
	for (i=0;i<pro;i++)
	{
		sum1 = sum1 - a[i].art;
	}

	printf("Average Response Time     : %.2f\n",(float)sum1/pro);
}


//function toprint gantt chart for srtf scheduling
void gantt_chart_srtf(struct sjf arr[],int p[],int n,int nop)
{
	int i,a[100],s=0;
	float avgtt=0,avgwt=0;
	//Gantt chart
	printf("\n");
	printf("          GANTT CHART          \n");
	printf("          ***********          \n");
	printf("0");
	for(i=0;i<n-1;i++)
	{
		while(i<n-1&&p[i]==p[i+1])
		{
			s++;
			i++;
		}
		s++;
		printf(" -> [P%d] <- %d",arr[p[i]].pno,s);
		arr[p[i]].wt=s-arr[p[i]].at-arr[p[i]].tt;
	}
	for(i=0;i<nop;i++)
	{
		arr[i].tt+=arr[i].wt;
		avgwt+=arr[i].wt;
		avgtt+=arr[i].tt;
	}

	//print results
       	printf("\n\n\n");
	printf("|*****|**************|************|**************|*****************|\n");
	printf("| PID | Arrival Time | Burst Time | Waiting Time | Turnaround Time |\n");
	printf("|*****|**************|************|**************|*****************|\n");
				      
	for(i=0;i<nop;i++)
	{
		printf("| %2d  |     %2d       |     %2d     |      %2d      |        %2d       |\n",arr[i].pno,arr[i].at,arr[i].cbt,arr[i].wt,arr[i].tt);
	printf("|*****|**************|************|**************|*****************|\n");
	}
	//calculate average times
	avgwt = avgwt/nop;
	avgtt = avgtt/nop;
	printf("Average Waiting Time : %.2f\n",avgwt);
	printf("Average Turnaround Time : %.2f\n",avgtt);
	return;
}

// find the starting process
int iscomplite(struct sjf arr[],int n)
{
	int i;
	for(i=0;i<n;i++)
		if(arr[i].st==0)
			return 0;
	return 1;
}
// get the min arrival time 
int get(struct sjf arr[],int t,int n)
{
	int imin,min=9999,i;
	for(i=0;i<n;i++)
	{
		if(arr[i].at<=t&&arr[i].st==0)
			if(min>arr[i].bt)
			{
				min=arr[i].bt;
				imin=i;
			}
	}
	return imin;
}
//shortest remaining time first scheduling
void srtf()
{
	int n,i,a,t=0;
	int p[100];
	float avgwt=0,avgtt=0;
	struct sjf arr[100];

	printf("Enter Number of Processes\n");
	scanf("%d",&n);
	 printf("Enter Arrival Time & Burst Time for Process : ");
	for(i=0;i<n;i++)
	{
		printf(" [P%d] : ",i);
		scanf("%d%d",&arr[i].at,&arr[i].bt);
		arr[i].pno = i;
		arr[i].cbt = arr[i].bt;
		arr[i].st=0;
		arr[i].tt=arr[i].bt;
		arr[i].wt=0;
	}
	i=0;
	while(1)
	{
		if(iscomplite(arr,n))
			break;
		a=get(arr,t,n);
		p[i]=a;
		arr[a].bt-=1;
		if(arr[a].bt==0)
			arr[a].st=1;
		t=t+1;
		i++;
	}
	gantt_chart_srtf(arr,p,i,n);
}
int main()
{
	int choice ;
	printf("\n");
	printf("\t\t|***********************************************|\n");
	printf("\t\t|        Welcome  to CPU scheduling             |\n");
	printf("\t\t|  Available Scheduling Methods to choose from  |\n");
	printf("\t\t|       1.First Come First Served (FCFS)        |\n");
	printf("\t\t|       2.Shortest Job First (SJF)              |\n"); 
	printf("\t\t|       3.Shortest Remaining Time First (SRTF)  |\n");
	printf("\t\t|       4.Round Robin Scheduling (RR)           |\n");
	printf("\t\t|       5.Exit from program                     |\n");
	printf("\t\t|***********************************************|\n");
	printf("\n\nEnter Your choice                       \n");
	scanf ("\t\t%d",&choice);
	switch (choice)
	{
		case 1:
			fcfs();
			break;
		case 2:
			sjf();
			break;
		case 3:
			srtf();
			break;
		case 4:
			round_robin();
			break;
		case 5 :
			exit(0);
			break;
		default:printf ("WRONG CHOICE !!");
	}
	return 0;
}
