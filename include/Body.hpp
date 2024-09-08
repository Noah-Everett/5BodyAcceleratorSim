
#ifndef BODY_HPP
#define BODY_HPP

#include "Vector4.hpp"

class Body {
public:
    // Constructor
    Body(double mass, double charge) : mass_(mass), charge_(charge) {}

    // Getters
    double GetMass() const { return mass_; }
    double GetCharge() const { return charge_; }

    // Setters
    void SetMass(double mass) { mass_ = mass; }
    void SetCharge(double charge) { charge_ = charge; }

    // Calculate gravitational force
    double CalculateGravitationalForce(double other_mass, double distance) const {
        const double G = 6.67430e-11;  // Gravitational constant
        return G * mass_ * other_mass / (distance * distance);
    }

    // Calculate electromagnetic force
    double CalculateElectromagneticForce(double other_charge, double distance) const {
        const double k = 8.987551787e9;  // Coulomb's constant
        return k * charge_ * other_charge / (distance * distance);
    }

private:
    double mass_;
    double charge_;
};

#endif



