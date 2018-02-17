.PHONY build:
build:
	maike

.PHONY test:
test: build
	find __targets -name '*.test' -exec {} \; > __targets/test_results.txt

.PHONY depgraph:
depgraph:
	maike --dump-graph-dot | xdot /dev/stdin
