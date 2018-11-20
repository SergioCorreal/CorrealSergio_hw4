Resultados_hw4.pdf : Resultados_hw4.tex 45.png otherAngles.png initial.png ci1.png ci2.png cf.png oi1.png oi2.png of.png pi1.png pi2.png pf.png i1.png i2.png f.png
	pdflatex Resultados_hw4.tex 
45.png otherAngles.png initial.png ci1.png ci2.png cf.png oi1.png oi2.png of.png pi1.png pi2.png pf.png i1.png i2.png f.png : Plots_hw4.py pde_initial.txt pde_ci1.txt pde_ci2.txt pde_cf.txt pde_oi1.txt pde_oi2.txt pde_of.txt pde_pi1.txt pde_pi2.txt pde_pf.txt ode_10.txt ode_20.txt ode_30.txt ode_40.txt ode_50.txt ode_60.txt ode_70.txt ode_45.txt
	python Plots_hw4.py
pde_initial.txt pde_ci1.txt pde_ci2.txt pde_cf.txt pde_oi1.txt pde_oi2.txt pde_of.txt pde_pi1.txt pde_pi2.txt pde_pf.txt : PDE.cpp
	g++ PDE.cpp
	./a.out
ode_10.txt ode_20.txt ode_30.txt ode_40.txt ode_50.txt ode_60.txt ode_70.txt ode_45.txt: ODE.cpp
	g++ ODE.cpp
	./a.out
