#ifndef EULERFUNCTIONS_H
#define EULERFUNCTIONS_H


inline void ComputeEulerConservatives(const double &rho, const double &u, const double &p, double &u1, double&u2, double &u3, const double &gmma){
    double e;
    u1 = rho;
    u2 = rho*u;
    e = p/(gmma-1)/rho;
    u3 = rho*(0.5*u*u+e);
}

inline double ComputeTotalEnthalpy(double rho, double u, double p, double e){
    double ht = e + 0.5*u*u + p/rho;
    return ht;
}

inline double* EulerFlux(const double u1, const double u2, const double u3, const double u4, const double u5, const double gmma){
    double flux [5];
    flux[0] = u2;
    flux[1] = 0.5*(3-gmma)*u2*u2/u1+(gmma-1)*u3;
    flux[2] = 0.0;
    flux[3] = 0.0;
    flux[4] = gmma*u2*u3/u1-0.5*(gmma-1)*u2*u2*u2/u1/u1;
    return flux;
}

#endif
