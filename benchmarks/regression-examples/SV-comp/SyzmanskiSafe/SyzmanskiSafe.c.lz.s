	.file	"/home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c.lz.opt.bc"
	.file	1 "/home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c"
	.section	.debug_info,"",@progbits
.Lsection_info:
	.section	.debug_abbrev,"",@progbits
.Lsection_abbrev:
	.section	.debug_aranges,"",@progbits
	.section	.debug_macinfo,"",@progbits
	.section	.debug_line,"",@progbits
.Lsection_line:
	.section	.debug_loc,"",@progbits
	.section	.debug_pubnames,"",@progbits
	.section	.debug_pubtypes,"",@progbits
	.section	.debug_str,"",@progbits
.Lsection_str:
	.section	.debug_ranges,"",@progbits
.Ldebug_range:
	.section	.debug_loc,"",@progbits
.Lsection_debug_loc:
	.text
.Ltext_begin:
	.data
	.text
	.globl	thr1
	.align	16, 0x90
	.type	thr1,@function
thr1:                                   # @thr1
.Ltmp2:
	.cfi_startproc
.Lfunc_begin0:
	.loc	1 10 0                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:10:0
# BB#0:                                 # %entry
	.loc	1 11 13 prologue_end    # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:11:13
	pushl	%esi
.Ltmp3:
	.cfi_def_cfa_offset 8
	subl	$40, %esp
.Ltmp4:
	.cfi_def_cfa_offset 48
.Ltmp5:
	.cfi_offset %esi, -8
	movl	$0, 36(%esp)
	.loc	1 12 13                 # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:12:13
	movl	$0, 32(%esp)
	.loc	1 13 13                 # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:13:13
	movl	$0, 28(%esp)
	.loc	1 14 13                 # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:14:13
	movl	$0, 24(%esp)
	movl	$13, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 15 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:15:5
	movl	$1, flag1
	movl	$13, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	.align	16, 0x90
.LBB0_1:                                # %while.cond
                                        # =>This Inner Loop Header: Depth=1
	movl	$15, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 16 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:16:5
	movl	flag2, %esi
	movl	$15, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	cmpl	$3, %esi
	jl	.LBB0_3
# BB#2:                                 # %while.body
                                        #   in Loop: Header=BB0_1 Depth=1
	.loc	1 16 24                 # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:16:24
.Ltmp6:
	movl	36(%esp), %eax
	leal	1(%eax), %ecx
	movl	%ecx, 36(%esp)
	testl	%eax, %eax
	jle	.LBB0_1
.Ltmp7:
.LBB0_3:                                # %while.end
	movl	$25, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$3, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 18 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:18:5
	movl	$3, flag1
	movl	$25, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$3, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$26, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 19 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:19:5
	movl	flag2, %esi
	movl	$26, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	cmpl	$1, %esi
	jne	.LBB0_7
# BB#4:                                 # %if.then3
	movl	$29, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$2, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 20 2                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:20:2
.Ltmp8:
	movl	$2, flag1
	movl	$29, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$2, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	.align	16, 0x90
.LBB0_5:                                # %while.cond4
                                        # =>This Inner Loop Header: Depth=1
	movl	$31, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 21 2                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:21:2
	movl	flag2, %esi
	movl	$31, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	cmpl	$4, %esi
	je	.LBB0_7
# BB#6:                                 # %while.body6
                                        #   in Loop: Header=BB0_5 Depth=1
	.loc	1 21 21                 # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:21:21
.Ltmp9:
	movl	32(%esp), %eax
	leal	1(%eax), %ecx
	movl	%ecx, 32(%esp)
	testl	%eax, %eax
	jle	.LBB0_5
.Ltmp10:
.LBB0_7:                                # %if.end12
	movl	$42, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$4, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 23 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:23:5
	movl	$4, flag1
	movl	$42, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$4, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	.align	16, 0x90
.LBB0_8:                                # %while.cond13
                                        # =>This Inner Loop Header: Depth=1
	movl	$44, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 24 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:24:5
	movl	flag2, %esi
	movl	$44, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	cmpl	$2, %esi
	jl	.LBB0_10
# BB#9:                                 # %while.body15
                                        #   in Loop: Header=BB0_8 Depth=1
	.loc	1 24 24                 # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:24:24
.Ltmp11:
	movl	28(%esp), %eax
	leal	1(%eax), %ecx
	movl	%ecx, 28(%esp)
	testl	%eax, %eax
	jle	.LBB0_8
