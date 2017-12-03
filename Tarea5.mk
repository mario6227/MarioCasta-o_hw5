all: curva

curva: Plots.py Results_hw5.tex CurvaRotacion.c
	cc CurvaRotacion.c -lm -o CR.x
	./CR.x
	python Plots.py
	pdflatex Results_hw5.tex

Plots.py: CurvaRotacion.c
	cc CurvaRotacion.c -lm -o CR.x
	./CR.x
	python Plots.py
	pdflatex Results_hw5.tex

Results_hw5.tex: Plots.py
	python Plots.py
	pdflatex Results_hw5.tex
