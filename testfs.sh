#!/bin/sh

LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:lib" java -Xmx512M -cp lib/jfuse.jar org.catacombae.jfuse.test.TestFS "$@"
