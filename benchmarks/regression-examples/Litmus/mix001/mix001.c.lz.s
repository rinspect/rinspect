	.file	"../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c.lz.opt.bc"
	.file	1 "/home/naling/src/inspect-0.3/../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c"
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
	.globl	P0
	.align	16, 0x90
	.type	P0,@function
P0:                                     # @P0
.Ltmp2:
	.cfi_startproc
.Lfunc_begin0:
	.loc	1 32 0                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:32:0
# BB#0:                                 # %entry
	pushl	%esi
.Ltmp3:
	.cfi_def_cfa_offset 8
	subl	$40, %esp
.Ltmp4:
	.cfi_def_cfa_offset 48
.Ltmp5:
	.cfi_offset %esi, -8
	movl	48(%esp), %eax
	movl	%eax, 36(%esp)
	movl	$8, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$z, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 34 3 prologue_end     # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:34:3
.Ltmp6:
	movl	$1, z
	movl	$8, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$z, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$9, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$z, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 35 3                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:35:3
	movl	z, %esi
	movl	$9, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$z, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%esi, 32(%esp)
	movl	$11, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$x, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 36 3                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:36:3
	movl	x, %esi
	movl	$11, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$x, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%esi, 28(%esp)
	.loc	1 37 3                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:37:3
	movl	32(%esp), %eax
	movl	%esi, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$.L.str, (%esp)
	calll	printf
	xorb	%al, %al
	.loc	1 38 3                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:38:3
	cmpl	$1, 32(%esp)
	jne	.LBB0_2
# BB#1:                                 # %land.rhs
	cmpl	$0, 28(%esp)
	sete	%al
.Ltmp7:
.LBB0_2:                                # %land.end
	movzbl	%al, %eax
	.loc	1 39 1                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:39:1
	addl	$40, %esp
	popl	%esi
	ret
.Ltmp8:
.Ltmp9:
	.size	P0, .Ltmp9-P0
.Lfunc_end0:
.Ltmp10:
	.cfi_endproc
.Leh_func_end0:

	.globl	P1
	.align	16, 0x90
	.type	P1,@function
P1:                                     # @P1
.Ltmp13:
	.cfi_startproc
.Lfunc_begin1:
	.loc	1 42 0                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:42:0
# BB#0:                                 # %entry
	pushl	%esi
.Ltmp14:
	.cfi_def_cfa_offset 8
	subl	$40, %esp
.Ltmp15:
	.cfi_def_cfa_offset 48
.Ltmp16:
	.cfi_offset %esi, -8
	movl	48(%esp), %eax
	movl	%eax, 36(%esp)
	movl	$33, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$x, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 44 3 prologue_end     # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:44:3
.Ltmp17:
	movl	$1, x
	movl	$33, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$x, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$34, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$x, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 45 3                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:45:3
	movl	x, %esi
	movl	$34, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$x, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%esi, 32(%esp)
	movl	$36, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 46 3                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:46:3
	movl	y, %esi
	movl	$36, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%esi, 28(%esp)
	.loc	1 47 3                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:47:3
	movl	32(%esp), %eax
	movl	%esi, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$.L.str1, (%esp)
	calll	printf
	xorb	%al, %al
	.loc	1 48 3                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:48:3
	cmpl	$1, 32(%esp)
	jne	.LBB1_2
# BB#1:                                 # %land.rhs
	cmpl	$0, 28(%esp)
	sete	%al
.Ltmp18:
.LBB1_2:                                # %land.end
	movzbl	%al, %eax
	.loc	1 49 1                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:49:1
	addl	$40, %esp
	popl	%esi
	ret
.Ltmp19:
.Ltmp20:
	.size	P1, .Ltmp20-P1
.Lfunc_end1:
.Ltmp21:
	.cfi_endproc
.Leh_func_end1:

	.globl	P2
	.align	16, 0x90
	.type	P2,@function
P2:                                     # @P2
.Ltmp24:
	.cfi_startproc
.Lfunc_begin2:
	.loc	1 52 0                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:52:0