.Ltmp12:
	.align	16, 0x90
.LBB0_10:                               # %while.cond21
                                        # =>This Inner Loop Header: Depth=1
	movl	$55, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 30 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:30:5
	movl	flag2, %esi
	movl	$55, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	xorb	%al, %al
	cmpl	$2, %esi
	jl	.LBB0_12
# BB#11:                                # %land.rhs
                                        #   in Loop: Header=BB0_10 Depth=1
	movl	$58, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	movl	flag2, %esi
	movl	$58, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	cmpl	$4, %esi
	setl	%al
.LBB0_12:                               # %land.end
                                        #   in Loop: Header=BB0_10 Depth=1
	cmpb	$1, %al
	jne	.LBB0_14
# BB#13:                                # %while.body24
                                        #   in Loop: Header=BB0_10 Depth=1
	.loc	1 30 38                 # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:30:38
.Ltmp13:
	movl	24(%esp), %eax
	leal	1(%eax), %ecx
	movl	%ecx, 24(%esp)
	testl	%eax, %eax
	jle	.LBB0_10
.Ltmp14:
.LBB0_14:                               # %while.end29
	movl	$70, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 31 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:31:5
	movl	$0, flag1
	movl	$70, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	xorl	%eax, %eax
	.loc	1 33 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:33:5
	addl	$40, %esp
	popl	%esi
	ret
.Ltmp15:
.Ltmp16:
	.size	thr1, .Ltmp16-thr1
.Lfunc_end0:
.Ltmp17:
	.cfi_endproc
.Leh_func_end0:

	.globl	thr2
	.align	16, 0x90
	.type	thr2,@function
thr2:                                   # @thr2
.Ltmp20:
	.cfi_startproc
.Lfunc_begin1:
	.loc	1 36 0                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:36:0
# BB#0:                                 # %entry
	.loc	1 37 13 prologue_end    # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:37:13
	pushl	%esi
.Ltmp21:
	.cfi_def_cfa_offset 8
	subl	$40, %esp
.Ltmp22:
	.cfi_def_cfa_offset 48
.Ltmp23:
	.cfi_offset %esi, -8
	movl	$0, 36(%esp)
	.loc	1 38 13                 # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:38:13
	movl	$0, 32(%esp)
	.loc	1 39 13                 # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:39:13
	movl	$0, 28(%esp)
	.loc	1 40 13                 # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:40:13
	movl	$0, 24(%esp)
	movl	$84, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 41 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:41:5
	movl	$1, flag2
	movl	$84, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	.align	16, 0x90
.LBB1_1:                                # %while.cond
                                        # =>This Inner Loop Header: Depth=1
	movl	$86, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 42 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:42:5
	movl	flag1, %esi
	movl	$86, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	cmpl	$3, %esi
	jl	.LBB1_3
# BB#2:                                 # %while.body
                                        #   in Loop: Header=BB1_1 Depth=1
	.loc	1 42 24                 # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:42:24
.Ltmp24:
	movl	36(%esp), %eax
	leal	1(%eax), %ecx
	movl	%ecx, 36(%esp)
	testl	%eax, %eax
	jle	.LBB1_1
.Ltmp25:
.LBB1_3:                                # %while.end
	movl	$96, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$3, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 43 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:43:5
	movl	$3, flag2
	movl	$96, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$3, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$97, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 44 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:44:5
	movl	flag1, %esi
	movl	$97, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	cmpl	$1, %esi
	jne	.LBB1_7
# BB#4:                                 # %if.then3
	movl	$100, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$2, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 45 2                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:45:2
.Ltmp26:
	movl	$2, flag2
	movl	$100, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$2, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	.align	16, 0x90
.LBB1_5:                                # %while.cond4
                                        # =>This Inner Loop Header: Depth=1
	movl	$102, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 46 2                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:46:2
	movl	flag1, %esi
	movl	$102, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	cmpl	$4, %esi
	je	.LBB1_7
# BB#6:                                 # %while.body6
                                        #   in Loop: Header=BB1_5 Depth=1
	.loc	1 46 21                 # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:46:21
.Ltmp27:
	movl	32(%esp), %eax
	leal	1(%eax), %ecx
	movl	%ecx, 32(%esp)
	testl	%eax, %eax
	jle	.LBB1_5
.Ltmp28:
.LBB1_7:                                # %if.end12
	movl	$113, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$4, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 48 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:48:5
	movl	$4, flag2
	movl	$113, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$4, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	.align	16, 0x90
