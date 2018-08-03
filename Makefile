# Compile the shared library
all:
	$(MAKE) -C src 

# Compile a sample C++ synthesizer program 
sample:
	$(MAKE) -C samples

# Prevent errors from occuring if a file were named 'clean'
.PHONY: clean

# Clean rule for getting rid of stray files
clean:
	$(MAKE) -C samples clean
	$(MAKE) -C src clean
	rm -f *~ core*
	rm -rf bin

