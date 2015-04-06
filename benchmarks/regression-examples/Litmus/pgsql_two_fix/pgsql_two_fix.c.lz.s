	.file	"/home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c.lz.opt.bc"
	.file	1 "/home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c"
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
	.loc	1 24 0                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:24:0
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
	.loc	1 24 16 prologue_end    # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:24:16
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
	.loc	1 24 48                 # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:24:48
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
	.loc	1 53 0                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:53:0
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
	.loc	1 55 13 prologue_end    # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:55:13
.Ltmp13:
	movl	$0, 44(%esp)
	.loc	1 55 27                 # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:55:27
	movl	$0, 40(%esp)
	movl	$0, 36(%esp)
	.align	16, 0x90
.LBB1_1:                                # %while.cond
                                        # =>This Inner Loop Header: Depth=1
	movl	$18, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 58 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:58:2
.Ltmp14:
	movl	latch1, %esi
	movl	$18, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB1_1
# BB#2:                                 # %while.end
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$23, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 63 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:63:2
	movl	latch1, %esi
	movl	$23, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB1_5
# BB#3:                                 # %land.lhs.true
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$29, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	movl	flag1, %esi
	movl	$29, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB1_4
.LBB1_5:                                # %if.end
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$35, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 64 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:64:2
	movl	$0, latch1
	movl	$35, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$36, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 65 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:65:2
	movl	flag1, %esi
	movl	$36, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB1_7
# BB#6:                                 # %if.then5
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$39, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 67 6                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:67:6
.Ltmp15:
	movl	$0, flag1
	movl	$39, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$40, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 68 6                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:68:6
	movl	$1, flag2
	movl	$40, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$41, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 69 6                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:69:6
	movl	$1, latch2
	movl	$41, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
.Ltmp16:
.LBB1_7:                                # %if.end6
                                        #   in Loop: Header=BB1_1 Depth=1
	.loc	1 72 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:72:2
	movl	40(%esp), %eax
	leal	1(%eax), %ecx
	movl	%ecx, 40(%esp)
	testl	%eax, %eax
	jle	.LBB1_1
.Ltmp17:
.LBB1_8:                                # %for.end
	.loc	1 75 1                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:75:1
	movl	52(%esp), %eax
	addl	$56, %esp
	popl	%esi
	ret
.LBB1_4:                                # %if.then
	.loc	1 63 30                 # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:63:30
.Ltmp18:
	movl	$.L.str, (%esp)
	calll	printf
	.loc	1 63 49                 # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:63:49
	movl	$0, 52(%esp)
	jmp	.LBB1_8
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
.Ltmp25:
	.cfi_startproc
.Lfunc_begin2:
	.loc	1 78 0                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:78:0
# BB#0:                                 # %entry
	pushl	%edi
.Ltmp26:
	.cfi_def_cfa_offset 8
	pushl	%esi
.Ltmp27:
	.cfi_def_cfa_offset 12
	subl	$52, %esp
.Ltmp28:
	.cfi_def_cfa_offset 64
.Ltmp29:
	.cfi_offset %esi, -12
.Ltmp30:
	.cfi_offset %edi, -8
	movl	64(%esp), %eax
	movl	%eax, 44(%esp)
	.loc	1 80 13 prologue_end    # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:80:13
.Ltmp31:
	movl	$0, 40(%esp)
	.loc	1 80 27                 # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:80:27
	movl	$0, 36(%esp)
	movl	$0, 32(%esp)
	.align	16, 0x90
.LBB2_1:                                # %while.cond
                                        # =>This Inner Loop Header: Depth=1
	movl	$67, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 83 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:83:2
.Ltmp32:
	movl	latch2, %esi
	movl	$67, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB2_1
# BB#2:                                 # %while.end
                                        #   in Loop: Header=BB2_1 Depth=1
	movl	$72, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 88 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:88:2
	movl	latch2, %esi
	movl	$72, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB2_5
# BB#3:                                 # %land.lhs.true
                                        #   in Loop: Header=BB2_1 Depth=1
	movl	$78, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	movl	flag2, %esi
	movl	$78, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB2_4
