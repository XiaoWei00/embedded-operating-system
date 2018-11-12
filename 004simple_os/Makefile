

CC := arm-linux-gcc

LD := arm-linux-ld

LDS := simple_os.lds

SSRCS := $(wildcard *.S)

CSRCS := $(wildcard *.c)

SRCS := $(SSRCS) + $(CSRCS)

OBJS := $(patsubst %.S,%.o,$(SSRCS))

OBJS += $(patsubst %.c,%.o,$(CSRCS))


TARGET := simple_os.elf


all:$(OBJS)
	$(LD) -T $(LDS) $^  -o $(TARGET)  
		
%.o: %.S %.c
	$(CC) -static -nostartfiles -nostdlib  $< -o $@ 	
	

sinclude $(INSRCS:.c=.d)
%.d:%.c 
	$(CC) -MM $^ > $@.$$$$;\
	sed 's/\($*.o\)/\1 $@/g' < $@.$$$$ > $@;\
	rm -f $@.$$$$	
	
.PHONY : bin
bin :
	arm-linux-objcopy -O binary -S  $(TARGET) simple_os.bin
	
.PHONY : dis
dis:
	arm-linux-objdump -D $(TARGET) > simple_os.dis
		
.PHONY:clean
clean:
	rm -f *.o *.elf *.bin *.i *.d *.dis




