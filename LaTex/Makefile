PAPER = project
BIB = $(wildcard *.bib *.bst)
TEX = $(wildcard *.tex)
FIG = $(wildcard figures/*.pdf)
SRC = $(wildcard *.cls *.sty)

.PHONY: tar zip distclean clean

$(PAPER).pdf: $(TEX) $(BIB) $(FIG) $(SRC)
	@make clean
	@pdflatex $(PAPER)
	@bibtex $(PAPER)
	@pdflatex $(PAPER) > /dev/null
	@pdflatex $(PAPER) > /dev/null

tar:
	make; make distclean
	mkdir $(PAPER)
	cp -rf $(TEX) $(SRC) *.pdf figures Makefile $(PAPER)/
	zip -r $(PAPER).zip $(PAPER)/
	rm -rf $(PAPER)/

zip:
	make tar

distclean:
	rm -rf *.glsdefs *.aux *.bbl *.blg *.log *.out *.xml *.bcf *blx.bib $(PAPER)/ $(PAPER).zip

clean:
	make distclean; rm -f $(PAPER).pdf

push:
	git add $(BIB) $(TEX) $(FIG) $(SRC) Makefile; git commit -m "update"; git pull > /dev/null; git push; make

pull:
	git pull; make