# BB#0:                                 # %entry
	pushl	%esi
.Ltmp25:
	.cfi_def_cfa_offset 8
	subl	$40, %esp
.Ltmp26:
	.cfi_def_cfa_offset 48
.Ltmp27:
	.cfi_offset %esi, -8
	movl	48(%esp), %eax
	movl	%eax, 36(%esp)
	movl	$58, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$y, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 54 3 prologue_end     # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:54:3
.Ltmp28:
	movl	$1, y
	movl	$58, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$y, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$59, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 55 3                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:55:3
	movl	y, %esi
	movl	$59, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%esi, 32(%esp)
	movl	$61, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$z, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 56 3                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:56:3
	movl	z, %esi
	movl	$61, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$z, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%esi, 28(%esp)
	.loc	1 57 3                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:57:3
	movl	32(%esp), %eax
	movl	%esi, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$.L.str2, (%esp)
	calll	printf
	xorb	%al, %al
	.loc	1 58 3                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:58:3
	cmpl	$1, 32(%esp)
	jne	.LBB2_2
# BB#1:                                 # %land.rhs
	cmpl	$0, 28(%esp)
	sete	%al
.Ltmp29:
.LBB2_2:                                # %land.end
	movzbl	%al, %eax
	.loc	1 59 1                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:59:1
	addl	$40, %esp
	popl	%esi
	ret
.Ltmp30:
.Ltmp31:
	.size	P2, .Ltmp31-P2
.Lfunc_end2:
.Ltmp32:
	.cfi_endproc
.Leh_func_end2:

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
.Ltmp34:
	.cfi_startproc
.Lfunc_begin3:
	.loc	1 62 0                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:62:0
# BB#0:                                 # %entry
	subl	$44, %esp
.Ltmp35:
	.cfi_def_cfa_offset 48
	movl	$0, 40(%esp)
	leal	36(%esp), %eax
	.loc	1 66 3 prologue_end     # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:66:3
.Ltmp36:
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$P1, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	leal	32(%esp), %eax
	.loc	1 67 3                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:67:3
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$P0, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	leal	28(%esp), %eax
	.loc	1 68 3                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:68:3
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$P2, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	.loc	1 70 3                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:70:3
	movl	36(%esp), %eax
	leal	24(%esp), %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	calll	clap_thread_join
	.loc	1 71 3                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:71:3
	movl	32(%esp), %eax
	leal	20(%esp), %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	calll	clap_thread_join
	.loc	1 72 3                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:72:3
	movl	28(%esp), %eax
	leal	16(%esp), %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	calll	clap_thread_join
	.loc	1 75 3                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:75:3
	cmpl	$0, 24(%esp)
	je	.LBB3_4
# BB#1:                                 # %land.lhs.true
	cmpl	$0, 20(%esp)
	je	.LBB3_4
# BB#2:                                 # %land.lhs.true7
	cmpl	$0, 16(%esp)
	je	.LBB3_4
# BB#3:                                 # %if.then
	.loc	1 76 5                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:76:5
.Ltmp37:
	movl	$.L.str3, (%esp)
	calll	printf
	.loc	1 77 5                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:77:5
	movl	$.L.str4, (%esp)
	calll	printf
.Ltmp38:
.LBB3_4:                                # %if.end
	xorl	%eax, %eax
	.loc	1 80 3                  # ../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c:80:3
	addl	$44, %esp
	ret
.Ltmp39:
.Ltmp40:
	.size	main, .Ltmp40-main
.Lfunc_end3:
.Ltmp41:
	.cfi_endproc
.Leh_func_end3:

	.type	z,@object               # @z
	.comm	z,4,4
	.type	x,@object               # @x
	.comm	x,4,4
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	 "\n %%%% (EAX0=%d, EBX0=%d) %%%%\n"
	.size	.L.str, 32

	.type	y,@object               # @y
	.comm	y,4,4
	.type	.L.str1,@object         # @.str1
.L.str1:
	.asciz	 "\n %%%% (EAX1=%d, EBX1=%d) %%%%\n"
	.size	.L.str1, 32

	.type	.L.str2,@object         # @.str2
