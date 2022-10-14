include config.mk

.SILENT: help
.PHONY: help # display help, and exit
help:
	grep '^.PHONY: .* #' $(firstword $(MAKEFILE_LIST)) |\
	sed 's/\.PHONY: \(.*\) # \(.*\)/\1 # \2/' |\
	awk 'BEGIN {FS = "#"}; {printf "\033[36m%-52s\033[0m %s\n", $$1, $$2}'

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
pintool: build
	echo -e "$(CHL)Compiling...$(CRS) $(DXVC_SRC)"
	PIN_ROOT="$(PIN_DIR)" make -C $(DXVC_DIR) -j 16 -s

.SILENT: bench
.PHONY: bench # run a single benchmark (requires BENCH_NAME and BENCH_OUT vars)
bench: pintool
	echo -e "$(CHL)Running benchmark$(CRS) $(BENCH_NAME)"
	$(PIN_BIN) -t $(DXVC_SO) -o $(BENCH_OUT) -- $(JAVA_BIN) --add-modules jdk.incubator.vector -jar $(JVBENCH_JAR) "$(BENCH_NAME)" -o "$(BENCH_OUT).bm.log"

	echo -e "$(CHL)Creating Directory$(CRS) $(TEST_DIR)/$(BENCH_OUT)"
	mkdir -p "$(TEST_DIR)/$(BENCH_OUT)"

	echo -e "$(CHL)Moving$(CRS) $(BENCH_OUT).[td,nt].csv to $(JVBENCH_TEST_PATH)/$(BENCH_OUT)"
	mv "$(BENCH_OUT).td.csv" "$(TEST_DIR)/$(BENCH_OUT)"
	mv "$(BENCH_OUT).nt.csv" "$(TEST_DIR)/$(BENCH_OUT)"
	mv "$(BENCH_OUT).bm.log" "$(TEST_DIR)/$(BENCH_OUT)"

	echo -e "$(CHL)Displaying Results ...$(CRS)"
	column -s, -t < "$(TEST_DIR)/$(BENCH_OUT)/$(BENCH_OUT).td.csv" | cut -c -$(shell stty size | cut -d' ' -f2) | sed 15q 
	column -s, -t < "$(TEST_DIR)/$(BENCH_OUT)/$(BENCH_OUT).nt.csv"

# generated

.SILENT: AxpyPatternBenchmark.fmaScalar
.PHONY: AxpyPatternBenchmark.fmaScalar # run the AxpyPatternBenchmark.fmaScalar benchmark
AxpyPatternBenchmark.fmaScalar:
	BENCH_NAME=AxpyPatternBenchmark.fmaScalar BENCH_OUT=AxpyPatternBenchmark_fmaScalar $(MAKE) bench -s

.SILENT: SwaptionsPatternBenchmark.conversion
.PHONY: SwaptionsPatternBenchmark.conversion # run the SwaptionsPatternBenchmark.conversion benchmark
SwaptionsPatternBenchmark.conversion:
	BENCH_NAME=SwaptionsPatternBenchmark.conversion BENCH_OUT=SwaptionsPatternBenchmark_conversion $(MAKE) bench -s

.SILENT: SwaptionsPatternBenchmark.indexInRange
.PHONY: SwaptionsPatternBenchmark.indexInRange # run the SwaptionsPatternBenchmark.indexInRange benchmark
SwaptionsPatternBenchmark.indexInRange:
	BENCH_NAME=SwaptionsPatternBenchmark.indexInRange BENCH_OUT=SwaptionsPatternBenchmark_indexInRange $(MAKE) bench -s

.SILENT: SwaptionsPatternBenchmark.pow
.PHONY: SwaptionsPatternBenchmark.pow # run the SwaptionsPatternBenchmark.pow benchmark
SwaptionsPatternBenchmark.pow:
	BENCH_NAME=SwaptionsPatternBenchmark.pow BENCH_OUT=SwaptionsPatternBenchmark_pow $(MAKE) bench -s

.SILENT: AxpyBenchmark.autoVec
.PHONY: AxpyBenchmark.autoVec # run the AxpyBenchmark.autoVec benchmark
AxpyBenchmark.autoVec:
	BENCH_NAME=AxpyBenchmark.autoVec BENCH_OUT=AxpyBenchmark_autoVec $(MAKE) bench -s

.SILENT: AxpyBenchmark.explicitVec
.PHONY: AxpyBenchmark.explicitVec # run the AxpyBenchmark.explicitVec benchmark
AxpyBenchmark.explicitVec:
	BENCH_NAME=AxpyBenchmark.explicitVec BENCH_OUT=AxpyBenchmark_explicitVec $(MAKE) bench -s

.SILENT: AxpyBenchmark.fullVec
.PHONY: AxpyBenchmark.fullVec # run the AxpyBenchmark.fullVec benchmark
AxpyBenchmark.fullVec:
	BENCH_NAME=AxpyBenchmark.fullVec BENCH_OUT=AxpyBenchmark_fullVec $(MAKE) bench -s

.SILENT: AxpyBenchmark.serial
.PHONY: AxpyBenchmark.serial # run the AxpyBenchmark.serial benchmark
AxpyBenchmark.serial:
	BENCH_NAME=AxpyBenchmark.serial BENCH_OUT=AxpyBenchmark_serial $(MAKE) bench -s

.SILENT: AxpyPatternBenchmark.broadcastExternal
.PHONY: AxpyPatternBenchmark.broadcastExternal # run the AxpyPatternBenchmark.broadcastExternal benchmark
AxpyPatternBenchmark.broadcastExternal:
	BENCH_NAME=AxpyPatternBenchmark.broadcastExternal BENCH_OUT=AxpyPatternBenchmark_broadcastExternal $(MAKE) bench -s

