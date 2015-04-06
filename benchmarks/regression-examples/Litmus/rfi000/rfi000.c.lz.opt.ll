; ModuleID = '/home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c.lz.opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%struct.tmp_ex = type { i32, i32 }
%struct.tmp_ex.0 = type { i32, i32 }
%union.pthread_attr_t = type { i32, [32 x i8] }

@y = common global i32 0, align 4
@x = common global i32 0, align 4
@.str = private unnamed_addr constant [36 x i8] c"@@@CLAP: There is a SC violation! \0A\00", align 1
@.str1 = private unnamed_addr constant [32 x i8] c"\1B[1;31m  SC Violation!!!  \1B[0m\0A\00", align 1
@.str2 = private unnamed_addr constant [41 x i8] c"\0A%%%%%%%% EAX0=%ld, EBX=%ld,  %%%%%%%% \0A\00", align 1

define i8* @P0() nounwind {
entry:
  %EAX0 = alloca i32, align 4, !clap !22
  call void @llvm.dbg.declare(metadata !{i32* %EAX0}, metadata !23), !dbg !25, !clap !26
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 2, i32 0, i32 32, i32 3)
  store i32 2, i32* @y, align 4, !dbg !27, !clap !28
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 2, i32 0, i32 32, i32 3)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 4)
  store i32 1, i32* @x, align 4, !dbg !29, !clap !30
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 4)
  ret i8* null, !dbg !31, !clap !32
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

define i8* @P1() nounwind {
entry:
  %EAX = alloca i32, align 4, !clap !33
  %EBX = alloca i32, align 4, !clap !34
  %t = alloca %struct.tmp_ex*, align 4, !clap !35
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !36), !dbg !38, !clap !39
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !40), !dbg !41, !clap !42
  call void @llvm.dbg.declare(metadata !{%struct.tmp_ex** %t}, metadata !43), !dbg !50, !clap !51
  %call = call i8* @malloc(i32 8), !dbg !52, !clap !53
  %tmp = bitcast i8* %call to %struct.tmp_ex*, !dbg !52, !clap !54
  store %struct.tmp_ex* %tmp, %struct.tmp_ex** %t, align 4, !dbg !52, !clap !55
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 2, i32 0, i32 32, i32 15)
  store i32 2, i32* @x, align 4, !dbg !56, !clap !57
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 2, i32 0, i32 32, i32 15)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 16)
  store i32 1, i32* @y, align 4, !dbg !58, !clap !59
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 16)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 17)
  %tmp1 = load i32* @y, align 4, !dbg !60, !clap !61
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 17)
  %tmp2 = load %struct.tmp_ex** %t, align 4, !dbg !60, !clap !62
  %eax = getelementptr inbounds %struct.tmp_ex* %tmp2, i32 0, i32 0, !dbg !60, !clap !63
  call void (i32, ...)* @clap_store_pre(i32 5, i32* %eax, i32 %tmp1, i32 0, i32 32, i32 20)
  store i32 %tmp1, i32* %eax, align 4, !dbg !60, !clap !64
  call void (i32, ...)* @clap_store_post(i32 5, i32* %eax, i32 %tmp1, i32 0, i32 32, i32 20)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 21)
  %tmp3 = load i32* @y, align 4, !dbg !65, !clap !66
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 21)
  %tmp4 = load %struct.tmp_ex** %t, align 4, !dbg !65, !clap !67
  %ebx = getelementptr inbounds %struct.tmp_ex* %tmp4, i32 0, i32 1, !dbg !65, !clap !68
  call void (i32, ...)* @clap_store_pre(i32 5, i32* %ebx, i32 %tmp3, i32 0, i32 32, i32 24)
  store i32 %tmp3, i32* %ebx, align 4, !dbg !65, !clap !69
  call void (i32, ...)* @clap_store_post(i32 5, i32* %ebx, i32 %tmp3, i32 0, i32 32, i32 24)
  %tmp5 = load %struct.tmp_ex** %t, align 4, !dbg !70, !clap !71
  %tmp6 = bitcast %struct.tmp_ex* %tmp5 to i8*, !dbg !70, !clap !72
  ret i8* %tmp6, !dbg !70, !clap !73
}

