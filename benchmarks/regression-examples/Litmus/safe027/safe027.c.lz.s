	.file	"../examples/tso/regression-examples/safe027/safe027.c.lz.opt.bc"
	.file	1 "/home/naling/src/inspect-0.3/../examples/tso/regression-examples/safe027/safe027.c"
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
.Ltmp0:
	.cfi_startproc
.Lfunc_begin0:
	.loc	1 30 0                  # ../examples/tso/regression-examples/safe027/safe027.c:30:0
# BB#0:                                 # %entry
	.loc	1 30 15 prologue_end    # ../examples/tso/regression-examples/safe027/safe027.c:30:15
	ret
.Ltmp1:
.Ltmp2:
	.size	MFENCE, .Ltmp2-MFENCE
.Lfunc_end0:
.Ltmp3:
	.cfi_endproc
.Leh_func_end0:

	.globl	P0
	.align	16, 0x90
	.type	P0,@function
P0:                                     # @P0
.Ltmp6:
	.cfi_startproc
.Lfunc_begin1:
	.loc	1 33 0                  # ../examples/tso/regression-examples/safe027/safe027.c:33:0
# BB#0:                                 # %entry
	pushl	%esi
.Ltmp7:
	.cfi_def_cfa_offset 8
	subl	$40, %esp
.Ltmp8:
	.cfi_def_cfa_offset 48
.Ltmp9:
	.cfi_offset %esi, -8
	movl	48(%esp), %eax
	movl	%eax, 36(%esp)
	movl	$9, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 35 3 prologue_end     # ../examples/tso/regression-examples/safe027/safe027.c:35:3
.Ltmp10:
	movl	y, %esi
	movl	$9, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%esi, 32(%esp)
	movl	$11, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$x, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 36 3                  # ../examples/tso/regression-examples/safe027/safe027.c:36:3
	movl	x, %esi
	movl	$11, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$x, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%esi, 28(%esp)
	.loc	1 37 3                  # ../examples/tso/regression-examples/safe027/safe027.c:37:3
	movl	32(%esp), %eax
	movl	%esi, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$.L.str, (%esp)
	calll	printf
	xorb	%al, %al
	.loc	1 38 3                  # ../examples/tso/regression-examples/safe027/safe027.c:38:3
	cmpl	$1, 32(%esp)
	jne	.LBB1_2
# BB#1:                                 # %land.rhs
	cmpl	$0, 28(%esp)
	sete	%al
.Ltmp11:
.LBB1_2:                                # %land.end
	movzbl	%al, %eax
	.loc	1 39 1                  # ../examples/tso/regression-examples/safe027/safe027.c:39:1
	addl	$40, %esp
	popl	%esi
	ret
.Ltmp12:
.Ltmp13:
	.size	P0, .Ltmp13-P0
.Lfunc_end1:
.Ltmp14:
	.cfi_endproc
.Leh_func_end1:

	.globl	P1
	.align	16, 0x90
	.type	P1,@function
P1:                                     # @P1
.Ltmp16:
	.cfi_startproc
.Lfunc_begin2:
	.loc	1 42 0                  # ../examples/tso/regression-examples/safe027/safe027.c:42:0
# BB#0:                                 # %entry
	subl	$44, %esp
.Ltmp17:
	.cfi_def_cfa_offset 48
	movl	48(%esp), %eax
	movl	%eax, 40(%esp)
	movl	$33, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$x, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 44 3 prologue_end     # ../examples/tso/regression-examples/safe027/safe027.c:44:3
.Ltmp18:
	movl	$1, x
	movl	$33, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$x, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$1, %eax
	.loc	1 45 3                  # ../examples/tso/regression-examples/safe027/safe027.c:45:3
	addl	$44, %esp
	ret
.Ltmp19:
.Ltmp20:
	.size	P1, .Ltmp20-P1
.Lfunc_end2:
.Ltmp21:
	.cfi_endproc
