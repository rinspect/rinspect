	.file	"/home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c.lz.opt.bc"
	.file	1 "/home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c"
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
	.loc	1 26 0                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:26:0
# BB#0:                                 # %entry
	subl	$28, %esp
.Ltmp2:
	.cfi_def_cfa_offset 32
	movl	$3, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$2, 8(%esp)
	movl	$y, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 28 4 prologue_end     # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:28:4
.Ltmp3:
	movl	$2, y
	movl	$3, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$2, 8(%esp)
	movl	$y, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$4, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$x, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 29 4                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:29:4
	movl	$1, x
	movl	$4, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$x, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	xorl	%eax, %eax
	.loc	1 31 4                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:31:4
	addl	$28, %esp
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
.Ltmp11:
	.cfi_startproc
.Lfunc_begin1:
	.loc	1 34 0                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:34:0
# BB#0:                                 # %entry
	.loc	1 42 15 prologue_end    # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:42:15
	pushl	%ebx
.Ltmp12:
	.cfi_def_cfa_offset 8
	pushl	%edi
.Ltmp13:
	.cfi_def_cfa_offset 12
	pushl	%esi
.Ltmp14:
	.cfi_def_cfa_offset 16
	subl	$48, %esp
.Ltmp15:
	.cfi_def_cfa_offset 64
.Ltmp16:
	.cfi_offset %esi, -16
.Ltmp17:
	.cfi_offset %edi, -12
