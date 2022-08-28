#ifndef Mountainous_Mission_
#define Mountainous_Mission_

#include"Mission.h"


class MountainousMission : public Mission
{
private:
	int Formulation_Day;
	char Mission_Type;
	double Target_Location;
	int Mission_Duration;
	double Signature;
	int ID;
	int Waiting_Duration;
	int MissionsCount;           // why we need this ? , Mustafa
	double Inexecution_Days;
public:
	MountainousMission(int fd = -1, char mt = '-1', double tl = -1, int md = -1, double sg = -1, int id = -1, int wd = -1);
	virtual void Set_Formulation_Day(int fd);
	virtual void Set_Mission_Type(char mt);
	virtual void Set_Target_Location(double tl);
	virtual void Set_Mission_Duration(int md);
	virtual void Set_Signature(double sg);
	virtual void Set_ID(int id);
	virtual void Set_Waiting_Duration(int wd);
	virtual void Set_Inexecution_Days(int speed);
	virtual int Get_Formulation_Day();
	virtual char Get_Mission_Type();
	virtual double Get_Target_Location();
	virtual int Get_Mission_Duration();
	virtual double Get_Signature();
	virtual int Get_ID();
	virtual int Get_Waiting_Duration();
	virtual double Get_Inexecution_Days();
	virtual double Get_Completion_Days();
	//virtual ~MountainousMission();

	MountainousMission(const MountainousMission& obj);
	void operator=(const MountainousMission& obj);

};

#endif