.Leh_func_end2:

	.globl	P2
	.align	16, 0x90
	.type	P2,@function
P2:                                     # @P2
.Ltmp24:
	.cfi_startproc
.Lfunc_begin3:
	.loc	1 49 0                  # ../examples/tso/regression-examples/safe027/safe027.c:49:0
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
	movl	$42, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$x, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 51 3 prologue_end     # ../examples/tso/regression-examples/safe027/safe027.c:51:3
.Ltmp28:
	movl	x, %esi
	movl	$42, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$x, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%esi, 32(%esp)
	movl	$44, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 52 3                  # ../examples/tso/regression-examples/safe027/safe027.c:52:3
	movl	y, %esi
	movl	$44, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%esi, 28(%esp)
	.loc	1 53 3                  # ../examples/tso/regression-examples/safe027/safe027.c:53:3
	movl	32(%esp), %eax
	movl	%esi, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$.L.str1, (%esp)
	calll	printf
	xorb	%al, %al
	.loc	1 54 3                  # ../examples/tso/regression-examples/safe027/safe027.c:54:3
	cmpl	$1, 32(%esp)
	jne	.LBB3_2
# BB#1:                                 # %land.rhs
	cmpl	$0, 28(%esp)
	sete	%al
.Ltmp29:
.LBB3_2:                                # %land.end
	movzbl	%al, %eax
	.loc	1 55 1                  # ../examples/tso/regression-examples/safe027/safe027.c:55:1
	addl	$40, %esp
	popl	%esi
	ret
.Ltmp30:
.Ltmp31:
	.size	P2, .Ltmp31-P2
.Lfunc_end3:
.Ltmp32:
	.cfi_endproc
.Leh_func_end3:

	.globl	P3
	.align	16, 0x90
	.type	P3,@function
P3:                                     # @P3
.Ltmp34:
	.cfi_startproc
.Lfunc_begin4:
	.loc	1 58 0                  # ../examples/tso/regression-examples/safe027/safe027.c:58:0
# BB#0:                                 # %entry
	subl	$44, %esp
.Ltmp35:
	.cfi_def_cfa_offset 48
	movl	48(%esp), %eax
	movl	%eax, 40(%esp)
	movl	$66, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$y, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 60 3 prologue_end     # ../examples/tso/regression-examples/safe027/safe027.c:60:3
.Ltmp36:
	movl	$1, y
	movl	$66, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$y, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$1, %eax
	.loc	1 61 3                  # ../examples/tso/regression-examples/safe027/safe027.c:61:3
	addl	$44, %esp
	ret
.Ltmp37:
.Ltmp38:
	.size	P3, .Ltmp38-P3
.Lfunc_end4:
.Ltmp39:
	.cfi_endproc
.Leh_func_end4:

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
.Ltmp41:
	.cfi_startproc
.Lfunc_begin5:
	.loc	1 65 0                  # ../examples/tso/regression-examples/safe027/safe027.c:65:0
# BB#0:                                 # %entry
	subl	$60, %esp
.Ltmp42:
	.cfi_def_cfa_offset 64
	movl	$0, 56(%esp)
	movl	$86, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 69 3 prologue_end     # ../examples/tso/regression-examples/safe027/safe027.c:69:3
