	.file	"/home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c.lz.opt.bc"
	.file	1 "/home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c"
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
	.globl	MFENCE
	.align	16, 0x90
	.type	MFENCE,@function
MFENCE:                                 # @MFENCE
.Ltmp1:
	.cfi_startproc
.Lfunc_begin0:
	.loc	1 18 0                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:18:0
# BB#0:                                 # %entry
	subl	$28, %esp
.Ltmp2:
	.cfi_def_cfa_offset 32
	movl	$1, 20(%esp)
	movl	$32, 16(%esp)
	movl	$7, 12(%esp)
	movl	$0, 8(%esp)
	movl	$dummy, 4(%esp)
	movl	$5, (%esp)
	calll	clap_atomicrmw_pre
	.loc	1 18 27 prologue_end    # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:18:27
.Ltmp3:
	lock
	addl	$0, dummy
	movl	$1, 20(%esp)
	movl	$32, 16(%esp)
	movl	$7, 12(%esp)
	movl	$0, 8(%esp)
	movl	$dummy, 4(%esp)
	movl	$5, (%esp)
	calll	clap_atomicrmw_post
	.loc	1 18 59                 # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:18:59
	addl	$28, %esp
	ret
.Ltmp4:
.Ltmp5:
	.size	MFENCE, .Ltmp5-MFENCE
.Lfunc_end0:
.Ltmp6:
	.cfi_endproc
.Leh_func_end0:

	.globl	worker_1
	.align	16, 0x90
	.type	worker_1,@function
worker_1:                               # @worker_1
.Ltmp9:
	.cfi_startproc
.Lfunc_begin1:
	.loc	1 49 0                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:49:0
# BB#0:                                 # %entry
	pushl	%esi
.Ltmp10:
	.cfi_def_cfa_offset 8
	subl	$56, %esp
.Ltmp11:
	.cfi_def_cfa_offset 64
.Ltmp12:
	.cfi_offset %esi, -8
	movl	64(%esp), %eax
	movl	%eax, 48(%esp)
	.loc	1 50 13 prologue_end    # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:50:13
.Ltmp13:
	movl	$0, 44(%esp)
	.loc	1 50 27                 # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:50:27
	movl	$0, 40(%esp)
	movl	$0, 36(%esp)
	.align	16, 0x90
.LBB1_1:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	movl	$17, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 55 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:55:2
.Ltmp14:
	movl	latch1, %esi
	movl	$17, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB1_7
# BB#2:                                 # %if.end
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$21, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 58 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:58:2
	movl	latch1, %esi
	movl	$21, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB1_4
# BB#3:                                 # %lor.lhs.false
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$24, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	movl	flag1, %esi
	movl	$24, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB1_8
.LBB1_4:                                # %cond.end
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$31, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 59 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:59:2
	movl	$0, latch1
	movl	$31, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$32, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 60 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:60:2
	movl	flag1, %esi
	movl	$32, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB1_6
# BB#5:                                 # %if.then4
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$35, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 62 6                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:62:6
.Ltmp15:
	movl	$0, flag1
	movl	$35, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$36, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 63 6                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:63:6
	movl	$1, flag2
	movl	$36, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$37, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 64 6                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:64:6
	movl	$1, latch2
	movl	$37, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
.Ltmp16:
.LBB1_6:                                # %if.end5
                                        #   in Loop: Header=BB1_1 Depth=1
	.loc	1 66 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:66:2
	movl	44(%esp), %eax
	leal	1(%eax), %ecx
	movl	%ecx, 44(%esp)
	cmpl	$2, %eax
	jl	.LBB1_1
.Ltmp17:
.LBB1_7:                                # %for.end
	.loc	1 69 1                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:69:1
	movl	52(%esp), %eax
	addl	$56, %esp
	popl	%esi
	ret
.LBB1_8:                                # %cond.false
	.loc	1 58 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:58:2
.Ltmp18:
	movl	$.L__PRETTY_FUNCTION__.worker_1, 12(%esp)
	movl	$58, 8(%esp)
	movl	$.L.str1, 4(%esp)
	movl	$.L.str, (%esp)
	calll	clap___assert_fail
.Ltmp19:
.Ltmp20:
	.size	worker_1, .Ltmp20-worker_1
.Lfunc_end1:
.Ltmp21:
	.cfi_endproc
.Leh_func_end1:

	.globl	worker_2
	.align	16, 0x90
	.type	worker_2,@function
worker_2:                               # @worker_2
.Ltmp24:
	.cfi_startproc
.Lfunc_begin2:
	.loc	1 72 0                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:72:0