.SILENT: AxpyPatternBenchmark.fma
.PHONY: AxpyPatternBenchmark.fma # run the AxpyPatternBenchmark.fma benchmark
AxpyPatternBenchmark.fma:
	BENCH_NAME=AxpyPatternBenchmark.fma BENCH_OUT=AxpyPatternBenchmark_fma $(MAKE) bench -s

.SILENT: AxpyPatternBenchmark.indexInRange
.PHONY: AxpyPatternBenchmark.indexInRange # run the AxpyPatternBenchmark.indexInRange benchmark
AxpyPatternBenchmark.indexInRange:
	BENCH_NAME=AxpyPatternBenchmark.indexInRange BENCH_OUT=AxpyPatternBenchmark_indexInRange $(MAKE) bench -s

.SILENT: BlackscholesBenchmark.autoVec
.PHONY: BlackscholesBenchmark.autoVec # run the BlackscholesBenchmark.autoVec benchmark
BlackscholesBenchmark.autoVec:
	BENCH_NAME=BlackscholesBenchmark.autoVec BENCH_OUT=BlackscholesBenchmark_autoVec $(MAKE) bench -s

.SILENT: BlackscholesBenchmark.explicitVec
.PHONY: BlackscholesBenchmark.explicitVec # run the BlackscholesBenchmark.explicitVec benchmark
BlackscholesBenchmark.explicitVec:
	BENCH_NAME=BlackscholesBenchmark.explicitVec BENCH_OUT=BlackscholesBenchmark_explicitVec $(MAKE) bench -s

.SILENT: BlackscholesBenchmark.fullVec
.PHONY: BlackscholesBenchmark.fullVec # run the BlackscholesBenchmark.fullVec benchmark
BlackscholesBenchmark.fullVec:
	BENCH_NAME=BlackscholesBenchmark.fullVec BENCH_OUT=BlackscholesBenchmark_fullVec $(MAKE) bench -s

.SILENT: BlackscholesBenchmark.serial
.PHONY: BlackscholesBenchmark.serial # run the BlackscholesBenchmark.serial benchmark
BlackscholesBenchmark.serial:
	BENCH_NAME=BlackscholesBenchmark.serial BENCH_OUT=BlackscholesBenchmark_serial $(MAKE) bench -s

.SILENT: BlackscholesPatternBenchmark.indexInRange
.PHONY: BlackscholesPatternBenchmark.indexInRange # run the BlackscholesPatternBenchmark.indexInRange benchmark
BlackscholesPatternBenchmark.indexInRange:
	BENCH_NAME=BlackscholesPatternBenchmark.indexInRange BENCH_OUT=BlackscholesPatternBenchmark_indexInRange $(MAKE) bench -s

.SILENT: BlackscholesPatternBenchmark.mergeWithoutBlend
.PHONY: BlackscholesPatternBenchmark.mergeWithoutBlend # run the BlackscholesPatternBenchmark.mergeWithoutBlend benchmark
BlackscholesPatternBenchmark.mergeWithoutBlend:
	BENCH_NAME=BlackscholesPatternBenchmark.mergeWithoutBlend BENCH_OUT=BlackscholesPatternBenchmark_mergeWithoutBlend $(MAKE) bench -s

.SILENT: BlackscholesPatternBenchmark.pow
.PHONY: BlackscholesPatternBenchmark.pow # run the BlackscholesPatternBenchmark.pow benchmark
BlackscholesPatternBenchmark.pow:
	BENCH_NAME=BlackscholesPatternBenchmark.pow BENCH_OUT=BlackscholesPatternBenchmark_pow $(MAKE) bench -s

.SILENT: CannealBenchmark.autoVec
.PHONY: CannealBenchmark.autoVec # run the CannealBenchmark.autoVec benchmark
CannealBenchmark.autoVec:
	BENCH_NAME=CannealBenchmark.autoVec BENCH_OUT=CannealBenchmark_autoVec $(MAKE) bench -s

.SILENT: CannealBenchmark.explicitVec
.PHONY: CannealBenchmark.explicitVec # run the CannealBenchmark.explicitVec benchmark
CannealBenchmark.explicitVec:
	BENCH_NAME=CannealBenchmark.explicitVec BENCH_OUT=CannealBenchmark_explicitVec $(MAKE) bench -s

.SILENT: CannealBenchmark.fullVec
.PHONY: CannealBenchmark.fullVec # run the CannealBenchmark.fullVec benchmark
CannealBenchmark.fullVec:
	BENCH_NAME=CannealBenchmark.fullVec BENCH_OUT=CannealBenchmark_fullVec $(MAKE) bench -s

.SILENT: CannealBenchmark.serial
.PHONY: CannealBenchmark.serial # run the CannealBenchmark.serial benchmark
CannealBenchmark.serial:
	BENCH_NAME=CannealBenchmark.serial BENCH_OUT=CannealBenchmark_serial $(MAKE) bench -s

.SILENT: CannealPatternBenchmark.indexInRange
.PHONY: CannealPatternBenchmark.indexInRange # run the CannealPatternBenchmark.indexInRange benchmark
CannealPatternBenchmark.indexInRange:
	BENCH_NAME=CannealPatternBenchmark.indexInRange BENCH_OUT=CannealPatternBenchmark_indexInRange $(MAKE) bench -s

.SILENT: CannealPatternBenchmark.minSizeCheck
.PHONY: CannealPatternBenchmark.minSizeCheck # run the CannealPatternBenchmark.minSizeCheck benchmark
CannealPatternBenchmark.minSizeCheck:
	BENCH_NAME=CannealPatternBenchmark.minSizeCheck BENCH_OUT=CannealPatternBenchmark_minSizeCheck $(MAKE) bench -s

.SILENT: CannealPatternBenchmark.noMinSizeCheck
.PHONY: CannealPatternBenchmark.noMinSizeCheck # run the CannealPatternBenchmark.noMinSizeCheck benchmark
CannealPatternBenchmark.noMinSizeCheck:
	BENCH_NAME=CannealPatternBenchmark.noMinSizeCheck BENCH_OUT=CannealPatternBenchmark_noMinSizeCheck $(MAKE) bench -s

