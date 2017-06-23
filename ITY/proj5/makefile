NAME=proj5

make: $(NAME).tex
	latex $(NAME).tex
	latex $(NAME).tex
	dvips -t a4 $(NAME).dvi
	ps2pdf -sPAPERSIZE=a4 $(NAME).ps	
	rm -f $(NAME).dvi $(NAME).ps $(NAME).aux $(NAME).bbl $(NAME).blg $(NAME).log $(NAME).out