declare i8* @malloc(i32)

define i32 @main() nounwind {
entry:
  %retval = alloca i32, align 4, !clap !74
  %t1 = alloca i32, align 4, !clap !75
  %t2 = alloca i32, align 4, !clap !76
  %EAX = alloca i32, align 4, !clap !77
  %EBX = alloca i32, align 4, !clap !78
  %tmp_num = alloca %struct.tmp_ex.0*, align 4, !clap !79
  store i32 0, i32* %retval, !clap !80
  call void @llvm.dbg.declare(metadata !{i32* %t1}, metadata !81), !dbg !85, !clap !86
  call void @llvm.dbg.declare(metadata !{i32* %t2}, metadata !87), !dbg !88, !clap !89
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !90), !dbg !91, !clap !92
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !93), !dbg !94, !clap !95
  call void @llvm.dbg.declare(metadata !{%struct.tmp_ex.0** %tmp_num}, metadata !96), !dbg !103, !clap !104
  %call = call i32 @clap_thread_create(i32* %t1, %union.pthread_attr_t* null, i8* (i8*)* bitcast (i8* ()* @P0 to i8* (i8*)*), i8* null) nounwind, !dbg !105, !clap !106
  %call1 = call i32 @clap_thread_create(i32* %t2, %union.pthread_attr_t* null, i8* (i8*)* bitcast (i8* ()* @P1 to i8* (i8*)*), i8* null) nounwind, !dbg !107, !clap !108
  %tmp = load i32* %t1, align 4, !dbg !109, !clap !110
  %call2 = call i32 @clap_thread_join(i32 %tmp, i8** null), !dbg !109, !clap !111
  %tmp1 = load i32* %t2, align 4, !dbg !112, !clap !113
  %tmp2 = bitcast %struct.tmp_ex.0** %tmp_num to i8**, !dbg !112, !clap !114
  %call3 = call i32 @clap_thread_join(i32 %tmp1, i8** %tmp2), !dbg !112, !clap !115
  %tmp3 = load %struct.tmp_ex.0** %tmp_num, align 4, !dbg !116, !clap !117
  %eax = getelementptr inbounds %struct.tmp_ex.0* %tmp3, i32 0, i32 0, !dbg !116, !clap !118
  call void (i32, ...)* @clap_load_pre(i32 4, i32* %eax, i32 0, i32 32, i32 49)
  %tmp4 = load i32* %eax, align 4, !dbg !116, !clap !119
  call void (i32, ...)* @clap_load_post(i32 4, i32* %eax, i32 0, i32 32, i32 49)
  store i32 %tmp4, i32* %EAX, align 4, !dbg !116, !clap !120
  %tmp5 = load %struct.tmp_ex.0** %tmp_num, align 4, !dbg !121, !clap !122
  %ebx = getelementptr inbounds %struct.tmp_ex.0* %tmp5, i32 0, i32 1, !dbg !121, !clap !123
  call void (i32, ...)* @clap_load_pre(i32 4, i32* %ebx, i32 0, i32 32, i32 53)
  %tmp6 = load i32* %ebx, align 4, !dbg !121, !clap !124
  call void (i32, ...)* @clap_load_post(i32 4, i32* %ebx, i32 0, i32 32, i32 53)
  store i32 %tmp6, i32* %EBX, align 4, !dbg !121, !clap !125
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 55)
  %tmp7 = load i32* @x, align 4, !dbg !126, !clap !127
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 55)
  %cmp = icmp eq i32 %tmp7, 2, !dbg !126, !clap !128
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !126, !clap !129

land.lhs.true:                                    ; preds = %entry
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 58)
  %tmp8 = load i32* @y, align 4, !dbg !126, !clap !130
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 58)
  %cmp4 = icmp eq i32 %tmp8, 2, !dbg !126, !clap !131
  br i1 %cmp4, label %land.lhs.true5, label %if.end, !dbg !126, !clap !132

