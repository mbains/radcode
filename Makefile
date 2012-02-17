DIRS = \
	openGL \
	qt \
	numpy \
	general_c \
	kernel \
	python \

.PHONY: dirs $(DIRS)

dirs: $(DIRS)

$(DIRS):
	$(MAKE) -C $@

clean:
	for dir in $(DIRS); do \
		$(MAKE) -C $$dir clean; \
	done

#$(MAKE) -C $@2 
#clean: $(DIRS)
#	cd $< && "$(MAKE)" clean
