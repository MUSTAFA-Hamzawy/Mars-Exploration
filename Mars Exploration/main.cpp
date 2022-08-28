#include<iostream>
#include"MarsStation.h"

using namespace std;

int main()
{
	MarsStation mars;

	mars.getInput();
	mars.Get_Data_Into_PQ_Q();

	const int MODE = 1;

	while (!mars.finished())
	{
		mars.incrementDays();
		mars.decrementCheckUpDuration();
		mars.excute_Events();
		mars.assignMissions();
		mars.Statistics();
		mars.Complete_Missions();
		if (MODE != 3)
		{
			mars.outputdata(MODE);
		}
	}
	if (MODE == 3)
	{
		mars.outputdata(MODE);
	}
	mars.outfile();
	
	
	return 0;
}

/*	
	UI<int> screen;
	screen.input();

	MarsStation<int> mars;
	int Days = 0;

	mars.Get_Data_Into_PQ_Q();
	while (!mars.finished())
	{
		Days++;
		mars.excute_Events();
		mars.assignMissions();
		mars.Complete_Missions();
	}
	screen.output(1);
*/


//Checking for Priority Queue
	   //NOTE : PriorityQueue Dequeue LowestPriority First
/*
LinkedPriorityQueue<char> pq;

LinkedPriorityQueue <char> pp;
pp.enqueue('k', 15);
pp.enqueue('A', 3);
pp.enqueue('g', 9);
pp.enqueue('y', 7);

char t;
while (!pp.isEmpty())
{
	pp.dequeue(t);
	cout << t << "==>" << " ";
}

cout << "END MAIN" << endl;
*/