SHELL = /bin/sh

EXAMPLES_PATH = cores/validation

all:
	cd $(EXAMPLES_PATH)/blink
	make --no-builtin-rules -C $(VARIANT_NAME)

clean:
	cd $(EXAMPLES_PATH)/blink
	make --no-builtin-rules -C $(VARIANT_NAME) clean