land.lhs.true5:                                   ; preds = %land.lhs.true
  %tmp9 = load i32* %EAX, align 4, !dbg !126, !clap !133
  %cmp6 = icmp eq i32 %tmp9, 1, !dbg !126, !clap !134
  br i1 %cmp6, label %land.lhs.true7, label %if.end, !dbg !126, !clap !135

land.lhs.true7:                                   ; preds = %land.lhs.true5
  %tmp10 = load i32* %EBX, align 4, !dbg !126, !clap !136
  %cmp8 = icmp eq i32 %tmp10, 1, !dbg !126, !clap !137
  br i1 %cmp8, label %if.then, label %if.end, !dbg !126, !clap !138

if.then:                                          ; preds = %land.lhs.true7
  %call9 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([36 x i8]* @.str, i32 0, i32 0)), !dbg !139, !clap !141
  %call10 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([32 x i8]* @.str1, i32 0, i32 0)), !dbg !142, !clap !143
  br label %if.end, !dbg !144, !clap !145

if.end:                                           ; preds = %if.then, %land.lhs.true7, %land.lhs.true5, %land.lhs.true, %entry
  %tmp11 = load i32* %EAX, align 4, !dbg !146, !clap !147
  %tmp12 = load i32* %EBX, align 4, !dbg !146, !clap !148
  %call11 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([41 x i8]* @.str2, i32 0, i32 0), i32 %tmp11, i32 %tmp12), !dbg !146, !clap !149
  ret i32 0, !dbg !150, !clap !151
}

declare i32 @clap_thread_create(i32*, %union.pthread_attr_t*, i8* (i8*)*, i8*) nounwind

declare i32 @clap_thread_join(i32, i8**)

declare i32 @printf(i8*, ...)

declare void @clap_load_pre(i32, ...)

declare void @clap_load_post(i32, ...)

declare void @clap_store_pre(i32, ...)

declare void @clap_store_post(i32, ...)

declare void @clap_cmpxchg_pre(i32, ...)

declare void @clap_cmpxchg_post(i32, ...)

declare void @clap_atomicrmw_pre(i32, ...)

