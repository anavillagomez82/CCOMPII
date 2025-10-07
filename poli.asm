# poly_eval.asm
# Evaluación de polinomio P(x) con coeficientes enteros y x float (usa Horner)
.data
prompt_n:    .asciiz "Ingrese grado n (entero >= 0): "
prompt_coef: .asciiz "Ingrese coeficiente (entero): "
prompt_x:    .asciiz "Ingrese x (float): "
msg_res:     .asciiz "Resultado P(x) = "
newline:     .asciiz "\n"

.text
.globl main
main:
    # --- Leer grado n ---
    la   $a0, prompt_n
    li   $v0, 4
    syscall
    li   $v0, 5       # read int
    syscall
    move $s1, $v0     # s1 = n
    bltz $s1, finish  # si n < 0, terminar

    # --- Reservar memoria para n+1 coeficientes (cada coef 4 bytes) ---
    addi $t0, $s1, 1
    sll  $t0, $t0, 2
    move $a0, $t0
    li   $v0, 9
    syscall
    move $s0, $v0     # s0 = base pointer

    # --- Leer coeficientes ---
    li   $t1, 0
read_coefs:
    bgt  $t1, $s1, read_coefs_done
    la   $a0, prompt_coef
    li   $v0, 4
    syscall
    li   $v0, 5
    syscall
    move $t2, $v0
    sll  $t3, $t1, 2
    addu $t4, $s0, $t3
    sw   $t2, 0($t4)
    addi $t1, $t1, 1
    j read_coefs

read_coefs_done:
    # --- Leer x (float) ---
    la   $a0, prompt_x
    li   $v0, 4
    syscall
    li   $v0, 6
    syscall             # float → $f0

    # --- Horner: result = an ---
    sll  $t3, $s1, 2
    addu $t4, $s0, $t3
    lw   $t2, 0($t4)
    mtc1 $t2, $f4
    cvt.s.w $f4, $f4

    addi $t5, $s1, -1
horner_loop:
    bltz $t5, horner_done
    mul.s $f4, $f4, $f0
    sll  $t3, $t5, 2
    addu $t4, $s0, $t3
    lw   $t2, 0($t4)
    mtc1 $t2, $f6
    cvt.s.w $f6, $f6
    add.s $f4, $f4, $f6
    addi $t5, $t5, -1
    j horner_loop

horner_done:
    la   $a0, msg_res
    li   $v0, 4
    syscall
    mov.s $f12, $f4
    li   $v0, 2
    syscall
    la   $a0, newline
    li   $v0, 4
    syscall

finish:
    li   $v0, 10
    syscall
