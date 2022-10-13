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

.SILENT: pintool
.PHONY: pintool # compile the dxvc pintool (uses PIN_ROOT var)
pintool:
	echo -e "$(CHL)Compiling...$(CRS) $(DXVC_SRC)"
	PIN_ROOT="$(PIN_DIR)" make -C $(DXVC_DIR) -j 16 -s

.SILENT: bench
.PHONY: bench # run a single benchmark (requires TEST_NAME and TEST_OUT vars)
bench: pintool
	echo -e "$(CHL)Running benchmark$(CRS) $(TEST_NAME)"
	$(PIN_BIN) -t $(DXVC_SO) -o $(TEST_OUT) -- $(JAVA_BIN) --add-modules jdk.incubator.vector -jar $(JVBENCH_JAR) "$(TEST_NAME)"

	echo -e "$(CHL)Creating Directory$(CRS) $(TEST_DIR)/$(TEST_OUT)"
	mkdir -p "$(TEST_DIR)/$(TEST_OUT)"

	echo -e "$(CHL)Moving$(CRS) $(TEST_OUT).[td,nt].csv to $(JVBENCH_TEST_PATH)/$(TEST_OUT)"
	mv "$(TEST_OUT).td.csv" "$(TEST_DIR)/$(TEST_OUT)"
	mv "$(TEST_OUT).nt.csv" "$(TEST_DIR)/$(TEST_OUT)"

	echo -e "$(CHL)Displaying Results ...$(CRS)"
	column -s, -t < "$(TEST_DIR)/$(TEST_OUT)/$(TEST_OUT).td.csv" | cut -c -$(shell stty size | cut -d' ' -f2) | sed 30q 
	column -s, -t < "$(TEST_DIR)/$(TEST_OUT)/$(TEST_OUT).nt.csv"
