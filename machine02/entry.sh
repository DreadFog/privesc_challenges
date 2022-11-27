#!/bin/sh

# start cron
crond -f -l 8
tail -f /dev/null