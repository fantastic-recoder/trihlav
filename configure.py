#!/usr/bin/env python
"""
SYNOPSIS

    configure.py [-h,--help] [-v,--verbose] [--version]

DESCRIPTION

    Basicly call cmake.

EXAMPLES

    configure.py --dir my_build --type=RelWithDebInfo

EXIT STATUS

    0 ok
    1 failoure

AUTHOR

    Recoder <recoder@resdium.net>

LICENSE

    GPL.

"""

import sys, os, traceback, optparse
import time
import re
import subprocess

#from pexpect import run, spawn

def main ():

    global options, args
    # TODO: Do something more interesting here...
    print 'Calling cmake'
    cmake = subprocess.check_output(["/usr/bin/env", "cmake", "-DCMAKE_BUILD_TYPE=Debug","../trihlav-build"])
    print 'Executing '+cmake
if __name__ == '__main__':
    try:
        start_time = time.time()
        parser = optparse.OptionParser(formatter=optparse.TitledHelpFormatter(), usage=globals()['__doc__'], version='$Id$')
        parser.add_option ('-v', '--verbose', action='store_true', default=False, help='verbose output')
        (options, args) = parser.parse_args()
        #if len(args) < 1:
        #    parser.error ('missing argument')
        if options.verbose: print time.asctime()
        main()
        if options.verbose: print time.asctime()
        if options.verbose: print 'TOTAL TIME IN MINUTES:',
        if options.verbose: print (time.time() - start_time) / 60.0
        sys.exit(0)
    except KeyboardInterrupt, e: # Ctrl-C
        raise e
    except SystemExit, e: # sys.exit()
        raise e
    except Exception, e:
        print 'ERROR, UNEXPECTED EXCEPTION'
        print str(e)
        traceback.print_exc()
        os._exit(1)

