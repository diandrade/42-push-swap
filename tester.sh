#!/usr/bin/env bash
# =============================================================================
#  tester.sh - bateria de testes para push_swap (42)
#
#  Cobre as secoes da regua de avaliacao: norminette, Makefile, gestao de
#  erros, identidade, flags de estrategia, modo bench, benchmarks de 100/500
#  numeros, vazamentos e correcao exaustiva/aleatoria.
#
#  uso:  ./tester.sh [opcoes]
#          --quick        pula norminette, valgrind e benchmarks grandes
#          --full         adiciona permutacoes exaustivas e stress longo
#          --no-norm      pula a norminette
#          --no-valgrind  pula a checagem de vazamentos
#          --no-color     saida sem cores
#          --seed N       semente do gerador (padrao: aleatoria)
#          -h, --help     esta ajuda
#
#  O tester usa ./checker_linux ou ./checker_Mac se existirem no diretorio.
#  Caso contrario, cai num checker de referencia proprio escrito em awk.
# =============================================================================

set -uo pipefail

# ----------------------------------------------------------------------------
# configuracao
# ----------------------------------------------------------------------------
BIN=./push_swap
TMP=$(mktemp -d "${TMPDIR:-/tmp}/pstester.XXXXXX")
AWKCHK="$TMP/check.awk"

MODE=normal
DO_NORM=1
DO_VALGRIND=1
USE_COLOR=1
SEED=$RANDOM

PASS=0
FAIL=0
WARN=0
FAILED_LIST=()

cleanup() { rm -rf "$TMP"; }
trap cleanup EXIT

# ----------------------------------------------------------------------------
# argumentos
# ----------------------------------------------------------------------------
while [ $# -gt 0 ]; do
	case "$1" in
		--quick)       MODE=quick ;;
		--full)        MODE=full ;;
		--no-norm)     DO_NORM=0 ;;
		--no-valgrind) DO_VALGRIND=0 ;;
		--no-color)    USE_COLOR=0 ;;
		--seed)        shift; SEED="$1" ;;
		-h|--help)     sed -n '2,22p' "$0" | sed 's/^# \?//'; exit 0 ;;
		*)             echo "opcao desconhecida: $1"; exit 2 ;;
	esac
	shift
done

[ "$MODE" = quick ] && { DO_NORM=0; DO_VALGRIND=0; }

if [ "$USE_COLOR" = 1 ] && [ -t 1 ]; then
	R=$'\033[31m'; G=$'\033[32m'; Y=$'\033[33m'; B=$'\033[34m'
	D=$'\033[2m'; BOLD=$'\033[1m'; N=$'\033[0m'
else
	R=; G=; Y=; B=; D=; BOLD=; N=
fi

RANDOM=$SEED

# ----------------------------------------------------------------------------
# helpers de relatorio
# ----------------------------------------------------------------------------
section() { printf '\n%s%s== %s ==%s\n' "$BOLD" "$B" "$1" "$N"; }

