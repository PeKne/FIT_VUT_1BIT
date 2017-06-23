NAME=proj4

make: $(NAME).tex
	latex $(NAME).tex
	bibtex $(NAME).aux
	latex $(NAME).tex
	latex $(NAME).tex
	dvips $(NAME).dvi
	ps2pdf $(NAME).ps	
	rm -f $(NAME).dvi $(NAME).ps $(NAME).aux $(NAME).bbl $(NAME).blg $(NAME).log
