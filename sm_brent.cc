/*
 * sm_brent.cc - Brent's line minimization for StatModel
 *
 * Jun Korenaga
 */

#include <cmath>
#include <limits>
#include "statmodel.h"

double StatModel::brent(double ax, double bx, double cx,
			double& xmin, PF1DIM pfunc)
{
    const int ITMAX = 100;
    const double CGOLD = 0.3819660;
    const double ZEPS = std::numeric_limits<double>::epsilon()*1.0e-3;

    double a, b, d = 0.0, etemp, fu, fv, fw, fx, p, q, r, tol1, tol2, u, v, w, x, xm;
    double e = 0.0;
    a = (ax<cx ? ax : cx);
    b = (ax>cx ? ax : cx);
    x = w = v = bx;
    fw = fv = fx = (this->*pfunc)(x);
    for (int iter=0; iter<ITMAX; iter++){
        xm = 0.5*(a+b);
        tol2 = 2.0*(tol1 = brent_tol*fabs(x)+ZEPS);
        if (fabs(x-xm) <= (tol2-0.5*(b-a))) {
            xmin = x;
            return fx;
        }
        if (fabs(e)>tol1){
            r = (x-w)*(fx-fv);
            q = (x-v)*(fx-fw);
            p = (x-v)*q-(x-w)*r;
            q = 2.0*(q-r);
            if (q > 0.0) p = -p;
            q = fabs(q);
            etemp = e;
            e = d;
            if (fabs(p)>=fabs(0.5*q*etemp) || p<=q*(a-x) || p>=q*(b-x)){
                d = CGOLD*(e = (x >= xm ? a-x : b-x));
	    }else{
                d = p/q;
                u = x+d;
                if (u-a<tol2 || b-u<tol2){
                    d = (xm-x >= 0.0 ? fabs(tol1) : -fabs(tol1));
		}
            }
        }else{
            d = CGOLD*(e=(x>=xm ? a-x : b-x));
        }
        u = (fabs(d)>=tol1 ? x+d : x+(d>=0.0 ? fabs(tol1) : -fabs(tol1)));
        fu = (this->*pfunc)(u);
        if (fu<=fx){
            if (u>=x){
		a=x;
	    }else{
		b = x;
	    }
            v = w;
            fv = fw;
            w = x;
            fw = fx;
            x = u;
            fx = fu;
        }else{
            if (u<x){
		a = u;
	    }else{
		b = u;
	    }
            if (fu<=fw || w==x){
                v = w;
                fv = fw;
                w = u;
                fw = fu;
            }else if (fu<=fv || v==x || v==w){
                v = u;
                fv = fu;
            }
        }
    }
    std::cerr << "StatModel::brent() too many iterations" << std::endl;
    xmin = x;
    return fx;
}
