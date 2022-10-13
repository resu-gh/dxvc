PIN_PATH := ${HOME}/Downloads/pin-3.24-98612-g6bd5931f2-gcc-linux
PIN_BIN := $(PIN_PATH)/pin
PIN_TOOLS_PATH := $(PIN_PATH)/source/tools

DXVC_PINTOOL_PATH := $(PIN_TOOLS_PATH)/dxvc
DXVC_PINTOOL_SRC := $(DXVC_PINTOOL_PATH)/dxvc.cpp
DXVC_PINTOOL_SO := $(DXVC_PINTOOL_PATH)/obj-intel64/dxvc.so

DXVC_REPO_PATH := ${HOME}/workspace/github/resu-gh/dxvc
DXVC_REPO_TEST_PATH := $(DXVC_REPO_PATH)/tests/jvbench
DXVC_REPO_SRC_PATH := $(DXVC_REPO_PATH)/src

JVBENCH_PATH := ${HOME}/Downloads/jvbench
JVBENCH_TEST_PATH := $(JVBENCH_PATH)/test
JVBENCH_JAR_PATH := $(JVBENCH_PATH)/JVBench-1.0.jar

JAVA_BIN = java

CHL = \033[32m
CRS = \033[0m

.PHONY: test
.SILENT: test
test: compile run
	echo -e "$(CHL)Copying SourceCode$(CRS) $(DXVC_PINTOOL_SRC) to $(DXVC_REPO_SRC_PATH)"
	cp -f $(DXVC_PINTOOL_SRC) $(DXVC_REPO_SRC_PATH)
	echo -e "$(CHL)Copying Makefile$(CRS) to $(DXVC_REPO_SRC_PATH)"
	cp -f "Makefile" $(DXVC_REPO_SRC_PATH)
	echo -e "$(CHL)Copying Script make.py$(CRS) to $(DXVC_REPO_SRC_PATH)"
	cp -f "make.py" $(DXVC_REPO_SRC_PATH)

.SILENT: compile
compile:
	clear
	echo -e "$(CHL)Compiling SourceCode...$(CRS)"
	make -C $(DXVC_PINTOOL_PATH) -j 16 -s
	clear

.SILENT: run
run:
	echo -e "$(CHL)Running benchmark$(CRS) $(TEST_NAME)"
	$(PIN_BIN) -t $(DXVC_PINTOOL_SO) -o $(TEST_OUT) -- $(JAVA_BIN) --add-modules jdk.incubator.vector -jar $(JVBENCH_JAR_PATH) "$(TEST_NAME)"

	echo -e "$(CHL)Creating Directory$(CRS) $(JVBENCH_TEST_PATH)/$(TEST_OUT)"
	mkdir -p "$(JVBENCH_TEST_PATH)/$(TEST_OUT)"

	echo -e "$(CHL)Moving$(CRS) $(TEST_OUT).[td,nt].csv to $(JVBENCH_TEST_PATH)/$(TEST_OUT)"
	mv "$(TEST_OUT).td.csv" "$(JVBENCH_TEST_PATH)/$(TEST_OUT)"
	mv "$(TEST_OUT).nt.csv" "$(JVBENCH_TEST_PATH)/$(TEST_OUT)"

	echo -e "$(CHL)Displaying Results ...$(CRS)"
	csview "$(JVBENCH_TEST_PATH)/$(TEST_OUT)/$(TEST_OUT).td.csv" --sniff 1 | sed 30q
	csview "$(JVBENCH_TEST_PATH)/$(TEST_OUT)/$(TEST_OUT).nt.csv"

	echo -e "$(CHL)Creating Directory$(CRS) $(DXVC_REPO_TEST_PATH)"
	mkdir -p "$(DXVC_REPO_TEST_PATH)"

	echo -e "$(CHL)Copying Directory$(CRS) $(JVBENCH_TEST_PATH)/$(TEST_OUT) to $(DXVC_REPO_TEST_PATH)"
	cp -rf "$(JVBENCH_TEST_PATH)/$(TEST_OUT)" "$(DXVC_REPO_TEST_PATH)"
