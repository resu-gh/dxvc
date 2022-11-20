PREFIX := $(PWD)

JAVA_BIN := $(PREFIX)/env/jdk18u/build/linux-x86_64-server-release/images/jdk/bin/java

ENV_DIR := $(PREFIX)/env
SRC_DIR := $(PREFIX)/src
TEST_DIR := $(PREFIX)/test

PIN_URL := https://software.intel.com/sites/landingpage/pintool/downloads/pin-3.24-98612-g6bd5931f2-gcc-linux.tar.gz
PIN_DIR := $(ENV_DIR)/intelpin
PIN_BIN := $(PIN_DIR)/pin
PIN_TOOLS_DIR := $(PIN_DIR)/source/tools

JVBENCH_URL := https://www.github.com/usi-dag/JVBench
JVBENCH_DIR := $(ENV_DIR)/jvbench
JVBENCH_JAR := $(JVBENCH_DIR)/JVBench-1.0.1.jar
JVBENCH_JAR_URL := https://github.com/usi-dag/JVBench/releases/download/v1.0.1/JVBench-1.0.1.jar

VTUNE_URL := https://registrationcenter-download.intel.com/akdlm/irc_nas/18888/l_oneapi_vtune_p_2022.4.0.8705_offline.sh
VTUNE_SH := $(ENV_DIR)/vtune.sh

DXVC_DIR := $(SRC_DIR)/dxvc
DXVC_SRC := $(DXVC_DIR)/dxvc.cpp
DXVC_SO := $(DXVC_DIR)/obj-intel64/dxvc.so

CHL = \033[32m
CRS = \033[0m
