CC=gcc
CFLAGS=-Wall -Werror -ansi -g

.PHONY: clean dist

memshell: memshell.o mem.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o memshell *.ps

sources.ps: mem.h mem_internal.h memshell.c
	LC_ALL=fr_FR a2ps -o $@ -A fill  --rows=2 --major=columns $?

sources_corrige.ps: mem.c mem.h mem_internal.h memshell.c
	LC_ALL=fr_FR a2ps -o $@  $?

dist: sources.ps sources_corrige.ps
	cd .. ; tar cvzf mem.tgz $(addprefix $(notdir $(CURDIR))/,*.c *.h Makefile sources.ps sources_corrige.ps *.txt)