.Ltmp18:
	.cfi_offset %ebx, -8
	movl	$8, (%esp)
	calll	malloc
	movl	%eax, 36(%esp)
	movl	$15, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$2, 8(%esp)
	movl	$x, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 44 5                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:44:5
	movl	$2, x
	movl	$15, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$2, 8(%esp)
	movl	$x, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$16, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$y, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	.loc	1 45 5                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:45:5
	movl	$1, y
	movl	$16, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1, 8(%esp)
	movl	$y, 4(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$17, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 47 5                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:47:5
	movl	y, %esi
	movl	$17, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	36(%esp), %edi
	movl	%esi, 8(%esp)
	movl	%edi, 4(%esp)
	movl	$20, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	movl	%esi, (%edi)
	movl	%esi, 8(%esp)
	movl	%edi, 4(%esp)
	movl	$20, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	movl	$21, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 48 5                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:48:5
	movl	y, %esi
	movl	$21, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	36(%esp), %ebx
	movl	%esi, 8(%esp)
	leal	4(%ebx), %edi
	movl	%edi, 4(%esp)
	movl	$24, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$5, (%esp)
	calll	clap_store_pre
	movl	%esi, 4(%ebx)
	movl	%esi, 8(%esp)
	movl	%edi, 4(%esp)
	movl	$24, 20(%esp)
	movl	$32, 16(%esp)
	movl	$0, 12(%esp)
	movl	$5, (%esp)
	calll	clap_store_post
	.loc	1 50 5                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:50:5
	movl	36(%esp), %eax
	addl	$48, %esp
	popl	%esi
	popl	%edi
	popl	%ebx
	ret
.Ltmp19:
.Ltmp20:
	.size	P1, .Ltmp20-P1
.Lfunc_end1:
.Ltmp21:
	.cfi_endproc
.Leh_func_end1:

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
.Ltmp25:
	.cfi_startproc
.Lfunc_begin2:
	.loc	1 55 0                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:55:0
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
	movl	$0, 48(%esp)
	leal	44(%esp), %eax
	.loc	1 66 5 prologue_end     # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:66:5
.Ltmp31:
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$P0, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	leal	40(%esp), %eax
	.loc	1 67 5                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:67:5
	movl	%eax, (%esp)
	movl	$0, 12(%esp)
	movl	$P1, 8(%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_create
	.loc	1 71 5                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:71:5
	movl	44(%esp), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	calll	clap_thread_join
	.loc	1 72 5                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:72:5
	movl	40(%esp), %eax
	leal	28(%esp), %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	calll	clap_thread_join
	.loc	1 74 5                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:74:5
	movl	28(%esp), %esi
	movl	%esi, 4(%esp)
	movl	$49, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	movl	(%esi), %edi
	movl	%esi, 4(%esp)
	movl	$49, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%edi, 36(%esp)
	.loc	1 75 5                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:75:5
	movl	28(%esp), %edi
	leal	4(%edi), %esi
	movl	%esi, 4(%esp)
	movl	$53, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	movl	4(%edi), %edi
	movl	%esi, 4(%esp)
	movl	$53, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	movl	%edi, 32(%esp)
	movl	$55, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$x, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	.loc	1 76 5                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:76:5
	movl	x, %esi
	movl	$55, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$x, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	cmpl	$2, %esi
	jne	.LBB2_5
# BB#1:                                 # %land.lhs.true
	movl	$58, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_pre
	movl	y, %esi
	movl	$58, 16(%esp)
	movl	$32, 12(%esp)
	movl	$0, 8(%esp)
	movl	$y, 4(%esp)
	movl	$4, (%esp)
	calll	clap_load_post
	cmpl	$2, %esi
	jne	.LBB2_5
# BB#2:                                 # %land.lhs.true5
	cmpl	$1, 36(%esp)
	jne	.LBB2_5
# BB#3:                                 # %land.lhs.true7
	cmpl	$1, 32(%esp)
	jne	.LBB2_5
# BB#4:                                 # %if.then
	.loc	1 77 3                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:77:3
.Ltmp32:
	movl	$.L.str, (%esp)
	calll	printf
	.loc	1 78 3                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:78:3
	movl	$.L.str1, (%esp)
	calll	printf
.Ltmp33:
.LBB2_5:                                # %if.end
	.loc	1 80 5                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:80:5
	movl	36(%esp), %eax
	movl	32(%esp), %ecx
	movl	%ecx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$.L.str2, (%esp)
	calll	printf
	xorl	%eax, %eax
	.loc	1 81 5                  # /home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c:81:5
	addl	$52, %esp
	popl	%esi
	popl	%edi
	ret
.Ltmp34:
.Ltmp35:
	.size	main, .Ltmp35-main
.Lfunc_end2:
.Ltmp36:
	.cfi_endproc
.Leh_func_end2:

	.type	y,@object               # @y
	.comm	y,4,4
	.type	x,@object               # @x
	.comm	x,4,4
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	 "@@@CLAP: There is a SC violation! \n"
	.size	.L.str, 36

	.type	.L.str1,@object         # @.str1
.L.str1:
	.asciz	 "\033[1;31m  SC Violation!!!  \033[0m\n"
	.size	.L.str1, 32

	.type	.L.str2,@object         # @.str2
.L.str2:
	.asciz	 "\n%%%%%%%% EAX0=%ld, EBX=%ld,  %%%%%%%% \n"
	.size	.L.str2, 41

	.cfi_sections .debug_frame
	.text
.Ltext_end:
	.data
.Ldata_end:
	.text
.Lsection_end1:
	.section	.debug_info,"",@progbits
.Linfo_begin1:
	.long	618                     # Length of Compilation Unit Info
	.short	2                       # DWARF version number
	.long	.Labbrev_begin          # Offset Into Abbrev. Section
	.byte	4                       # Address Size (in bytes)
	.byte	1                       # Abbrev [1] 0xb:0x263 DW_TAG_compile_unit
	.ascii	 "clang version 3.0 (tags/RELEASE_30/final)" # DW_AT_producer
	.byte	0
	.short	12                      # DW_AT_language
	.ascii	 "/home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c" # DW_AT_name
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
	.byte	120                     # DW_AT_name
	.byte	0
	.long	159                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	22                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	x
	.byte	3                       # Abbrev [3] 0xbb:0x10 DW_TAG_variable
	.byte	121                     # DW_AT_name
	.byte	0
	.long	159                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	23                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.long	y
	.byte	4                       # Abbrev [4] 0xcb:0x34 DW_TAG_subprogram
	.long	255                     # DW_AT_sibling
	.ascii	 "P0"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	26                      # DW_AT_decl_line
	.long	255                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin0           # DW_AT_low_pc
	.long	.Lfunc_end0             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	5                       # Abbrev [5] 0xe5:0x19 DW_TAG_lexical_block
	.long	.Ltmp3                  # DW_AT_low_pc
	.long	.Ltmp4                  # DW_AT_high_pc
	.byte	6                       # Abbrev [6] 0xee:0xf DW_TAG_variable
	.ascii	 "EAX0"                 # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	27                      # DW_AT_decl_line
	.long	159                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	24
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	7                       # Abbrev [7] 0xff:0x2 DW_TAG_pointer_type
	.byte	4                       # DW_AT_byte_size
	.byte	4                       # Abbrev [4] 0x101:0x89 DW_TAG_subprogram
	.long	394                     # DW_AT_sibling
	.ascii	 "P1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	34                      # DW_AT_decl_line
	.long	255                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin1           # DW_AT_low_pc
	.long	.Lfunc_end1             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	8                       # Abbrev [8] 0x11b:0x2e DW_TAG_structure_type
	.long	329                     # DW_AT_sibling
	.ascii	 "tmp_ex"               # DW_AT_name
	.byte	0
	.byte	8                       # DW_AT_byte_size
	.byte	1                       # DW_AT_decl_file
	.byte	37                      # DW_AT_decl_line
	.byte	9                       # Abbrev [9] 0x12a:0xf DW_TAG_member
	.ascii	 "eax"                  # DW_AT_name
	.byte	0
	.long	159                     # DW_AT_type
	.byte	1                       # DW_AT_decl_file
	.byte	38                      # DW_AT_decl_line
	.byte	2                       # DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	9                       # Abbrev [9] 0x139:0xf DW_TAG_member
	.ascii	 "ebx"                  # DW_AT_name
	.byte	0
	.long	159                     # DW_AT_type
	.byte	1                       # DW_AT_decl_file
	.byte	39                      # DW_AT_decl_line
	.byte	2                       # DW_AT_data_member_location
	.byte	35
	.byte	4
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	10                      # Abbrev [10] 0x149:0xe DW_TAG_typedef
	.long	283                     # DW_AT_type
	.ascii	 "Values"               # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	40                      # DW_AT_decl_line
	.byte	5                       # Abbrev [5] 0x157:0x32 DW_TAG_lexical_block
	.long	.Lfunc_begin1           # DW_AT_low_pc
	.long	.Ltmp19                 # DW_AT_high_pc
	.byte	6                       # Abbrev [6] 0x160:0xe DW_TAG_variable
	.ascii	 "EAX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	35                      # DW_AT_decl_line
	.long	159                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	44
	.byte	6                       # Abbrev [6] 0x16e:0xe DW_TAG_variable
	.ascii	 "EBX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	36                      # DW_AT_decl_line
	.long	159                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	40
	.byte	6                       # Abbrev [6] 0x17c:0xc DW_TAG_variable
	.byte	116                     # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	42                      # DW_AT_decl_line
	.long	573                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	11                      # Abbrev [11] 0x18a:0xac DW_TAG_subprogram
	.long	566                     # DW_AT_sibling
	.ascii	 "main"                 # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	55                      # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	566                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.long	.Lfunc_begin2           # DW_AT_low_pc
	.long	.Lfunc_end2             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	84
	.byte	1                       # DW_AT_APPLE_omit_frame_ptr
	.byte	8                       # Abbrev [8] 0x1a7:0x2e DW_TAG_structure_type
	.long	469                     # DW_AT_sibling
	.ascii	 "tmp_ex"               # DW_AT_name
	.byte	0
	.byte	8                       # DW_AT_byte_size
	.byte	1                       # DW_AT_decl_file
	.byte	59                      # DW_AT_decl_line
	.byte	9                       # Abbrev [9] 0x1b6:0xf DW_TAG_member
	.ascii	 "eax"                  # DW_AT_name
	.byte	0
	.long	159                     # DW_AT_type
	.byte	1                       # DW_AT_decl_file
	.byte	60                      # DW_AT_decl_line
	.byte	2                       # DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	9                       # Abbrev [9] 0x1c5:0xf DW_TAG_member
	.ascii	 "ebx"                  # DW_AT_name
	.byte	0
	.long	159                     # DW_AT_type
	.byte	1                       # DW_AT_decl_file
	.byte	61                      # DW_AT_decl_line
	.byte	2                       # DW_AT_data_member_location
	.byte	35
	.byte	4
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	10                      # Abbrev [10] 0x1d5:0xe DW_TAG_typedef
	.long	423                     # DW_AT_type
	.ascii	 "Values"               # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	62                      # DW_AT_decl_line
	.byte	5                       # Abbrev [5] 0x1e3:0x52 DW_TAG_lexical_block
	.long	.Ltmp31                 # DW_AT_low_pc
	.long	.Ltmp34                 # DW_AT_high_pc
	.byte	6                       # Abbrev [6] 0x1ec:0xd DW_TAG_variable
	.ascii	 "t1"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	56                      # DW_AT_decl_line
	.long	600                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	44
	.byte	6                       # Abbrev [6] 0x1f9:0xd DW_TAG_variable
	.ascii	 "t2"                   # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	56                      # DW_AT_decl_line
	.long	600                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	40
	.byte	6                       # Abbrev [6] 0x206:0xe DW_TAG_variable
	.ascii	 "EAX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	57                      # DW_AT_decl_line
	.long	159                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	36
	.byte	6                       # Abbrev [6] 0x214:0xe DW_TAG_variable
	.ascii	 "EBX"                  # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	57                      # DW_AT_decl_line
	.long	159                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.byte	6                       # Abbrev [6] 0x222:0x12 DW_TAG_variable
	.ascii	 "tmp_num"              # DW_AT_name
	.byte	0
	.byte	1                       # DW_AT_decl_file
	.byte	64                      # DW_AT_decl_line
	.long	615                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	28
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	2                       # Abbrev [2] 0x236:0x7 DW_TAG_base_type
	.ascii	 "int"                  # DW_AT_name
	.byte	0
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	12                      # Abbrev [12] 0x23d:0x6 DW_TAG_pointer_type
	.long	329                     # DW_AT_type
	.byte	4                       # DW_AT_byte_size
	.byte	2                       # Abbrev [2] 0x243:0x15 DW_TAG_base_type
	.ascii	 "long unsigned int"    # DW_AT_name
	.byte	0
	.byte	7                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	13                      # Abbrev [13] 0x258:0xf DW_TAG_typedef
	.long	579                     # DW_AT_type
	.ascii	 "pthread_t"            # DW_AT_name
	.byte	0
	.byte	12                      # Abbrev [12] 0x267:0x6 DW_TAG_pointer_type
	.long	469                     # DW_AT_type
	.byte	4                       # DW_AT_byte_size
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
	.byte	19                      # DW_TAG_structure_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	1                       # DW_AT_sibling
	.byte	19                      # DW_FORM_ref4
	.byte	3                       # DW_AT_name
	.byte	8                       # DW_FORM_string
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	9                       # Abbreviation Code
	.byte	13                      # DW_TAG_member
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	8                       # DW_FORM_string
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	56                      # DW_AT_data_member_location
	.byte	10                      # DW_FORM_block1
	.byte	50                      # DW_AT_accessibility
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
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	11                      # Abbreviation Code
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
	.byte	12                      # Abbreviation Code
	.byte	15                      # DW_TAG_pointer_type
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	13                      # Abbreviation Code
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
	.long	203                     # DIE offset
	.asciz	 "P0"                   # External Name
	.long	257                     # DIE offset
	.asciz	 "P1"                   # External Name
	.long	394                     # DIE offset
	.asciz	 "main"                 # External Name
	.long	171                     # DIE offset
	.asciz	 "x"                    # External Name
	.long	187                     # DIE offset
	.asciz	 "y"                    # External Name
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
