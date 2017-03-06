-include def.mk
srcs := $(shell ls *.cpp)
objs := $(srcs:.cpp=.o)
deps := $(srcs:.cpp=.d)

objs1 := $(addprefix ../,$(objs))
all:$(objs)
	echo pub_obj:=$(objs1) > objs.mk

-include $(deps)
%.d: %.cpp
	$(CC) -MM $< > $@ $(LIBS)

clean:
	rm *.d *.o *.bin
