// Driver program for the Westfield Carpet Company Carpet Calculator
#include <iostream>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include "FeetInches.h"
#include "RoomDimension.h"
#include "RoomCarpet.h"

using namespace std;

// Helper function to clear invalid input from cin
void clearInputStream()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Reads and validates a non-negative FeetInches measurement (must be > 0 total inches)
FeetInches readValidMeasurement(const string& label)
{
	int feet = 0;
	int inches = 0;

	while (true)
	{
		cout << "Enter " << label << " feet (non-negative integer): ";
		if (!(cin >> feet))
		{
			cout << "Error: Please enter a valid integer for feet.\n";
			clearInputStream();
			continue;
		}

		cout << "Enter " << label << " inches (non-negative integer): ";
		if (!(cin >> inches))
		{
			cout << "Error: Please enter a valid integer for inches.\n";
			clearInputStream();
			continue;
		}

		if (feet < 0 || inches < 0)
		{
			cout << "Error: Feet and inches cannot be negative. Please try again.\n";
			continue;
		}

		if (feet == 0 && inches == 0)
		{
			cout << "Error: " << label << " must be greater than zero. Please try again.\n";
			continue;
		}

		// FeetInches constructor automatically normalizes inches >= 12
		return FeetInches(feet, inches);
	}
}

// Reads and validates a positive carpet price per square foot
double readValidPrice()
{
	double price = 0.0;

	while (true)
	{
		cout << "Enter carpet price per square foot ($): ";
		if (!(cin >> price))
		{
			cout << "Error: Please enter a valid numeric price.\n";
			clearInputStream();
			continue;
		}

		if (price <= 0.0)
		{
			cout << "Error: Price per square foot must be greater than 0. Please try again.\n";
			continue;
		}

		return price;
	}
}

// Runs automated verification tests for core class features and relationships
void runAutomatedTests()
{
	cout << "====================================================\n";
	cout << "  AUTOMATED FEATURE & RELATIONSHIP VERIFICATION\n";
	cout << "====================================================\n";

	// 1. FeetInches construction and normalization
	FeetInches normTest(3, 14);
	cout << "[Test 1] Normalization (3 ft, 14 in): " << normTest << "\n";

	// 2. Explicit demonstration of FeetInches copy constructor and independence
	FeetInches original(8, 6);
	FeetInches copyObj(original); // Invokes copy constructor
	cout << "[Test 2] Copy Constructor:\n";
	cout << "         Original: " << original << " | Copy: " << copyObj << "\n";
	copyObj.setFeet(12);
	copyObj.setInches(3);
	cout << "         After modifying copy -> Original: " << original
		<< " | Copy: " << copyObj << "\n";

	// 3. Independent test of FeetInches::operator* (whole feet)
	FeetInches wholeA(10, 0);
	FeetInches wholeB(12, 0);
	double wholeArea = wholeA * wholeB;
	cout << fixed << setprecision(3);
	cout << "[Test 3] operator* (Whole feet): (" << wholeA << ") * (" << wholeB
		<< ") = " << wholeArea << " sq ft\n";

	// 4. Independent test of FeetInches::operator* (nonzero inches, fractional result)
	FeetInches fracA(5, 6);
	FeetInches fracB(4, 3);
	double fracArea = fracA * fracB;
	cout << "[Test 4] operator* (Fractional): (" << fracA << ") * (" << fracB
		<< ") = " << fracArea << " sq ft\n";
	cout << "         Operands unchanged -> fracA: " << fracA << " | fracB: " << fracB << "\n";

	// 5. RoomDimension::getArea() and Composition independence
	FeetInches lenSource(12, 6);
	FeetInches widSource(10, 0);
	RoomDimension sampleRoom(lenSource, widSource);
	lenSource.setFeet(99); // Modifying source should not affect sampleRoom
	cout << "[Test 5] RoomDimension Composition & getArea():\n";
	cout << "         Room Length: " << sampleRoom.getLength()
		<< " | Width: " << sampleRoom.getWidth()
		<< " | Area: " << sampleRoom.getArea() << " sq ft\n";

	// 6. RoomCarpet::getTotalCost() with two prices sharing one RoomDimension (Aggregation)
	RoomCarpet standardQuote(&sampleRoom, 4.50);
	RoomCarpet premiumQuote(&sampleRoom, 8.25);
	cout << fixed << setprecision(2);
	cout << "[Test 6] RoomCarpet Aggregation (two quotes for same room):\n";
	cout << "         Standard ($4.50/sq ft): $" << standardQuote.getTotalCost() << "\n";
	cout << "         Premium  ($8.25/sq ft): $" << premiumQuote.getTotalCost() << "\n";

	// 7. Invalid state protection (null pointer / non-positive price)
	cout << "[Test 7] Guarding against invalid RoomCarpet arguments:\n";
	try
	{
		RoomCarpet badPtr(nullptr, 5.00);
	}
	catch (const invalid_argument& ex)
	{
		cout << "         Caught expected error: " << ex.what() << "\n";
	}
	try
	{
		RoomCarpet badPrice(&sampleRoom, -2.50);
	}
	catch (const invalid_argument& ex)
	{
		cout << "         Caught expected error: " << ex.what() << "\n";
	}
	cout << "====================================================\n\n";
}

int main()
{
	runAutomatedTests();

	cout << "====================================================\n";
	cout << "      WESTFIELD CARPET COMPANY CALCULATOR\n";
	cout << "====================================================\n";

	FeetInches roomLength = readValidMeasurement("room length");
	FeetInches roomWidth = readValidMeasurement("room width");
	double pricePerSqFt = readValidPrice();

	// Composition: RoomDimension owns copies of roomLength and roomWidth
	RoomDimension userRoom(roomLength, roomWidth);

	// Aggregation: RoomCarpet refers to userRoom via a non-owning pointer
	RoomCarpet userCarpet(&userRoom, pricePerSqFt);

	cout << "\n---------------- CARPET QUOTE SUMMARY ----------------\n";
	cout << "Room Length:          " << userRoom.getLength() << "\n";
	cout << "Room Width:           " << userRoom.getWidth() << "\n";
	cout << fixed << setprecision(3);
	cout << "Room Area:            " << userRoom.getArea() << " sq ft\n";
	cout << fixed << setprecision(2);
	cout << "Carpet Price:         $" << userCarpet.getCostPerSquareFoot() << " per sq ft\n";
	cout << "Total Carpet Cost:    $" << userCarpet.getTotalCost() << "\n";
	cout << "------------------------------------------------------\n";

	return 0;
}

