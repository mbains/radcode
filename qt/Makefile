DIRS = \
	dialog \
	calculatorform \
	browser \
	ex1 \
	ex2 \
	borderlayout \
	quit \
	slider \
	converter \
	converter2 \
	creator_example \
	flickscroll \
	svgToggleDemo


.PHONY: dirs $(DIRS)

dirs: $(DIRS)

$(DIRS):
	cd $@ && qmake && $(MAKE)

clean: 
	for dir in $(DIRS); do \
		cd $$dir && $(MAKE) distclean && cd ..; \
	done

#$(MAKE) -C $@2 
#clean: $(DIRS)
#	cd $< && "$(MAKE)" clean
