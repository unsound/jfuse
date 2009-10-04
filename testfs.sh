#!/bin/sh

case `uname -s` in
[Dd]arwin*)
	if test -z "${DYLD_LIBRARY_PATH}"; then
	    # Set up a sane initial library path.
	    DYLD_LIBRARY_PATH=$HOME/lib:/usr/local/lib:/usr/lib
	fi
	export DYLD_LIBRARY_PATH="${DYLD_LIBRARY_PATH}:lib"
	;;
[Ll]inux* | [Nn]et[Bb][Ss][Dd]*)
	export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:/usr/local/lib"
	;;
esac

export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:lib"
java -Xmx512M -cp lib/jfuse.jar org.catacombae.jfuse.test.TestFS "$@"
