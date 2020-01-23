#pragma once

// as I can't have a strongly typed enum to int implicit conversion...

template <typename E>
constexpr typename std::underlying_type<E>::type to_underlying(E e) noexcept {
    return static_cast<typename std::underlying_type<E>::type>(e);
}

// enums used both by parser and ast tree

enum class Operator
{
	equalToOp, notEqualToOp, greaterThanOp, greaterThanOrEqualToOp, lessThanOp, lessThanOrEqualToOp,
	additionOp, subtractionOp, multiplicationOp, divisionOp, notOp, MAX_OPERATOR

};

enum class Unit
{
	distance, mass, timeUnit, frequency, force, energy, work, speed, acceleration, momentum,
	angularMomentum, momentOfInertia, NUMBER_OF_UNITS
};