.SILENT: CannealPatternBenchmark.reductionExternal
.PHONY: CannealPatternBenchmark.reductionExternal # run the CannealPatternBenchmark.reductionExternal benchmark
CannealPatternBenchmark.reductionExternal:
	BENCH_NAME=CannealPatternBenchmark.reductionExternal BENCH_OUT=CannealPatternBenchmark_reductionExternal $(MAKE) bench -s

.SILENT: CannealPatternBenchmark.reductionInternal
.PHONY: CannealPatternBenchmark.reductionInternal # run the CannealPatternBenchmark.reductionInternal benchmark
CannealPatternBenchmark.reductionInternal:
	BENCH_NAME=CannealPatternBenchmark.reductionInternal BENCH_OUT=CannealPatternBenchmark_reductionInternal $(MAKE) bench -s

.SILENT: Jacobi2dBenchmark.autoVec
.PHONY: Jacobi2dBenchmark.autoVec # run the Jacobi2dBenchmark.autoVec benchmark
Jacobi2dBenchmark.autoVec:
	BENCH_NAME=Jacobi2dBenchmark.autoVec BENCH_OUT=Jacobi2dBenchmark_autoVec $(MAKE) bench -s

.SILENT: Jacobi2dBenchmark.explicitVec
.PHONY: Jacobi2dBenchmark.explicitVec # run the Jacobi2dBenchmark.explicitVec benchmark
Jacobi2dBenchmark.explicitVec:
	BENCH_NAME=Jacobi2dBenchmark.explicitVec BENCH_OUT=Jacobi2dBenchmark_explicitVec $(MAKE) bench -s

.SILENT: Jacobi2dBenchmark.fullVec
.PHONY: Jacobi2dBenchmark.fullVec # run the Jacobi2dBenchmark.fullVec benchmark
Jacobi2dBenchmark.fullVec:
	BENCH_NAME=Jacobi2dBenchmark.fullVec BENCH_OUT=Jacobi2dBenchmark_fullVec $(MAKE) bench -s

.SILENT: Jacobi2dBenchmark.serial
.PHONY: Jacobi2dBenchmark.serial # run the Jacobi2dBenchmark.serial benchmark
Jacobi2dBenchmark.serial:
	BENCH_NAME=Jacobi2dBenchmark.serial BENCH_OUT=Jacobi2dBenchmark_serial $(MAKE) bench -s

.SILENT: Jacobi2dPatternBenchmark.indexInRange
.PHONY: Jacobi2dPatternBenchmark.indexInRange # run the Jacobi2dPatternBenchmark.indexInRange benchmark
Jacobi2dPatternBenchmark.indexInRange:
	BENCH_NAME=Jacobi2dPatternBenchmark.indexInRange BENCH_OUT=Jacobi2dPatternBenchmark_indexInRange $(MAKE) bench -s

.SILENT: LavaMDBenchmark.autoVec
.PHONY: LavaMDBenchmark.autoVec # run the LavaMDBenchmark.autoVec benchmark
LavaMDBenchmark.autoVec:
	BENCH_NAME=LavaMDBenchmark.autoVec BENCH_OUT=LavaMDBenchmark_autoVec $(MAKE) bench -s

.SILENT: LavaMDBenchmark.explicitVec
.PHONY: LavaMDBenchmark.explicitVec # run the LavaMDBenchmark.explicitVec benchmark
LavaMDBenchmark.explicitVec:
	BENCH_NAME=LavaMDBenchmark.explicitVec BENCH_OUT=LavaMDBenchmark_explicitVec $(MAKE) bench -s

.SILENT: LavaMDBenchmark.fullVec
.PHONY: LavaMDBenchmark.fullVec # run the LavaMDBenchmark.fullVec benchmark
LavaMDBenchmark.fullVec:
	BENCH_NAME=LavaMDBenchmark.fullVec BENCH_OUT=LavaMDBenchmark_fullVec $(MAKE) bench -s

.SILENT: LavaMDBenchmark.serial
.PHONY: LavaMDBenchmark.serial # run the LavaMDBenchmark.serial benchmark
LavaMDBenchmark.serial:
	BENCH_NAME=LavaMDBenchmark.serial BENCH_OUT=LavaMDBenchmark_serial $(MAKE) bench -s

.SILENT: LavaMDPatternBenchmark.fma
.PHONY: LavaMDPatternBenchmark.fma # run the LavaMDPatternBenchmark.fma benchmark
LavaMDPatternBenchmark.fma:
	BENCH_NAME=LavaMDPatternBenchmark.fma BENCH_OUT=LavaMDPatternBenchmark_fma $(MAKE) bench -s

.SILENT: LavaMDPatternBenchmark.fmaScalar
.PHONY: LavaMDPatternBenchmark.fmaScalar # run the LavaMDPatternBenchmark.fmaScalar benchmark
LavaMDPatternBenchmark.fmaScalar:
	BENCH_NAME=LavaMDPatternBenchmark.fmaScalar BENCH_OUT=LavaMDPatternBenchmark_fmaScalar $(MAKE) bench -s

.SILENT: LavaMDPatternBenchmark.indexInRange
.PHONY: LavaMDPatternBenchmark.indexInRange # run the LavaMDPatternBenchmark.indexInRange benchmark
LavaMDPatternBenchmark.indexInRange:
	BENCH_NAME=LavaMDPatternBenchmark.indexInRange BENCH_OUT=LavaMDPatternBenchmark_indexInRange $(MAKE) bench -s

.SILENT: LavaMDPatternBenchmark.reduction
.PHONY: LavaMDPatternBenchmark.reduction # run the LavaMDPatternBenchmark.reduction benchmark
LavaMDPatternBenchmark.reduction:
	BENCH_NAME=LavaMDPatternBenchmark.reduction BENCH_OUT=LavaMDPatternBenchmark_reduction $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarACOS
.PHONY: TranscendentalOperationBenchmark.scalarACOS # run the TranscendentalOperationBenchmark.scalarACOS benchmark
TranscendentalOperationBenchmark.scalarACOS:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarACOS BENCH_OUT=TranscendentalOperationBenchmark_scalarACOS $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarASIN
.PHONY: TranscendentalOperationBenchmark.scalarASIN # run the TranscendentalOperationBenchmark.scalarASIN benchmark
TranscendentalOperationBenchmark.scalarASIN:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarASIN BENCH_OUT=TranscendentalOperationBenchmark_scalarASIN $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarATAN
.PHONY: TranscendentalOperationBenchmark.scalarATAN # run the TranscendentalOperationBenchmark.scalarATAN benchmark
TranscendentalOperationBenchmark.scalarATAN:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarATAN BENCH_OUT=TranscendentalOperationBenchmark_scalarATAN $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarATAN2
.PHONY: TranscendentalOperationBenchmark.scalarATAN2 # run the TranscendentalOperationBenchmark.scalarATAN2 benchmark
TranscendentalOperationBenchmark.scalarATAN2:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarATAN2 BENCH_OUT=TranscendentalOperationBenchmark_scalarATAN2 $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarCBRT
.PHONY: TranscendentalOperationBenchmark.scalarCBRT # run the TranscendentalOperationBenchmark.scalarCBRT benchmark
TranscendentalOperationBenchmark.scalarCBRT:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarCBRT BENCH_OUT=TranscendentalOperationBenchmark_scalarCBRT $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarCOS
.PHONY: TranscendentalOperationBenchmark.scalarCOS # run the TranscendentalOperationBenchmark.scalarCOS benchmark
TranscendentalOperationBenchmark.scalarCOS:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarCOS BENCH_OUT=TranscendentalOperationBenchmark_scalarCOS $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarCOSH
.PHONY: TranscendentalOperationBenchmark.scalarCOSH # run the TranscendentalOperationBenchmark.scalarCOSH benchmark
TranscendentalOperationBenchmark.scalarCOSH:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarCOSH BENCH_OUT=TranscendentalOperationBenchmark_scalarCOSH $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarEXP
.PHONY: TranscendentalOperationBenchmark.scalarEXP # run the TranscendentalOperationBenchmark.scalarEXP benchmark
TranscendentalOperationBenchmark.scalarEXP:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarEXP BENCH_OUT=TranscendentalOperationBenchmark_scalarEXP $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarEXPM1
.PHONY: TranscendentalOperationBenchmark.scalarEXPM1 # run the TranscendentalOperationBenchmark.scalarEXPM1 benchmark
TranscendentalOperationBenchmark.scalarEXPM1:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarEXPM1 BENCH_OUT=TranscendentalOperationBenchmark_scalarEXPM1 $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarHYPOT
.PHONY: TranscendentalOperationBenchmark.scalarHYPOT # run the TranscendentalOperationBenchmark.scalarHYPOT benchmark
TranscendentalOperationBenchmark.scalarHYPOT:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarHYPOT BENCH_OUT=TranscendentalOperationBenchmark_scalarHYPOT $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarLOG
.PHONY: TranscendentalOperationBenchmark.scalarLOG # run the TranscendentalOperationBenchmark.scalarLOG benchmark
TranscendentalOperationBenchmark.scalarLOG:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarLOG BENCH_OUT=TranscendentalOperationBenchmark_scalarLOG $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarLOG10
.PHONY: TranscendentalOperationBenchmark.scalarLOG10 # run the TranscendentalOperationBenchmark.scalarLOG10 benchmark
TranscendentalOperationBenchmark.scalarLOG10:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarLOG10 BENCH_OUT=TranscendentalOperationBenchmark_scalarLOG10 $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarLOG1P
.PHONY: TranscendentalOperationBenchmark.scalarLOG1P # run the TranscendentalOperationBenchmark.scalarLOG1P benchmark
TranscendentalOperationBenchmark.scalarLOG1P:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarLOG1P BENCH_OUT=TranscendentalOperationBenchmark_scalarLOG1P $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarMUL0
.PHONY: TranscendentalOperationBenchmark.scalarMUL0 # run the TranscendentalOperationBenchmark.scalarMUL0 benchmark
TranscendentalOperationBenchmark.scalarMUL0:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarMUL0 BENCH_OUT=TranscendentalOperationBenchmark_scalarMUL0 $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarMUL1
.PHONY: TranscendentalOperationBenchmark.scalarMUL1 # run the TranscendentalOperationBenchmark.scalarMUL1 benchmark
TranscendentalOperationBenchmark.scalarMUL1:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarMUL1 BENCH_OUT=TranscendentalOperationBenchmark_scalarMUL1 $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarMUL2
.PHONY: TranscendentalOperationBenchmark.scalarMUL2 # run the TranscendentalOperationBenchmark.scalarMUL2 benchmark
TranscendentalOperationBenchmark.scalarMUL2:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarMUL2 BENCH_OUT=TranscendentalOperationBenchmark_scalarMUL2 $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarPOW
.PHONY: TranscendentalOperationBenchmark.scalarPOW # run the TranscendentalOperationBenchmark.scalarPOW benchmark
TranscendentalOperationBenchmark.scalarPOW:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarPOW BENCH_OUT=TranscendentalOperationBenchmark_scalarPOW $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarPOW0
.PHONY: TranscendentalOperationBenchmark.scalarPOW0 # run the TranscendentalOperationBenchmark.scalarPOW0 benchmark
TranscendentalOperationBenchmark.scalarPOW0:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarPOW0 BENCH_OUT=TranscendentalOperationBenchmark_scalarPOW0 $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarPOW1
.PHONY: TranscendentalOperationBenchmark.scalarPOW1 # run the TranscendentalOperationBenchmark.scalarPOW1 benchmark
TranscendentalOperationBenchmark.scalarPOW1:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarPOW1 BENCH_OUT=TranscendentalOperationBenchmark_scalarPOW1 $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarPOW2
.PHONY: TranscendentalOperationBenchmark.scalarPOW2 # run the TranscendentalOperationBenchmark.scalarPOW2 benchmark
TranscendentalOperationBenchmark.scalarPOW2:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarPOW2 BENCH_OUT=TranscendentalOperationBenchmark_scalarPOW2 $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarSIN
.PHONY: TranscendentalOperationBenchmark.scalarSIN # run the TranscendentalOperationBenchmark.scalarSIN benchmark
TranscendentalOperationBenchmark.scalarSIN:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarSIN BENCH_OUT=TranscendentalOperationBenchmark_scalarSIN $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarSINH
.PHONY: TranscendentalOperationBenchmark.scalarSINH # run the TranscendentalOperationBenchmark.scalarSINH benchmark
TranscendentalOperationBenchmark.scalarSINH:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarSINH BENCH_OUT=TranscendentalOperationBenchmark_scalarSINH $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarTAN
.PHONY: TranscendentalOperationBenchmark.scalarTAN # run the TranscendentalOperationBenchmark.scalarTAN benchmark
TranscendentalOperationBenchmark.scalarTAN:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarTAN BENCH_OUT=TranscendentalOperationBenchmark_scalarTAN $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.scalarTANH
.PHONY: TranscendentalOperationBenchmark.scalarTANH # run the TranscendentalOperationBenchmark.scalarTANH benchmark
TranscendentalOperationBenchmark.scalarTANH:
	BENCH_NAME=TranscendentalOperationBenchmark.scalarTANH BENCH_OUT=TranscendentalOperationBenchmark_scalarTANH $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorACOS
.PHONY: TranscendentalOperationBenchmark.vectorACOS # run the TranscendentalOperationBenchmark.vectorACOS benchmark
TranscendentalOperationBenchmark.vectorACOS:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorACOS BENCH_OUT=TranscendentalOperationBenchmark_vectorACOS $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorASIN
.PHONY: TranscendentalOperationBenchmark.vectorASIN # run the TranscendentalOperationBenchmark.vectorASIN benchmark
TranscendentalOperationBenchmark.vectorASIN:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorASIN BENCH_OUT=TranscendentalOperationBenchmark_vectorASIN $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorATAN
.PHONY: TranscendentalOperationBenchmark.vectorATAN # run the TranscendentalOperationBenchmark.vectorATAN benchmark
TranscendentalOperationBenchmark.vectorATAN:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorATAN BENCH_OUT=TranscendentalOperationBenchmark_vectorATAN $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorATAN2
.PHONY: TranscendentalOperationBenchmark.vectorATAN2 # run the TranscendentalOperationBenchmark.vectorATAN2 benchmark
TranscendentalOperationBenchmark.vectorATAN2:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorATAN2 BENCH_OUT=TranscendentalOperationBenchmark_vectorATAN2 $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorCBRT
.PHONY: TranscendentalOperationBenchmark.vectorCBRT # run the TranscendentalOperationBenchmark.vectorCBRT benchmark
TranscendentalOperationBenchmark.vectorCBRT:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorCBRT BENCH_OUT=TranscendentalOperationBenchmark_vectorCBRT $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorCOS
.PHONY: TranscendentalOperationBenchmark.vectorCOS # run the TranscendentalOperationBenchmark.vectorCOS benchmark
TranscendentalOperationBenchmark.vectorCOS:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorCOS BENCH_OUT=TranscendentalOperationBenchmark_vectorCOS $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorCOSH
.PHONY: TranscendentalOperationBenchmark.vectorCOSH # run the TranscendentalOperationBenchmark.vectorCOSH benchmark
TranscendentalOperationBenchmark.vectorCOSH:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorCOSH BENCH_OUT=TranscendentalOperationBenchmark_vectorCOSH $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorEXP
.PHONY: TranscendentalOperationBenchmark.vectorEXP # run the TranscendentalOperationBenchmark.vectorEXP benchmark
TranscendentalOperationBenchmark.vectorEXP:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorEXP BENCH_OUT=TranscendentalOperationBenchmark_vectorEXP $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorEXPM1
.PHONY: TranscendentalOperationBenchmark.vectorEXPM1 # run the TranscendentalOperationBenchmark.vectorEXPM1 benchmark
TranscendentalOperationBenchmark.vectorEXPM1:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorEXPM1 BENCH_OUT=TranscendentalOperationBenchmark_vectorEXPM1 $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorHYPOT
.PHONY: TranscendentalOperationBenchmark.vectorHYPOT # run the TranscendentalOperationBenchmark.vectorHYPOT benchmark
TranscendentalOperationBenchmark.vectorHYPOT:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorHYPOT BENCH_OUT=TranscendentalOperationBenchmark_vectorHYPOT $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorLOG
.PHONY: TranscendentalOperationBenchmark.vectorLOG # run the TranscendentalOperationBenchmark.vectorLOG benchmark
TranscendentalOperationBenchmark.vectorLOG:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorLOG BENCH_OUT=TranscendentalOperationBenchmark_vectorLOG $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorLOG10
.PHONY: TranscendentalOperationBenchmark.vectorLOG10 # run the TranscendentalOperationBenchmark.vectorLOG10 benchmark
TranscendentalOperationBenchmark.vectorLOG10:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorLOG10 BENCH_OUT=TranscendentalOperationBenchmark_vectorLOG10 $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorLOG1P
.PHONY: TranscendentalOperationBenchmark.vectorLOG1P # run the TranscendentalOperationBenchmark.vectorLOG1P benchmark
TranscendentalOperationBenchmark.vectorLOG1P:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorLOG1P BENCH_OUT=TranscendentalOperationBenchmark_vectorLOG1P $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorMUL0
.PHONY: TranscendentalOperationBenchmark.vectorMUL0 # run the TranscendentalOperationBenchmark.vectorMUL0 benchmark
TranscendentalOperationBenchmark.vectorMUL0:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorMUL0 BENCH_OUT=TranscendentalOperationBenchmark_vectorMUL0 $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorMUL1
.PHONY: TranscendentalOperationBenchmark.vectorMUL1 # run the TranscendentalOperationBenchmark.vectorMUL1 benchmark
TranscendentalOperationBenchmark.vectorMUL1:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorMUL1 BENCH_OUT=TranscendentalOperationBenchmark_vectorMUL1 $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorMUL2
.PHONY: TranscendentalOperationBenchmark.vectorMUL2 # run the TranscendentalOperationBenchmark.vectorMUL2 benchmark
TranscendentalOperationBenchmark.vectorMUL2:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorMUL2 BENCH_OUT=TranscendentalOperationBenchmark_vectorMUL2 $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorPOW
.PHONY: TranscendentalOperationBenchmark.vectorPOW # run the TranscendentalOperationBenchmark.vectorPOW benchmark
TranscendentalOperationBenchmark.vectorPOW:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorPOW BENCH_OUT=TranscendentalOperationBenchmark_vectorPOW $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorPOW0
.PHONY: TranscendentalOperationBenchmark.vectorPOW0 # run the TranscendentalOperationBenchmark.vectorPOW0 benchmark
TranscendentalOperationBenchmark.vectorPOW0:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorPOW0 BENCH_OUT=TranscendentalOperationBenchmark_vectorPOW0 $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorPOW1
.PHONY: TranscendentalOperationBenchmark.vectorPOW1 # run the TranscendentalOperationBenchmark.vectorPOW1 benchmark
TranscendentalOperationBenchmark.vectorPOW1:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorPOW1 BENCH_OUT=TranscendentalOperationBenchmark_vectorPOW1 $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorPOW2
.PHONY: TranscendentalOperationBenchmark.vectorPOW2 # run the TranscendentalOperationBenchmark.vectorPOW2 benchmark
TranscendentalOperationBenchmark.vectorPOW2:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorPOW2 BENCH_OUT=TranscendentalOperationBenchmark_vectorPOW2 $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorSIN
.PHONY: TranscendentalOperationBenchmark.vectorSIN # run the TranscendentalOperationBenchmark.vectorSIN benchmark
TranscendentalOperationBenchmark.vectorSIN:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorSIN BENCH_OUT=TranscendentalOperationBenchmark_vectorSIN $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorSINH
.PHONY: TranscendentalOperationBenchmark.vectorSINH # run the TranscendentalOperationBenchmark.vectorSINH benchmark
TranscendentalOperationBenchmark.vectorSINH:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorSINH BENCH_OUT=TranscendentalOperationBenchmark_vectorSINH $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorTAN
.PHONY: TranscendentalOperationBenchmark.vectorTAN # run the TranscendentalOperationBenchmark.vectorTAN benchmark
TranscendentalOperationBenchmark.vectorTAN:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorTAN BENCH_OUT=TranscendentalOperationBenchmark_vectorTAN $(MAKE) bench -s

