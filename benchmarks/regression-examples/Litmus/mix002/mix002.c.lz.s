	.file	"/home/naling/src/examples/tso/regression-examples/mix002/mix002.c.lz.opt.bc"
	.file	1 "/home/naling/src/examples/tso/regression-examples/mix002/mix002.c"
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
	.loc	1 34 0                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:34:0
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
	movl	$a, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 36 3 prologue_end     # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:36:3
.Ltmp6:
	movl	$1, a
	movl	$8, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$a, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$9, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$x, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 37 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:37:3
	movl	$1, x
	movl	$9, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$x, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$10, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$x, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 38 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:38:3
	movl	x, %esi
	movl	$10, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$x, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%esi, 32(%esp)
	movl	$12, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 39 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:39:3
	movl	y, %esi
	movl	$12, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%esi, 28(%esp)
	.loc	1 40 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:40:3
	movl	32(%esp), %eax
	movl	%esi, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$.L.str, (%esp)
	calll	printf
	xorb	%al, %al
	.loc	1 41 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:41:3
	cmpl	$1, 32(%esp)
	jne	.LBB0_2
# BB#1:                                 # %land.rhs
	cmpl	$0, 28(%esp)
	sete	%al
.Ltmp7:
.LBB0_2:                                # %land.end
	movzbl	%al, %eax
	.loc	1 42 1                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:42:1
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
	.loc	1 45 0                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:45:0
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
	movl	$34, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$y, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 47 3 prologue_end     # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:47:3
.Ltmp17:
	movl	$1, y
	movl	$34, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$y, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$35, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 48 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:48:3
	movl	y, %esi
	movl	$35, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%esi, 32(%esp)
	movl	$37, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$z, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 49 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:49:3
	movl	z, %esi
	movl	$37, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$z, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%esi, 28(%esp)
	.loc	1 50 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:50:3
	movl	32(%esp), %eax
	movl	%esi, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$.L.str1, (%esp)
	calll	printf
	xorb	%al, %al
	.loc	1 51 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:51:3
	cmpl	$1, 32(%esp)
	jne	.LBB1_2
# BB#1:                                 # %land.rhs
	cmpl	$0, 28(%esp)
	sete	%al
.Ltmp18:
.LBB1_2:                                # %land.end
	movzbl	%al, %eax
	.loc	1 52 1                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:52:1
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
	.loc	1 55 0                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:55:0
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
	movl	$59, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$z, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 57 3 prologue_end     # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:57:3
.Ltmp28:
	movl	$1, z
	movl	$59, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$z, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$60, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$z, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 58 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:58:3
	movl	z, %esi
	movl	$60, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$z, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%esi, 32(%esp)
	movl	$62, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$a, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 59 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:59:3
	movl	a, %esi
	movl	$62, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$a, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%esi, 28(%esp)
	.loc	1 60 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:60:3
	movl	32(%esp), %eax
	movl	%esi, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$.L.str2, (%esp)
	calll	printf
	xorb	%al, %al
	.loc	1 61 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:61:3
	cmpl	$1, 32(%esp)
	jne	.LBB2_2
# BB#1:                                 # %land.rhs
	cmpl	$0, 28(%esp)
	sete	%al
.Ltmp29:
.LBB2_2:                                # %land.end
	movzbl	%al, %eax
	.loc	1 62 1                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:62:1
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
	.loc	1 65 0                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:65:0
# BB#0:                                 # %entry
	subl	$44, %esp
.Ltmp35:
	.cfi_def_cfa_offset 48
	movl	$0, 40(%esp)
	leal	36(%esp), %eax
	.loc	1 69 3 prologue_end     # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:69:3
.Ltmp36:
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$P0, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	leal	32(%esp), %eax
	.loc	1 70 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:70:3
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$P1, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	leal	28(%esp), %eax
	.loc	1 71 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:71:3
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$P2, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	.loc	1 73 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:73:3
	movl	36(%esp), %eax
	leal	24(%esp), %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	calll	clap_thread_join
	.loc	1 74 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:74:3
	movl	32(%esp), %eax
	leal	20(%esp), %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	calll	clap_thread_join
	.loc	1 75 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:75:3
	movl	28(%esp), %eax
	leal	16(%esp), %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	calll	clap_thread_join
	.loc	1 78 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:78:3
	cmpl	$0, 24(%esp)
	je	.LBB3_4
