#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

//Warning: Global variables should be declared before functions to be seen
int seatsnumber[2][50];
int turn=0;
int m=0;//number of seats that are got by the user.

/* There are there functions that work with same process. Becuse of this I will explain only one of them. */
void *TravelAgency1(void *i)
{
	while(true)
	{
		while(turn!=0);
		int seatnumberi;
		int x=rand()%2;//random x value of array
		int y=rand()%50;//random y value of array
		if(m!=100)
		{
			while(seatsnumber[x][y]!=0)//until find a empty seat.
			{
				x=rand()%2;
				y=rand()%50;
			}
			if(seatsnumber[x][y]==0&&m!=100)//if the seat is empty and # of seats that are got by the user is not 100.
			{
				seatsnumber[x][y]=1;
				m++;//increasing got seats 

				//setting seats number by looking at x value.
				if(x==0)
				{
					seatnumberi=2*y+1;
					cout<<"Seat Number "<<seatnumberi;
				}
				else
				{
					seatnumberi=2*y+2;
					cout<<"Seat Number "<<seatnumberi;
				}
			}
			cout<<"  are reserved by TravelAgency1"<<endl;
		}
		turn=1;//turn for another thread.
	}

}

void *TravelAgency2( void *i )
{
	while(true)
	{
		while(turn!=1);
		int seatnumberi;
		int x=rand()%2;
		int y=rand()%50;
		if(m!=100)
		{
			while(seatsnumber[x][y]!=0)
			{
				x=rand()%2;
				y=rand()%50;
			}
			if(seatsnumber[x][y]==0&&m!=100)
			{
				seatsnumber[x][y]=2;
				m++;
				if(x==0)
				{
					seatnumberi=2*y+1;
					cout<<"Seat Number "<<seatnumberi;
				}
				else
				{
					seatnumberi=2*y+2;
					cout<<"Seat Number "<<seatnumberi;
				}
			}
			cout<<"  are reserved by TravelAgency2"<<endl;
		}
		turn=2;
	}
}

void *TravelAgency3( void *i)
{
	while(true)
	{
		while(turn!=2);
		int seatnumberi;
		int x=rand()%2;
		int y=rand()%50;
		if(m!=100)
		{
			while(seatsnumber[x][y]!=0)
			{
				x=rand()%2;
				y=rand()%50;
			}
			if(seatsnumber[x][y]==0&&m!=100)
			{
				seatsnumber[x][y]=3;
				m++;
				if(x==0)
				{
					seatnumberi=2*y+1;
					cout<<"Seat Number "<<seatnumberi;
				}
				else
				{
					seatnumberi=2*y+2;
					cout<<"Seat Number "<<seatnumberi;
				}
			}
			cout<<"  are reserved by TravelAgency3"<<endl;
		}
		turn=0;
	}
}

int main()
{
	srand(time(NULL));
	pthread_t thread1, thread2, thread3;
	int id1=1,id2=1,id3=1;

	//to initilize all elements of array
	for(int i=0;i<=1;i++)
	{
		for(int j=0;j<=49;j++)
			seatsnumber[i][j]=0;
	}


	pthread_create( &thread1, NULL, TravelAgency1, (void*) &id1);
	pthread_create( &thread2, NULL, TravelAgency2, (void*) &id2);
	pthread_create( &thread3, NULL, TravelAgency3, (void*) &id3);

	/* Wait till threads are complete before main continues. Unless we  */
	/* wait we run the risk of executing an exit which will terminate   */
	/* the process and all threads before the threads have completed.   */

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL); 
	pthread_join(thread3, NULL); 

	return 0;
}
