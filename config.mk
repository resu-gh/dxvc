PREFIX := $(PWD)

ENV_DIR := $(PREFIX)/env
SRC_DIR := $(PREFIX)/src

PIN_URL := https://software.intel.com/sites/landingpage/pintool/downloads/pin-3.24-98612-g6bd5931f2-gcc-linux.tar.gz
PIN_DIR := $(ENV_DIR)/intelpin
PIN_TOOLS_DIR := $(PIN_DIR)/source/tools

JVBENCH_URL := https://www.github.com/usi-dag/JVBench
JVBENCH_DIR := $(ENV_DIR)/jvbench
JVBENCH_JAR := $(JVBENCH_DIR)/JVBench-1.0.jar
JVBENCH_JAR_URL := https://github.com/usi-dag/JVBench/releases/download/v1.0.0/JVBench-1.0.jar

DXVC_DIR := $(SRC_DIR)/dxvc

CHL = \033[32m
CRS = \033[0m
