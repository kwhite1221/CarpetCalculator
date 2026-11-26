// Specification file for the RoomDimension class
#ifndef ROOMDIMENSION_H
#define ROOMDIMENSION_H

#include "FeetInches.h"

// The RoomDimension class represents the length and width of a
// rectangular room using composition with two FeetInches objects.
class RoomDimension
{
private:
	FeetInches length; // Owned by RoomDimension (composition)
	FeetInches width;  // Owned by RoomDimension (composition)

public:
	// Constructor using member initializer list
	RoomDimension(const FeetInches& roomLength, const FeetInches& roomWidth);

	// Accessors
	FeetInches getLength() const;
	FeetInches getWidth() const;

	// Returns room area in square feet using FeetInches::operator*
	double getArea() const;
};

#endif
