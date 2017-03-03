CC := g++
target := client.bin
srcs := $(shell find -name "*.cpp")
objs := $(srcs:.cpp=.o)
deps := $(srcs:.cpp=.d)


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