.LBB1_8:                                # %while.cond13
                                        # =>This Inner Loop Header: Depth=1
	movl	$115, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 49 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:49:5
	movl	flag1, %esi
	movl	$115, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	cmpl	$2, %esi
	jl	.LBB1_10
# BB#9:                                 # %while.body15
                                        #   in Loop: Header=BB1_8 Depth=1
	.loc	1 49 24                 # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:49:24
.Ltmp29:
	movl	28(%esp), %eax
	leal	1(%eax), %ecx
	movl	%ecx, 28(%esp)
	testl	%eax, %eax
	jle	.LBB1_8
.Ltmp30:
	.align	16, 0x90
.LBB1_10:                               # %while.cond21
                                        # =>This Inner Loop Header: Depth=1
	movl	$126, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 55 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:55:5
	movl	flag1, %esi
	movl	$126, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	xorb	%al, %al
	cmpl	$2, %esi
	jl	.LBB1_12
# BB#11:                                # %land.rhs
                                        #   in Loop: Header=BB1_10 Depth=1
	movl	$129, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	movl	flag1, %esi
	movl	$129, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	cmpl	$4, %esi
	setl	%al
.LBB1_12:                               # %land.end
                                        #   in Loop: Header=BB1_10 Depth=1
	cmpb	$1, %al
	jne	.LBB1_14
# BB#13:                                # %while.body24
                                        #   in Loop: Header=BB1_10 Depth=1
	.loc	1 55 38                 # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:55:38
.Ltmp31:
	movl	24(%esp), %eax
	leal	1(%eax), %ecx
	movl	%ecx, 24(%esp)
	testl	%eax, %eax
	jle	.LBB1_10
.Ltmp32:
.LBB1_14:                               # %while.end29
	movl	$141, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 56 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:56:5
	movl	$0, flag2
	movl	$141, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	xorl	%eax, %eax
	.loc	1 57 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:57:5
	addl	$40, %esp
	popl	%esi
	ret
.Ltmp33:
.Ltmp34:
	.size	thr2, .Ltmp34-thr2
.Lfunc_end1:
.Ltmp35:
	.cfi_endproc
.Leh_func_end1:

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
.Ltmp37:
	.cfi_startproc
.Lfunc_begin2:
	.loc	1 60 0                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:60:0
# BB#0:                                 # %entry
	subl	$28, %esp
.Ltmp38:
	.cfi_def_cfa_offset 32
	movl	$0, 24(%esp)
	leal	20(%esp), %eax
	.loc	1 62 5 prologue_end     # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:62:5
.Ltmp39:
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$thr1, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	leal	16(%esp), %eax
	.loc	1 63 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:63:5
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$thr2, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	.loc	1 64 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:64:5
	movl	20(%esp), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_join
	.loc	1 65 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:65:5
	movl	16(%esp), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_join
	xorl	%eax, %eax
	.loc	1 66 5                  # /home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c:66:5
	addl	$28, %esp
	ret
.Ltmp40:
.Ltmp41:
	.size	main, .Ltmp41-main
.Lfunc_end2:
.Ltmp42:
	.cfi_endproc
.Leh_func_end2:

	.type	flag1,@object           # @flag1
	.bss
	.globl	flag1
	.align	4
flag1:
	.long	0                       # 0x0
	.size	flag1, 4

	.type	flag2,@object           # @flag2
	.globl	flag2
	.align	4
flag2:
	.long	0                       # 0x0
	.size	flag2, 4

	.type	x,@object               # @x
	.comm	x,4,4
	.cfi_sections .debug_frame
	.text
.Ltext_end:
	.data
.Ldata_end:
	.text
.Lsection_end1:
	.section	.debug_info,"",@progbits
