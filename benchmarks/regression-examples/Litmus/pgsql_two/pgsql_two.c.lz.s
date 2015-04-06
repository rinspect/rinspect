	.file	"/home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c.lz.opt.bc"
	.file	1 "/home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c"
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
	.globl	worker_1
	.align	16, 0x90
	.type	worker_1,@function
worker_1:                               # @worker_1
.Ltmp2:
	.cfi_startproc
.Lfunc_begin0:
	.loc	1 48 0                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:48:0
# BB#0:                                 # %entry
	pushl	%esi
.Ltmp3:
	.cfi_def_cfa_offset 8
	subl	$56, %esp
.Ltmp4:
	.cfi_def_cfa_offset 64
.Ltmp5:
	.cfi_offset %esi, -8
	movl	64(%esp), %eax
	movl	%eax, 48(%esp)
	.loc	1 49 13 prologue_end    # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:49:13
.Ltmp6:
	movl	$0, 44(%esp)
	.loc	1 49 27                 # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:49:27
	movl	$0, 40(%esp)
	movl	$0, 36(%esp)
	.align	16, 0x90
.LBB0_1:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	movl	$15, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 55 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:55:2
.Ltmp7:
	movl	latch1, %esi
	movl	$15, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB0_6
# BB#2:                                 # %land.lhs.true
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	$20, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 58 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:58:2
	movl	flag1, %esi
	movl	$20, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB0_7
# BB#3:                                 # %cond.end
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	$27, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 59 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:59:2
	movl	$0, latch1
	movl	$27, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$28, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 60 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:60:2
	movl	flag1, %esi
	movl	$28, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB0_5
# BB#4:                                 # %if.then3
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	$31, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 62 6                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:62:6
.Ltmp8:
	movl	$0, flag1
	movl	$31, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$32, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 63 6                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:63:6
	movl	$1, flag2
	movl	$32, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$33, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 64 6                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:64:6
	movl	$1, latch2
	movl	$33, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
.Ltmp9:
.LBB0_5:                                # %if.end4
                                        #   in Loop: Header=BB0_1 Depth=1
	.loc	1 68 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:68:2
	movl	36(%esp), %eax
	leal	1(%eax), %ecx
	movl	%ecx, 36(%esp)
	testl	%eax, %eax
	jle	.LBB0_1
.Ltmp10:
.LBB0_6:                                # %for.end
	.loc	1 70 1                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:70:1
	movl	52(%esp), %eax
	addl	$56, %esp
	popl	%esi
	ret
.LBB0_7:                                # %cond.false
	.loc	1 58 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:58:2
.Ltmp11:
	movl	$.L__PRETTY_FUNCTION__.worker_1, 12(%esp)
	movl	$58, 8(%esp)
	movl	$.L.str2, 4(%esp)
	movl	$.L.str1, (%esp)
	calll	clap___assert_fail
.Ltmp12:
.Ltmp13:
	.size	worker_1, .Ltmp13-worker_1
.Lfunc_end0:
.Ltmp14:
	.cfi_endproc
.Leh_func_end0:

	.globl	worker_2
	.align	16, 0x90
	.type	worker_2,@function
worker_2:                               # @worker_2
.Ltmp17:
	.cfi_startproc
.Lfunc_begin1:
	.loc	1 73 0                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:73:0
# BB#0:                                 # %entry
	pushl	%esi
.Ltmp18:
	.cfi_def_cfa_offset 8
	subl	$56, %esp
.Ltmp19:
	.cfi_def_cfa_offset 64
.Ltmp20:
	.cfi_offset %esi, -8
	movl	64(%esp), %eax
	movl	%eax, 48(%esp)
	.loc	1 73 11 prologue_end    # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:73:11
.Ltmp21:
	movl	$0, 44(%esp)
	.loc	1 73 25                 # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:73:25
	movl	$0, 40(%esp)
	movl	$0, 36(%esp)
	.align	16, 0x90
.LBB1_1:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	movl	$58, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 79 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:79:2
.Ltmp22:
	movl	latch2, %esi
	movl	$58, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB1_6
# BB#2:                                 # %land.lhs.true
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$63, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 82 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:82:2
	movl	flag2, %esi
	movl	$63, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB1_7
# BB#3:                                 # %cond.end
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$70, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 83 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:83:2
	movl	$0, latch2
	movl	$70, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$latch2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$71, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 84 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:84:2
	movl	flag2, %esi
	movl	$71, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	testl	%esi, %esi
	je	.LBB1_5
# BB#4:                                 # %if.then3
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$74, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 86 6                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:86:6
.Ltmp23:
	movl	$0, flag2
	movl	$74, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$flag2, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$75, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 87 6                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:87:6
	movl	$1, flag1
	movl	$75, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$flag1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$76, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 88 6                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:88:6
	movl	$1, latch1
	movl	$76, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$latch1, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
.Ltmp24:
.LBB1_5:                                # %if.end4
                                        #   in Loop: Header=BB1_1 Depth=1
	.loc	1 92 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:92:2
	movl	36(%esp), %eax
	leal	1(%eax), %ecx
	movl	%ecx, 36(%esp)
	testl	%eax, %eax
	jle	.LBB1_1
