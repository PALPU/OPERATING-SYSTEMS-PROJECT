#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int n;
struct Process
{
	char process[5];
	int arr_t;
	double estRun_t;
	double priority;
	int wait_t;
	double turnAround_t;
};
struct Process *obj;
int i,min_arrtime=65537;
int cur_time=0,i=0,j=0,p=0;
char cur_process[5];
double avgTurnAround_t=0,avgWait_t=0;
double runTime=100000000.0;
void findMinTime()
{
	min_arrtime=65537;
	
	for(i=0;i<n;i++)
	{
		if(obj[i].priority==-1)
			continue;
		if(min_arrtime==obj[i].arr_t)
		{
			if(obj[i].estRun_t<runTime)
			{
				strcpy(cur_process,obj[i].process);
				runTime=obj[i].estRun_t;
				min_arrtime=obj[i].arr_t;		
			}
		}
		else if(min_arrtime>obj[i].arr_t)
		{
			strcpy(cur_process,obj[i].process);
			runTime=obj[i].estRun_t;
			min_arrtime=obj[i].arr_t;
		}
	
	}
	cur_time=min_arrtime;
	return;
}
void findMaxPriority()//FUNCTION TO FIND THE MAXIMUM PRIORITY
{
	double max_priority=-10000000.0;
	for(i=0;i<n;i++)
	{
		if(obj[i].priority==-1)
		{
			continue;
		}
		else
		{
			if(max_priority<obj[i].priority)
			{
				max_priority=obj[i].priority;
				strcpy(cur_process,obj[i].process);
			}
		}
	}
	return;
}
void main()
{

	printf("enter the number of processes: ");
	scanf("%d",&n);
	printf("\n\t\tEnter the details of the %d processes one by one\n\n",n);
	obj=(struct Process*)malloc(sizeof( struct Process)*n);
	for(i=0;i<n;i++)
	{
		printf("Enter %d the Process Name: ",i+1);
		scanf("%s",obj[i].process);
		printf("Enter its Arrival Time: ");
		scanf("%d",&(obj[i].arr_t));
		printf("Enter its Burst Time  : ");
		scanf("%lf",&(obj[i].estRun_t));
		printf("******************************************\n\n");
		if(min_arrtime==obj[i].arr_t)
		{
			if(obj[i].estRun_t<runTime)
			{
				strcpy(cur_process,obj[i].process);
				runTime=obj[i].estRun_t;
				min_arrtime=obj[i].arr_t;		
			}
		}
		else if(min_arrtime>obj[i].arr_t)
		{
			strcpy(cur_process,obj[i].process);
			runTime=obj[i].estRun_t;
			min_arrtime=obj[i].arr_t;
		}
	}
	cur_time=min_arrtime;
	min_arrtime=65537;
	for(j=0;j<n;j++)
	{
		for(i=0;i<n;i++)
		{
			if(obj[i].priority!=-1 && strcmp(obj[i].process,cur_process)==0)
			{
				obj[i].priority=-1;
				obj[i].wait_t=cur_time-obj[i].arr_t;
				cur_time=cur_time+(int)obj[i].estRun_t;
				obj[i].turnAround_t=cur_time-obj[i].arr_t;
			}
		}
		for(i=0;i<n;i++)
		{
			if(obj[i].priority==-1)
				continue;
			else if(cur_time<obj[i].arr_t)
			{
				p=1;
				continue;
			}
			else
			{
				p=-1;
				break;
			}
		}
		if(p==1)
		{
			findMinTime();
		}
		else
		{
			for(i=0;i<n;i++)
			{
				if(obj[i].priority!=-1 && cur_time>obj[i].arr_t)
				{
					obj[i].wait_t=cur_time-obj[i].arr_t;
					obj[i].priority=1+(obj[i].wait_t/obj[i].estRun_t);
				}
			}
			findMaxPriority();
		}
		
	}	
	//final printing
	printf("\n\t\t\t\tRESULTS AFTER CALCULATIONS\n\n");
	printf("\n       Process  Arrival time    Est_RunTime    WaitingTime     TurnAroundTime      StartTime\n\n");
	for(i=0;i<n;i++)
	{
		printf("\n          %s        %3d           %3.0lf        %6d 	         %4.0lf		    %3d  ",obj[i].process,obj[i].arr_t,obj[i].estRun_t,obj[i].wait_t,obj[i].turnAround_t,obj[i].arr_t+obj[i].wait_t);
		avgTurnAround_t=avgTurnAround_t+obj[i].turnAround_t;
		avgWait_t=avgWait_t+obj[i].wait_t;
	}
	printf("\n\n\n\t\tAverage_Waiting_Time of all the processes is %.2lf units",avgWait_t/n);
	printf("\n\n\t\tAverage_TurnAround_Time of all the processes is %.2lf units\n\n\n\n",avgTurnAround_t/n);
	
}
