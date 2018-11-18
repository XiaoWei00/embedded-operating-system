







CC := arm-linux-gcc

LD := arm-linux-ld

LDS := s3c2440.lds

SRCS := $(wildcard *.c)

OBJS := $(patsubst %.c,%.o,$(SRCS))

TARGET := user.elf


$(TARGET):$(OBJS)
	$(LD) -T $(LDS)  $^ -o $(TARGET)

%.o:%.c
	$(CC) -c -o $@ $<

sinclude $(SRCS:.c=.d)
%.d:%.c 
	$(CC) -MM $^ > $@.$$$$;\
	sed 's/\($*.o\)/\1 $@/g' < $@.$$$$ > $@;\
	rm -f $@.$$$$	

.PHONY : bin
bin :
	arm-linux-objcopy -O binary -S  $(TARGET) user.bin
	
.PHONY : dis
dis:
	arm-linux-objdump -D $(TARGET) > user.dis

.PHONY : clean
clean: 
	rm -f *.elf *.bin *.o *.dis *.i *.d	