# BB#0:                                 # %entry
	pushl	%esi
.Ltmp25:
	.cfi_def_cfa_offset 8
	subl	$56, %esp
.Ltmp26:
	.cfi_def_cfa_offset 64
.Ltmp27:
	.cfi_offset %esi, -8
	movl	64(%esp), %eax
	movl	%eax, 48(%esp)
	.loc	1 74 13 prologue_end    # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:74:13
.Ltmp28:
	movl	$0, 44(%esp)
	.loc	1 74 27                 # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:74:27
	movl	$0, 40(%esp)
	movl	$0, 36(%esp)
	.align	16, 0x90
.LBB2_1:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	movl	$62, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 78 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:78:2
.Ltmp29:
	movl	latch2, %esi
	movl	$62, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB2_7
# BB#2:                                 # %if.end
                                        #   in Loop: Header=BB2_1 Depth=1
	movl	$66, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 81 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:81:2
	movl	latch2, %esi
	movl	$66, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB2_4
# BB#3:                                 # %lor.lhs.false
                                        #   in Loop: Header=BB2_1 Depth=1
	movl	$69, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	movl	flag2, %esi
	movl	$69, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB2_8
.LBB2_4:                                # %cond.end
                                        #   in Loop: Header=BB2_1 Depth=1
	movl	$76, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 82 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:82:2
	movl	$0, latch2
	movl	$76, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	.loc	1 84 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:84:2
	calll	MFENCE
	movl	$78, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 86 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:86:2
	movl	flag2, %esi
	movl	$78, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB2_6
# BB#5:                                 # %if.then4
                                        #   in Loop: Header=BB2_1 Depth=1
	movl	$81, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 88 6                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:88:6
.Ltmp30:
	movl	$0, flag2
	movl	$81, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$82, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 89 6                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:89:6
	movl	$1, flag1
	movl	$82, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$83, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 91 6                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:91:6
	movl	$1, latch1
	movl	$83, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
.Ltmp31:
.LBB2_6:                                # %if.end5
                                        #   in Loop: Header=BB2_1 Depth=1
	.loc	1 93 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:93:2
	movl	44(%esp), %eax
	leal	1(%eax), %ecx
	movl	%ecx, 44(%esp)
	cmpl	$2, %eax
	jl	.LBB2_1
.Ltmp32:
.LBB2_7:                                # %for.end
	.loc	1 97 1                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:97:1
	movl	52(%esp), %eax
	addl	$56, %esp
	popl	%esi
	ret
.LBB2_8:                                # %cond.false
	.loc	1 81 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:81:2
.Ltmp33:
	movl	$.L__PRETTY_FUNCTION__.worker_2, 12(%esp)
	movl	$81, 8(%esp)
	movl	$.L.str1, 4(%esp)
	movl	$.L.str2, (%esp)
	calll	clap___assert_fail
.Ltmp34:
.Ltmp35:
	.size	worker_2, .Ltmp35-worker_2
.Lfunc_end2:
.Ltmp36:
	.cfi_endproc
.Leh_func_end2:

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
.Ltmp38:
	.cfi_startproc
.Lfunc_begin3:
	.loc	1 111 0                 # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:111:0
# BB#0:                                 # %entry
	subl	$28, %esp
.Ltmp39:
	.cfi_def_cfa_offset 32
	movl	$0, 24(%esp)
	leal	20(%esp), %eax
	.loc	1 116 5 prologue_end    # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:116:5
.Ltmp40:
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$worker_1, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	leal	16(%esp), %eax
	.loc	1 117 5                 # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:117:5
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$worker_2, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	.loc	1 119 5                 # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:119:5
	movl	20(%esp), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_join
	.loc	1 120 5                 # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:120:5
	movl	16(%esp), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_join
	xorl	%eax, %eax
	.loc	1 128 3                 # /home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c:128:3
	addl	$28, %esp
	ret
.Ltmp41:
.Ltmp42:
	.size	main, .Ltmp42-main
.Lfunc_end3:
.Ltmp43:
	.cfi_endproc
.Leh_func_end3:

	.type	latch1,@object          # @latch1
	.data
	.globl	latch1
	.align	4
latch1:
	.long	1                       # 0x1
	.size	latch1, 4

	.type	flag1,@object           # @flag1
	.globl	flag1
	.align	4
flag1:
	.long	1                       # 0x1
	.size	flag1, 4

	.type	dummy,@object           # @dummy
	.comm	dummy,4,4
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	 "!latch1 || flag1"
	.size	.L.str, 17

	.type	.L.str1,@object         # @.str1
