#pragma once

#include <string>
#include "../commonElements.h"

struct UnitDistribution
{
	int kg;
	int m;
	int s;

	UnitDistribution(int kilograms = 0, int metres = 0, int seconds = 0) :
		kg(kilograms), m(metres), s(seconds) {}
	UnitDistribution operator+(const UnitDistribution& rhs);
	UnitDistribution operator-(const UnitDistribution& rhs);
	bool operator==(UnitDistribution rhs) const;
	bool operator!=(UnitDistribution rhs) const;
};

struct Constant
{
	/* null object; neither value nor unit is defined; to use e.g. when function does not return 
	anything, although it's result is assigned to variable */
	bool nullObject;
	UnitDistribution unit;
	bool unitNotDefined;
	int value;

	Constant(bool flag = false);
	Constant(int val, UnitDistribution distribution = UnitDistribution(0, 0, 0));
	std::string toString();
	Constant operator+(const Constant& c);
	Constant operator-(const Constant& c);
	Constant operator*(const Constant& c);
	Constant operator/(const Constant& c);
	Constant operator<(const Constant& c);
	Constant operator>(const Constant& c);
	Constant operator==(const Constant& c);
	Constant operator!=(const Constant& c);
	Constant operator<=(const Constant& c);
	Constant operator>=(const Constant& c);
	Constant operator&&(const Constant& c);
	Constant operator||(const Constant& c);
	Constant operator!();
	Constant operator-();
};

struct UnitDescriptor
{
	UnitDistribution distribution;
	std::string representation;
	Unit unit;
};

const UnitDescriptor unitTable[to_underlying(Unit::NUMBER_OF_UNITS)] =
{
	// distribution					representation		unit			  
	//---------------------------------------------------------------------------
	 { UnitDistribution(0, 1, 0),	"m",				Unit::distance			},
	 { UnitDistribution(1, 0, 0),	"kg",				Unit::mass				},
	 { UnitDistribution(0, 0, 1),	"s",				Unit::timeUnit			},
	 { UnitDistribution(0, 0, -1),	"Hz",				Unit::frequency			},
	 { UnitDistribution(1, 1, -2),	"N",				Unit::force				},
	 { UnitDistribution(1, 2, -2),	"J",				Unit::energy 			},
	 { UnitDistribution(1, 2, -3),	"W",				Unit::work  			},
	 { UnitDistribution(0, 1, -1),	"m/s",				Unit::speed 			},
	 { UnitDistribution(0, 1, -2),	"m/s^2",			Unit::acceleration		},
	 { UnitDistribution(1, 1, -1),	"N*s",				Unit::momentum			},
	 { UnitDistribution(1, 2, -1),	"J*s",				Unit::angularMomentum 	},
	 { UnitDistribution(1, 2, 0),	"kg*m^2",			Unit::momentOfInertia 	}
};

class Variable
{
	Constant assignedConstant;
	const std::string id;
	bool notInitialized;

public:
	Variable(const std::string& varId);
	Variable(const std::string& varId, Constant constant);
	Constant getAssignedConstant();
	std::string getId();
	void setAssignedConstant(const Constant& newConstant);
};