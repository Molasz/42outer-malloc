#!/bin/bash

# Color per a la sortida
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

# Ruta a la teva llibreria
LIB_PATH="./libft_malloc.so"

if [ ! -f "$LIB_PATH" ]; then
    exit 1
fi


#Llista de comandes a provar
COMMANDS=("ls -la" "whoami" "hostname" "uname -a" "date" "df -h")

echo -e "Norminette test: \n"
norminette
echo -e "\n"


for cmd in "${COMMANDS[@]}"; do
    echo -n "Provant: $cmd ... "
    
    # Executem la comanda amb el teu malloc
    LD_PRELOAD=$LIB_PATH $cmd > /dev/null 2>&1
    
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}OK${NC}"
    else
        echo -e "${RED}FAIL (Segfault o Error)${NC}"
        exit 1
    fi
done

echo -e "\n${GREEN}ALL TEST PASS!${NC}"