.LBB2_5:                                # %if.end
                                        #   in Loop: Header=BB2_1 Depth=1
	movl	$84, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 89 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:89:2
	movl	$0, latch2
	movl	$84, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$85, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 91 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:91:2
	movl	latch2, %esi
	movl	$85, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	$86, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	movl	latch2, %edi
	movl	$86, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$4, (%esp)
	xorl	%esi, %edi
	calll	clap_load_post
	movl	%edi, 8(%esp)
	movl	$88, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$__unbuffered_tmp2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	movl	%edi, __unbuffered_tmp2
	movl	%edi, 8(%esp)
	movl	$88, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$__unbuffered_tmp2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$89, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 92 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:92:2
	movl	flag2, %esi
	movl	$89, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	$90, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$__unbuffered_tmp2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	movl	__unbuffered_tmp2, %edi
	movl	$90, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$__unbuffered_tmp2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	orl	%esi, %edi
	je	.LBB2_7
# BB#6:                                 # %if.then5
                                        #   in Loop: Header=BB2_1 Depth=1
	movl	$94, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 94 6                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:94:6
.Ltmp33:
	movl	$0, flag2
	movl	$94, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$95, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 95 6                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:95:6
	movl	$1, flag1
	movl	$95, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	.loc	1 97 6                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:97:6
	calll	MFENCE
	movl	$97, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 98 6                  # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:98:6
	movl	$1, latch1
	movl	$97, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
.Ltmp34:
.LBB2_7:                                # %if.end6
                                        #   in Loop: Header=BB2_1 Depth=1
	.loc	1 100 2                 # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:100:2
	movl	36(%esp), %eax
	leal	1(%eax), %ecx
	movl	%ecx, 36(%esp)
	testl	%eax, %eax
	jle	.LBB2_1
.Ltmp35:
.LBB2_8:                                # %for.end
	.loc	1 103 1                 # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:103:1
	movl	48(%esp), %eax
	addl	$52, %esp
	popl	%esi
	popl	%edi
	ret
.LBB2_4:                                # %if.then
	.loc	1 88 30                 # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:88:30
.Ltmp36:
	movl	$.L.str1, (%esp)
	calll	printf
	.loc	1 88 49                 # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:88:49
	movl	$0, 48(%esp)
	jmp	.LBB2_8
.Ltmp37:
.Ltmp38:
	.size	worker_2, .Ltmp38-worker_2
.Lfunc_end2:
.Ltmp39:
	.cfi_endproc
.Leh_func_end2:

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
.Ltmp41:
	.cfi_startproc
.Lfunc_begin3:
	.loc	1 117 0                 # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:117:0
# BB#0:                                 # %entry
	subl	$28, %esp
.Ltmp42:
	.cfi_def_cfa_offset 32
	movl	$0, 24(%esp)
	leal	20(%esp), %eax
	.loc	1 122 5 prologue_end    # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:122:5
.Ltmp43:
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$worker_1, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	leal	16(%esp), %eax
	.loc	1 123 5                 # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:123:5
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$worker_2, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	.loc	1 125 5                 # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:125:5
	movl	20(%esp), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_join
	.loc	1 126 5                 # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:126:5
	movl	16(%esp), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_join
	xorl	%eax, %eax
	.loc	1 134 5                 # /home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c:134:5
	addl	$28, %esp
	ret
.Ltmp44:
.Ltmp45:
	.size	main, .Ltmp45-main
.Lfunc_end3:
.Ltmp46:
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

	.type	latch2,@object          # @latch2
	.bss
	.globl	latch2
	.align	4
latch2:
	.long	0                       # 0x0
	.size	latch2, 4

	.type	flag2,@object           # @flag2
	.globl	flag2
	.align	4
flag2:
	.long	0                       # 0x0
	.size	flag2, 4

	.type	dummy,@object           # @dummy
	.comm	dummy,4,4
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	 "worker1"
	.size	.L.str, 8

	.type	.L.str1,@object         # @.str1
