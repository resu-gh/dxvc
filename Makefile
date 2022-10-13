include config.mk

.SILENT: help
.PHONY: help # print this help message
help:
	clear
	grep '^.PHONY: .* #' $(firstword $(MAKEFILE_LIST)) |\
	sed 's/\.PHONY: \(.*\) # \(.*\)/\1 # \2/' |\
	awk 'BEGIN {FS = "#"}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

# combo rules

.SILENT: build-all
.PHONY: build-all # combo (build-env get-intelpin)
build-all: build-env get-intelpin

.SILENT: rebuild-all
.PHONY: rebuild-all # combo (clean-env build-all)
rebuild-all: clean-env build-all

# env

.SILENT: build-env
build-env:
	echo -e "$(CHL)Creating Directory$(CRS) $(ENV_DIR)"
	mkdir -p "$(ENV_DIR)"

.SILENT: clean-env
.PHONY: clean-env # clean `env`
clean-env:
	echo -e "$(CHL)Cleaning $(CRS) $(ENV_DIR)"
	rm -rf $(ENV_DIR)/*

# env/intelpin

.SILENT: get-intelpin
.PHONY: get-intelpin # build `env/intelpin` (intel pin)
get-intelpin: build-env
	echo -e "$(CHL)Downloading/Moving Intel Pin$(CRS) to $(PIN_DIR)"
	curl "https://software.intel.com/sites/landingpage/pintool/downloads/pin-3.24-98612-g6bd5931f2-gcc-linux.tar.gz" -o "$(PIN_DIR).tar.gz" -z "$(PIN_DIR).tar.gz" -A "Mozilla/5.0"
	echo -e "$(CHL)Unzipping $(PIN_DIR).tar.gz$(CRS)"
	tar -xf "$(PIN_DIR).tar.gz" -C "$(ENV_DIR)" --one-top-level="$(PIN_DIR)" --strip-components 1 --skip-old-files
