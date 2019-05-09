#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

/*
Limitations:
Multi-Levels? Yes
How many car sizes? Let's say 3, but could be more

Need to consider payment ? No

Who are the actors?
Car
Parking Lot
Parking Spot

Use case:
1. Car can park in parking spot larger than it ? Yes
*/

enum class Size
{
	COMPACT = 0,
	SMALL = 1,
	LARGE = 2,
};


class Car;
class ParkingSpot
{
public:
	ParkingSpot(int id, int size)
	{

	}
	int getSize()
	{
		return m_size;
	}
	void parkVehicle(Car* vehicle)
	{

	}
private:
	int m_size;
};

class Car
{
public:
	Car(string licensePlate) {

	}
	virtual ~Car() = default;
	virtual Size getCarSize() const = 0;
protected:
};

class Bus : public Car
{
public:
	Bus()
	:Car("")
	{

	}
	virtual Size getCarSize()
	{
		return Size::LARGE;
	}
};

class Level {

void parkVehicle(Car * vehicle)
	{
		if (vehicle->getCarSize() == Size::COMPACT)
		{

		}
		else if (vehicle->getCarSize() == Size::LARGE)
		{

		}
		else
		{
		 	// Nomral
		}
		// Take from 
	}

	vector<ParkingSpot*> largeSpots;
	vector<ParkingSpot*> compactSpots;
	vector<ParkingSpot*> normalSpots;
};

class ParkingLot {
	void parkVehicle(Car * vehicle)
	{
		parkVehicle(vehicle);
		// Take from 
	}
	vector<Level> levels;
};


int main()
{


}