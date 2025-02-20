# labmc
MCMC inversion code for rock deformation data

This code is made public in conjuction with the publication of Fernandez & Korenaga (JGR, 2025). The current version of our MCMC inversion code relies on several functions from Numerical Recipes (Press et al., 1992), which are licensed, so we cannot deposit our code in its entirety in a public depository. We plan to replace these functions with our own implementation in future, but in the meantime, to ensure transparency and reproducibility, we have deposited all parts of our code that do not contain Numerical Recipes functions, and for the functions that rely on Numerical Recipes, we provide descriptions for which Numerical Recipes functions are used (see Makefile). 
