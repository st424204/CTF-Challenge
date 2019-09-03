#/bin/bash
socat TCP-LISTEN:54321,reuseaddr,fork EXEC:/home/knote/run.sh,pty,stderr,setsid,sigint,sane
