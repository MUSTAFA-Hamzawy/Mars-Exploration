#ifndef Polar_Mission
#define Polar_Mission
#include"Mission.h"

class PolarMission : public Mission
{
private:
	int Formulation_Day;
	char Mission_Type;
	double Target_Location;
	int Mission_Duration;
	double Signature;
	int ID;
	int Waiting_Duration;
	int MissionsCount;
	int Inexecution_Days;
public:
	PolarMission(int fd = -1, char mt = '-1', double tl = -1, int md = -1, double sg = -1, int id = -1, int wd = -1);
	virtual void Set_Formulation_Day(int fd);
	virtual void Set_Mission_Type(char mt);
	virtual void Set_Target_Location(double tl);
	virtual void Set_Mission_Duration(int md);
	virtual void Set_Signature(double sg);
	virtual void Set_ID(int id);
	virtual void Set_Waiting_Duration(int wd);
	virtual void Set_Inexecution_Days(int speed);
	virtual int Get_Formulation_Day()const;
	virtual char Get_Mission_Type()const;
	virtual double Get_Target_Location()const;
	virtual int Get_Mission_Duration()const;
	virtual double Get_Signature()const;
	virtual int Get_ID()const;
	virtual int Get_Waiting_Duration()const;
	virtual double Get_Inexecution_Days()const;
	virtual double Get_Completion_Days() const;
	virtual ~PolarMission();

	PolarMission(const PolarMission& obj);
	void operator=(const PolarMission& obj);

};
#endif