.Ltmp43:
	movl	$0, y
	movl	$86, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$87, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$x, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	movl	$0, x
	movl	$87, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$x, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	leal	52(%esp), %eax
	.loc	1 71 3                  # ../examples/tso/regression-examples/safe027/safe027.c:71:3
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$P0, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	leal	48(%esp), %eax
	.loc	1 72 3                  # ../examples/tso/regression-examples/safe027/safe027.c:72:3
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$P1, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	leal	44(%esp), %eax
	.loc	1 73 3                  # ../examples/tso/regression-examples/safe027/safe027.c:73:3
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$P2, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	leal	40(%esp), %eax
	.loc	1 74 3                  # ../examples/tso/regression-examples/safe027/safe027.c:74:3
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$P3, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	.loc	1 76 3                  # ../examples/tso/regression-examples/safe027/safe027.c:76:3
	movl	52(%esp), %eax
	leal	36(%esp), %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	calll	clap_thread_join
	.loc	1 77 3                  # ../examples/tso/regression-examples/safe027/safe027.c:77:3
	movl	48(%esp), %eax
	leal	32(%esp), %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	calll	clap_thread_join
	.loc	1 78 3                  # ../examples/tso/regression-examples/safe027/safe027.c:78:3
	movl	44(%esp), %eax
	leal	28(%esp), %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	calll	clap_thread_join
	.loc	1 79 3                  # ../examples/tso/regression-examples/safe027/safe027.c:79:3
	movl	40(%esp), %eax
	leal	24(%esp), %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	calll	clap_thread_join
	.loc	1 82 3                  # ../examples/tso/regression-examples/safe027/safe027.c:82:3
	cmpl	$0, 36(%esp)
	je	.LBB5_3
# BB#1:                                 # %land.lhs.true
	cmpl	$0, 28(%esp)
	je	.LBB5_3
# BB#2:                                 # %if.then
	.loc	1 83 5                  # ../examples/tso/regression-examples/safe027/safe027.c:83:5
.Ltmp44:
	movl	$.L.str2, (%esp)
	calll	printf
	.loc	1 84 5                  # ../examples/tso/regression-examples/safe027/safe027.c:84:5
	movl	$.L.str3, (%esp)
	calll	printf
.Ltmp45:
.LBB5_3:                                # %if.end
	xorl	%eax, %eax
	.loc	1 87 3                  # ../examples/tso/regression-examples/safe027/safe027.c:87:3
	addl	$60, %esp
	ret
.Ltmp46:
.Ltmp47:
	.size	main, .Ltmp47-main
.Lfunc_end5:
.Ltmp48:
	.cfi_endproc
.Leh_func_end5:

	.type	y,@object               # @y
	.comm	y,4,4
	.type	x,@object               # @x
	.comm	x,4,4
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	 "\n (EAX0=%d, EBX0=%d) \n"
	.size	.L.str, 23

	.type	.L.str1,@object         # @.str1
.L.str1:
	.asciz	 "\n (EAX2=%d, EBX2=%d) \n"
	.size	.L.str1, 23

	.type	.L.str2,@object         # @.str2
.L.str2:
	.asciz	 "\n@@@CLAP: There is a SC violation! \n"
	.size	.L.str2, 37

	.type	.L.str3,@object         # @.str3
.L.str3:
	.asciz	 "\033[1;31m SC Violation!!! \033[0m\n"
	.size	.L.str3, 30

	.type	z,@object               # @z
	.comm	z,4,4
	.cfi_sections .debug_frame
	.text
.Ltext_end:
	.data
.Ldata_end:
	.text
.Lsection_end1:
	.section	.debug_info,"",@progbits
