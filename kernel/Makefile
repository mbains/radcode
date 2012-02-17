DIRS = example1 \
	example2 \
	mods \
	hpet \
#	rtc-example 

.PHONY: dirs $(DIRS)

dirs: $(DIRS)

$(DIRS):
	cd $@; $(MAKE) 

clean:
	for dir in $(DIRS); do \
		$(MAKE) -C $$dir clean; \
	done

#$(MAKE) -C $@2 
#clean: $(DIRS)
#	cd $< && "$(MAKE)" clean
