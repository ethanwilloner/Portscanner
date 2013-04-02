all:
	gcc -std=c11 -o portscanner main.c connect_scan.c
install:
	@echo "You don't want to install this, install a real port scanner like nmap"
clean:
	rm -f portscanner