.L.str1:
	.asciz	 "/home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c"
	.size	.L.str1, 100

	.type	.L__PRETTY_FUNCTION__.worker_1,@object # @__PRETTY_FUNCTION__.worker_1
.L__PRETTY_FUNCTION__.worker_1:
	.asciz	 "void *worker_1(void *)"
	.size	.L__PRETTY_FUNCTION__.worker_1, 23

	.type	flag2,@object           # @flag2
	.comm	flag2,4,4
	.type	latch2,@object          # @latch2
	.comm	latch2,4,4
	.type	.L.str2,@object         # @.str2
.L.str2:
	.asciz	 "!latch2 || flag2"
	.size	.L.str2, 17

	.type	.L__PRETTY_FUNCTION__.worker_2,@object # @__PRETTY_FUNCTION__.worker_2
.L__PRETTY_FUNCTION__.worker_2:
	.asciz	 "void *worker_2(void *)"
	.size	.L__PRETTY_FUNCTION__.worker_2, 23

	.type	__unbuffered_tmp2,@object # @__unbuffered_tmp2
	.comm	__unbuffered_tmp2,4,4
	.cfi_sections .debug_frame
	.text
.Ltext_end:
	.data
.Ldata_end:
	.text
.Lsection_end1:
	.section	.debug_info,"",@progbits