declare void @clap_atomicrmw_post(i32, ...)

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 720913, i32 0, i32 12, metadata !"/home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c", metadata !"/home/naling/src/inspect-0.3", metadata !"clang version 3.0 (tags/RELEASE_30/final)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !17} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !12, metadata !13}
!5 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P0", metadata !"P0", metadata !"", metadata !6, i32 26, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 0, i1 false, i8* ()* @P0, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 720937, metadata !"/home/naling/src/examples/tso/regression-examples/rfi000/rfi000.c", metadata !"/home/naling/src/inspect-0.3", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{metadata !9}
!9 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ]
!10 = metadata !{metadata !11}
!11 = metadata !{i32 720932}                      ; [ DW_TAG_base_type ]
!12 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P1", metadata !"P1", metadata !"", metadata !6, i32 34, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 0, i1 false, i8* ()* @P1, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!13 = metadata !{i32 720942, i32 0, metadata !6, metadata !"main", metadata !"main", metadata !"", metadata !6, i32 55, metadata !14, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i32 ()* @main, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!14 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !15, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!15 = metadata !{metadata !16}
!16 = metadata !{i32 720932, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!17 = metadata !{metadata !18}
!18 = metadata !{metadata !19, metadata !21}
!19 = metadata !{i32 720948, i32 0, null, metadata !"x", metadata !"x", metadata !"", metadata !6, i32 22, metadata !20, i32 0, i32 1, i32* @x} ; [ DW_TAG_variable ]
!20 = metadata !{i32 720932, null, metadata !"long int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!21 = metadata !{i32 720948, i32 0, null, metadata !"y", metadata !"y", metadata !"", metadata !6, i32 23, metadata !20, i32 0, i32 1, i32* @y} ; [ DW_TAG_variable ]
!22 = metadata !{i32 1}
!23 = metadata !{i32 721152, metadata !24, metadata !"EAX0", metadata !6, i32 27, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!24 = metadata !{i32 720907, metadata !5, i32 26, i32 1, metadata !6, i32 0} ; [ DW_TAG_lexical_block ]
!25 = metadata !{i32 27, i32 14, metadata !24, null}
!26 = metadata !{i32 2}
!27 = metadata !{i32 28, i32 4, metadata !24, null}
!28 = metadata !{i32 3}
!29 = metadata !{i32 29, i32 4, metadata !24, null}
!30 = metadata !{i32 4}
!31 = metadata !{i32 31, i32 4, metadata !24, null}
!32 = metadata !{i32 5}
!33 = metadata !{i32 6}
!34 = metadata !{i32 7}
!35 = metadata !{i32 8}
!36 = metadata !{i32 721152, metadata !37, metadata !"EAX", metadata !6, i32 35, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!37 = metadata !{i32 720907, metadata !12, i32 34, i32 1, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!38 = metadata !{i32 35, i32 14, metadata !37, null}
!39 = metadata !{i32 9}
!40 = metadata !{i32 721152, metadata !37, metadata !"EBX", metadata !6, i32 36, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!41 = metadata !{i32 36, i32 14, metadata !37, null}
!42 = metadata !{i32 10}
!43 = metadata !{i32 721152, metadata !37, metadata !"t", metadata !6, i32 42, metadata !44, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!44 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, metadata !45} ; [ DW_TAG_pointer_type ]
!45 = metadata !{i32 720918, metadata !12, metadata !"Values", metadata !6, i32 40, i64 0, i64 0, i64 0, i32 0, metadata !46} ; [ DW_TAG_typedef ]
!46 = metadata !{i32 720915, metadata !12, metadata !"tmp_ex", metadata !6, i32 37, i64 64, i64 32, i32 0, i32 0, i32 0, metadata !47, i32 0, i32 0} ; [ DW_TAG_structure_type ]
!47 = metadata !{metadata !48, metadata !49}
!48 = metadata !{i32 720909, metadata !46, metadata !"eax", metadata !6, i32 38, i64 32, i64 32, i64 0, i32 0, metadata !20} ; [ DW_TAG_member ]
!49 = metadata !{i32 720909, metadata !46, metadata !"ebx", metadata !6, i32 39, i64 32, i64 32, i64 32, i32 0, metadata !20} ; [ DW_TAG_member ]
!50 = metadata !{i32 42, i32 13, metadata !37, null}
!51 = metadata !{i32 11}
!52 = metadata !{i32 42, i32 15, metadata !37, null}
!53 = metadata !{i32 12}
!54 = metadata !{i32 13}
!55 = metadata !{i32 14}
!56 = metadata !{i32 44, i32 5, metadata !37, null}
!57 = metadata !{i32 15}
!58 = metadata !{i32 45, i32 5, metadata !37, null}
!59 = metadata !{i32 16}
!60 = metadata !{i32 47, i32 5, metadata !37, null}
!61 = metadata !{i32 17}
!62 = metadata !{i32 18}
!63 = metadata !{i32 19}
!64 = metadata !{i32 20}
!65 = metadata !{i32 48, i32 5, metadata !37, null}
!66 = metadata !{i32 21}
!67 = metadata !{i32 22}
!68 = metadata !{i32 23}
!69 = metadata !{i32 24}
!70 = metadata !{i32 50, i32 5, metadata !37, null}
!71 = metadata !{i32 25}
!72 = metadata !{i32 26}
!73 = metadata !{i32 27}
!74 = metadata !{i32 28}
!75 = metadata !{i32 29}
!76 = metadata !{i32 30}
!77 = metadata !{i32 31}
!78 = metadata !{i32 32}
!79 = metadata !{i32 33}
!80 = metadata !{i32 34}
!81 = metadata !{i32 721152, metadata !82, metadata !"t1", metadata !6, i32 56, metadata !83, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!82 = metadata !{i32 720907, metadata !13, i32 55, i32 1, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!83 = metadata !{i32 720918, null, metadata !"pthread_t", metadata !6, i32 60, i64 0, i64 0, i64 0, i32 0, metadata !84} ; [ DW_TAG_typedef ]
!84 = metadata !{i32 720932, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!85 = metadata !{i32 56, i32 15, metadata !82, null}
!86 = metadata !{i32 35}
!87 = metadata !{i32 721152, metadata !82, metadata !"t2", metadata !6, i32 56, metadata !83, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!88 = metadata !{i32 56, i32 19, metadata !82, null}
!89 = metadata !{i32 36}
!90 = metadata !{i32 721152, metadata !82, metadata !"EAX", metadata !6, i32 57, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!91 = metadata !{i32 57, i32 14, metadata !82, null}
!92 = metadata !{i32 37}
!93 = metadata !{i32 721152, metadata !82, metadata !"EBX", metadata !6, i32 57, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!94 = metadata !{i32 57, i32 19, metadata !82, null}
!95 = metadata !{i32 38}
!96 = metadata !{i32 721152, metadata !82, metadata !"tmp_num", metadata !6, i32 64, metadata !97, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!97 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, metadata !98} ; [ DW_TAG_pointer_type ]
!98 = metadata !{i32 720918, metadata !13, metadata !"Values", metadata !6, i32 62, i64 0, i64 0, i64 0, i32 0, metadata !99} ; [ DW_TAG_typedef ]
!99 = metadata !{i32 720915, metadata !13, metadata !"tmp_ex", metadata !6, i32 59, i64 64, i64 32, i32 0, i32 0, i32 0, metadata !100, i32 0, i32 0} ; [ DW_TAG_structure_type ]
!100 = metadata !{metadata !101, metadata !102}
!101 = metadata !{i32 720909, metadata !99, metadata !"eax", metadata !6, i32 60, i64 32, i64 32, i64 0, i32 0, metadata !20} ; [ DW_TAG_member ]
!102 = metadata !{i32 720909, metadata !99, metadata !"ebx", metadata !6, i32 61, i64 32, i64 32, i64 32, i32 0, metadata !20} ; [ DW_TAG_member ]
!103 = metadata !{i32 64, i32 13, metadata !82, null}
!104 = metadata !{i32 39}
!105 = metadata !{i32 66, i32 5, metadata !82, null}
!106 = metadata !{i32 40}
!107 = metadata !{i32 67, i32 5, metadata !82, null}
!108 = metadata !{i32 41}
!109 = metadata !{i32 71, i32 5, metadata !82, null}
!110 = metadata !{i32 42}
!111 = metadata !{i32 43}
!112 = metadata !{i32 72, i32 5, metadata !82, null}
!113 = metadata !{i32 44}
!114 = metadata !{i32 45}
!115 = metadata !{i32 46}
!116 = metadata !{i32 74, i32 5, metadata !82, null}
!117 = metadata !{i32 47}
!118 = metadata !{i32 48}
!119 = metadata !{i32 49}
!120 = metadata !{i32 50}
!121 = metadata !{i32 75, i32 5, metadata !82, null}
!122 = metadata !{i32 51}
!123 = metadata !{i32 52}
!124 = metadata !{i32 53}
!125 = metadata !{i32 54}
!126 = metadata !{i32 76, i32 5, metadata !82, null}
!127 = metadata !{i32 55}
!128 = metadata !{i32 56}
!129 = metadata !{i32 57}
!130 = metadata !{i32 58}
!131 = metadata !{i32 59}
!132 = metadata !{i32 60}
!133 = metadata !{i32 61}
!134 = metadata !{i32 62}
!135 = metadata !{i32 63}
!136 = metadata !{i32 64}
!137 = metadata !{i32 65}
!138 = metadata !{i32 66}
!139 = metadata !{i32 77, i32 3, metadata !140, null}
!140 = metadata !{i32 720907, metadata !82, i32 76, i32 41, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!141 = metadata !{i32 67}
!142 = metadata !{i32 78, i32 3, metadata !140, null}
!143 = metadata !{i32 68}
!144 = metadata !{i32 79, i32 5, metadata !140, null}
!145 = metadata !{i32 69}
!146 = metadata !{i32 80, i32 5, metadata !82, null}
!147 = metadata !{i32 70}
!148 = metadata !{i32 71}
!149 = metadata !{i32 72}
!150 = metadata !{i32 81, i32 5, metadata !82, null}
!151 = metadata !{i32 73}
