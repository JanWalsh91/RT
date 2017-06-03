#!/bin/bash
while true
do
	norminette -R CheckForbiddenSourceHeader $1
    sleep 10
	printf "\033c"
done
