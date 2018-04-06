.PHONY build:
build:
	maike

.PHONY test:
test: build
	find __targets -name '*.test' -exec {} \;

.PHONY depgraph:
depgraph:
	maike --dump-graph-dot | xdot /dev/stdin
