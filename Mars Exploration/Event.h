#ifndef Event_
#define Event_

class Event
{
private:
	int ID;
	int Event_Day;

public:
	Event(double speed = -1, int checkDuration = -1, int missionsCount = -1);
	//virtual void Set_ID(int id) = 0;
	//virtual void Set_Event_Day(int event_day) = 0;
	//virtual int Get_ID() = 0;
	//virtual int Get_Event_Day() = 0;
	//virtual bool  Execute() = 0;
	virtual ~Event() = 0;
};

#endif