.L.str2:
	.asciz	 "\n %%%% (EAX2=%d, EBX2=%d) %%%%\n"
	.size	.L.str2, 32

	.type	.L.str3,@object         # @.str3
.L.str3:
	.asciz	 "\n@@@CLAP: There is a SC violation! \n"
	.size	.L.str3, 37

	.type	.L.str4,@object         # @.str4
.L.str4:
	.asciz	 "\033[1;31m SC Violation!!! \033[0m\n"
	.size	.L.str4, 30

	.cfi_sections .debug_frame
	.text
.Ltext_end:
	.data
.Ldata_end:
	.text
.Lsection_end1:
	.section	.debug_info,"",@progbits
.Linfo_begin1:
	.long	638                     # Length of Compilation Unit Info
	.short	2                       # DWARF version number
	.long	.Labbrev_begin          # Offset Into Abbrev. Section
	.byte	4                       # Address Size (in bytes)
	.byte	1                       # Abbrev [1] 0xb:0x277 DW_TAG_compile_unit
	.ascii	 "clang version 3.0 (tags/RELEASE_30/final)" # DW_AT_producer
	.byte	0
	.short	12                      # DW_AT_language
	.ascii	 "../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c" # DW_AT_name
	.byte	0
	.long	0                       # DW_AT_entry_pc
	.long	.Lsection_line          # DW_AT_stmt_list
	.ascii	 "/home/naling/src/inspect-0.3" # DW_AT_comp_dir
	.byte	0
	.byte	2                       # Abbrev [2] 0xa9:0xc DW_TAG_base_type
	.ascii	 "long int"             # DW_AT_name
	.byte	0
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	3                       # Abbrev [3] 0xb5:0x10 DW_TAG_variable
	.byte	120                     # DW_AT_name
	.byte	0
	.long	169                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	29                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	x
	.byte	3                       # Abbrev [3] 0xc5:0x10 DW_TAG_variable
	.byte	121                     # DW_AT_name
	.byte	0
	.long	169                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	29                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	y
	.byte	3                       # Abbrev [3] 0xd5:0x10 DW_TAG_variable
	.byte	122                     # DW_AT_name
	.byte	0
	.long	169                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	29                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	z
	.byte	4                       # Abbrev [4] 0xe5:0x50 DW_TAG_subprogram
	.long	309                     # DW_AT_sibling
	.ascii	 "P0"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	32                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	309                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin0           # DW_AT_low_pc
	.long	.Lfunc_end0             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	5                       # Abbrev [5] 0x100:0xe DW_TAG_formal_parameter
	.ascii	 "arg"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	31                      # DW_AT_decl_line
	.long	309                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	6                       # Abbrev [6] 0x10e:0x26 DW_TAG_lexical_block
	.long	.Ltmp6                  # DW_AT_low_pc
	.long	.Ltmp7                  # DW_AT_high_pc
	.byte	7                       # Abbrev [7] 0x117:0xe DW_TAG_variable
	.ascii	 "EAX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	33                      # DW_AT_decl_line
	.long	169                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	7                       # Abbrev [7] 0x125:0xe DW_TAG_variable
	.ascii	 "EBX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	33                      # DW_AT_decl_line
	.long	169                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	28
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	8                       # Abbrev [8] 0x135:0x2 DW_TAG_pointer_type
	.byte	4                       # DW_AT_byte_size
	.byte	4                       # Abbrev [4] 0x137:0x50 DW_TAG_subprogram
	.long	391                     # DW_AT_sibling
	.ascii	 "P1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	42                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	309                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin1           # DW_AT_low_pc
	.long	.Lfunc_end1             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	5                       # Abbrev [5] 0x152:0xe DW_TAG_formal_parameter
	.ascii	 "arg"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	41                      # DW_AT_decl_line
	.long	309                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	6                       # Abbrev [6] 0x160:0x26 DW_TAG_lexical_block
	.long	.Ltmp17                 # DW_AT_low_pc
	.long	.Ltmp18                 # DW_AT_high_pc
	.byte	7                       # Abbrev [7] 0x169:0xe DW_TAG_variable
	.ascii	 "EAX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	43                      # DW_AT_decl_line
	.long	169                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	7                       # Abbrev [7] 0x177:0xe DW_TAG_variable
	.ascii	 "EBX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	43                      # DW_AT_decl_line
	.long	169                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	28
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	4                       # Abbrev [4] 0x187:0x50 DW_TAG_subprogram
	.long	471                     # DW_AT_sibling
	.ascii	 "P2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	52                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	309                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin2           # DW_AT_low_pc
	.long	.Lfunc_end2             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	5                       # Abbrev [5] 0x1a2:0xe DW_TAG_formal_parameter
	.ascii	 "arg"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	51                      # DW_AT_decl_line
	.long	309                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	6                       # Abbrev [6] 0x1b0:0x26 DW_TAG_lexical_block
	.long	.Ltmp28                 # DW_AT_low_pc
	.long	.Ltmp29                 # DW_AT_high_pc
	.byte	7                       # Abbrev [7] 0x1b9:0xe DW_TAG_variable
	.ascii	 "EAX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	53                      # DW_AT_decl_line
	.long	169                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	7                       # Abbrev [7] 0x1c7:0xe DW_TAG_variable
	.ascii	 "EBX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	53                      # DW_AT_decl_line
	.long	169                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	28
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	4                       # Abbrev [4] 0x1d7:0x7f DW_TAG_subprogram
	.long	598                     # DW_AT_sibling
	.ascii	 "main"                 # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	62                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	598                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin3           # DW_AT_low_pc
	.long	.Lfunc_end3             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	6                       # Abbrev [6] 0x1f4:0x61 DW_TAG_lexical_block
	.long	.Ltmp36                 # DW_AT_low_pc
	.long	.Ltmp39                 # DW_AT_high_pc
	.byte	7                       # Abbrev [7] 0x1fd:0xd DW_TAG_variable
	.ascii	 "t0"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	63                      # DW_AT_decl_line
	.long	626                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	7                       # Abbrev [7] 0x20a:0xd DW_TAG_variable
	.ascii	 "t1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	63                      # DW_AT_decl_line
	.long	626                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	7                       # Abbrev [7] 0x217:0xd DW_TAG_variable
	.ascii	 "t2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	63                      # DW_AT_decl_line
	.long	626                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	28
	.byte	7                       # Abbrev [7] 0x224:0x10 DW_TAG_variable
	.ascii	 "cond0"                # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	64                      # DW_AT_decl_line
	.long	169                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	24
	.byte	7                       # Abbrev [7] 0x234:0x10 DW_TAG_variable
	.ascii	 "cond1"                # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	64                      # DW_AT_decl_line
	.long	169                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	20
	.byte	7                       # Abbrev [7] 0x244:0x10 DW_TAG_variable
	.ascii	 "cond2"                # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	64                      # DW_AT_decl_line
	.long	169                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	16
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	2                       # Abbrev [2] 0x256:0x7 DW_TAG_base_type
	.ascii	 "int"                  # DW_AT_name
	.byte	0
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	2                       # Abbrev [2] 0x25d:0x15 DW_TAG_base_type
	.ascii	 "long unsigned int"    # DW_AT_name
	.byte	0
	.byte	7                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	9                       # Abbrev [9] 0x272:0xf DW_TAG_typedef
	.long	605                     # DW_AT_type
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
	.long	229                     # DIE offset
	.asciz	 "P0"                   # External Name
	.long	311                     # DIE offset
	.asciz	 "P1"                   # External Name
	.long	391                     # DIE offset
	.asciz	 "P2"                   # External Name
	.long	471                     # DIE offset
	.asciz	 "main"                 # External Name
	.long	181                     # DIE offset
	.asciz	 "x"                    # External Name
	.long	197                     # DIE offset
	.asciz	 "y"                    # External Name
	.long	213                     # DIE offset
	.asciz	 "z"                    # External Name
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
