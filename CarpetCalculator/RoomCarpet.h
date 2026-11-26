// Specification file for the RoomCarpet class
#ifndef ROOMCARPET_H
#define ROOMCARPET_H

#include "RoomDimension.h"

// The RoomCarpet class represents carpet pricing for a room.
// It uses aggregation (a non-owning pointer) to refer to a
// RoomDimension object that exists independently.
class RoomCarpet
{
private:
	const RoomDimension* dimensions; // Non-owning pointer (aggregation)
	double costPerSquareFoot;

public:
	// Constructor using member initializer list
	RoomCarpet(const RoomDimension* room, double price);

	// Accessors
	const RoomDimension* getDimensions() const;
	double getCostPerSquareFoot() const;

	// Returns total carpet cost using RoomDimension::getArea()
	double getTotalCost() const;
};

#endif

