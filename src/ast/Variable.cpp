#include "Variable.h"

UnitDistribution UnitDistribution::operator+(const UnitDistribution& rhs)
{
	return UnitDistribution(this->kg + rhs.kg, this->m + rhs.m, this->s + rhs.s);
}

UnitDistribution UnitDistribution::operator-(const UnitDistribution& rhs)
{
	return UnitDistribution(this->kg - rhs.kg, this->m - rhs.m, this->s - rhs.s);
}

bool UnitDistribution::operator==(UnitDistribution rhs) const
{
	return this->kg == rhs.kg && this->m == rhs.m && this->s == rhs.s;
}

bool UnitDistribution::operator!=(UnitDistribution rhs) const
{
	return !(*this == rhs);
}

Constant::Constant(bool flag) : nullObject(flag)
{
	unit = UnitDistribution(0, 0, 0);
	unitNotDefined = false;
	value = 0;
}

Constant::Constant(int val, UnitDistribution distribution) : unit(distribution), value(val)
{
	nullObject = false;
	bool flag = true;
	
	for (int i = 0; i < to_underlying(Unit::NUMBER_OF_UNITS); i++)
	{
		if (distribution == unitTable[i].distribution) flag = false;
	}

	if (distribution == UnitDistribution(0, 0, 0)) flag = false;
	unitNotDefined = flag;
}

std::string Constant::toString()
{
	if (!unitNotDefined)
	{
		for (int i = 0; i < to_underlying(Unit::NUMBER_OF_UNITS); i++)
		{
			if (unitTable[i].distribution == unit)
				return std::to_string(value) + "[" + unitTable[i].representation + "]\n";
		}

		return std::to_string(value) + "\n";
	}

	// returning / printing not predefined unit could be solved here
	return std::string("[UNKNOWN_UNIT]");
}

Constant Constant::operator+(const Constant& c)
{
	if (this->unit != c.unit) return Constant(true);
	else return Constant(this->value + c.value, this->unit);
}

Constant Constant::operator-(const Constant& c)
{
	if (this->unit != c.unit) return Constant(true);
	else return Constant(this->value - c.value, this->unit);
}

Constant Constant::operator*(const Constant& c)
{
	return Constant(this->value * c.value, this->unit + c.unit);
}

Constant Constant::operator/(const Constant& c)
{
	return Constant(this->value / c.value, this->unit - c.unit);
}

Constant Constant::operator<(const Constant& c)
{
	if (this->unit != c.unit) return Constant(true);
	else return Constant(this->value < c.value, UnitDistribution(0, 0, 0));
}

Constant Constant::operator>(const Constant& c)
{
	if (this->unit != c.unit) return Constant(true);
	else return Constant(this->value > c.value, UnitDistribution(0, 0, 0));
}

Constant Constant::operator==(const Constant& c)
{
	if (this->unit != c.unit) return Constant(true);
	else return Constant(this->value == c.value, UnitDistribution(0, 0, 0));
}

Constant Constant::operator!=(const Constant& c)
{
	if (this->unit != c.unit) return Constant(true);
	else return Constant(this->value != c.value, UnitDistribution(0, 0, 0));
}

Constant Constant::operator<=(const Constant& c)
{
	if (this->unit != c.unit) return Constant(true);
	else return Constant(this->value <= c.value, UnitDistribution(0, 0, 0));
}

Constant Constant::operator>=(const Constant& c)
{
	if (this->unit != c.unit) return Constant(true);
	else return Constant(this->value >= c.value, UnitDistribution(0, 0, 0));
}

Constant Constant::operator&&(const Constant& c)
{
	if (this->unit != c.unit) return Constant(true);
	else return Constant(this->value && c.value, UnitDistribution(0, 0, 0));
}

Constant Constant::operator||(const Constant& c)
{
	if (this->unit != c.unit) return Constant(true);
	else return Constant(this->value || c.value, UnitDistribution(0, 0, 0));
}

Constant Constant::operator!()
{
	return Constant(!this->value);
}

Constant Constant::operator-()
{
	return Constant(-this->value, this->unit);
}

Variable::Variable(const std::string& varId) : id(varId)
{
	assignedConstant = Constant(true);
	notInitialized = true;
}

Variable::Variable(const std::string& varId, Constant constant) : assignedConstant(constant), id(varId)
{
	notInitialized = false;
}

Constant Variable::getAssignedConstant()
{
	return assignedConstant;
}

std::string Variable::getId()
{
	return id;
}

void Variable::setAssignedConstant(const Constant& newConstant)
{
	assignedConstant = newConstant;
	if (notInitialized) notInitialized = false;
}