all:
	make -C client
	make -C control
	make -C filetransmit
clean:
	make -C client clean
	make -C control clean
	make -C filetransmit clean