.L.str1:
	.asciz	 "worker2"
	.size	.L.str1, 8

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
	.long	662                     # Length of Compilation Unit Info
	.short	2                       # DWARF version number
	.long	.Labbrev_begin          # Offset Into Abbrev. Section
	.byte	4                       # Address Size (in bytes)
	.byte	1                       # Abbrev [1] 0xb:0x28f DW_TAG_compile_unit
	.ascii	 "clang version 3.0 (tags/RELEASE_30/final)" # DW_AT_producer
	.byte	0
	.short	12                      # DW_AT_language
	.ascii	 "/home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c" # DW_AT_name
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
	.byte	3                       # Abbrev [3] 0xb4:0x15 DW_TAG_variable
	.ascii	 "latch1"               # DW_AT_name
	.byte	0
	.long	173                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	12                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	latch1
	.byte	3                       # Abbrev [3] 0xc9:0x14 DW_TAG_variable
	.ascii	 "flag1"                # DW_AT_name
	.byte	0
	.long	173                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	13                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	flag1
	.byte	3                       # Abbrev [3] 0xdd:0x15 DW_TAG_variable
	.ascii	 "latch2"               # DW_AT_name
	.byte	0
	.long	173                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	14                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	latch2
	.byte	3                       # Abbrev [3] 0xf2:0x14 DW_TAG_variable
	.ascii	 "flag2"                # DW_AT_name
	.byte	0
	.long	173                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	15                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	flag2
	.byte	4                       # Abbrev [4] 0x106:0x16 DW_TAG_enumeration_type
	.long	284                     # DW_AT_sibling
	.byte	4                       # DW_AT_byte_size
	.byte	5                       # Abbrev [5] 0x10c:0x8 DW_TAG_enumerator
	.ascii	 "false"                # DW_AT_name
	.byte	0
	.byte	0                       # DW_AT_const_value
	.byte	5                       # Abbrev [5] 0x114:0x7 DW_TAG_enumerator
	.ascii	 "true"                 # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_const_value
	.byte	0                       # End Of Children Mark
	.byte	6                       # Abbrev [6] 0x11c:0xa DW_TAG_typedef
	.long	262                     # DW_AT_type
	.ascii	 "bool"                 # DW_AT_name
	.byte	0
	.byte	3                       # Abbrev [3] 0x126:0x20 DW_TAG_variable
	.ascii	 "__unbuffered_tmp2"    # DW_AT_name
	.byte	0
	.long	284                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	22                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	__unbuffered_tmp2
	.byte	3                       # Abbrev [3] 0x146:0x14 DW_TAG_variable
	.ascii	 "dummy"                # DW_AT_name
	.byte	0
	.long	173                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	23                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	dummy
	.byte	7                       # Abbrev [7] 0x15a:0x16 DW_TAG_subprogram
	.ascii	 "MFENCE"               # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	24                      # DW_AT_decl_line
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin0           # DW_AT_low_pc
	.long	.Lfunc_end0             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	8                       # Abbrev [8] 0x170:0x61 DW_TAG_subprogram
	.long	465                     # DW_AT_sibling
	.ascii	 "worker_1"             # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	53                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	465                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin1           # DW_AT_low_pc
	.long	.Lfunc_end1             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	9                       # Abbrev [9] 0x191:0xe DW_TAG_formal_parameter
	.ascii	 "arg"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	52                      # DW_AT_decl_line
	.long	465                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	48
	.byte	10                      # Abbrev [10] 0x19f:0x31 DW_TAG_lexical_block
	.long	.Ltmp13                 # DW_AT_low_pc
	.long	.Ltmp19                 # DW_AT_high_pc
	.byte	11                      # Abbrev [11] 0x1a8:0xd DW_TAG_variable
	.ascii	 "n1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	55                      # DW_AT_decl_line
	.long	173                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	44
	.byte	11                      # Abbrev [11] 0x1b5:0xd DW_TAG_variable
	.ascii	 "n2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	55                      # DW_AT_decl_line
	.long	173                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	40
	.byte	11                      # Abbrev [11] 0x1c2:0xd DW_TAG_variable
	.ascii	 "n3"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	55                      # DW_AT_decl_line
	.long	173                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	12                      # Abbrev [12] 0x1d1:0x2 DW_TAG_pointer_type
	.byte	4                       # DW_AT_byte_size
	.byte	8                       # Abbrev [8] 0x1d3:0x61 DW_TAG_subprogram
	.long	564                     # DW_AT_sibling
	.ascii	 "worker_2"             # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	78                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	465                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin2           # DW_AT_low_pc
	.long	.Lfunc_end2             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	9                       # Abbrev [9] 0x1f4:0xe DW_TAG_formal_parameter
	.ascii	 "arg"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	77                      # DW_AT_decl_line
	.long	465                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	44
	.byte	10                      # Abbrev [10] 0x202:0x31 DW_TAG_lexical_block
	.long	.Ltmp31                 # DW_AT_low_pc
	.long	.Ltmp37                 # DW_AT_high_pc
	.byte	11                      # Abbrev [11] 0x20b:0xd DW_TAG_variable
	.ascii	 "n1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	80                      # DW_AT_decl_line
	.long	173                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	40
	.byte	11                      # Abbrev [11] 0x218:0xd DW_TAG_variable
	.ascii	 "n2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	80                      # DW_AT_decl_line
	.long	173                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	11                      # Abbrev [11] 0x225:0xd DW_TAG_variable
	.ascii	 "n3"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	80                      # DW_AT_decl_line
	.long	173                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	13                      # Abbrev [13] 0x234:0x41 DW_TAG_subprogram
	.long	629                     # DW_AT_sibling
	.ascii	 "main"                 # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	117                     # DW_AT_decl_line
	.long	173                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin3           # DW_AT_low_pc
	.long	.Lfunc_end3             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	10                      # Abbrev [10] 0x250:0x24 DW_TAG_lexical_block
	.long	.Ltmp43                 # DW_AT_low_pc
	.long	.Ltmp44                 # DW_AT_high_pc
	.byte	11                      # Abbrev [11] 0x259:0xd DW_TAG_variable
	.ascii	 "t1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	120                     # DW_AT_decl_line
	.long	650                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	20
	.byte	11                      # Abbrev [11] 0x266:0xd DW_TAG_variable
	.ascii	 "t2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	120                     # DW_AT_decl_line
	.long	650                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	16
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	2                       # Abbrev [2] 0x275:0x15 DW_TAG_base_type
	.ascii	 "long unsigned int"    # DW_AT_name
	.byte	0
	.byte	7                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	6                       # Abbrev [6] 0x28a:0xf DW_TAG_typedef
	.long	629                     # DW_AT_type
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
	.byte	4                       # DW_TAG_enumeration_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	1                       # DW_AT_sibling
	.byte	19                      # DW_FORM_ref4
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	5                       # Abbreviation Code
	.byte	40                      # DW_TAG_enumerator
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	8                       # DW_FORM_string
	.byte	28                      # DW_AT_const_value
	.byte	13                      # DW_FORM_sdata
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	6                       # Abbreviation Code
	.byte	22                      # DW_TAG_typedef
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	3                       # DW_AT_name
	.byte	8                       # DW_FORM_string
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	7                       # Abbreviation Code
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
	.byte	8                       # Abbreviation Code
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
	.byte	9                       # Abbreviation Code
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
	.byte	10                      # Abbreviation Code
	.byte	11                      # DW_TAG_lexical_block
	.byte	1                       # DW_CHILDREN_yes
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	11                      # Abbreviation Code
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
	.byte	12                      # Abbreviation Code
	.byte	15                      # DW_TAG_pointer_type
	.byte	0                       # DW_CHILDREN_no
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	13                      # Abbreviation Code
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
	.long	346                     # DIE offset
	.asciz	 "MFENCE"               # External Name
	.long	467                     # DIE offset
	.asciz	 "worker_2"             # External Name
	.long	294                     # DIE offset
	.asciz	 "__unbuffered_tmp2"    # External Name
	.long	564                     # DIE offset
	.asciz	 "main"                 # External Name
	.long	368                     # DIE offset
	.asciz	 "worker_1"             # External Name
	.long	201                     # DIE offset
	.asciz	 "flag1"                # External Name
	.long	242                     # DIE offset
	.asciz	 "flag2"                # External Name
	.long	180                     # DIE offset
	.asciz	 "latch1"               # External Name
	.long	221                     # DIE offset
	.asciz	 "latch2"               # External Name
	.long	326                     # DIE offset
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
