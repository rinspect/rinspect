  
CC  = g++

AC_FLAGS = "-I../yices-1.0.28/include"

CFLAGS =  -Wall  -g  -pthread -D__USE_XOPEN2K $(AC_FLAGS)

LIB_SRC_NAME = yices_dp

ALL_SRC_NAME = $(LIB_SRC_NAME) 

PRODUCT = smtdp

LIBDIR =  lib
PRODUCT_LIB = $(LIBDIR)/lib$(PRODUCT).a
PRODUCT_DLL = $(LIBDIR)/lib$(PRODUCT).so

LIB_OBJS = $(foreach file, $(LIB_SRC_NAME), $(file).o)
DLL_OBJS = $(foreach file, $(LIB_SRC_NAME), $(file).os)

ALL_SRC = $(foreach file, $(ALL_SRC_NAME), $(file).cc )

#all: test_dep_dirs  dep  $(PRODUCT_LIB) $(PRODUCT_DLL) 

all: $(PRODUCT_LIB) $(PRODUCT_DLL) 

test_dep_dirs:
	if test -d $(DEP_DIR); then :; else mkdir $(DEP_DIR); fi

$(PRODUCT_LIB):   $(LIB_OBJS)
	ar rcs $@ $(LIB_OBJS)
	ranlib $@
	cp $(PRODUCT_LIB) ../build/Release+Debug+Asserts/lib/

$(PRODUCT_DLL):   $(DLL_OBJS)
	$(CC) -shared -o $@  $(DLL_OBJS)
	cp $(PRODUCT_DLL) ../build/Release+Debug+Asserts/lib/

cleandep:
	@echo "Cleaning dependent info files .... "
	@rm -f $(DEPS)

clean:  cleandep
	@echo "Cleaning object files ...."
	@rm -f *.o *.os
	@rm -f lib/lib$(PRODUCT).*
	@echo "Cleaning backup files ...."
	@rm -f *~

dep : $(DEPS)

-include $(DEPS)

%.o : %.cc
	$(CC) $(CFLAGS) -c $^  -o $@

%.os : %.cc
	$(CC) $(CFLAGS) -fPIC -c $^ -o $@

.deps/%.d : %.cc
	@echo  "Generating dependency information for " $<
	@$(CC) -MM -MF $@ -MT ext/$*.o $(USR_DEFS) $(INCDIRS)  $<
	@test -f Makefile.dep && cp Makefile.dep Makefile.dep.new || :
	@cat $@ >> Makefile.dep.new
	@mv Makefile.dep.new Makefile.dep