# BB#1:                                 # %land.lhs.true
	cmpl	$0, 20(%esp)
	je	.LBB3_4
# BB#2:                                 # %land.lhs.true7
	cmpl	$0, 16(%esp)
	je	.LBB3_4
# BB#3:                                 # %if.then
	.loc	1 79 5                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:79:5
.Ltmp37:
	movl	$.L.str3, (%esp)
	calll	printf
	.loc	1 80 5                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:80:5
	movl	$.L.str4, (%esp)
	calll	printf
.Ltmp38:
.LBB3_4:                                # %if.end
	xorl	%eax, %eax
	.loc	1 83 3                  # /home/naling/src/examples/tso/regression-examples/mix002/mix002.c:83:3
	addl	$44, %esp
	ret
.Ltmp39:
.Ltmp40:
	.size	main, .Ltmp40-main
.Lfunc_end3:
.Ltmp41:
	.cfi_endproc
.Leh_func_end3:

	.type	a,@object               # @a
	.comm	a,4,4
	.type	x,@object               # @x
	.comm	x,4,4
	.type	y,@object               # @y
	.comm	y,4,4
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	 "\n %%%% (EAX0=%d, EBX0=%d) %%%%\n"
	.size	.L.str, 32

	.type	z,@object               # @z
	.comm	z,4,4
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
	.long	644                     # Length of Compilation Unit Info
	.short	2                       # DWARF version number
	.long	.Labbrev_begin          # Offset Into Abbrev. Section
	.byte	4                       # Address Size (in bytes)
	.byte	1                       # Abbrev [1] 0xb:0x27d DW_TAG_compile_unit
	.ascii	 "clang version 3.0 (tags/RELEASE_30/final)" # DW_AT_producer
	.byte	0
	.short	12                      # DW_AT_language
	.ascii	 "/home/naling/src/examples/tso/regression-examples/mix002/mix002.c" # DW_AT_name
	.byte	0
	.long	0                       # DW_AT_entry_pc
	.long	.Lsection_line          # DW_AT_stmt_list
	.ascii	 "/home/naling/src/inspect-0.3" # DW_AT_comp_dir
	.byte	0
	.byte	2                       # Abbrev [2] 0x9f:0xc DW_TAG_base_type
	.ascii	 "long int"             # DW_AT_name
	.byte	0
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	3                       # Abbrev [3] 0xab:0x10 DW_TAG_variable
	.byte	97                      # DW_AT_name
	.byte	0
	.long	159                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	31                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	a
	.byte	3                       # Abbrev [3] 0xbb:0x10 DW_TAG_variable
	.byte	120                     # DW_AT_name
	.byte	0
	.long	159                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	31                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	x
	.byte	3                       # Abbrev [3] 0xcb:0x10 DW_TAG_variable
	.byte	121                     # DW_AT_name
	.byte	0
	.long	159                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	31                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	y
	.byte	3                       # Abbrev [3] 0xdb:0x10 DW_TAG_variable
	.byte	122                     # DW_AT_name
	.byte	0
	.long	159                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	31                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	z
	.byte	4                       # Abbrev [4] 0xeb:0x50 DW_TAG_subprogram
	.long	315                     # DW_AT_sibling
	.ascii	 "P0"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	34                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	315                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin0           # DW_AT_low_pc
	.long	.Lfunc_end0             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	5                       # Abbrev [5] 0x106:0xe DW_TAG_formal_parameter
	.ascii	 "arg"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	33                      # DW_AT_decl_line
	.long	315                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	6                       # Abbrev [6] 0x114:0x26 DW_TAG_lexical_block
	.long	.Ltmp6                  # DW_AT_low_pc
	.long	.Ltmp7                  # DW_AT_high_pc
	.byte	7                       # Abbrev [7] 0x11d:0xe DW_TAG_variable
	.ascii	 "EAX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	35                      # DW_AT_decl_line
	.long	159                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	7                       # Abbrev [7] 0x12b:0xe DW_TAG_variable
	.ascii	 "EBX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	35                      # DW_AT_decl_line
	.long	159                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	28
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	8                       # Abbrev [8] 0x13b:0x2 DW_TAG_pointer_type
	.byte	4                       # DW_AT_byte_size
	.byte	4                       # Abbrev [4] 0x13d:0x50 DW_TAG_subprogram
	.long	397                     # DW_AT_sibling
	.ascii	 "P1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	45                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	315                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin1           # DW_AT_low_pc
	.long	.Lfunc_end1             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	5                       # Abbrev [5] 0x158:0xe DW_TAG_formal_parameter
	.ascii	 "arg"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	44                      # DW_AT_decl_line
	.long	315                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	6                       # Abbrev [6] 0x166:0x26 DW_TAG_lexical_block
	.long	.Ltmp17                 # DW_AT_low_pc
	.long	.Ltmp18                 # DW_AT_high_pc
	.byte	7                       # Abbrev [7] 0x16f:0xe DW_TAG_variable
	.ascii	 "EAX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	46                      # DW_AT_decl_line
	.long	159                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	7                       # Abbrev [7] 0x17d:0xe DW_TAG_variable
	.ascii	 "EBX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	46                      # DW_AT_decl_line
	.long	159                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	28
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	4                       # Abbrev [4] 0x18d:0x50 DW_TAG_subprogram
	.long	477                     # DW_AT_sibling
	.ascii	 "P2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	55                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	315                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin2           # DW_AT_low_pc
	.long	.Lfunc_end2             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	5                       # Abbrev [5] 0x1a8:0xe DW_TAG_formal_parameter
	.ascii	 "arg"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	54                      # DW_AT_decl_line
	.long	315                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	6                       # Abbrev [6] 0x1b6:0x26 DW_TAG_lexical_block
	.long	.Ltmp28                 # DW_AT_low_pc
	.long	.Ltmp29                 # DW_AT_high_pc
	.byte	7                       # Abbrev [7] 0x1bf:0xe DW_TAG_variable
	.ascii	 "EAX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	56                      # DW_AT_decl_line
	.long	159                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	7                       # Abbrev [7] 0x1cd:0xe DW_TAG_variable
	.ascii	 "EBX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	56                      # DW_AT_decl_line
	.long	159                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	28
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	4                       # Abbrev [4] 0x1dd:0x7f DW_TAG_subprogram
	.long	604                     # DW_AT_sibling
	.ascii	 "main"                 # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	65                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	604                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin3           # DW_AT_low_pc
	.long	.Lfunc_end3             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	6                       # Abbrev [6] 0x1fa:0x61 DW_TAG_lexical_block
	.long	.Ltmp36                 # DW_AT_low_pc
	.long	.Ltmp39                 # DW_AT_high_pc
	.byte	7                       # Abbrev [7] 0x203:0xd DW_TAG_variable
	.ascii	 "t0"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	66                      # DW_AT_decl_line
	.long	632                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	7                       # Abbrev [7] 0x210:0xd DW_TAG_variable
	.ascii	 "t1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	66                      # DW_AT_decl_line
	.long	632                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	7                       # Abbrev [7] 0x21d:0xd DW_TAG_variable
	.ascii	 "t2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	66                      # DW_AT_decl_line
	.long	632                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	28
	.byte	7                       # Abbrev [7] 0x22a:0x10 DW_TAG_variable
	.ascii	 "cond0"                # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	67                      # DW_AT_decl_line
	.long	159                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	24
	.byte	7                       # Abbrev [7] 0x23a:0x10 DW_TAG_variable
	.ascii	 "cond1"                # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	67                      # DW_AT_decl_line
	.long	159                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	20
	.byte	7                       # Abbrev [7] 0x24a:0x10 DW_TAG_variable
	.ascii	 "cond2"                # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	67                      # DW_AT_decl_line
	.long	159                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	16
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	2                       # Abbrev [2] 0x25c:0x7 DW_TAG_base_type
	.ascii	 "int"                  # DW_AT_name
	.byte	0
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	2                       # Abbrev [2] 0x263:0x15 DW_TAG_base_type
	.ascii	 "long unsigned int"    # DW_AT_name
	.byte	0
	.byte	7                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	9                       # Abbrev [9] 0x278:0xf DW_TAG_typedef
	.long	611                     # DW_AT_type
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
	.long	235                     # DIE offset
	.asciz	 "P0"                   # External Name
	.long	171                     # DIE offset
	.asciz	 "a"                    # External Name
	.long	317                     # DIE offset
	.asciz	 "P1"                   # External Name
	.long	397                     # DIE offset
	.asciz	 "P2"                   # External Name
	.long	477                     # DIE offset
	.asciz	 "main"                 # External Name
	.long	187                     # DIE offset
	.asciz	 "x"                    # External Name
	.long	203                     # DIE offset
	.asciz	 "y"                    # External Name
	.long	219                     # DIE offset
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
