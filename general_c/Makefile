DIRS =  macros \
        curses \
        random_number_gen \
        time \
        memory \
        bitfield \
        twokeymap \
	reverseString \
	strcopy \
	epoll \
	readfile \
	factory \


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