.Linfo_begin1:
	.long	518                     # Length of Compilation Unit Info
	.short	2                       # DWARF version number
	.long	.Labbrev_begin          # Offset Into Abbrev. Section
	.byte	4                       # Address Size (in bytes)
	.byte	1                       # Abbrev [1] 0xb:0x1ff DW_TAG_compile_unit
	.ascii	 "clang version 3.0 (tags/RELEASE_30/final)" # DW_AT_producer
	.byte	0
	.short	12                      # DW_AT_language
	.ascii	 "/home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c" # DW_AT_name
	.byte	0
	.long	0                       # DW_AT_entry_pc
	.long	.Lsection_line          # DW_AT_stmt_list
	.ascii	 "/home/naling/src/inspect-0.3" # DW_AT_comp_dir
	.byte	0
	.byte	2                       # Abbrev [2] 0xad:0x7 DW_TAG_base_type
	.ascii	 "int"                  # DW_AT_name
	.byte	0
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	3                       # Abbrev [3] 0xb4:0x14 DW_TAG_variable
	.ascii	 "flag1"                # DW_AT_name
	.byte	0
	.long	173                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	7                       # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	flag1
	.byte	3                       # Abbrev [3] 0xc8:0x14 DW_TAG_variable
	.ascii	 "flag2"                # DW_AT_name
	.byte	0
	.long	173                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	7                       # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	flag2
	.byte	3                       # Abbrev [3] 0xdc:0x10 DW_TAG_variable
	.byte	120                     # DW_AT_name
	.byte	0
	.long	173                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	8                       # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	x
	.byte	4                       # Abbrev [4] 0xec:0x5b DW_TAG_subprogram
	.long	327                     # DW_AT_sibling
	.ascii	 "thr1"                 # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	10                      # DW_AT_decl_line
	.long	327                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin0           # DW_AT_low_pc
	.long	.Lfunc_end0             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	5                       # Abbrev [5] 0x108:0x3e DW_TAG_lexical_block
	.long	.Lfunc_begin0           # DW_AT_low_pc
	.long	.Ltmp15                 # DW_AT_high_pc
	.byte	6                       # Abbrev [6] 0x111:0xd DW_TAG_variable
	.ascii	 "n1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	11                      # DW_AT_decl_line
	.long	173                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	6                       # Abbrev [6] 0x11e:0xd DW_TAG_variable
	.ascii	 "n2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	12                      # DW_AT_decl_line
	.long	173                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	6                       # Abbrev [6] 0x12b:0xd DW_TAG_variable
	.ascii	 "n3"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	13                      # DW_AT_decl_line
	.long	173                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	28
	.byte	6                       # Abbrev [6] 0x138:0xd DW_TAG_variable
	.ascii	 "n4"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	14                      # DW_AT_decl_line
	.long	173                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	24
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	7                       # Abbrev [7] 0x147:0x2 DW_TAG_pointer_type
	.byte	4                       # DW_AT_byte_size
	.byte	4                       # Abbrev [4] 0x149:0x5b DW_TAG_subprogram
	.long	420                     # DW_AT_sibling
	.ascii	 "thr2"                 # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	36                      # DW_AT_decl_line
	.long	327                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin1           # DW_AT_low_pc
	.long	.Lfunc_end1             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	5                       # Abbrev [5] 0x165:0x3e DW_TAG_lexical_block
	.long	.Lfunc_begin1           # DW_AT_low_pc
	.long	.Ltmp33                 # DW_AT_high_pc
	.byte	6                       # Abbrev [6] 0x16e:0xd DW_TAG_variable
	.ascii	 "n1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	37                      # DW_AT_decl_line
	.long	173                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	6                       # Abbrev [6] 0x17b:0xd DW_TAG_variable
	.ascii	 "n2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	38                      # DW_AT_decl_line
	.long	173                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	6                       # Abbrev [6] 0x188:0xd DW_TAG_variable
	.ascii	 "n3"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	39                      # DW_AT_decl_line
	.long	173                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	28
	.byte	6                       # Abbrev [6] 0x195:0xd DW_TAG_variable
	.ascii	 "n4"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	40                      # DW_AT_decl_line
	.long	173                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	24
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	4                       # Abbrev [4] 0x1a4:0x41 DW_TAG_subprogram
	.long	485                     # DW_AT_sibling
	.ascii	 "main"                 # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	60                      # DW_AT_decl_line
	.long	173                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin2           # DW_AT_low_pc
	.long	.Lfunc_end2             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	5                       # Abbrev [5] 0x1c0:0x24 DW_TAG_lexical_block
	.long	.Ltmp39                 # DW_AT_low_pc
	.long	.Ltmp40                 # DW_AT_high_pc
	.byte	6                       # Abbrev [6] 0x1c9:0xd DW_TAG_variable
	.ascii	 "t1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	61                      # DW_AT_decl_line
	.long	506                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	20
	.byte	6                       # Abbrev [6] 0x1d6:0xd DW_TAG_variable
	.ascii	 "t2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	61                      # DW_AT_decl_line
	.long	506                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	16
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	2                       # Abbrev [2] 0x1e5:0x15 DW_TAG_base_type
	.ascii	 "long unsigned int"    # DW_AT_name
	.byte	0
	.byte	7                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	8                       # Abbrev [8] 0x1fa:0xf DW_TAG_typedef
	.long	485                     # DW_AT_type
	.ascii	 "pthread_t"            # DW_AT_name
	.byte	0
	.byte	0                       # End Of Children Mark