.SILENT: TranscendentalOperationBenchmark.vectorTANH
.PHONY: TranscendentalOperationBenchmark.vectorTANH # run the TranscendentalOperationBenchmark.vectorTANH benchmark
TranscendentalOperationBenchmark.vectorTANH:
	BENCH_NAME=TranscendentalOperationBenchmark.vectorTANH BENCH_OUT=TranscendentalOperationBenchmark_vectorTANH $(MAKE) bench -s

.SILENT: ParticlefilterBenchmark.autoVec
.PHONY: ParticlefilterBenchmark.autoVec # run the ParticlefilterBenchmark.autoVec benchmark
ParticlefilterBenchmark.autoVec:
	BENCH_NAME=ParticlefilterBenchmark.autoVec BENCH_OUT=ParticlefilterBenchmark_autoVec $(MAKE) bench -s

.SILENT: ParticlefilterBenchmark.explicitVec
.PHONY: ParticlefilterBenchmark.explicitVec # run the ParticlefilterBenchmark.explicitVec benchmark
ParticlefilterBenchmark.explicitVec:
	BENCH_NAME=ParticlefilterBenchmark.explicitVec BENCH_OUT=ParticlefilterBenchmark_explicitVec $(MAKE) bench -s

.SILENT: ParticlefilterBenchmark.fullVec
.PHONY: ParticlefilterBenchmark.fullVec # run the ParticlefilterBenchmark.fullVec benchmark
ParticlefilterBenchmark.fullVec:
	BENCH_NAME=ParticlefilterBenchmark.fullVec BENCH_OUT=ParticlefilterBenchmark_fullVec $(MAKE) bench -s

.SILENT: ParticlefilterBenchmark.serial
.PHONY: ParticlefilterBenchmark.serial # run the ParticlefilterBenchmark.serial benchmark
ParticlefilterBenchmark.serial:
	BENCH_NAME=ParticlefilterBenchmark.serial BENCH_OUT=ParticlefilterBenchmark_serial $(MAKE) bench -s

.SILENT: ParticlefilterPatternBenchmark.indexInRange
.PHONY: ParticlefilterPatternBenchmark.indexInRange # run the ParticlefilterPatternBenchmark.indexInRange benchmark
ParticlefilterPatternBenchmark.indexInRange:
	BENCH_NAME=ParticlefilterPatternBenchmark.indexInRange BENCH_OUT=ParticlefilterPatternBenchmark_indexInRange $(MAKE) bench -s

.SILENT: ParticlefilterPatternBenchmark.loadMaskInsideLoop
.PHONY: ParticlefilterPatternBenchmark.loadMaskInsideLoop # run the ParticlefilterPatternBenchmark.loadMaskInsideLoop benchmark
ParticlefilterPatternBenchmark.loadMaskInsideLoop:
	BENCH_NAME=ParticlefilterPatternBenchmark.loadMaskInsideLoop BENCH_OUT=ParticlefilterPatternBenchmark_loadMaskInsideLoop $(MAKE) bench -s

