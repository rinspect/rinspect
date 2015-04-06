	.file	"../examples/tso/regression-examples/mix019/mix019.c.lz.opt.bc"
	.file	1 "/home/naling/src/inspect-0.3/../examples/tso/regression-examples/mix019/mix019.c"
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
.Ltmp1:
	.cfi_startproc
.Lfunc_begin0:
	.loc	1 32 0                  # ../examples/tso/regression-examples/mix019/mix019.c:32:0
# BB#0:                                 # %entry
	subl	$44, %esp
.Ltmp2:
	.cfi_def_cfa_offset 48
	movl	48(%esp), %eax
	movl	%eax, 40(%esp)
	movl	$8, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$z, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 34 3 prologue_end     # ../examples/tso/regression-examples/mix019/mix019.c:34:3
.Ltmp3:
	movl	$1, z
	movl	$8, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$z, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$9, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$x, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 35 3                  # ../examples/tso/regression-examples/mix019/mix019.c:35:3
	movl	$1, x
	movl	$9, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$x, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$1, %eax
	.loc	1 36 3                  # ../examples/tso/regression-examples/mix019/mix019.c:36:3
	addl	$44, %esp
	ret
.Ltmp4:
.Ltmp5:
	.size	P0, .Ltmp5-P0
.Lfunc_end0:
.Ltmp6:
	.cfi_endproc
.Leh_func_end0:

	.globl	P1
	.align	16, 0x90
	.type	P1,@function
P1:                                     # @P1
.Ltmp9:
	.cfi_startproc
.Lfunc_begin1:
	.loc	1 40 0                  # ../examples/tso/regression-examples/mix019/mix019.c:40:0
# BB#0:                                 # %entry
	pushl	%esi
.Ltmp10:
	.cfi_def_cfa_offset 8
	subl	$40, %esp
.Ltmp11:
	.cfi_def_cfa_offset 48
.Ltmp12:
	.cfi_offset %esi, -8
	movl	48(%esp), %eax
	movl	%eax, 36(%esp)
	movl	$18, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$2, 8(%esp)
	movl	$x, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 42 3 prologue_end     # ../examples/tso/regression-examples/mix019/mix019.c:42:3
.Ltmp13:
	movl	$2, x
	movl	$18, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$2, 8(%esp)
	movl	$x, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$19, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 43 3                  # ../examples/tso/regression-examples/mix019/mix019.c:43:3
	movl	y, %esi
	movl	$19, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%esi, 32(%esp)
	.loc	1 44 3                  # ../examples/tso/regression-examples/mix019/mix019.c:44:3
	movl	%esi, 4(%esp)
	movl	$.L.str, (%esp)
	calll	printf
	.loc	1 45 3                  # ../examples/tso/regression-examples/mix019/mix019.c:45:3
	cmpl	$0, 32(%esp)
	sete	%al
	movzbl	%al, %eax
	addl	$40, %esp
	popl	%esi
	ret
.Ltmp14:
.Ltmp15:
	.size	P1, .Ltmp15-P1
.Lfunc_end1:
.Ltmp16:
	.cfi_endproc
.Leh_func_end1:

	.globl	P2
	.align	16, 0x90
	.type	P2,@function
P2:                                     # @P2
.Ltmp19:
	.cfi_startproc
.Lfunc_begin2:
	.loc	1 49 0                  # ../examples/tso/regression-examples/mix019/mix019.c:49:0
# BB#0:                                 # %entry
	pushl	%esi
.Ltmp20:
	.cfi_def_cfa_offset 8
	subl	$40, %esp
.Ltmp21:
	.cfi_def_cfa_offset 48
.Ltmp22:
	.cfi_offset %esi, -8
	movl	48(%esp), %eax
	movl	%eax, 36(%esp)
	movl	$35, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$y, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 51 3 prologue_end     # ../examples/tso/regression-examples/mix019/mix019.c:51:3
