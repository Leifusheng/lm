all:
	make -f pub.mk
	make -C client
	make -C control
	make -C filetransmit
clean:
	make -f pub.mk clean
	make -C client clean
	make -C control clean
	make -C filetransmit clean