.SILENT: ParticlefilterPatternBenchmark.mergeWithBlend
.PHONY: ParticlefilterPatternBenchmark.mergeWithBlend # run the ParticlefilterPatternBenchmark.mergeWithBlend benchmark
ParticlefilterPatternBenchmark.mergeWithBlend:
	BENCH_NAME=ParticlefilterPatternBenchmark.mergeWithBlend BENCH_OUT=ParticlefilterPatternBenchmark_mergeWithBlend $(MAKE) bench -s

.SILENT: ParticlefilterPatternBenchmark.noSecondMask
.PHONY: ParticlefilterPatternBenchmark.noSecondMask # run the ParticlefilterPatternBenchmark.noSecondMask benchmark
ParticlefilterPatternBenchmark.noSecondMask:
	BENCH_NAME=ParticlefilterPatternBenchmark.noSecondMask BENCH_OUT=ParticlefilterPatternBenchmark_noSecondMask $(MAKE) bench -s

.SILENT: ParticlefilterPatternBenchmark.staticMask
.PHONY: ParticlefilterPatternBenchmark.staticMask # run the ParticlefilterPatternBenchmark.staticMask benchmark
ParticlefilterPatternBenchmark.staticMask:
	BENCH_NAME=ParticlefilterPatternBenchmark.staticMask BENCH_OUT=ParticlefilterPatternBenchmark_staticMask $(MAKE) bench -s

.SILENT: ParticlefilterPatternBenchmark.updateMaskInsideLoop
.PHONY: ParticlefilterPatternBenchmark.updateMaskInsideLoop # run the ParticlefilterPatternBenchmark.updateMaskInsideLoop benchmark
ParticlefilterPatternBenchmark.updateMaskInsideLoop:
	BENCH_NAME=ParticlefilterPatternBenchmark.updateMaskInsideLoop BENCH_OUT=ParticlefilterPatternBenchmark_updateMaskInsideLoop $(MAKE) bench -s

.SILENT: ParticlefilterPatternBenchmark.xorExtended
.PHONY: ParticlefilterPatternBenchmark.xorExtended # run the ParticlefilterPatternBenchmark.xorExtended benchmark
ParticlefilterPatternBenchmark.xorExtended:
	BENCH_NAME=ParticlefilterPatternBenchmark.xorExtended BENCH_OUT=ParticlefilterPatternBenchmark_xorExtended $(MAKE) bench -s

.SILENT: PathfinderBenchmark.autoVec
.PHONY: PathfinderBenchmark.autoVec # run the PathfinderBenchmark.autoVec benchmark
PathfinderBenchmark.autoVec:
	BENCH_NAME=PathfinderBenchmark.autoVec BENCH_OUT=PathfinderBenchmark_autoVec $(MAKE) bench -s

.SILENT: PathfinderBenchmark.explicitVec
.PHONY: PathfinderBenchmark.explicitVec # run the PathfinderBenchmark.explicitVec benchmark
PathfinderBenchmark.explicitVec:
	BENCH_NAME=PathfinderBenchmark.explicitVec BENCH_OUT=PathfinderBenchmark_explicitVec $(MAKE) bench -s

.SILENT: PathfinderBenchmark.fullVec
.PHONY: PathfinderBenchmark.fullVec # run the PathfinderBenchmark.fullVec benchmark
PathfinderBenchmark.fullVec:
	BENCH_NAME=PathfinderBenchmark.fullVec BENCH_OUT=PathfinderBenchmark_fullVec $(MAKE) bench -s

.SILENT: PathfinderBenchmark.serial
.PHONY: PathfinderBenchmark.serial # run the PathfinderBenchmark.serial benchmark
PathfinderBenchmark.serial:
	BENCH_NAME=PathfinderBenchmark.serial BENCH_OUT=PathfinderBenchmark_serial $(MAKE) bench -s

.SILENT: PathfinderPatternBenchmark.conditionInsideLoop
.PHONY: PathfinderPatternBenchmark.conditionInsideLoop # run the PathfinderPatternBenchmark.conditionInsideLoop benchmark
PathfinderPatternBenchmark.conditionInsideLoop:
	BENCH_NAME=PathfinderPatternBenchmark.conditionInsideLoop BENCH_OUT=PathfinderPatternBenchmark_conditionInsideLoop $(MAKE) bench -s

.SILENT: PathfinderPatternBenchmark.indexInRange
.PHONY: PathfinderPatternBenchmark.indexInRange # run the PathfinderPatternBenchmark.indexInRange benchmark
PathfinderPatternBenchmark.indexInRange:
	BENCH_NAME=PathfinderPatternBenchmark.indexInRange BENCH_OUT=PathfinderPatternBenchmark_indexInRange $(MAKE) bench -s

.SILENT: SomierBenchmark.autoVec
.PHONY: SomierBenchmark.autoVec # run the SomierBenchmark.autoVec benchmark
SomierBenchmark.autoVec:
	BENCH_NAME=SomierBenchmark.autoVec BENCH_OUT=SomierBenchmark_autoVec $(MAKE) bench -s

.SILENT: SomierBenchmark.explicitVec
.PHONY: SomierBenchmark.explicitVec # run the SomierBenchmark.explicitVec benchmark
SomierBenchmark.explicitVec:
	BENCH_NAME=SomierBenchmark.explicitVec BENCH_OUT=SomierBenchmark_explicitVec $(MAKE) bench -s

.SILENT: SomierBenchmark.fullVec
.PHONY: SomierBenchmark.fullVec # run the SomierBenchmark.fullVec benchmark
SomierBenchmark.fullVec:
	BENCH_NAME=SomierBenchmark.fullVec BENCH_OUT=SomierBenchmark_fullVec $(MAKE) bench -s

