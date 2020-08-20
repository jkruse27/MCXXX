	.file	"mapa.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.globl	mapa
	.data
	.align	2
	.type	mapa, @object
	.size	mapa, 100
mapa:
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	95
	.byte	95
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	88
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	88
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	95
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	95
	.byte	95
	.byte	88
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	88
	.byte	95
	.byte	95
	.byte	88
	.byte	95
	.byte	95
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	95
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	88
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	88
	.byte	95
	.byte	95
	.byte	88
	.byte	95
	.byte	88
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	95
	.byte	88
	.byte	95
	.byte	95
	.byte	95
	.byte	88
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	95
	.byte	95
	.byte	95
	.byte	88
	.byte	95
	.byte	95
	.byte	95
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.comm	visitados,400,4
	.comm	xRob,4,4
	.comm	yRob,4,4
	.comm	xLoc,4,4
	.comm	yLoc,4,4
	.text
	.align	1
	.globl	_start
	.type	_start, @function
_start:
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	addi	s0,sp,32
	sw	a0,-20(s0)
	sw	a1,-24(s0)
	lui	a5,%hi(xRob)
	li	a4,3
	sw	a4,%lo(xRob)(a5)
	lui	a5,%hi(yRob)
	li	a4,1
	sw	a4,%lo(yRob)(a5)
	lui	a5,%hi(xLoc)
	li	a4,8
	sw	a4,%lo(xLoc)(a5)
	lui	a5,%hi(yLoc)
	li	a4,3
	sw	a4,%lo(yLoc)(a5)
	call	ajudaORobinson
	li	a5,0
	mv	a0,a5
	lw	ra,28(sp)
	lw	s0,24(sp)
	addi	sp,sp,32
	jr	ra
	.size	_start, .-_start
	.align	1
	.globl	daParaPassar
	.type	daParaPassar, @function
daParaPassar:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	sw	a0,-20(s0)
	sw	a1,-24(s0)
	lw	a5,-20(s0)
	blt	a5,zero,.L4
	lw	a4,-20(s0)
	li	a5,9
	bgt	a4,a5,.L4
	lw	a5,-24(s0)
	blt	a5,zero,.L4
	lw	a4,-24(s0)
	li	a5,9
	ble	a4,a5,.L5
.L4:
	li	a5,0
	j	.L6
.L5:
	lui	a5,%hi(mapa)
	addi	a3,a5,%lo(mapa)
	lw	a4,-20(s0)
	mv	a5,a4
	slli	a5,a5,2
	add	a5,a5,a4
	slli	a5,a5,1
	add	a4,a3,a5
	lw	a5,-24(s0)
	add	a5,a4,a5
	lbu	a5,0(a5)
	addi	a5,a5,-88
	snez	a5,a5
	andi	a5,a5,0xff
.L6:
	mv	a0,a5
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	daParaPassar, .-daParaPassar
	.align	1
	.globl	posicaoXRobinson
	.type	posicaoXRobinson, @function
posicaoXRobinson:
	addi	sp,sp,-16
	sw	s0,12(sp)
	addi	s0,sp,16
	lui	a5,%hi(xRob)
	lw	a5,%lo(xRob)(a5)
	mv	a0,a5
	lw	s0,12(sp)
	addi	sp,sp,16
	jr	ra
	.size	posicaoXRobinson, .-posicaoXRobinson
	.align	1
	.globl	posicaoYRobinson
	.type	posicaoYRobinson, @function
posicaoYRobinson:
	addi	sp,sp,-16
	sw	s0,12(sp)
	addi	s0,sp,16
	lui	a5,%hi(yRob)
	lw	a5,%lo(yRob)(a5)
	mv	a0,a5
	lw	s0,12(sp)
	addi	sp,sp,16
	jr	ra
	.size	posicaoYRobinson, .-posicaoYRobinson
	.align	1
	.globl	posicaoXLocal
	.type	posicaoXLocal, @function
posicaoXLocal:
	addi	sp,sp,-16
	sw	s0,12(sp)
	addi	s0,sp,16
	lui	a5,%hi(xLoc)
	lw	a5,%lo(xLoc)(a5)
	mv	a0,a5
	lw	s0,12(sp)
	addi	sp,sp,16
	jr	ra
	.size	posicaoXLocal, .-posicaoXLocal
	.align	1
	.globl	posicaoYLocal
	.type	posicaoYLocal, @function
posicaoYLocal:
	addi	sp,sp,-16
	sw	s0,12(sp)
	addi	s0,sp,16
	lui	a5,%hi(yLoc)
	lw	a5,%lo(yLoc)(a5)
	mv	a0,a5
	lw	s0,12(sp)
	addi	sp,sp,16
	jr	ra
	.size	posicaoYLocal, .-posicaoYLocal
	.align	1
	.globl	inicializaVisitados
	.type	inicializaVisitados, @function
inicializaVisitados:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	sw	zero,-20(s0)
	j	.L16
.L19:
	sw	zero,-24(s0)
	j	.L17
.L18:
	lui	a5,%hi(visitados)
	addi	a3,a5,%lo(visitados)
	lw	a4,-20(s0)
	mv	a5,a4
	slli	a5,a5,2
	add	a5,a5,a4
	slli	a5,a5,1
	lw	a4,-24(s0)
	add	a5,a5,a4
	slli	a5,a5,2
	add	a5,a3,a5
	sw	zero,0(a5)
	lw	a5,-24(s0)
	addi	a5,a5,1
	sw	a5,-24(s0)
.L17:
	lw	a4,-24(s0)
	li	a5,9
	ble	a4,a5,.L18
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L16:
	lw	a4,-20(s0)
	li	a5,9
	ble	a4,a5,.L19
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	inicializaVisitados, .-inicializaVisitados
	.align	1
	.globl	foiVisitado
	.type	foiVisitado, @function
foiVisitado:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	sw	a0,-20(s0)
	sw	a1,-24(s0)
	lui	a5,%hi(visitados)
	addi	a3,a5,%lo(visitados)
	lw	a4,-20(s0)
	mv	a5,a4
	slli	a5,a5,2
	add	a5,a5,a4
	slli	a5,a5,1
	lw	a4,-24(s0)
	add	a5,a5,a4
	slli	a5,a5,2
	add	a5,a3,a5
	lw	a5,0(a5)
	addi	a5,a5,-1
	seqz	a5,a5
	andi	a5,a5,0xff
	mv	a0,a5
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	foiVisitado, .-foiVisitado
	.align	1
	.globl	visitaCelula
	.type	visitaCelula, @function
visitaCelula:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	sw	a0,-20(s0)
	sw	a1,-24(s0)
	lui	a5,%hi(visitados)
	addi	a3,a5,%lo(visitados)
	lw	a4,-20(s0)
	mv	a5,a4
	slli	a5,a5,2
	add	a5,a5,a4
	slli	a5,a5,1
	lw	a4,-24(s0)
	add	a5,a5,a4
	slli	a5,a5,2
	add	a5,a3,a5
	li	a4,1
	sw	a4,0(a5)
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	visitaCelula, .-visitaCelula
	.ident	"GCC: (GNU) 8.3.0"