.Ltmp23:
	movl	$1, y
	movl	$35, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$y, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$36, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 52 3                  # ../examples/tso/regression-examples/mix019/mix019.c:52:3
	movl	y, %esi
	movl	$36, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%esi, 32(%esp)
	movl	$38, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$z, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 53 3                  # ../examples/tso/regression-examples/mix019/mix019.c:53:3
	movl	z, %esi
	movl	$38, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$z, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%esi, 28(%esp)
	.loc	1 54 3                  # ../examples/tso/regression-examples/mix019/mix019.c:54:3
	movl	32(%esp), %eax
	movl	%esi, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$.L.str1, (%esp)
	calll	printf
	xorb	%al, %al
	.loc	1 55 3                  # ../examples/tso/regression-examples/mix019/mix019.c:55:3
	cmpl	$1, 32(%esp)
	jne	.LBB2_2
# BB#1:                                 # %land.rhs
	cmpl	$0, 28(%esp)
	sete	%al
.Ltmp24:
.LBB2_2:                                # %land.end
	movzbl	%al, %eax
	.loc	1 56 1                  # ../examples/tso/regression-examples/mix019/mix019.c:56:1
	addl	$40, %esp
	popl	%esi
	ret
.Ltmp25:
.Ltmp26:
	.size	P2, .Ltmp26-P2
.Lfunc_end2:
.Ltmp27:
	.cfi_endproc
.Leh_func_end2:

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
.Ltmp30:
	.cfi_startproc
.Lfunc_begin3:
	.loc	1 59 0                  # ../examples/tso/regression-examples/mix019/mix019.c:59:0
# BB#0:                                 # %entry
	pushl	%esi
.Ltmp31:
	.cfi_def_cfa_offset 8
	subl	$56, %esp
.Ltmp32:
	.cfi_def_cfa_offset 64
.Ltmp33:
	.cfi_offset %esi, -8
	movl	$0, 52(%esp)
	leal	48(%esp), %eax
	.loc	1 63 3 prologue_end     # ../examples/tso/regression-examples/mix019/mix019.c:63:3
.Ltmp34:
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$P0, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	leal	44(%esp), %eax
	.loc	1 64 3                  # ../examples/tso/regression-examples/mix019/mix019.c:64:3
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$P1, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	leal	40(%esp), %eax
	.loc	1 65 3                  # ../examples/tso/regression-examples/mix019/mix019.c:65:3
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$P2, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	.loc	1 67 3                  # ../examples/tso/regression-examples/mix019/mix019.c:67:3
	movl	48(%esp), %eax
	leal	32(%esp), %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	calll	clap_thread_join
	.loc	1 68 3                  # ../examples/tso/regression-examples/mix019/mix019.c:68:3
	movl	44(%esp), %eax
	leal	28(%esp), %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	calll	clap_thread_join
	.loc	1 69 3                  # ../examples/tso/regression-examples/mix019/mix019.c:69:3
	movl	40(%esp), %eax
	leal	24(%esp), %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	calll	clap_thread_join
	movl	$83, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$x, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 72 3                  # ../examples/tso/regression-examples/mix019/mix019.c:72:3
	movl	x, %esi
	movl	$83, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$x, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	cmpl	$2, %esi
	jne	.LBB3_4
# BB#1:                                 # %land.lhs.true
	cmpl	$0, 28(%esp)
	je	.LBB3_4
# BB#2:                                 # %land.lhs.true6
	cmpl	$0, 24(%esp)
	je	.LBB3_4
# BB#3:                                 # %if.then
	.loc	1 73 5                  # ../examples/tso/regression-examples/mix019/mix019.c:73:5
.Ltmp35:
	movl	$.L.str2, (%esp)
	calll	printf
	.loc	1 74 5                  # ../examples/tso/regression-examples/mix019/mix019.c:74:5
	movl	$.L.str3, (%esp)
	calll	printf
.Ltmp36:
.LBB3_4:                                # %if.end
	xorl	%eax, %eax
	.loc	1 77 3                  # ../examples/tso/regression-examples/mix019/mix019.c:77:3
	addl	$56, %esp
	popl	%esi
	ret
.Ltmp37:
.Ltmp38:
	.size	main, .Ltmp38-main
.Lfunc_end3:
.Ltmp39:
	.cfi_endproc
.Leh_func_end3:

	.type	z,@object               # @z
	.comm	z,4,4
	.type	x,@object               # @x
	.comm	x,4,4
	.type	y,@object               # @y
	.comm	y,4,4
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	 "\n %%%% (EAX1=%d) %%%%"
	.size	.L.str, 22

	.type	.L.str1,@object         # @.str1
