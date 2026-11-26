// Implementation file for the RoomCarpet class
#include <stdexcept>
#include "RoomCarpet.h"

RoomCarpet::RoomCarpet(const RoomDimension* room, double price)
	: dimensions(room), costPerSquareFoot(price)
{
	if (dimensions == nullptr)
	{
		throw std::invalid_argument("RoomDimension pointer cannot be null.");
	}
	if (costPerSquareFoot <= 0.0)
	{
		throw std::invalid_argument("Carpet price per square foot must be greater than zero.");
	}
}

const RoomDimension* RoomCarpet::getDimensions() const
{
	return dimensions;
}

double RoomCarpet::getCostPerSquareFoot() const
{
	return costPerSquareFoot;
}

double RoomCarpet::getTotalCost() const
{
	return dimensions->getArea() * costPerSquareFoot;
}

