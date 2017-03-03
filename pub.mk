CC=g++
srcs := $(shell ls *.cpp)
objs := $(srcs:.cpp=.o)
deps := $(srcs:.cpp=.d)

objs1 := $(addprefix ../,$(objs))
all:$(objs)
	echo pub_obj:=$(objs1) > objs.mk

-include $(deps)
%.d: %.cpp
	$(CC) -MM $< > $@

clean:
	rm *.d *.o *.bin
