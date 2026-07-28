#!/bin/bash

# ==============================================================================
# PUSH_SWAP PRO TESTER - STRESS & MEMORY EDITION
# ==============================================================================

PUSH_SWAP="./push_swap"
CHECKER="./checker_linux"

# Cores
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'

echo -e "${BLUE}======================================================${NC}"
echo -e "${BLUE}          PUSH_SWAP PRO TESTER (STRESS TEST)          ${NC}"
echo -e "${BLUE}======================================================${NC}\n"

# ==============================================================================
# 1. VALGRIND (MEMORY LEAKS)
# ==============================================================================
echo -e "${CYAN}--- 1. Teste de Vazamento de Memória (Valgrind) ---${NC}"
if command -v valgrind &> /dev/null; then
    # Força o valgrind a retornar erro (código 42) se houver leak
    valgrind --leak-check=full --errors-for-leak-kinds=all --error-exitcode=42 $PUSH_SWAP 42 15 -9 0 88 3 > /dev/null 2> valgrind_log.txt
    if [ $? -eq 42 ]; then
        echo -e "${RED}[KO]${NC} Leaks de memória detectados! Verifique 'valgrind_log.txt'."
    else
        echo -e "${GREEN}[OK]${NC} Nenhum leak detectado (Heap limpa)."
        rm -f valgrind_log.txt
    fi
else
    echo -e "${YELLOW}[AVISO]${NC} Valgrind não instalado. Pulando teste de memória."
fi
echo ""

# ==============================================================================
# 2. EXAUSTÃO DE TAMANHO 3 (Todas as 6 permutações)
# ==============================================================================
echo -e "${CYAN}--- 2. Exaustão Tamanho 3 (Máx: 5 ops) ---${NC}"
PERMS=("1 2 3" "1 3 2" "2 1 3" "2 3 1" "3 1 2" "3 2 1")
ALL_OK=true

for p in "${PERMS[@]}"; do
    $PUSH_SWAP $p > tmp_out.txt 2> /dev/null
    COUNT=$(wc -l < tmp_out.txt)
    CHK=$(cat tmp_out.txt | $CHECKER $p 2>&1)
    
    if [[ "$CHK" != *"OK"* ]] || [ "$COUNT" -gt 5 ]; then
        echo -e "${RED}[KO]${NC} Permutação '$p' - $COUNT ops - Checker: $CHK"
        ALL_OK=false
    fi
done

if $ALL_OK; then
    echo -e "${GREEN}[OK]${NC} Todas as permutações de 3 números passaram (<= 5 ops)."
fi
rm -f tmp_out.txt
echo ""

# ==============================================================================
# 3. STRESS TEST (Múltiplas execuções)
# ==============================================================================
echo -e "${CYAN}--- 3. Stress Test de Performance ---${NC}"

stress_test() {
    local size=$1
    local limit_pass=$2
    local limit_excellent=$3
    local iterations=$4
    local flags=$5
    
    local sum=0
    local min=999999
    local max=0
    local all_sorted=true
    
    echo -n "Testando $size números ($iterations runs) $flags... "
    
    for ((i=1; i<=iterations; i++)); do
        local input=$(shuf -i 1-50000 -n $size | tr '\n' ' ')
        $PUSH_SWAP $flags $input > tmp_out.txt 2> /dev/null
        
        local count=$(wc -l < tmp_out.txt)
        local chk=$(cat tmp_out.txt | $CHECKER $input 2>&1)
        
        if [[ "$chk" != *"OK"* ]]; then
            all_sorted=false
        fi
        
        sum=$((sum + count))
        if [ "$count" -lt "$min" ]; then min=$count; fi
        if [ "$count" -gt "$max" ]; then max=$count; fi
    done
    
    local avg=$((sum / iterations))
    
    echo ""
    if ! $all_sorted; then
        echo -e "   ${RED}-> FALHOU AO ORDENAR EM PELO MENOS UMA RODADA!${NC}"
    else
        echo -e "   ${GREEN}-> Média: ${avg} | Mín: ${min} | Máx: ${max}${NC}"
        if [ "$max" -le "$limit_excellent" ]; then
            echo -e "   ${GREEN}-> Resultado: EXCELENTE (Pior caso ficou abaixo de $limit_excellent)${NC}"
        elif [ "$max" -le "$limit_pass" ]; then
            echo -e "   ${YELLOW}-> Resultado: BOM (Passou no limite de $limit_pass, mas não pegou nota máxima)${NC}"
        else
            echo -e "   ${RED}-> Resultado: KO (Pior caso de $max ultrapassou o limite de $limit_pass)${NC}"
        fi
    fi
    rm -f tmp_out.txt
}

# 100 números - Limite 2000 (Excelente < 700)
stress_test 100 2000 700 10 ""

# 500 números - Limite 12000 (Excelente < 5500)
stress_test 500 12000 5500 10 ""
echo ""

# ==============================================================================
# 4. SIMULAÇÃO DE LIVE CODING DA AVALIAÇÃO
# ==============================================================================
echo -e "${CYAN}--- 4. Preparação para a Defesa (Live Coding) ---${NC}"
echo -e "A 'scale' pede para testar se você consegue adicionar uma flag '--count-only'"
echo -e "que imprime APENAS o número total de operações, sem a lista de comandos.\n"

OUT_COUNT=$($PUSH_SWAP --count-only 3 2 1 2>/dev/null)
if [[ "$OUT_COUNT" =~ ^[0-9]+$ ]]; then
    if [ "$OUT_COUNT" -gt 0 ] && [ "$OUT_COUNT" -le 5 ]; then
        echo -e "${GREEN}[OK]${NC} Flag '--count-only' detectada e funcionando (Retornou: $OUT_COUNT)."
    else
        echo -e "${YELLOW}[AVISO]${NC} '--count-only' retornou um número ($OUT_COUNT), mas parece incorreto."
    fi
else
    echo -e "${YELLOW}[PENDENTE]${NC} A flag '--count-only' não retornou apenas um número."
    echo -e "Dica: Tente implementar isso antes da avaliação para gabaritar o live coding!"
fi
echo -e "\n${BLUE}======================================================${NC}"