.L.str1:
	.asciz	 "\n %%%% (EAX2=%d, EBX2=%d) %%%%"
	.size	.L.str1, 31

	.type	.L.str2,@object         # @.str2
.L.str2:
	.asciz	 "\n@@@CLAP: There is a SC violation! \n"
	.size	.L.str2, 37

	.type	.L.str3,@object         # @.str3
.L.str3:
	.asciz	 "\033[1;31m SC Violation!!! \033[0m\n"
	.size	.L.str3, 30

	.cfi_sections .debug_frame
	.text
.Ltext_end:
	.data
.Ldata_end:
	.text
.Lsection_end1:
	.section	.debug_info,"",@progbits
.Linfo_begin1:
	.long	643                     # Length of Compilation Unit Info
	.short	2                       # DWARF version number
	.long	.Labbrev_begin          # Offset Into Abbrev. Section
	.byte	4                       # Address Size (in bytes)
	.byte	1                       # Abbrev [1] 0xb:0x27c DW_TAG_compile_unit
	.ascii	 "clang version 3.0 (tags/RELEASE_30/final)" # DW_AT_producer
	.byte	0
	.short	12                      # DW_AT_language
	.ascii	 "../examples/tso/regression-examples/mix019/mix019.c" # DW_AT_name
	.byte	0
	.long	0                       # DW_AT_entry_pc
	.long	.Lsection_line          # DW_AT_stmt_list
	.ascii	 "/home/naling/src/inspect-0.3" # DW_AT_comp_dir
	.byte	0
	.byte	2                       # Abbrev [2] 0x91:0xc DW_TAG_base_type
	.ascii	 "long int"             # DW_AT_name
	.byte	0
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	3                       # Abbrev [3] 0x9d:0x10 DW_TAG_variable
	.byte	120                     # DW_AT_name
	.byte	0
	.long	145                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	29                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	x
	.byte	3                       # Abbrev [3] 0xad:0x10 DW_TAG_variable
	.byte	121                     # DW_AT_name
	.byte	0
	.long	145                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	29                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	y
	.byte	3                       # Abbrev [3] 0xbd:0x10 DW_TAG_variable
	.byte	122                     # DW_AT_name
	.byte	0
	.long	145                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	29                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	z
	.byte	4                       # Abbrev [4] 0xcd:0x50 DW_TAG_subprogram
	.long	285                     # DW_AT_sibling
	.ascii	 "P0"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	32                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	285                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin0           # DW_AT_low_pc
	.long	.Lfunc_end0             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	5                       # Abbrev [5] 0xe8:0xe DW_TAG_formal_parameter
	.ascii	 "arg"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	31                      # DW_AT_decl_line
	.long	285                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	40
	.byte	6                       # Abbrev [6] 0xf6:0x26 DW_TAG_lexical_block
	.long	.Ltmp3                  # DW_AT_low_pc
	.long	.Ltmp4                  # DW_AT_high_pc
	.byte	7                       # Abbrev [7] 0xff:0xe DW_TAG_variable
	.ascii	 "EAX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	33                      # DW_AT_decl_line
	.long	145                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	7                       # Abbrev [7] 0x10d:0xe DW_TAG_variable
	.ascii	 "EBX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	33                      # DW_AT_decl_line
	.long	145                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	8                       # Abbrev [8] 0x11d:0x2 DW_TAG_pointer_type
	.byte	4                       # DW_AT_byte_size
	.byte	4                       # Abbrev [4] 0x11f:0x50 DW_TAG_subprogram
	.long	367                     # DW_AT_sibling
	.ascii	 "P1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	40                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	285                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin1           # DW_AT_low_pc
	.long	.Lfunc_end1             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	5                       # Abbrev [5] 0x13a:0xe DW_TAG_formal_parameter
	.ascii	 "arg"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	39                      # DW_AT_decl_line
	.long	285                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	6                       # Abbrev [6] 0x148:0x26 DW_TAG_lexical_block
	.long	.Ltmp13                 # DW_AT_low_pc
	.long	.Ltmp14                 # DW_AT_high_pc
	.byte	7                       # Abbrev [7] 0x151:0xe DW_TAG_variable
	.ascii	 "EAX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	41                      # DW_AT_decl_line
	.long	145                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	7                       # Abbrev [7] 0x15f:0xe DW_TAG_variable
	.ascii	 "EBX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	41                      # DW_AT_decl_line
	.long	145                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	28
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	4                       # Abbrev [4] 0x16f:0x50 DW_TAG_subprogram
	.long	447                     # DW_AT_sibling
	.ascii	 "P2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	49                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	285                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin2           # DW_AT_low_pc
	.long	.Lfunc_end2             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	5                       # Abbrev [5] 0x18a:0xe DW_TAG_formal_parameter
	.ascii	 "arg"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	48                      # DW_AT_decl_line
	.long	285                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	6                       # Abbrev [6] 0x198:0x26 DW_TAG_lexical_block
	.long	.Ltmp23                 # DW_AT_low_pc
	.long	.Ltmp24                 # DW_AT_high_pc
	.byte	7                       # Abbrev [7] 0x1a1:0xe DW_TAG_variable
	.ascii	 "EAX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	50                      # DW_AT_decl_line
	.long	145                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	7                       # Abbrev [7] 0x1af:0xe DW_TAG_variable
	.ascii	 "EBX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	50                      # DW_AT_decl_line
	.long	145                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	28
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	4                       # Abbrev [4] 0x1bf:0x9c DW_TAG_subprogram
	.long	603                     # DW_AT_sibling
	.ascii	 "main"                 # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	59                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	603                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin3           # DW_AT_low_pc
	.long	.Lfunc_end3             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	6                       # Abbrev [6] 0x1dc:0x7e DW_TAG_lexical_block
	.long	.Ltmp34                 # DW_AT_low_pc
	.long	.Ltmp37                 # DW_AT_high_pc
	.byte	7                       # Abbrev [7] 0x1e5:0xd DW_TAG_variable
	.ascii	 "t0"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	60                      # DW_AT_decl_line
	.long	631                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	48
	.byte	7                       # Abbrev [7] 0x1f2:0xd DW_TAG_variable
	.ascii	 "t1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	60                      # DW_AT_decl_line
	.long	631                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	44
	.byte	7                       # Abbrev [7] 0x1ff:0xd DW_TAG_variable
	.ascii	 "t2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	60                      # DW_AT_decl_line
	.long	631                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	40
	.byte	7                       # Abbrev [7] 0x20c:0xd DW_TAG_variable
	.ascii	 "t3"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	60                      # DW_AT_decl_line
	.long	631                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	7                       # Abbrev [7] 0x219:0x10 DW_TAG_variable
	.ascii	 "cond0"                # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	61                      # DW_AT_decl_line
	.long	145                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	7                       # Abbrev [7] 0x229:0x10 DW_TAG_variable
	.ascii	 "cond1"                # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	61                      # DW_AT_decl_line
	.long	145                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	28
	.byte	7                       # Abbrev [7] 0x239:0x10 DW_TAG_variable
	.ascii	 "cond2"                # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	61                      # DW_AT_decl_line
	.long	145                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	24
	.byte	7                       # Abbrev [7] 0x249:0x10 DW_TAG_variable
	.ascii	 "cond3"                # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	61                      # DW_AT_decl_line
	.long	145                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	20
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	2                       # Abbrev [2] 0x25b:0x7 DW_TAG_base_type
	.ascii	 "int"                  # DW_AT_name
	.byte	0
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	2                       # Abbrev [2] 0x262:0x15 DW_TAG_base_type
	.ascii	 "long unsigned int"    # DW_AT_name
	.byte	0
	.byte	7                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	9                       # Abbrev [9] 0x277:0xf DW_TAG_typedef
	.long	610                     # DW_AT_type
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
	.long	205                     # DIE offset
	.asciz	 "P0"                   # External Name
	.long	287                     # DIE offset
	.asciz	 "P1"                   # External Name
	.long	367                     # DIE offset
	.asciz	 "P2"                   # External Name
	.long	447                     # DIE offset
	.asciz	 "main"                 # External Name
	.long	157                     # DIE offset
	.asciz	 "x"                    # External Name
	.long	173                     # DIE offset
	.asciz	 "y"                    # External Name
	.long	189                     # DIE offset
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
