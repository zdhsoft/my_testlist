#工程注释

#工程名称
name := commonlib
#程序名
program := libcommonlib.a

INCLUDE := -I. 
LIBS := 
CPP := g++
CC  := gcc
AR  := ar
MACRO_DEFINE := -D_DEBUG 
CPPFLAGS  := -g -Wall $(INCLUDE) $(INCLUDE_FLAG) $(MACRO_DEFINE)
CFLAGS := $(CPPFLAGS) 
RM := rm -f
CP := cp

SRCDIRS := .
SRCEXTS := .cpp .c
SOURCES := $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(SRCEXTS))))
OBJS    := $(foreach x,$(SRCEXTS),$(patsubst %$(x),%.o,$(filter %$(x),$(SOURCES))))
DEPS    := $(patsubst %.o,%.d,$(OBJS))
DEST	:= ../lib/$(program)

.PHONY : all objs deps clean r cleanall show 

all:$(program)

deps:$(DEPS)
%.d : %.c
	@echo D... $<
	@$(CC) -MM -MD $(CFLAGS) $<
%.d : %.C
	@echo D... $<
	@$(CC) -MM -MD $(CFLAGS) $<
%.d : %.cpp
	@echo D... $<
	@$(CPP) -MM -MD $(CPPFLAGS) $<
%.d : %.CPP
	@echo D... $<
	@$(CPP) -MM -MD $(CPPFLAGS) $<
%.d : %.cc
	@echo D... $<
	@$(CC) -MM -MD $(CPPFLAGS) $<
%.d : %.CC
	@echo D... $<
	@$(CC) -MM -MD $(CPPFLAGS) $<

-include $(DEPS)
	
objs:$(OBJS)
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $(patsubst %.c,%.o,$<)
%.o : %.C
	$(CC) $(CFLAGS) -c $< -o $(patsubst %.C,%.o,$<)
%.o : %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $(patsubst %.cpp,%.o,$<)
%.o : %.CPP
	$(CPP)  $(CPPFLAGS) -c $< -o $(patsubst %.CPP,%.o,$<)
%.o : %.cc
	$(CPP) $(CPPFLAGS) -c $< -o $(patsubst %.cc,%.o,$<)
%.o : %.CC
	$(CPP)  $(CPPFLAGS) -c $< -o $(patsubst %.CC,%.o,$<)

$(program) : $(OBJS)
	$(AR) -r $(program) $(OBJS)
	$(CP) $(program) $(DEST)
	@echo Build $(name) Finish.

#-include $(DEPS)

clean:
	$(RM) *.o *.log
	$(RM) $(program)

cleanall: clean 
	$(RM) *.d

r: cleanall all

show:
	@echo program=$(program)
	@echo name=$(name)
	@echo MACRO_DEFINE=$(MACRO_DEFINE)
	@echo SRCDIRS=$(SRCDIRS)
	@echo SRCEXTS=$(SRCEXTS)
	@echo SOURCES=$(SOURCES)
	@echo OBJS=$(OBJS)
	@echo DEPS=$(DEPS)
	@echo LIBS=$(LIBS)
	@echo CC=$(CC)
	@echo CPP=$(CPP)
	@echo INCLUDE=$(INCLUDE)
	@echo CPPFLAGS=$(CPPFLAGS)
	@echo CFLAGS=$(CFLAGS)
	@echo DEST = $(DEST)