.Linfo_end1:
	.section	.debug_abbrev,"",@progbits
.Labbrev_begin:
	.byte	1                       # Abbreviation Code
	.byte	17                      # DW_TAG_compile_unit
	.byte	1                       # DW_CHILDREN_yes
	.byte	37                      # DW_AT_producer
	.byte	8                       # DW_FORM_string
	.byte	19                      # DW_AT_language
	.byte	5                       # DW_FORM_data2
	.byte	3                       # DW_AT_name
	.byte	8                       # DW_FORM_string
	.byte	82                      # DW_AT_entry_pc
	.byte	1                       # DW_FORM_addr
	.byte	16                      # DW_AT_stmt_list
	.byte	6                       # DW_FORM_data4
	.byte	27                      # DW_AT_comp_dir
	.byte	8                       # DW_FORM_string
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	2                       # Abbreviation Code
	.byte	36                      # DW_TAG_base_type
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	8                       # DW_FORM_string
	.byte	62                      # DW_AT_encoding
	.byte	11                      # DW_FORM_data1
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	3                       # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	8                       # DW_FORM_string
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	63                      # DW_AT_external
	.byte	12                      # DW_FORM_flag
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	2                       # DW_AT_location
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	4                       # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	1                       # DW_AT_sibling
	.byte	19                      # DW_FORM_ref4
	.byte	3                       # DW_AT_name
	.byte	8                       # DW_FORM_string
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	63                      # DW_AT_external
	.byte	12                      # DW_FORM_flag
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	64                      # DW_AT_frame_base
	.byte	10                      # DW_FORM_block1
	.ascii	 "\347\177"             # DW_AT_APPLE_omit_frame_ptr
	.byte	12                      # DW_FORM_flag
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	5                       # Abbreviation Code
	.byte	11                      # DW_TAG_lexical_block
	.byte	1                       # DW_CHILDREN_yes
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	6                       # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	8                       # DW_FORM_string
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	2                       # DW_AT_location
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	7                       # Abbreviation Code
	.byte	15                      # DW_TAG_pointer_type
	.byte	0                       # DW_CHILDREN_no
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	8                       # Abbreviation Code
	.byte	22                      # DW_TAG_typedef
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	3                       # DW_AT_name
	.byte	8                       # DW_FORM_string
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	0                       # EOM(3)
.Labbrev_end:
	.section	.debug_pubnames,"",@progbits
.Lset0 = .Lpubnames_end1-.Lpubnames_begin1 # Length of Public Names Info
	.long	.Lset0
.Lpubnames_begin1:
	.short	2                       # DWARF Version
	.long	.Linfo_begin1           # Offset of Compilation Unit Info
.Lset1 = .Linfo_end1-.Linfo_begin1      # Compilation Unit Length
	.long	.Lset1
	.long	329                     # DIE offset
	.asciz	 "thr2"                 # External Name
	.long	420                     # DIE offset
	.asciz	 "main"                 # External Name
	.long	220                     # DIE offset
	.asciz	 "x"                    # External Name
	.long	180                     # DIE offset
	.asciz	 "flag1"                # External Name
	.long	200                     # DIE offset
	.asciz	 "flag2"                # External Name
	.long	236                     # DIE offset
	.asciz	 "thr1"                 # External Name
	.long	0                       # End Mark
.Lpubnames_end1:
	.section	.debug_pubtypes,"",@progbits
.Lset2 = .Lpubtypes_end1-.Lpubtypes_begin1 # Length of Public Types Info
	.long	.Lset2
.Lpubtypes_begin1:
	.short	2                       # DWARF Version
	.long	.Linfo_begin1           # Offset of Compilation Unit Info
.Lset3 = .Linfo_end1-.Linfo_begin1      # Compilation Unit Length
	.long	.Lset3
	.long	0                       # End Mark
.Lpubtypes_end1:
	.section	.debug_aranges,"",@progbits
	.section	.debug_ranges,"",@progbits
	.section	.debug_macinfo,"",@progbits

	.section	".note.GNU-stack","",@progbits
