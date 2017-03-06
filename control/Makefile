target := control.bin

-include ../def.mk
srcs := $(shell find -name "*.cpp")
objs := $(srcs:.cpp=.o)
deps := $(srcs:.cpp=.d)

-include ../objs.mk
test:
	echo $(pub_obj)
$(target): $(objs) $(pub_obj)
	$(CC) -o $@ $^ ${LIBS}

-include $(deps)
%.d: %.cpp
	$(CC) -MM $< > $@

clean: 
	rm *.bin *.o *.d