ok()   { PASS=$((PASS+1)); printf '  %s✔%s %s\n' "$G" "$N" "$1"; }
ko()   { FAIL=$((FAIL+1)); FAILED_LIST+=("$1"); printf '  %s✘ %s%s\n' "$R" "$1" "$N"
         [ $# -gt 1 ] && printf '      %s%s%s\n' "$D" "$2" "$N"; return 0; }
warn() { WARN=$((WARN+1)); printf '  %s!%s %s\n' "$Y" "$N" "$1"; }
info() { printf '    %s%s%s\n' "$D" "$1" "$N"; }

# assert_eq <descricao> <esperado> <obtido>
assert_eq() {
	if [ "$2" = "$3" ]; then ok "$1"; else ko "$1" "esperado [$2] / obtido [$3]"; fi
}

# ----------------------------------------------------------------------------
# checker: usa o binario oficial se disponivel, senao o de referencia em awk
# ----------------------------------------------------------------------------
write_awk_checker() {
	cat > "$AWKCHK" << 'AWKEOF'
BEGIN {
	n = split(nums, arr, /[ \t\n]+/)
	AH = 1; AT = 0; BH = 1; BT = 0; bad = 0
	for (i = 1; i <= n; i++)
		if (arr[i] != "") A[++AT] = arr[i] + 0
}
{
	if ($0 == "") next
	if ($0 !~ /^(sa|sb|ss|pa|pb|ra|rb|rr|rra|rrb|rrr)$/) { bad = 1; exit }
	op = $0
	if (op == "sa" || op == "ss") if (AT > AH) { t = A[AH]; A[AH] = A[AH+1]; A[AH+1] = t }
	if (op == "sb" || op == "ss") if (BT > BH) { t = B[BH]; B[BH] = B[BH+1]; B[BH+1] = t }
	if (op == "pa")  if (BT >= BH) { v = B[BH]; BH++; AH--; A[AH] = v }
	if (op == "pb")  if (AT >= AH) { v = A[AH]; AH++; BH--; B[BH] = v }
	if (op == "ra"  || op == "rr")  if (AT > AH) { v = A[AH]; AH++; AT++; A[AT] = v }
	if (op == "rb"  || op == "rr")  if (BT > BH) { v = B[BH]; BH++; BT++; B[BT] = v }
	if (op == "rra" || op == "rrr") if (AT > AH) { v = A[AT]; AT--; AH--; A[AH] = v }
	if (op == "rrb" || op == "rrr") if (BT > BH) { v = B[BT]; BT--; BH--; B[BH] = v }
}
END {
	if (bad) { print "Error"; exit }
	if (BT >= BH) { print "KO"; exit }
	for (i = AH; i < AT; i++) if (A[i] > A[i+1]) { print "KO"; exit }
	print "OK"
}
AWKEOF
}

CHECKER=""
pick_checker() {
	local c
	for c in ./checker_linux ./checker_Mac; do
		[ -x "$c" ] && { CHECKER="$c"; return; }
	done
}

# verify <nums...> < opsfile  -> imprime OK/KO/Error
verify() {
	local nums="$1" opsfile="$2"
	if [ -n "$CHECKER" ]; then
		# shellcheck disable=SC2086
		"$CHECKER" $nums < "$opsfile" 2>/dev/null
	else
		awk -v nums="$nums" -f "$AWKCHK" "$opsfile"
	fi
}

# valida o proprio checker contra casos conhecidos da regua
selfcheck_checker() {
	local r
	printf 'rra\npb\nsa\nrra\npa\n' > "$TMP/sc1"
	r=$(verify "3 2 1 0" "$TMP/sc1")
	[ "$r" = OK ] || { ko "auto-teste do checker (sequencia valida)" "obtido: $r"; return; }
	printf 'sa\nrra\npb\n' > "$TMP/sc2"
	r=$(verify "3 2 1 0" "$TMP/sc2")
	[ "$r" = KO ] || { ko "auto-teste do checker (sequencia invalida)" "obtido: $r"; return; }
	printf 'pb\nra\npb\nra\nsa\nra\npa\npa\n' > "$TMP/sc3"
	r=$(verify "0 9 1 8 2" "$TMP/sc3")
	[ "$r" = OK ] || { ko "auto-teste do checker (caso da regua)" "obtido: $r"; return; }
	ok "checker validado contra os casos da regua"
}

# ----------------------------------------------------------------------------
# utilitarios
# ----------------------------------------------------------------------------
# gerador determinístico proprio: mawk ignora srand(), entao usamos um
# LCG de Lehmer (MINSTD). Todos os produtos cabem em 2^53, exato em double.
# O contador vai num arquivo porque gen_nums roda em subshell ($(...)).
gen_nums() {   # gen_nums <quantidade> <limite>
	local n="$1" m="$2" k
	[ "$m" -lt $((n * 2)) ] && m=$((n * 2))
	k=$(cat "$TMP/gencount" 2>/dev/null || echo 0)
	k=$((k + 1))
	echo "$k" > "$TMP/gencount"
	awk -v n="$n" -v m="$m" -v s="$(( (SEED + k * 7919) % 2147483646 + 1 ))" '
	function nextrand(   ) { x = (16807 * x) % 2147483647; return x / 2147483647 }
	BEGIN {
		x = s
		c = 0
		while (c < n) {
			v = int(nextrand() * m) + 1
			if (!(v in u)) { u[v] = 1; printf "%d ", v; c++ }
		}
	}'
}

count_ops() {
	local c
	c=$(grep -c . "$1" 2>/dev/null)
	echo "${c:-0}"
}

# run_sort <flag-ou-vazio> <nums>  -> grava ops em $TMP/ops, devolve rc
run_sort() {
	local flag="$1" nums="$2"
	if [ -z "$flag" ]; then
		# shellcheck disable=SC2086
		$BIN $nums > "$TMP/ops" 2> "$TMP/err"
	else
		# shellcheck disable=SC2086
		$BIN "$flag" $nums > "$TMP/ops" 2> "$TMP/err"
	fi
}

# sort_and_verify <flag> <nums> <rotulo>  -> 0 se OK
sort_and_verify() {
	local flag="$1" nums="$2" label="$3" res
	run_sort "$flag" "$nums"
	if [ -s "$TMP/err" ]; then
		ko "$label" "escreveu no stderr: $(head -1 "$TMP/err")"
		return 1
	fi
	res=$(verify "$nums" "$TMP/ops")
	if [ "$res" != OK ]; then
		ko "$label" "checker: $res"
		return 1
	fi
	return 0
}

# ----------------------------------------------------------------------------
# 1. build e Makefile
# ----------------------------------------------------------------------------
test_build() {
	section "1. Build e Makefile"

	[ -f Makefile ] || { ko "Makefile presente"; return 1; }
	ok "Makefile presente"

	local missing=""
	grep -qE '^\$\(NAME\)[[:space:]]*:' Makefile || missing="$missing \$(NAME)"
	for rule in all clean fclean re; do
		grep -qE "^$rule[[:space:]]*:" Makefile || missing="$missing $rule"
	done
	if [ -n "$missing" ]; then ko "regras obrigatorias" "faltando:$missing"
	else ok "regras NAME, all, clean, fclean, re"; fi

	grep -q -- "-Wall" Makefile && grep -q -- "-Wextra" Makefile \
		&& grep -q -- "-Werror" Makefile \
		&& ok "flags -Wall -Wextra -Werror" || ko "flags -Wall -Wextra -Werror"

	make fclean >/dev/null 2>&1
	if make >"$TMP/build.log" 2>&1; then ok "make compila sem erro"
	else ko "make compila sem erro" "veja o log abaixo"; sed 's/^/      /' "$TMP/build.log" | tail -15; return 1; fi

	grep -iE "warning" "$TMP/build.log" >/dev/null \
		&& warn "a compilacao emitiu warnings" || ok "compilacao sem warnings"

	[ -x "$BIN" ] && ok "binario push_swap criado" || { ko "binario push_swap criado"; return 1; }

	local second; second=$(make 2>&1)
	echo "$second" | grep -qiE "^(cc|gcc|clang)" \
		&& ko "make nao relinka" "recompilou sem mudanca no fonte" \
		|| ok "make nao relinka"

	make clean >/dev/null 2>&1
	if find . -name "*.o" | grep -q .; then ko "make clean remove os .o"
	else ok "make clean remove os .o"; fi

	make >/dev/null 2>&1
	make fclean >/dev/null 2>&1
	[ -x "$BIN" ] && ko "make fclean remove o binario" || ok "make fclean remove o binario"

	make re >/dev/null 2>&1
	[ -x "$BIN" ] && ok "make re reconstroi o binario" || { ko "make re reconstroi o binario"; return 1; }
	return 0
}

# ----------------------------------------------------------------------------
# 2. norminette
# ----------------------------------------------------------------------------
test_norm() {
	section "2. Norminette"
	if ! command -v norminette >/dev/null 2>&1; then
		warn "norminette nao instalada - secao pulada"
		return
	fi
	local files errors
	files=$(find . -name "*.c" -o -name "*.h" | grep -v "/\.git/")
	# shellcheck disable=SC2086
	norminette $files > "$TMP/norm.txt" 2>&1
	errors=$(grep -c "^Error:" "$TMP/norm.txt")
	if [ "$errors" -eq 0 ]; then
		ok "0 erros de norma ($(grep -c 'OK!' "$TMP/norm.txt") arquivos)"
	else
		ko "norminette limpa" "$errors erros"
		awk '/: Error!/{f=$1} /^Error:/{print "      " f " " $2 " " $3 " " $4}' \
			"$TMP/norm.txt" | head -20
		[ "$errors" -gt 20 ] && info "... e mais $((errors-20)) erros"
	fi
}

# ----------------------------------------------------------------------------
# 3. gestao de erros
# ----------------------------------------------------------------------------
# expect_error <descricao> <args...>
expect_error() {
	local label="$1"; shift
	local out err
	out=$("$BIN" "$@" 2>"$TMP/e"); err=$(cat "$TMP/e")
	if [ "$err" = "Error" ] && [ -z "$out" ]; then
		ok "$label"
	else
		ko "$label" "stdout=[$out] stderr=[$err]  (esperado stderr='Error', stdout vazio)"
	fi
}

test_errors() {
	section "3. Gestao de erros"

	expect_error "argumento nao numerico"            1 2 three
	expect_error "argumento alfabetico puro"         abc
	expect_error "duplicata em argumentos separados" 1 2 2 3
	expect_error "duplicata dentro de uma string"    "1 2 2"
	expect_error "duplicata cruzando argumentos"     1 "2 2"
	expect_error "acima de INT_MAX"                  2147483648
	expect_error "abaixo de INT_MIN"                 -2147483649
	expect_error "numero absurdamente grande"        99999999999999999999
	expect_error "string vazia"                      ""
	expect_error "string vazia com numero"           "" 1
	expect_error "flag inexistente"                  1 2 --xyz
	expect_error "hifen duplo solto"                 1 -- 3
	expect_error "sinal isolado"                     1 + 3
	expect_error "numero com sufixo"                 1 2x 3
	expect_error "numero com ponto"                  1 2.5 3

	local out err
	out=$("$BIN" 2>"$TMP/e"); err=$(cat "$TMP/e")
	if [ -z "$out" ] && [ -z "$err" ]; then ok "sem argumentos: nao imprime nada"
	else ko "sem argumentos: nao imprime nada" "stdout=[$out] stderr=[$err]"; fi

	# limites validos devem ser ACEITOS
	if "$BIN" 2147483647 -2147483648 0 >"$TMP/ops" 2>"$TMP/e" && [ ! -s "$TMP/e" ]; then
		[ "$(verify "2147483647 -2147483648 0" "$TMP/ops")" = OK ] \
			&& ok "INT_MAX e INT_MIN sao aceitos e ordenados" \
			|| ko "INT_MAX e INT_MIN sao aceitos e ordenados"
	else
		ko "INT_MAX e INT_MIN sao aceitos" "stderr=[$(cat "$TMP/e")]"
	fi
}

# ----------------------------------------------------------------------------
# 4. identidade (entradas ja ordenadas)
# ----------------------------------------------------------------------------
test_identity() {
	section "4. Identidade (entrada ja ordenada)"
	local args n
	for args in "42" "2 3" "0 1 2 3" "0 1 2 3 4 5 6 7 8 9" "-5 -1 0 7 900"; do
		run_sort "" "$args"
		n=$(count_ops "$TMP/ops")
		assert_eq "[$args] -> 0 operacoes" "0" "$n"
	done
	for flag in --simple --medium --complex --adaptive; do
		run_sort "$flag" "1 2 3 4 5 6"
		assert_eq "$flag com entrada ordenada -> 0 operacoes" "0" "$(count_ops "$TMP/ops")"
	done
}

# ----------------------------------------------------------------------------
# 5. entradas pequenas (regua: 3 numeros <=5 aceitavel / <=3 bom)
# ----------------------------------------------------------------------------
test_small() {
	section "5. Entradas pequenas (3 numeros)"
	local perms=("0 1 2" "0 2 1" "1 0 2" "1 2 0" "2 0 1" "2 1 0")
	local worst=0 p n bad=0
	for p in "${perms[@]}"; do
		sort_and_verify "" "$p" "ordena [$p]" || { bad=1; continue; }
		n=$(count_ops "$TMP/ops")
		[ "$n" -gt "$worst" ] && worst=$n
	done
	[ $bad -eq 0 ] && ok "todas as 6 permutacoes de 3 elementos ordenam"
	if   [ "$worst" -le 3 ]; then ok "pior caso: $worst operacoes (regua: <=3 e bom)"
	elif [ "$worst" -le 5 ]; then warn "pior caso: $worst operacoes (aceitavel, mas <=3 e o alvo)"
	else ko "pior caso de 3 numeros" "$worst operacoes (regua exige <=5)"; fi
}

test_medium_small() {
	section "6. Entradas medias (5 numeros)"
	local cases=("1 5 2 4 3" "5 1 4 2 3" "3 5 1 4 2" "5 4 3 2 1" "4 67 3 87 23" "2 1 3 6 5")
	local worst=0 c n bad=0
	for c in "${cases[@]}"; do
		sort_and_verify "" "$c" "ordena [$c]" || { bad=1; continue; }
		n=$(count_ops "$TMP/ops")
		[ "$n" -gt "$worst" ] && worst=$n
	done
	[ $bad -eq 0 ] && ok "todos os casos de 5 elementos ordenam"
	if   [ "$worst" -le 12 ]; then ok "pior caso: $worst operacoes (regua: <=12 e bom)"
	elif [ "$worst" -le 15 ]; then warn "pior caso: $worst operacoes (aceitavel, mas <=12 e o alvo)"
	else ko "pior caso de 5 numeros" "$worst operacoes (regua exige <=15)"; fi
}

# ----------------------------------------------------------------------------
# 7. flags de estrategia
# ----------------------------------------------------------------------------
test_flags() {
	section "7. Flags de estrategia"
	local nums="5 4 3 2 1" flag
	for flag in --simple --medium --complex --adaptive; do
		if sort_and_verify "$flag" "$nums" "$flag ordena [$nums]"; then
			ok "$flag ordena [$nums] ($(count_ops "$TMP/ops") operacoes)"
		fi
	done

	# sem flag deve equivaler a --adaptive
	run_sort "" "$nums";           cp "$TMP/ops" "$TMP/noflag"
	run_sort "--adaptive" "$nums"
	if cmp -s "$TMP/noflag" "$TMP/ops"; then ok "sem flag == --adaptive"
	else ko "sem flag == --adaptive" "as saidas diferem"; fi

	# flag depois dos numeros: roda com a flag no fim, valida so contra os numeros
	# shellcheck disable=SC2086
	$BIN $nums --simple > "$TMP/ops" 2> "$TMP/err"
	if [ -s "$TMP/err" ]; then
		ko "flag aceita depois dos numeros" "stderr: $(head -1 "$TMP/err")"
	elif [ "$(verify "$nums" "$TMP/ops")" = OK ]; then
		ok "flag aceita depois dos numeros"
	else
		ko "flag aceita depois dos numeros" "checker recusou a saida"
	fi

	# comparacao de desempenho em n=50
	local n50; n50=$(gen_nums 50 500)
	local s m c
	run_sort "--simple"  "$n50"; s=$(count_ops "$TMP/ops")
	run_sort "--medium"  "$n50"; m=$(count_ops "$TMP/ops")
	run_sort "--complex" "$n50"; c=$(count_ops "$TMP/ops")
	info "n=50 -> simple:$s  medium:$m  complex:$c"
	if [ "$c" -lt "$s" ]; then ok "complex usa menos operacoes que simple (n=50)"
	else warn "complex ($c) >= simple ($s) em n=50 - explique na defesa"; fi

	local n300; n300=$(gen_nums 300 3000)
	run_sort "--simple"  "$n300"; s=$(count_ops "$TMP/ops")
	run_sort "--complex" "$n300"; c=$(count_ops "$TMP/ops")
	info "n=300 -> simple:$s  complex:$c"
	[ "$c" -lt "$s" ] && ok "complex usa menos operacoes que simple (n=300)" \
	                  || ko "complex < simple em n=300" "simple:$s complex:$c"
}

# ----------------------------------------------------------------------------
# 8. modo bench
# ----------------------------------------------------------------------------
bench_field() { grep -m1 "$1" "$TMP/bench" 2>/dev/null; }

test_bench() {
	section "8. Modo --bench"

	# shellcheck disable=SC2086
	$BIN --bench --simple 5 4 3 2 1 > "$TMP/ops" 2> "$TMP/bench"
	[ -s "$TMP/ops" ] && ok "operacoes continuam no stdout" || ko "operacoes continuam no stdout"
	[ -s "$TMP/bench" ] && ok "metricas vao para o stderr" || ko "metricas vao para o stderr"
	grep -q "bench" "$TMP/ops" && ko "stdout limpo (sem vazar bench)" || ok "stdout limpo (sem vazar bench)"

	local f
	for f in disorder strategy total_ops; do
		grep -q "$f" "$TMP/bench" && ok "campo '$f' presente" || ko "campo '$f' presente"
	done
	local missing=""
	for f in sa sb ss pa pb ra rb rr rra rrb rrr; do
		grep -qE "\b$f:" "$TMP/bench" || missing="$missing $f"
	done
	[ -z "$missing" ] && ok "contadores de todas as 11 operacoes" \
	                  || ko "contadores das 11 operacoes" "faltando:$missing"

	# total_ops deve bater com as linhas do stdout
	local declared actual
	declared=$(grep -oE "total_ops:[[:space:]]*[0-9]+" "$TMP/bench" | grep -oE "[0-9]+$")
	actual=$(count_ops "$TMP/ops")
	assert_eq "total_ops confere com as linhas do stdout" "$actual" "${declared:-vazio}"

	# disorder em entradas conhecidas
	# shellcheck disable=SC2086
	$BIN --bench 1 2 3 4 5 >/dev/null 2> "$TMP/bench"
	if [ ! -s "$TMP/bench" ]; then
		ko "bench com entrada ordenada" "nao imprimiu nada (a regua testa disorder ~0.00%)"
	else
		grep -qE "disorder:[[:space:]]*0\.00" "$TMP/bench" \
			&& ok "entrada ordenada -> disorder 0.00%" \
			|| ko "entrada ordenada -> disorder 0.00%" "$(bench_field disorder)"
	fi

	# shellcheck disable=SC2086
	$BIN --bench 5 4 3 2 1 >/dev/null 2> "$TMP/bench"
	grep -qE "disorder:[[:space:]]*100\.00" "$TMP/bench" \
		&& ok "entrada invertida -> disorder 100.00%" \
		|| ko "entrada invertida -> disorder 100.00%" "$(bench_field disorder)"

	# LaTeX cru vazando na saida
	# shellcheck disable=SC2086
	$BIN --bench --medium 5 4 3 2 1 >/dev/null 2> "$TMP/bench"
	grep -q '\\sqrt\|\\frac\|{n}' "$TMP/bench" \
		&& ko "sem LaTeX cru na saida" "$(bench_field strategy)" \
		|| ok "sem LaTeX cru na saida"

	# sem a flag, nada deve ir para o stderr
	# shellcheck disable=SC2086
	$BIN 5 4 3 2 1 >/dev/null 2> "$TMP/bench"
	[ -s "$TMP/bench" ] && ko "sem --bench o stderr fica vazio" || ok "sem --bench o stderr fica vazio"
}

# ----------------------------------------------------------------------------
# 9. benchmarks de desempenho
# ----------------------------------------------------------------------------
# perf <n> <limite_max> <limite_bom> <limite_excelente> <runs>
perf() {
	local n="$1" lim="$2" good="$3" exc="$4" runs="$5"
	local i nums min=999999999 max=0 sum=0 c bad=0
	for i in $(seq "$runs"); do
		nums=$(gen_nums "$n" $((n*20)))
		if ! sort_and_verify "" "$nums" "n=$n run $i ordena corretamente"; then bad=1; continue; fi
		c=$(count_ops "$TMP/ops")
		sum=$((sum+c))
		[ "$c" -lt "$min" ] && min=$c
		[ "$c" -gt "$max" ] && max=$c
	done
	[ $bad -eq 0 ] && ok "n=$n: $runs/$runs execucoes retornaram OK"
	info "min=$min  media=$((sum/runs))  max=$max"
	if   [ "$max" -lt "$exc" ];  then ok "n=$n: pior caso $max (< $exc = EXCELENTE)"
	elif [ "$max" -lt "$good" ]; then ok "n=$n: pior caso $max (< $good = BOM)"
	elif [ "$max" -lt "$lim" ];  then warn "n=$n: pior caso $max (passa, mas acima de $good)"
	else ko "n=$n: limite de operacoes" "pior caso $max, a regua exige < $lim"; fi
}

test_perf() {
	section "9. Benchmarks de desempenho"
	local runs=5
	[ "$MODE" = full ] && runs=15
	perf 100 2000 1500 700 "$runs"
	perf 500 12000 8000 5500 "$runs"
	if [ "$MODE" = full ]; then
		section "9b. Escala extra"
		perf 1000 40000 25000 15000 3
	fi
}

# ----------------------------------------------------------------------------
# 10. correcao: permutacoes exaustivas e stress aleatorio
# ----------------------------------------------------------------------------
test_exhaustive() {
	section "10. Permutacoes exaustivas"
	local maxn=5
	[ "$MODE" = full ] && maxn=7
	local flags=("" --simple --medium --complex --adaptive)
	local n flag total=0 bad=0 perm res

	for n in $(seq 1 "$maxn"); do
		# gera todas as permutacoes de 0..n-1
		awk -v n="$n" '
		function perm(k,   i, t, s) {
			if (k == n) { s = ""; for (i = 0; i < n; i++) s = s p[i] " "; print s; return }
			for (i = k; i < n; i++) {
				t = p[k]; p[k] = p[i]; p[i] = t
				perm(k + 1)
				t = p[k]; p[k] = p[i]; p[i] = t
			}
		}
		BEGIN { for (i = 0; i < n; i++) p[i] = i; perm(0) }' > "$TMP/perms"

		while read -r perm; do
			for flag in "${flags[@]}"; do
				run_sort "$flag" "$perm"
				total=$((total+1))
				res=$(verify "$perm" "$TMP/ops")
				if [ "$res" != OK ] || [ -s "$TMP/err" ]; then
					bad=$((bad+1))
					[ "$bad" -le 5 ] && ko "n=$n flag='${flag:-default}' [$perm]" "checker: $res"
				fi
			done
		done < "$TMP/perms"
	done
	if [ "$bad" -eq 0 ]; then ok "$total execucoes exaustivas (n=1..$maxn, 5 estrategias): todas OK"
	else ko "permutacoes exaustivas" "$bad falhas em $total execucoes"; fi
}

test_stress() {
	section "11. Stress aleatorio"
	local sizes=(2 3 4 6 8 12 25 47 64 99 128 257 500)
	local iters=2
	[ "$MODE" = full ] && iters=6
	[ "$MODE" = quick ] && { sizes=(3 10 50 100); iters=2; }
	local flags=("" --simple --medium --complex --adaptive)
	local n i flag total=0 bad=0 nums res

	for n in "${sizes[@]}"; do
		for i in $(seq "$iters"); do
			nums=$(gen_nums "$n" $((n*50+100)))
			for flag in "${flags[@]}"; do
				run_sort "$flag" "$nums"
				total=$((total+1))
				res=$(verify "$nums" "$TMP/ops")
				if [ "$res" != OK ] || [ -s "$TMP/err" ]; then
					bad=$((bad+1))
					[ "$bad" -le 5 ] && ko "n=$n flag='${flag:-default}'" "checker: $res"
				fi
			done
		done
	done

	# entradas com estrutura, nao so aleatorias
	local special=("1 2 3 4 5 6 7 8 9 10" "10 9 8 7 6 5 4 3 2 1"
	               "5 1 2 3 4 6 7 8 9 10" "1 2 3 4 5 6 7 8 10 9"
	               "-3 -1 -2 0 2 1" "0 -1 1 -2 2 -3 3")
	for nums in "${special[@]}"; do
		for flag in "${flags[@]}"; do
			run_sort "$flag" "$nums"
			total=$((total+1))
			res=$(verify "$nums" "$TMP/ops")
			[ "$res" != OK ] && { bad=$((bad+1)); ko "estruturado [$nums] flag='${flag:-default}'" "checker: $res"; }
		done
	done

	[ "$bad" -eq 0 ] && ok "$total execucoes aleatorias/estruturadas: todas OK" \
	                 || ko "stress aleatorio" "$bad falhas em $total execucoes"
}

# ----------------------------------------------------------------------------
# 12. vazamentos de memoria
# ----------------------------------------------------------------------------
test_leaks() {
	section "12. Vazamentos de memoria"
	if ! command -v valgrind >/dev/null 2>&1; then
		warn "valgrind nao encontrado - secao pulada"
		return
	fi
	local nums500; nums500=$(gen_nums 500 10000)
	local cases=("5 1 4 2 3" "1 2 2" "1 abc 3" "2147483648" "1 2 3 --bench --medium"
	             "--complex 9 8 7 6 5 4 3 2 1" "$nums500")
	local c label
	for c in "${cases[@]}"; do
		label=$(printf '%.30s' "$c")
		# shellcheck disable=SC2086
		valgrind --leak-check=full --errors-for-leak-kinds=all --error-exitcode=99 \
			$BIN $c >/dev/null 2>"$TMP/vg"
		if [ $? -eq 99 ] || grep -qE "definitely lost: [1-9]|indirectly lost: [1-9]|Invalid (read|write|free)" "$TMP/vg"; then
			ko "sem vazamento em [$label]" "$(grep -E 'definitely lost|Invalid' "$TMP/vg" | head -2 | tr '\n' ' ')"
		else
			ok "sem vazamento em [$label]"
		fi
	done
}

# ----------------------------------------------------------------------------
# 13. higiene do repositorio (itens da regua que nao sao codigo)
# ----------------------------------------------------------------------------
test_repo() {
	section "13. Higiene do repositorio"

	if [ ! -f README.md ]; then ko "README.md existe"
	elif [ ! -s README.md ]; then ko "README.md nao esta vazio"
	else
		ok "README.md existe e tem conteudo"
		head -1 README.md | grep -qE '^\*.*42.*\*$|^_.*42.*_$' \
			&& ok "primeira linha do README em italico mencionando a 42" \
			|| ko "primeira linha do README em italico mencionando a 42"
		local sec
		for sec in Description Instructions Resources; do
			grep -qi "^#\+.*$sec" README.md && ok "secao '$sec' no README" \
			                                || ko "secao '$sec' no README"
		done
	fi

	if [ -d .git ]; then
		local names count
		names=$(git log --format='%an <%ae>' 2>/dev/null | sort -u)
		count=$(echo "$names" | grep -c .)
		if [ "$count" -lt 2 ]; then
			ko "projeto de dupla: 2 alunos no historico git" "so 1 identidade encontrada"
		else
			warn "$count identidades no git - confirme que sao 2 ALUNOS, nao 2 emails seus"
			echo "$names" | sed 's/^/      /'
		fi
	else
		warn "nao e um repositorio git - checagem de contribuidores pulada"
	fi

	[ -f .gitignore ] && ok ".gitignore presente" || warn ".gitignore ausente"
	if [ -d .git ]; then
		git ls-files 2>/dev/null | grep -qE '\.o$|^push_swap$' \
			&& ko "binarios/objetos nao versionados" \
			|| ok "binarios/objetos nao versionados"
	fi

	grep -rn "printf\|<stdio.h>" --include="*.c" --include="*.h" . 2>/dev/null \
		| grep -v "ft_printf" | grep -q . \
		&& ko "sem stdio.h / printf no fonte" || ok "sem stdio.h / printf no fonte"
}

# ----------------------------------------------------------------------------
# main
# ----------------------------------------------------------------------------
printf '%s%s' "$BOLD" "$B"
printf '\n╔════════════════════════════════════════════╗'
printf '\n║        push_swap tester  (modo: %-7s)   ║' "$MODE"
printf '\n╚════════════════════════════════════════════╝%s\n' "$N"

write_awk_checker
pick_checker
if [ -n "$CHECKER" ]; then info "usando o checker oficial: $CHECKER"
else info "checker_linux nao encontrado - usando o checker de referencia interno"; fi
selfcheck_checker

if ! test_build; then
	printf '\n%s%sBuild falhou - o resto da bateria nao pode rodar.%s\n' "$BOLD" "$R" "$N"
	exit 1
fi

[ "$DO_NORM" = 1 ] && test_norm
test_errors
test_identity
test_small
test_medium_small
test_flags
test_bench
[ "$MODE" != quick ] && test_perf
test_exhaustive
test_stress
[ "$DO_VALGRIND" = 1 ] && test_leaks
test_repo

# ----------------------------------------------------------------------------
# resumo
# ----------------------------------------------------------------------------
printf '\n%s%s== Resumo ==%s\n' "$BOLD" "$B" "$N"
printf '  %spassou : %d%s\n' "$G" "$PASS" "$N"
printf '  %sfalhou : %d%s\n' "$R" "$FAIL" "$N"
printf '  %savisos : %d%s\n' "$Y" "$WARN" "$N"
printf '  %ssemente: %s (reproduza com --seed %s)%s\n' "$D" "$SEED" "$SEED" "$N"

if [ "$FAIL" -gt 0 ]; then
	printf '\n%sFalhas:%s\n' "$BOLD" "$N"
	printf '  - %s\n' "${FAILED_LIST[@]}"
	printf '\n%s%sBATERIA REPROVADA%s\n' "$BOLD" "$R" "$N"
	exit 1
fi
printf '\n%s%sBATERIA APROVADA%s' "$BOLD" "$G" "$N"
[ "$WARN" -gt 0 ] && printf ' %s(com %d aviso[s])%s' "$Y" "$WARN" "$N"
printf '\n'
exit 0