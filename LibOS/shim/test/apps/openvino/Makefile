PYTHON_SRC = Python-2.7.9
PYTHON_INSTALL = $(PYTHON_SRC)/build

manifests = openvino.manifest

exec_target = $(manifests)

extra_rules = -e 's:\$$(PYTHONDIR):$(PYTHON_INSTALL)/:g'
clean-extra += clean-tmp

level = ../../
include ../../Makefile

clean-tmp:
	rm -f openvino.manifest.sgx *.sig *.token

