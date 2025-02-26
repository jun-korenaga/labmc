/*
 * sm_mnbrak.cc - initial bracket search for StatModel
 *
 * Jun Korenaga
 */

#include <cmath>
#include "statmodel.h"

void StatModel::mnbrak(double& ax, double& bx, double& cx,
		       double& fa, double& fb, double& fc,
		       PF1DIM pfunc)
{
    const double GOLD = 1.618034;
    const int MAX_ITER = 100;
    
    fa = (this->*pfunc)(ax);
    fb = (this->*pfunc)(bx);
    if (fb > fa){
        std::swap(ax, bx);
        std::swap(fa, fb);
    }
    cx = bx + GOLD*(bx - ax);
    fc = (this->*pfunc)(cx);
//    for (int iter=0; iter<MAX_ITER; ++iter) {
    while (fb>fc){
//        if (fb<fc) return;
        double r = (bx-ax)*(fb-fc);
        double q = (bx-cx)*(fb-fa);
        double u = bx - ((bx-cx)*q - (bx-ax)*r)
	    / (2.0 * ((q>r ? q-r : r-q)));
        double ulim = bx + 100.0*(cx-bx);
        double fu;
        if ((bx-u)*(u-cx) > 0.0){
            fu = (this->*pfunc)(u);
            if (fu<fc){
                ax = bx;
                bx = u;
                fa = fb;
                fb = fu;
                return;
            } else if (fu>fb){
                cx = u;
                fc = fu;
                return;
            }
            u = cx + GOLD*(cx-bx);
            fu = (this->*pfunc)(u);
        }else if ((cx-u)*(u-ulim) > 0.0){
            fu = (this->*pfunc)(u);
            if (fu<fc){
                bx = cx;
                cx = u;
                u = cx + GOLD*(cx-bx);
                fb = fc;
                fc = fu;
                fu = (this->*pfunc)(u);
            }
        }else if ((u-ulim)*(ulim-cx) >= 0.0){
            u = ulim;
            fu = (this->*pfunc)(u);
        }else{
            u = cx + GOLD*(cx-bx);
            fu = (this->*pfunc)(u);
        }
        ax = bx;
        bx = cx;
        cx = u;
        fa = fb;
        fb = fc;
        fc = fu;
    }
//    std::cerr << "StatModel::mnbrak() minimum did not converge" << std::endl;
}
    
