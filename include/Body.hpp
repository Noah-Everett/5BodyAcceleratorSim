#ifndef BODY_HPP
#define BODY_HPP

#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Units/PhysicalConstants.h"

#include <iostream>
#include <cmath>

class Body {
private:
    // 4-vector components
    CLHEP::HepLorentzVector m_position;  // (t, x, y, z)
    CLHEP::HepLorentzVector m_momentum;  // (e, px, py, pz)

    // Individual particle properties
    double& m_x  = m_position[1];
    double& m_y  = m_position[2];
    double& m_z  = m_position[3];
    double& m_px = m_momentum[1];
    double& m_py = m_momentum[2];
    double& m_pz = m_momentum[3];
    double& m_t  = m_position[0];
    double& m_e  = m_momentum[0];
    double  m_m;
    double  m_q;

public:
    // Constructor
    Body(double t_x  = 0.0, double t_y  = 0.0, double t_z  = 0.0, double t_t = 0.0, 
               double t_px = 0.0, double t_py = 0.0, double t_pz = 0.0, double t_m = 0.0,
               double t_q  = 0.0                                                         )
        : m_position(t_t, t_x, t_y, t_z), m_m(t_m), m_q(t_q) {
        update_momentum( t_px, t_py, t_pz );
    }

    // Destructor
   ~Body() {}

    // Component Getters
    double get_x () const { return m_x ; }; double x () const { return get_x (); }
    double get_y () const { return m_y ; }; double y () const { return get_y (); }
    double get_z () const { return m_z ; }; double z () const { return get_z (); }
    double get_px() const { return m_px; }; double px() const { return get_px(); }
    double get_py() const { return m_py; }; double py() const { return get_py(); }
    double get_pz() const { return m_pz; }; double pz() const { return get_pz(); }
    double get_t () const { return m_t ; }; double t () const { return get_t (); }
    double get_e () const { return m_e ; }; double e () const { return get_e (); }
    double get_m () const { return m_m ; }; double m () const { return get_m (); }
    double get_q () const { return m_q ; }; double q () const { return get_q (); }

    // Component Setters
    void set_x ( double t_x  ) { update_position( t_x, m_y, m_z      ); } 
    void set_y ( double t_y  ) { update_position( m_x, t_y, m_z      ); }
    void set_z ( double t_z  ) { update_position( m_x, m_y, t_z      ); }
    void set_px( double t_px ) { update_momentum( t_px, m_py, m_pz   ); }
    void set_py( double t_py ) { update_momentum( m_px, t_py, m_pz   ); }
    void set_pz( double t_pz ) { update_momentum( m_px, m_py, t_pz   ); }
    void set_t ( double t_t  ) { update_position( t_t, m_x, m_y, m_z ); }

protected:
    // Updators
    void update_position( double t_x , double t_y , double t_z              ) { m_position.set( m_t, t_x, t_y, t_z ); }
    void update_position( double t_t , double t_x , double t_y , double t_z ) { m_position.set( t_t, t_x, t_y, t_z ); }
    void update_momentum( double t_px, double t_py, double t_pz             ) {
        CLHEP::Hep3Vector p( t_px, t_py, t_pz );
        double energy = std::sqrt( p.mag2() * CLHEP::c_squared +m_m *m_m * CLHEP::c_squared * CLHEP::c_squared );
        m_momentum.setPx( t_px   );
        m_momentum.setPy( t_py   );
        m_momentum.setPz( t_pz   );
        m_momentum.setE ( energy );
    }

public:
    // Calculation Getters
    CLHEP::Hep3Vector velocity() const { return m_momentum.boostVector(); } 
    double gamma() const { return m_momentum.e() / (m_m * CLHEP::c_squared ); } // Calculate Lorentz factor (gamma)

    // Calculation Setters
    void boost( const CLHEP::Hep3Vector& beta ) { 
        m_position.boost( beta ); 
        m_momentum.boost( beta ); 
    } // Apply a Lorentz boost
    void rotate( const CLHEP::HepLorentzRotation& rotation ) { 
        m_position *= rotation;
        m_momentum *= rotation;
    } // Apply a Lorentz rotation

    // Steppers
    void step( double t_dt ) {
        CLHEP::Hep3Vector displacement = velocity() * t_dt;
        update_position( m_x + displacement.x(), m_y + displacement.y(), m_z + displacement.z() );
    } // Method to update position based on current momentum (time evolution)
    void step(const CLHEP::Hep3Vector& t_force, double t_dt) {
        CLHEP::Hep3Vector dp = t_force * t_dt;
        update_momentum( m_px + dp.x(), m_py + dp.y(), m_pz + dp.z() );
    } // Method to apply a force for a given time interval
};

#endif // BODY_HPP