.Linfo_begin1:
	.long	747                     # Length of Compilation Unit Info
	.short	2                       # DWARF version number
	.long	.Labbrev_begin          # Offset Into Abbrev. Section
	.byte	4                       # Address Size (in bytes)
	.byte	1                       # Abbrev [1] 0xb:0x2e4 DW_TAG_compile_unit
	.ascii	 "clang version 3.0 (tags/RELEASE_30/final)" # DW_AT_producer
	.byte	0
	.short	12                      # DW_AT_language
	.ascii	 "../examples/tso/regression-examples/safe027/safe027.c" # DW_AT_name
	.byte	0
	.long	0                       # DW_AT_entry_pc
	.long	.Lsection_line          # DW_AT_stmt_list
	.ascii	 "/home/naling/src/inspect-0.3" # DW_AT_comp_dir
	.byte	0
	.byte	2                       # Abbrev [2] 0x93:0xc DW_TAG_base_type
	.ascii	 "long int"             # DW_AT_name
	.byte	0
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	3                       # Abbrev [3] 0x9f:0x10 DW_TAG_variable
	.byte	120                     # DW_AT_name
	.byte	0
	.long	147                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	28                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	x
	.byte	3                       # Abbrev [3] 0xaf:0x10 DW_TAG_variable
	.byte	121                     # DW_AT_name
	.byte	0
	.long	147                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	28                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	y
	.byte	3                       # Abbrev [3] 0xbf:0x10 DW_TAG_variable
	.byte	122                     # DW_AT_name
	.byte	0
	.long	147                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	28                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	z
	.byte	4                       # Abbrev [4] 0xcf:0x16 DW_TAG_subprogram
	.ascii	 "MFENCE"               # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	30                      # DW_AT_decl_line
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin0           # DW_AT_low_pc
	.long	.Lfunc_end0             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	5                       # Abbrev [5] 0xe5:0x50 DW_TAG_subprogram
	.long	309                     # DW_AT_sibling
	.ascii	 "P0"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	33                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	309                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin1           # DW_AT_low_pc
	.long	.Lfunc_end1             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	6                       # Abbrev [6] 0x100:0xe DW_TAG_formal_parameter
	.ascii	 "arg"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	32                      # DW_AT_decl_line
	.long	309                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	7                       # Abbrev [7] 0x10e:0x26 DW_TAG_lexical_block
	.long	.Ltmp10                 # DW_AT_low_pc
	.long	.Ltmp11                 # DW_AT_high_pc
	.byte	8                       # Abbrev [8] 0x117:0xe DW_TAG_variable
	.ascii	 "EAX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	34                      # DW_AT_decl_line
	.long	147                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	8                       # Abbrev [8] 0x125:0xe DW_TAG_variable
	.ascii	 "EBX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	34                      # DW_AT_decl_line
	.long	147                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	28
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	9                       # Abbrev [9] 0x135:0x2 DW_TAG_pointer_type
	.byte	4                       # DW_AT_byte_size
	.byte	5                       # Abbrev [5] 0x137:0x50 DW_TAG_subprogram
	.long	391                     # DW_AT_sibling
	.ascii	 "P1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	42                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	309                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin2           # DW_AT_low_pc
	.long	.Lfunc_end2             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	6                       # Abbrev [6] 0x152:0xe DW_TAG_formal_parameter
	.ascii	 "arg"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	41                      # DW_AT_decl_line
	.long	309                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	40
	.byte	7                       # Abbrev [7] 0x160:0x26 DW_TAG_lexical_block
	.long	.Ltmp18                 # DW_AT_low_pc
	.long	.Ltmp19                 # DW_AT_high_pc
	.byte	8                       # Abbrev [8] 0x169:0xe DW_TAG_variable
	.ascii	 "EAX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	43                      # DW_AT_decl_line
	.long	147                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	8                       # Abbrev [8] 0x177:0xe DW_TAG_variable
	.ascii	 "EBX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	43                      # DW_AT_decl_line
	.long	147                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x187:0x50 DW_TAG_subprogram
	.long	471                     # DW_AT_sibling
	.ascii	 "P2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	49                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	309                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin3           # DW_AT_low_pc
	.long	.Lfunc_end3             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	6                       # Abbrev [6] 0x1a2:0xe DW_TAG_formal_parameter
	.ascii	 "arg"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	48                      # DW_AT_decl_line
	.long	309                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	7                       # Abbrev [7] 0x1b0:0x26 DW_TAG_lexical_block
	.long	.Ltmp28                 # DW_AT_low_pc
	.long	.Ltmp29                 # DW_AT_high_pc
	.byte	8                       # Abbrev [8] 0x1b9:0xe DW_TAG_variable
	.ascii	 "EAX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	50                      # DW_AT_decl_line
	.long	147                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	8                       # Abbrev [8] 0x1c7:0xe DW_TAG_variable
	.ascii	 "EBX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	50                      # DW_AT_decl_line
	.long	147                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	28
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x1d7:0x50 DW_TAG_subprogram
	.long	551                     # DW_AT_sibling
	.ascii	 "P3"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	58                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	309                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin4           # DW_AT_low_pc
	.long	.Lfunc_end4             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	6                       # Abbrev [6] 0x1f2:0xe DW_TAG_formal_parameter
	.ascii	 "arg"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	57                      # DW_AT_decl_line
	.long	309                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	40
	.byte	7                       # Abbrev [7] 0x200:0x26 DW_TAG_lexical_block
	.long	.Ltmp36                 # DW_AT_low_pc
	.long	.Ltmp37                 # DW_AT_high_pc
	.byte	8                       # Abbrev [8] 0x209:0xe DW_TAG_variable
	.ascii	 "EAX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	59                      # DW_AT_decl_line
	.long	147                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	8                       # Abbrev [8] 0x217:0xe DW_TAG_variable
	.ascii	 "EBX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	59                      # DW_AT_decl_line
	.long	147                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x227:0x9c DW_TAG_subprogram
	.long	707                     # DW_AT_sibling
	.ascii	 "main"                 # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	65                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	707                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin5           # DW_AT_low_pc
	.long	.Lfunc_end5             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	7                       # Abbrev [7] 0x244:0x7e DW_TAG_lexical_block
	.long	.Ltmp43                 # DW_AT_low_pc
	.long	.Ltmp46                 # DW_AT_high_pc
	.byte	8                       # Abbrev [8] 0x24d:0xd DW_TAG_variable
	.ascii	 "t0"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	66                      # DW_AT_decl_line
	.long	735                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	52
	.byte	8                       # Abbrev [8] 0x25a:0xd DW_TAG_variable
	.ascii	 "t1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	66                      # DW_AT_decl_line
	.long	735                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	48
	.byte	8                       # Abbrev [8] 0x267:0xd DW_TAG_variable
	.ascii	 "t2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	66                      # DW_AT_decl_line
	.long	735                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	44
	.byte	8                       # Abbrev [8] 0x274:0xd DW_TAG_variable
	.ascii	 "t3"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	66                      # DW_AT_decl_line
	.long	735                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	40
	.byte	8                       # Abbrev [8] 0x281:0x10 DW_TAG_variable
	.ascii	 "cond0"                # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	67                      # DW_AT_decl_line
	.long	147                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	8                       # Abbrev [8] 0x291:0x10 DW_TAG_variable
	.ascii	 "cond1"                # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	67                      # DW_AT_decl_line
	.long	147                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	8                       # Abbrev [8] 0x2a1:0x10 DW_TAG_variable
	.ascii	 "cond2"                # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	67                      # DW_AT_decl_line
	.long	147                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	28
	.byte	8                       # Abbrev [8] 0x2b1:0x10 DW_TAG_variable
	.ascii	 "cond3"                # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	67                      # DW_AT_decl_line
	.long	147                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	24
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	2                       # Abbrev [2] 0x2c3:0x7 DW_TAG_base_type
	.ascii	 "int"                  # DW_AT_name
	.byte	0
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	2                       # Abbrev [2] 0x2ca:0x15 DW_TAG_base_type
	.ascii	 "long unsigned int"    # DW_AT_name
	.byte	0
	.byte	7                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	10                      # Abbrev [10] 0x2df:0xf DW_TAG_typedef
	.long	714                     # DW_AT_type
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
	.asciz	 "P3"                   # External Name
	.long	551                     # DIE offset
	.asciz	 "main"                 # External Name
	.long	159                     # DIE offset
	.asciz	 "x"                    # External Name
	.long	175                     # DIE offset
	.asciz	 "y"                    # External Name
	.long	191                     # DIE offset
	.asciz	 "z"                    # External Name
	.long	207                     # DIE offset
	.asciz	 "MFENCE"               # External Name
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
