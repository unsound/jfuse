#!/bin/sh

java -Xmx512M -Djava.library.path=. -cp lib/jfuse.jar org.catacombae.jfuse.test.TestFS "$@"
