CC := g++
target := control.bin
srcs := $(shell find -name "*.cpp")
objs := $(srcs:.cpp=.o)
deps := $(srcs:.cpp=.d)
CPPFLAGS := -std=c++11

all: ${target}

-include ../objs.mk
test:
	echo $(pub_obj)
$(target): $(objs) $(pub_obj)
	$(CC) -o $@ $^

-include $(deps)
%.d: %.cpp
	$(CC) -MM $< > $@

clean: 
	rm *.bin *.o *.d

