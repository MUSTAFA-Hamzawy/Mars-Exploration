#ifndef Rover_
#define Rover_

class Rover
{
private:
	double Speed;
	int	CheckupDuration;
	int	MissionsCount;		// Number of missions before the checkup, ex : if it is = 3
	int ID;

public:
	Rover(double speed = -1, int checkDuration = -1, int missionsCount = -1);
	virtual bool available();     // check if the rover is available to be assigned a mission or in checkup
	virtual void Set_Speed(double speed) ;
	virtual void Set_CheckupDuration(int checkDuration);
	virtual void Set_MissionsCount(int missionsCount);
	virtual double Get_Speed()const;
	virtual int Get_MissionsCount()const;
	virtual int Get_CheckupDuration() const;
	virtual void Set_ID(int id);
	virtual int Get_ID()const;
	virtual ~Rover();

};

#endif