.Ltmp25:
.LBB1_6:                                # %for.end
	.loc	1 95 1                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:95:1
	movl	52(%esp), %eax
	addl	$56, %esp
	popl	%esi
	ret
.LBB1_7:                                # %cond.false
	.loc	1 82 2                  # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:82:2
.Ltmp26:
	movl	$.L__PRETTY_FUNCTION__.worker_2, 12(%esp)
	movl	$82, 8(%esp)
	movl	$.L.str2, 4(%esp)
	movl	$.L.str3, (%esp)
	calll	clap___assert_fail
.Ltmp27:
.Ltmp28:
	.size	worker_2, .Ltmp28-worker_2
.Lfunc_end1:
.Ltmp29:
	.cfi_endproc
.Leh_func_end1:

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
.Ltmp31:
	.cfi_startproc
.Lfunc_begin2:
	.loc	1 109 0                 # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:109:0
# BB#0:                                 # %entry
	subl	$28, %esp
.Ltmp32:
	.cfi_def_cfa_offset 32
	movl	$0, 24(%esp)
	leal	20(%esp), %eax
	.loc	1 114 5 prologue_end    # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:114:5
.Ltmp33:
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$worker_1, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	leal	16(%esp), %eax
	.loc	1 115 5                 # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:115:5
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$worker_2, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	.loc	1 117 5                 # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:117:5
	movl	20(%esp), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_join
	.loc	1 118 5                 # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:118:5
	movl	16(%esp), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_join
	xorl	%eax, %eax
	.loc	1 126 3                 # /home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c:126:3
	addl	$28, %esp
	ret
.Ltmp34:
.Ltmp35:
	.size	main, .Ltmp35-main
.Lfunc_end2:
.Ltmp36:
	.cfi_endproc
.Leh_func_end2:

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

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	 "violation"
	.size	.L.str, 10

	.type	.L.str1,@object         # @.str1
.L.str1:
	.asciz	 "\"violation\" && flag1"
	.size	.L.str1, 21

	.type	.L.str2,@object         # @.str2
.L.str2:
	.asciz	 "/home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c"
	.size	.L.str2, 72

	.type	.L__PRETTY_FUNCTION__.worker_1,@object # @__PRETTY_FUNCTION__.worker_1
.L__PRETTY_FUNCTION__.worker_1:
	.asciz	 "void *worker_1(void *)"
	.size	.L__PRETTY_FUNCTION__.worker_1, 23

	.type	flag2,@object           # @flag2
	.comm	flag2,4,4
	.type	latch2,@object          # @latch2
	.comm	latch2,4,4
	.type	.L.str3,@object         # @.str3
.L.str3:
	.asciz	 "\"violation\" && flag2"
	.size	.L.str3, 21

	.type	.L__PRETTY_FUNCTION__.worker_2,@object # @__PRETTY_FUNCTION__.worker_2
.L__PRETTY_FUNCTION__.worker_2:
	.asciz	 "void *worker_2(void *)"
	.size	.L__PRETTY_FUNCTION__.worker_2, 23

	.cfi_sections .debug_frame
	.text
.Ltext_end:
	.data
.Ldata_end:
	.text
.Lsection_end1:
	.section	.debug_info,"",@progbits
