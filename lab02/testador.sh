#!/bin/bash

# Created: Mar 18 2018
# Author: Victor Dalla
# Code snipets taken from Carla Negri Lintzmayer (carlanl@ic.unicamp.br), Zanoni Dias


# Colors
ESC_SEQ="\x1b["
COL_RESET=$ESC_SEQ"39;49;00m"
COL_RED=$ESC_SEQ"31;01m"
COL_GREEN=$ESC_SEQ"32;01m"
COL_YELLOW=$ESC_SEQ"33;01m"
COL_BLUE=$ESC_SEQ"34;01m"
COL_MAGENTA=$ESC_SEQ"35;01m"
COL_CYAN=$ESC_SEQ"36;01m"
COL_BOLD=$ESC_SEQ";1m"

if [[ $# -lt 3 ]]; then
    echo 'At least 3 parameters are needed'
    exit
fi

lab=$1
path=$2
turma=$3

# flag usada
while getopts "a::" OPTION
do
    case $OPTION in

        a)
            lab=$2
            turma=$4
            SUSY="https://susy.ic.unicamp.br:9999/$turma/$lab/aux"

            cd $3
            mkdir -p aux$lab
            cd aux$lab

            for input in $(curl -ks "$SUSY/aux.html" | tr \" \\n | grep '^a'); do
                printf "${COL_BOLD}%-12s${COL_RESET} ${COL_YELLOW}%-12s${COL_RESET}\n" "Downloading" "$input"
                curl -ks -O "$SUSY/$input"
            done
            exit
            ;;
        \?)
            printf "${COL_BOLD}%-7s${COL_RESET}: %s <laboratorio> <path/to/executable(main or labXX)> <turma>\n" "Uso" "$0"
            printf "${COL_BOLD}%-6s${COL_RESET}: %s 01 ./lab01/main(or lab01) mc202de\n" "Exemplo" "$0"

            printf "${COL_CYAN}%-7s${COL_RESET}" "Opções"

            printf "\t${COL_BOLD}%-1s${COL_RESET}: %s Use esta flag para baixar arquivos auxiliares\n" "-a"
            printf "\t${COL_BOLD}%-6s${COL_RESET}: %s -a <laboratorio> <para/onde/baixar/> <turma>\n" "Uso" "$0"
            exit
            ;;
    esac
done

cd ${path%/*}
mkdir -p dados$lab
executable=${path##*/}
erros=0
SUSY="https://susy.ic.unicamp.br:9999/$turma/$lab/dados"

# download e comparação dos testes
echo "Executando os testes..."
for input in $(curl -ks "$SUSY/testes.html" | sed -n '/Testes abertos/,/Testes fechados/p' | tr \" \\n | grep '^a' | grep '.in'); do
    
    printf "${COL_BOLD}%-12s${COL_RESET}" "$input"
    res="${input%.in}.res"

    curl -ks "$SUSY/$res" -o "dados$lab/$res"
    curl -ks "$SUSY/$input" -o "dados$lab/$input"
    cat "dados$lab/$input" | ./$executable 2>&1 | diff --color --palette=ad=31:de=32 "dados$lab/$res" - 

    if [[ $? -eq 0 ]]; then
        printf "${COL_GREEN}%-12s${COL_RESET}\n" "OK"
    else
        erros=$(($erros+1))
    fi
done    

if [[ $erros -eq 0 ]]; then
    echo -e "\nDeus é top"
else
    echo -e "\nComo dizia Marina Joyce help me"
fi
echo -e "Total de erros: $erros\n"