.SILENT: SomierBenchmark.serial
.PHONY: SomierBenchmark.serial # run the SomierBenchmark.serial benchmark
SomierBenchmark.serial:
	BENCH_NAME=SomierBenchmark.serial BENCH_OUT=SomierBenchmark_serial $(MAKE) bench -s

.SILENT: SomierPatternBenchmark.fma
.PHONY: SomierPatternBenchmark.fma # run the SomierPatternBenchmark.fma benchmark
SomierPatternBenchmark.fma:
	BENCH_NAME=SomierPatternBenchmark.fma BENCH_OUT=SomierPatternBenchmark_fma $(MAKE) bench -s

.SILENT: SomierPatternBenchmark.fmaScalar
.PHONY: SomierPatternBenchmark.fmaScalar # run the SomierPatternBenchmark.fmaScalar benchmark
SomierPatternBenchmark.fmaScalar:
	BENCH_NAME=SomierPatternBenchmark.fmaScalar BENCH_OUT=SomierPatternBenchmark_fmaScalar $(MAKE) bench -s

.SILENT: SomierPatternBenchmark.indexInRange
.PHONY: SomierPatternBenchmark.indexInRange # run the SomierPatternBenchmark.indexInRange benchmark
SomierPatternBenchmark.indexInRange:
	BENCH_NAME=SomierPatternBenchmark.indexInRange BENCH_OUT=SomierPatternBenchmark_indexInRange $(MAKE) bench -s

.SILENT: SomierPatternBenchmark.pow
.PHONY: SomierPatternBenchmark.pow # run the SomierPatternBenchmark.pow benchmark
SomierPatternBenchmark.pow:
	BENCH_NAME=SomierPatternBenchmark.pow BENCH_OUT=SomierPatternBenchmark_pow $(MAKE) bench -s

.SILENT: StreamclusterBenchmark.autoVec
.PHONY: StreamclusterBenchmark.autoVec # run the StreamclusterBenchmark.autoVec benchmark
StreamclusterBenchmark.autoVec:
	BENCH_NAME=StreamclusterBenchmark.autoVec BENCH_OUT=StreamclusterBenchmark_autoVec $(MAKE) bench -s

.SILENT: StreamclusterBenchmark.explicitVec
.PHONY: StreamclusterBenchmark.explicitVec # run the StreamclusterBenchmark.explicitVec benchmark
StreamclusterBenchmark.explicitVec:
	BENCH_NAME=StreamclusterBenchmark.explicitVec BENCH_OUT=StreamclusterBenchmark_explicitVec $(MAKE) bench -s

.SILENT: StreamclusterBenchmark.fullVec
.PHONY: StreamclusterBenchmark.fullVec # run the StreamclusterBenchmark.fullVec benchmark
StreamclusterBenchmark.fullVec:
	BENCH_NAME=StreamclusterBenchmark.fullVec BENCH_OUT=StreamclusterBenchmark_fullVec $(MAKE) bench -s

.SILENT: StreamclusterBenchmark.serial
.PHONY: StreamclusterBenchmark.serial # run the StreamclusterBenchmark.serial benchmark
StreamclusterBenchmark.serial:
	BENCH_NAME=StreamclusterBenchmark.serial BENCH_OUT=StreamclusterBenchmark_serial $(MAKE) bench -s

.SILENT: StreamclusterPatternBenchmark.indexInRange
.PHONY: StreamclusterPatternBenchmark.indexInRange # run the StreamclusterPatternBenchmark.indexInRange benchmark
StreamclusterPatternBenchmark.indexInRange:
	BENCH_NAME=StreamclusterPatternBenchmark.indexInRange BENCH_OUT=StreamclusterPatternBenchmark_indexInRange $(MAKE) bench -s

.SILENT: StreamclusterPatternBenchmark.pow
.PHONY: StreamclusterPatternBenchmark.pow # run the StreamclusterPatternBenchmark.pow benchmark
StreamclusterPatternBenchmark.pow:
	BENCH_NAME=StreamclusterPatternBenchmark.pow BENCH_OUT=StreamclusterPatternBenchmark_pow $(MAKE) bench -s

.SILENT: StreamclusterPatternBenchmark.reduction
.PHONY: StreamclusterPatternBenchmark.reduction # run the StreamclusterPatternBenchmark.reduction benchmark
StreamclusterPatternBenchmark.reduction:
	BENCH_NAME=StreamclusterPatternBenchmark.reduction BENCH_OUT=StreamclusterPatternBenchmark_reduction $(MAKE) bench -s

.SILENT: SwaptionsBenchmark.autoVec
.PHONY: SwaptionsBenchmark.autoVec # run the SwaptionsBenchmark.autoVec benchmark
SwaptionsBenchmark.autoVec:
	BENCH_NAME=SwaptionsBenchmark.autoVec BENCH_OUT=SwaptionsBenchmark_autoVec $(MAKE) bench -s

.SILENT: SwaptionsBenchmark.explicitVec
.PHONY: SwaptionsBenchmark.explicitVec # run the SwaptionsBenchmark.explicitVec benchmark
SwaptionsBenchmark.explicitVec:
	BENCH_NAME=SwaptionsBenchmark.explicitVec BENCH_OUT=SwaptionsBenchmark_explicitVec $(MAKE) bench -s

.SILENT: SwaptionsBenchmark.fullVec
.PHONY: SwaptionsBenchmark.fullVec # run the SwaptionsBenchmark.fullVec benchmark
SwaptionsBenchmark.fullVec:
	BENCH_NAME=SwaptionsBenchmark.fullVec BENCH_OUT=SwaptionsBenchmark_fullVec $(MAKE) bench -s

.SILENT: SwaptionsBenchmark.serial
.PHONY: SwaptionsBenchmark.serial # run the SwaptionsBenchmark.serial benchmark
SwaptionsBenchmark.serial:
	BENCH_NAME=SwaptionsBenchmark.serial BENCH_OUT=SwaptionsBenchmark_serial $(MAKE) bench -s
