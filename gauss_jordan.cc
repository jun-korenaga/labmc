//
// gaussJordan - solves A*x = b by Gauss-Jordan elimination
//
#include "array.h"

bool gaussJordan(Array2d<double>& A, Array1d<double>& b,
		 Array1d<double>& x)
{
    int n = A.nRow();
    for (int i=1; i<=n; i++) {
        // Search for maximum in this column
        double maxEl = abs(A(i,i));
        int maxRow = i;
        for (int k=i+1; k<=n; k++) {
            if (abs(A(k,i)) > maxEl) {
                maxEl = abs(A(k,i));
                maxRow = k;
            }
        }

        // Check for singularity
        if (maxEl < 1e-12) {
	    std::cout << "Matrix is singular or near singular." << std::endl;
            return false;
        }

        // Swap maximum row with current row (column by column)
        for (int k=i; k<=n; k++) {
            std::swap(A(maxRow,k), A(i,k));
        }
        std::swap(b(maxRow), b(i));

        // Make all rows below this one 0 in current column
        for (int k=i+1; k<=n; k++) {
            double c = -A(k,i)/A(i,i);
            for (int j=i; j<=n; j++) {
                if (i==j) {
                    A(k,j) = 0;
                } else {
                    A(k,j) += c*A(i,j);
                }
            }
            b(k) += c*b(i);
        }
    }

    // Solve equation Ax=b for an upper triangular matrix A
    for (int i=n; i>=1; i--) {
        if (abs(A(i,i)) < 1e-12) {
	    std::cout << "Matrix is singular or near singular." << std::endl;
            return false;
        }
        x(i) = b(i)/A(i,i);
        for (int k=i-1; k>=1; k--) {
            b(k) -= A(k,i)*x(i);
        }
    }

    return true;
}
