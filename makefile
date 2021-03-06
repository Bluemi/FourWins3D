start: compile run
run:
	@./bam/build/debug/fourwins
printlog:
	@if [ -f debug.log ]; then cat debug.log; else echo "no log file"; fi
gdb:
	@if [ -f core ]; then gdb ./bam/build/debug/fourwins core; else echo no core; echo; gdb ./bam/build/debug/fourwins ; fi
line-counter:
	@line-counter *pp
compile:
	@tput reset
	@bam -j `nproc`
.PHONY: run printlog gdb line-counter compile start