.Linfo_begin1:
	.long	548                     # Length of Compilation Unit Info
	.short	2                       # DWARF version number
	.long	.Labbrev_begin          # Offset Into Abbrev. Section
	.byte	4                       # Address Size (in bytes)
	.byte	1                       # Abbrev [1] 0xb:0x21d DW_TAG_compile_unit
	.ascii	 "clang version 3.0 (tags/RELEASE_30/final)" # DW_AT_producer
	.byte	0
	.short	12                      # DW_AT_language
	.ascii	 "/home/naling/src/examples/tso/regression-examples/pgsql_two/pgsql_two.c" # DW_AT_name
	.byte	0
	.long	0                       # DW_AT_entry_pc
	.long	.Lsection_line          # DW_AT_stmt_list
	.ascii	 "/home/naling/src/inspect-0.3" # DW_AT_comp_dir
	.byte	0
	.byte	2                       # Abbrev [2] 0xa5:0x7 DW_TAG_base_type
	.ascii	 "int"                  # DW_AT_name
	.byte	0
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	3                       # Abbrev [3] 0xac:0x15 DW_TAG_variable
	.ascii	 "latch1"               # DW_AT_name
	.byte	0
	.long	165                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	11                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	latch1
	.byte	3                       # Abbrev [3] 0xc1:0x14 DW_TAG_variable
	.ascii	 "flag1"                # DW_AT_name
	.byte	0
	.long	165                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	12                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	flag1
	.byte	3                       # Abbrev [3] 0xd5:0x15 DW_TAG_variable
	.ascii	 "latch2"               # DW_AT_name
	.byte	0
	.long	165                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	13                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	latch2
	.byte	3                       # Abbrev [3] 0xea:0x14 DW_TAG_variable
	.ascii	 "flag2"                # DW_AT_name
	.byte	0
	.long	165                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	13                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	flag2
	.byte	4                       # Abbrev [4] 0xfe:0x61 DW_TAG_subprogram
	.long	351                     # DW_AT_sibling
	.ascii	 "worker_1"             # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	48                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	351                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin0           # DW_AT_low_pc
	.long	.Lfunc_end0             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	5                       # Abbrev [5] 0x11f:0xe DW_TAG_formal_parameter
	.ascii	 "arg"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	47                      # DW_AT_decl_line
	.long	351                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	48
	.byte	6                       # Abbrev [6] 0x12d:0x31 DW_TAG_lexical_block
	.long	.Ltmp6                  # DW_AT_low_pc
	.long	.Ltmp12                 # DW_AT_high_pc
	.byte	7                       # Abbrev [7] 0x136:0xd DW_TAG_variable
	.ascii	 "n1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	49                      # DW_AT_decl_line
	.long	165                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	44
	.byte	7                       # Abbrev [7] 0x143:0xd DW_TAG_variable
	.ascii	 "n2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	49                      # DW_AT_decl_line
	.long	165                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	40
	.byte	7                       # Abbrev [7] 0x150:0xd DW_TAG_variable
	.ascii	 "n3"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	49                      # DW_AT_decl_line
	.long	165                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	8                       # Abbrev [8] 0x15f:0x2 DW_TAG_pointer_type
	.byte	4                       # DW_AT_byte_size
	.byte	4                       # Abbrev [4] 0x161:0x61 DW_TAG_subprogram
	.long	450                     # DW_AT_sibling
	.ascii	 "worker_2"             # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	73                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	351                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin1           # DW_AT_low_pc
	.long	.Lfunc_end1             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	5                       # Abbrev [5] 0x182:0xe DW_TAG_formal_parameter
	.ascii	 "arg"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	72                      # DW_AT_decl_line
	.long	351                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	48
	.byte	6                       # Abbrev [6] 0x190:0x31 DW_TAG_lexical_block
	.long	.Ltmp21                 # DW_AT_low_pc
	.long	.Ltmp27                 # DW_AT_high_pc
	.byte	7                       # Abbrev [7] 0x199:0xd DW_TAG_variable
	.ascii	 "n1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	73                      # DW_AT_decl_line
	.long	165                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	44
	.byte	7                       # Abbrev [7] 0x1a6:0xd DW_TAG_variable
	.ascii	 "n2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	73                      # DW_AT_decl_line
	.long	165                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	40
	.byte	7                       # Abbrev [7] 0x1b3:0xd DW_TAG_variable
	.ascii	 "n3"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	73                      # DW_AT_decl_line
	.long	165                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	9                       # Abbrev [9] 0x1c2:0x41 DW_TAG_subprogram
	.long	515                     # DW_AT_sibling
	.ascii	 "main"                 # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	109                     # DW_AT_decl_line
	.long	165                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin2           # DW_AT_low_pc
	.long	.Lfunc_end2             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	6                       # Abbrev [6] 0x1de:0x24 DW_TAG_lexical_block
	.long	.Ltmp33                 # DW_AT_low_pc
	.long	.Ltmp34                 # DW_AT_high_pc
	.byte	7                       # Abbrev [7] 0x1e7:0xd DW_TAG_variable
	.ascii	 "t1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	112                     # DW_AT_decl_line
	.long	536                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	20
	.byte	7                       # Abbrev [7] 0x1f4:0xd DW_TAG_variable
	.ascii	 "t2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	112                     # DW_AT_decl_line
	.long	536                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	16
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	2                       # Abbrev [2] 0x203:0x15 DW_TAG_base_type
	.ascii	 "long unsigned int"    # DW_AT_name
	.byte	0
	.byte	7                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	10                      # Abbrev [10] 0x218:0xf DW_TAG_typedef
	.long	515                     # DW_AT_type
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
	.byte	5                       # Abbreviation Code
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
	.byte	6                       # Abbreviation Code
	.byte	11                      # DW_TAG_lexical_block
	.byte	1                       # DW_CHILDREN_yes
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	7                       # Abbreviation Code
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
	.byte	8                       # Abbreviation Code
	.byte	15                      # DW_TAG_pointer_type
	.byte	0                       # DW_CHILDREN_no
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	9                       # Abbreviation Code
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
	.byte	10                      # Abbreviation Code
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
	.long	353                     # DIE offset
	.asciz	 "worker_2"             # External Name
	.long	450                     # DIE offset
	.asciz	 "main"                 # External Name
	.long	254                     # DIE offset
	.asciz	 "worker_1"             # External Name
	.long	193                     # DIE offset
	.asciz	 "flag1"                # External Name
	.long	234                     # DIE offset
	.asciz	 "flag2"                # External Name
	.long	172                     # DIE offset
	.asciz	 "latch1"               # External Name
	.long	213                     # DIE offset
	.asciz	 "latch2"               # External Name
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
