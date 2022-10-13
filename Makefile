include config.mk

.SILENT: help
.PHONY: help # print this help message
help:
	grep '^.PHONY: .* #' $(firstword $(MAKEFILE_LIST)) |\
	sed 's/\.PHONY: \(.*\) # \(.*\)/\1 # \2/' |\
	awk 'BEGIN {FS = "#"}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.SILENT: build
.PHONY: build # build all (dependencies and environment)
build:
	echo -e "$(CHL)Creating Directory$(CRS) $(ENV_DIR)"
	mkdir -p "$(ENV_DIR)"

	echo -e "$(CHL)Downloading Intel Pin$(CRS) to $(PIN_DIR)"
	test -f "$(PIN_DIR).tar.gz" || wget "$(PIN_URL)" -O "$(PIN_DIR).tar.gz" -U "Mozilla/5.0" -q --show-progress
	echo -e "$(CHL)Unzipping$(CRS) $(PIN_DIR).tar.gz"
	test -d "$(PIN_DIR)" || tar -xf "$(PIN_DIR).tar.gz" -C "$(ENV_DIR)" --one-top-level="$(PIN_DIR)" --strip-components 1 --checkpoint-action=ttyout='%u %T%*\r'

	echo -e "$(CHL)Cloning usi-dag/JVBench$(CRS) to $(JVBENCH_DIR)"
	test -d "$(JVBENCH_DIR)" || git clone --progress "$(JVBENCH_URL)" "$(JVBENCH_DIR)"
	echo -e "$(CHL)Downloading JVBench-1.0.jar$(CRS) to $(JVBENCH_DIR)"
	test -f "$(JVBENCH_JAR)" || wget "$(JVBENCH_JAR_URL)" -O "$(JVBENCH_JAR)" -q --show-progress

.SILENT: clean
.PHONY: clean # clean all
clean:
	echo -e "$(CHL)Cleaning $(CRS) $(ENV_DIR)"
	rm -rf $(ENV_DIR)/*

.SILENT: rebuild
.PHONY: rebuild # combo: rebuild all (clean, build)
rebuild: clean build
