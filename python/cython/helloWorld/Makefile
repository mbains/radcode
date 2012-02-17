OBJECT=helloworld
PYTHON=python2.5
all: $(OBJECT).so

$(OBJECT).so: $(OBJECT).pyx
	$(PYTHON) setup.py build_ext --inplace

clean:
	rm -f $(OBJECT).so $(OBJECT).c
	$(PYTHON) setup.py clean

