### Makefile for 2. Course project (IVS) ###
###  		Team: Pejaja		 ###
NAMES=xprukn00_xknetl00_xkosek03

all:
	
run:
	python3 ./Calc.py

pack: clean doc
	cd ./../../ && mkdir $(NAMES) && cd ./$(NAMES) && mkdir repo doc install
	cd ./../../ && cp -r ./pejaja-calc-ivs/. ./$(NAMES)/repo && mv ./$(NAMES)/repo/src/docs/html ./$(NAMES)/doc
	cd ./../../ && mv ./$(NAMES)/repo/pejajacalc_1.0_all.deb ./$(NAMES)/install
	cd ./../../ && zip -r $(NAMES) ./$(NAMES) && rm -rf $(NAMES)
clean:
	rm -rf ./__pycache__ ./mathlib/__pycache__ ./docs ./../.metadata
test:
	python3 mathlib_tests.py

doc:
	doxygen Doxyfile
