// Implementation file for the RoomDimension class
#include <stdexcept>
#include "RoomDimension.h"

RoomDimension::RoomDimension(const FeetInches& roomLength, const FeetInches& roomWidth)
	: length(roomLength), width(roomWidth)
{
	if (length.getFeet() < 0 || length.getInches() < 0 ||
		width.getFeet() < 0 || width.getInches() < 0)
	{
		throw std::invalid_argument("Room dimensions cannot be negative.");
	}
}

FeetInches RoomDimension::getLength() const
{
	return length;
}

FeetInches RoomDimension::getWidth() const
{
	return width;
}

double RoomDimension::getArea() const
{
	return length * width;
}

