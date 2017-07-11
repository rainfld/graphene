manifests = redis.manifest
SRCDIR = redis-3.2.9/src
HOST = $(firstword $(shell ifconfig | grep 'inet addr:'| grep -v '127.0.0.1' -m 1 | cut -d: -f2))
PORT = 6379
CORES = 4
MAXMEM = 256
MAXTHREADS = 16

target = redis $(manifests)
exec_target = redis

clean-extra = clean-build

extra_rules = \
	-e 's:\$$(HOST):$(HOST):g' \
	-e 's:\$$(PORT):$(PORT):g' \
	-e 's:\$$(MEMSIZE):$(shell expr $(MAXMEM) + $(MAXMEM))M:g' \
	-e 's:\$$(THREADNUM):$(shell expr 2 + $(MAXTHREADS)):g'

level = ../../
include ../../Makefile

redis-3.2.9.tar.gz:
	wget http://download.redis.io/releases/redis-3.2.9.tar.gz
	tar xzf redis-3.2.9.tar.gz

$(SRCDIR)/redis-server: redis-3.2.9.tar.gz 
	cd $(SRCDIR) && make all

redis: $(SRCDIR)/redis-server
	cp -f $< $@ 

clean-build:
	rm -rf $(BUILDDIR)

distclean: clean
	rm -rf $(SRCDIR)