.Linfo_begin1:
	.long	650                     # Length of Compilation Unit Info
	.short	2                       # DWARF version number
	.long	.Labbrev_begin          # Offset Into Abbrev. Section
	.byte	4                       # Address Size (in bytes)
	.byte	1                       # Abbrev [1] 0xb:0x283 DW_TAG_compile_unit
	.ascii	 "clang version 3.0 (tags/RELEASE_30/final)" # DW_AT_producer
	.byte	0
	.short	12                      # DW_AT_language
	.ascii	 "/home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c" # DW_AT_name
	.byte	0
	.long	0                       # DW_AT_entry_pc
	.long	.Lsection_line          # DW_AT_stmt_list
	.ascii	 "/home/naling/src/inspect-0.3" # DW_AT_comp_dir
	.byte	0
	.byte	2                       # Abbrev [2] 0xc1:0x7 DW_TAG_base_type
	.ascii	 "int"                  # DW_AT_name
	.byte	0
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	3                       # Abbrev [3] 0xc8:0x15 DW_TAG_variable
	.ascii	 "latch1"               # DW_AT_name
	.byte	0
	.long	193                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	11                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	latch1
	.byte	3                       # Abbrev [3] 0xdd:0x14 DW_TAG_variable
	.ascii	 "flag1"                # DW_AT_name
	.byte	0
	.long	193                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	12                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	flag1
	.byte	3                       # Abbrev [3] 0xf1:0x15 DW_TAG_variable
	.ascii	 "latch2"               # DW_AT_name
	.byte	0
	.long	193                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	13                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	latch2
	.byte	3                       # Abbrev [3] 0x106:0x14 DW_TAG_variable
	.ascii	 "flag2"                # DW_AT_name
	.byte	0
	.long	193                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	13                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	flag2
	.byte	3                       # Abbrev [3] 0x11a:0x14 DW_TAG_variable
	.ascii	 "dummy"                # DW_AT_name
	.byte	0
	.long	193                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	18                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	dummy
	.byte	3                       # Abbrev [3] 0x12e:0x20 DW_TAG_variable
	.ascii	 "__unbuffered_tmp2"    # DW_AT_name
	.byte	0
	.long	193                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	20                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	__unbuffered_tmp2
	.byte	4                       # Abbrev [4] 0x14e:0x16 DW_TAG_subprogram
	.ascii	 "MFENCE"               # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	18                      # DW_AT_decl_line
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin0           # DW_AT_low_pc
	.long	.Lfunc_end0             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	5                       # Abbrev [5] 0x164:0x61 DW_TAG_subprogram
	.long	453                     # DW_AT_sibling
	.ascii	 "worker_1"             # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	49                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	453                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin1           # DW_AT_low_pc
	.long	.Lfunc_end1             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	6                       # Abbrev [6] 0x185:0xe DW_TAG_formal_parameter
	.ascii	 "arg"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	48                      # DW_AT_decl_line
	.long	453                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	48
	.byte	7                       # Abbrev [7] 0x193:0x31 DW_TAG_lexical_block
	.long	.Ltmp13                 # DW_AT_low_pc
	.long	.Ltmp19                 # DW_AT_high_pc
	.byte	8                       # Abbrev [8] 0x19c:0xd DW_TAG_variable
	.ascii	 "n1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	50                      # DW_AT_decl_line
	.long	193                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	44
	.byte	8                       # Abbrev [8] 0x1a9:0xd DW_TAG_variable
	.ascii	 "n2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	50                      # DW_AT_decl_line
	.long	193                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	40
	.byte	8                       # Abbrev [8] 0x1b6:0xd DW_TAG_variable
	.ascii	 "n3"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	50                      # DW_AT_decl_line
	.long	193                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	9                       # Abbrev [9] 0x1c5:0x2 DW_TAG_pointer_type
	.byte	4                       # DW_AT_byte_size
	.byte	5                       # Abbrev [5] 0x1c7:0x61 DW_TAG_subprogram
	.long	552                     # DW_AT_sibling
	.ascii	 "worker_2"             # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	72                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	453                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin2           # DW_AT_low_pc
	.long	.Lfunc_end2             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	6                       # Abbrev [6] 0x1e8:0xe DW_TAG_formal_parameter
	.ascii	 "arg"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	71                      # DW_AT_decl_line
	.long	453                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	48
	.byte	7                       # Abbrev [7] 0x1f6:0x31 DW_TAG_lexical_block
	.long	.Ltmp28                 # DW_AT_low_pc
	.long	.Ltmp34                 # DW_AT_high_pc
	.byte	8                       # Abbrev [8] 0x1ff:0xd DW_TAG_variable
	.ascii	 "n1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	74                      # DW_AT_decl_line
	.long	193                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	44
	.byte	8                       # Abbrev [8] 0x20c:0xd DW_TAG_variable
	.ascii	 "n2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	74                      # DW_AT_decl_line
	.long	193                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	40
	.byte	8                       # Abbrev [8] 0x219:0xd DW_TAG_variable
	.ascii	 "n3"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	74                      # DW_AT_decl_line
	.long	193                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	10                      # Abbrev [10] 0x228:0x41 DW_TAG_subprogram
	.long	617                     # DW_AT_sibling
	.ascii	 "main"                 # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	111                     # DW_AT_decl_line
	.long	193                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin3           # DW_AT_low_pc
	.long	.Lfunc_end3             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	7                       # Abbrev [7] 0x244:0x24 DW_TAG_lexical_block
	.long	.Ltmp40                 # DW_AT_low_pc
	.long	.Ltmp41                 # DW_AT_high_pc
	.byte	8                       # Abbrev [8] 0x24d:0xd DW_TAG_variable
	.ascii	 "t1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	114                     # DW_AT_decl_line
	.long	638                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	20
	.byte	8                       # Abbrev [8] 0x25a:0xd DW_TAG_variable
	.ascii	 "t2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	114                     # DW_AT_decl_line
	.long	638                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	16
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	2                       # Abbrev [2] 0x269:0x15 DW_TAG_base_type
	.ascii	 "long unsigned int"    # DW_AT_name
	.byte	0
	.byte	7                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	11                      # Abbrev [11] 0x27e:0xf DW_TAG_typedef
	.long	617                     # DW_AT_type
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
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	8                       # DW_FORM_string
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
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
	.byte	39                      # DW_AT_prototyped
	.byte	12                      # DW_FORM_flag
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
	.byte	6                       # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
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
	.byte	11                      # DW_TAG_lexical_block
	.byte	1                       # DW_CHILDREN_yes
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	8                       # Abbreviation Code
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
	.byte	9                       # Abbreviation Code
	.byte	15                      # DW_TAG_pointer_type
	.byte	0                       # DW_CHILDREN_no
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	10                      # Abbreviation Code
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
	.byte	11                      # Abbreviation Code
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
	.long	334                     # DIE offset
	.asciz	 "MFENCE"               # External Name
	.long	455                     # DIE offset
	.asciz	 "worker_2"             # External Name
	.long	302                     # DIE offset
	.asciz	 "__unbuffered_tmp2"    # External Name
	.long	552                     # DIE offset
	.asciz	 "main"                 # External Name
	.long	356                     # DIE offset
	.asciz	 "worker_1"             # External Name
	.long	221                     # DIE offset
	.asciz	 "flag1"                # External Name
	.long	262                     # DIE offset
	.asciz	 "flag2"                # External Name
	.long	200                     # DIE offset
	.asciz	 "latch1"               # External Name
	.long	241                     # DIE offset
	.asciz	 "latch2"               # External Name
	.long	282                     # DIE offset
	.asciz	 "dummy"                # External Name
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
