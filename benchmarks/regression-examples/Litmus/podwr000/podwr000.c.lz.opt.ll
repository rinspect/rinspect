; ModuleID = '/home/naling/src/examples/tso/regression-examples/podwr000/podwr000.c.lz.opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%union.pthread_attr_t = type { i32, [32 x i8] }

@y = common global i32 0, align 4
@x = common global i32 0, align 4
@.str = private unnamed_addr constant [36 x i8] c"@@@CLAP: There is a SC violation !\0A\00", align 1
@.str1 = private unnamed_addr constant [32 x i8] c"\1B[1;31m  SC Violation!!!  \1B[0m\0A\00", align 1
@.str2 = private unnamed_addr constant [40 x i8] c"\0A%%%%%%%% EAX0=%ld, EAX1=%ld %%%%%%%% \0A\00", align 1

define i8* @P0(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !22
  %EAX0 = alloca i32, align 4, !clap !23
  store i8* %arg, i8** %arg.addr, align 4, !clap !24
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !25), !dbg !26, !clap !27
  call void @llvm.dbg.declare(metadata !{i32* %EAX0}, metadata !28), !dbg !30, !clap !31
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 6)
  store i32 1, i32* @y, align 4, !dbg !32, !clap !33
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 6)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 7)
  %tmp = load i32* @x, align 4, !dbg !34, !clap !35
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 7)
  store i32 %tmp, i32* %EAX0, align 4, !dbg !34, !clap !36
  %tmp1 = load i32* %EAX0, align 4, !dbg !37, !clap !38
  %tmp2 = inttoptr i32 %tmp1 to i8*, !dbg !37, !clap !39
  ret i8* %tmp2, !dbg !37, !clap !40
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

define i8* @P1(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !41
  %EAX1 = alloca i32, align 4, !clap !42
  store i8* %arg, i8** %arg.addr, align 4, !clap !43
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !44), !dbg !45, !clap !46
  call void @llvm.dbg.declare(metadata !{i32* %EAX1}, metadata !47), !dbg !49, !clap !50
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 17)
  store i32 1, i32* @x, align 4, !dbg !51, !clap !52
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 17)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 18)
  %tmp = load i32* @y, align 4, !dbg !53, !clap !54
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 18)
  store i32 %tmp, i32* %EAX1, align 4, !dbg !53, !clap !55
  %tmp1 = load i32* %EAX1, align 4, !dbg !56, !clap !57
  %tmp2 = inttoptr i32 %tmp1 to i8*, !dbg !56, !clap !58
  ret i8* %tmp2, !dbg !56, !clap !59
}

define i32 @main() nounwind {
entry:
  %retval = alloca i32, align 4, !clap !60
  %t0 = alloca i32, align 4, !clap !61
  %t1 = alloca i32, align 4, !clap !62
  %EAX0 = alloca i32, align 4, !clap !63
  %EAX1 = alloca i32, align 4, !clap !64
  store i32 0, i32* %retval, !clap !65
  call void @llvm.dbg.declare(metadata !{i32* %t0}, metadata !66), !dbg !70, !clap !71
  call void @llvm.dbg.declare(metadata !{i32* %t1}, metadata !72), !dbg !73, !clap !74
  call void @llvm.dbg.declare(metadata !{i32* %EAX0}, metadata !75), !dbg !76, !clap !77
  call void @llvm.dbg.declare(metadata !{i32* %EAX1}, metadata !78), !dbg !79, !clap !80
  %call = call i32 @clap_thread_create(i32* %t0, %union.pthread_attr_t* null, i8* (i8*)* @P0, i8* null) nounwind, !dbg !81, !clap !82
  %call1 = call i32 @clap_thread_create(i32* %t1, %union.pthread_attr_t* null, i8* (i8*)* @P1, i8* null) nounwind, !dbg !83, !clap !84
  %tmp = load i32* %t0, align 4, !dbg !85, !clap !86
  %tmp1 = bitcast i32* %EAX0 to i8**, !dbg !85, !clap !87
  %call2 = call i32 @clap_thread_join(i32 %tmp, i8** %tmp1), !dbg !85, !clap !88
  %tmp2 = load i32* %t1, align 4, !dbg !89, !clap !90
  %tmp3 = bitcast i32* %EAX1 to i8**, !dbg !89, !clap !91
  %call3 = call i32 @clap_thread_join(i32 %tmp2, i8** %tmp3), !dbg !89, !clap !92
  %tmp4 = load i32* %EAX0, align 4, !dbg !93, !clap !94
  %cmp = icmp eq i32 %tmp4, 0, !dbg !93, !clap !95
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !93, !clap !96

land.lhs.true:                                    ; preds = %entry
  %tmp5 = load i32* %EAX1, align 4, !dbg !93, !clap !97
  %cmp4 = icmp eq i32 %tmp5, 0, !dbg !93, !clap !98
  br i1 %cmp4, label %if.then, label %if.end, !dbg !93, !clap !99

if.then:                                          ; preds = %land.lhs.true
  %call5 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([36 x i8]* @.str, i32 0, i32 0)), !dbg !100, !clap !102
  %call6 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([32 x i8]* @.str1, i32 0, i32 0)), !dbg !103, !clap !104
  br label %if.end, !dbg !105, !clap !106

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  %tmp6 = load i32* %EAX0, align 4, !dbg !107, !clap !108
  %tmp7 = load i32* %EAX1, align 4, !dbg !107, !clap !109
  %call7 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([40 x i8]* @.str2, i32 0, i32 0), i32 %tmp6, i32 %tmp7), !dbg !107, !clap !110
  ret i32 0, !dbg !111, !clap !112
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

!0 = metadata !{i32 720913, i32 0, i32 12, metadata !"/home/naling/src/examples/tso/regression-examples/podwr000/podwr000.c", metadata !"/home/naling/src/inspect-0.3", metadata !"clang version 3.0 (tags/RELEASE_30/final)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !17} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !12, metadata !13}
!5 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P0", metadata !"P0", metadata !"", metadata !6, i32 28, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P0, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 720937, metadata !"/home/naling/src/examples/tso/regression-examples/podwr000/podwr000.c", metadata !"/home/naling/src/inspect-0.3", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{metadata !9}
!9 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ]
!10 = metadata !{metadata !11}
!11 = metadata !{i32 720932}                      ; [ DW_TAG_base_type ]
!12 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P1", metadata !"P1", metadata !"", metadata !6, i32 36, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P1, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!13 = metadata !{i32 720942, i32 0, metadata !6, metadata !"main", metadata !"main", metadata !"", metadata !6, i32 44, metadata !14, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i32 ()* @main, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!14 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !15, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!15 = metadata !{metadata !16}
!16 = metadata !{i32 720932, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!17 = metadata !{metadata !18}
!18 = metadata !{metadata !19, metadata !21}
!19 = metadata !{i32 720948, i32 0, null, metadata !"x", metadata !"x", metadata !"", metadata !6, i32 25, metadata !20, i32 0, i32 1, i32* @x} ; [ DW_TAG_variable ]
!20 = metadata !{i32 720932, null, metadata !"long int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!21 = metadata !{i32 720948, i32 0, null, metadata !"y", metadata !"y", metadata !"", metadata !6, i32 25, metadata !20, i32 0, i32 1, i32* @y} ; [ DW_TAG_variable ]
!22 = metadata !{i32 1}
!23 = metadata !{i32 2}
!24 = metadata !{i32 3}
!25 = metadata !{i32 721153, metadata !5, metadata !"arg", metadata !6, i32 16777243, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!26 = metadata !{i32 27, i32 16, metadata !5, null}
!27 = metadata !{i32 4}
!28 = metadata !{i32 721152, metadata !29, metadata !"EAX0", metadata !6, i32 29, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!29 = metadata !{i32 720907, metadata !5, i32 28, i32 1, metadata !6, i32 0} ; [ DW_TAG_lexical_block ]
!30 = metadata !{i32 29, i32 12, metadata !29, null}
!31 = metadata !{i32 5}
!32 = metadata !{i32 30, i32 3, metadata !29, null}
!33 = metadata !{i32 6}
!34 = metadata !{i32 31, i32 3, metadata !29, null}
!35 = metadata !{i32 7}
!36 = metadata !{i32 8}
!37 = metadata !{i32 32, i32 3, metadata !29, null}
!38 = metadata !{i32 9}
!39 = metadata !{i32 10}
!40 = metadata !{i32 11}
!41 = metadata !{i32 12}
!42 = metadata !{i32 13}
!43 = metadata !{i32 14}
!44 = metadata !{i32 721153, metadata !12, metadata !"arg", metadata !6, i32 16777251, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!45 = metadata !{i32 35, i32 16, metadata !12, null}
!46 = metadata !{i32 15}
!47 = metadata !{i32 721152, metadata !48, metadata !"EAX1", metadata !6, i32 37, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!48 = metadata !{i32 720907, metadata !12, i32 36, i32 1, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!49 = metadata !{i32 37, i32 12, metadata !48, null}
!50 = metadata !{i32 16}
!51 = metadata !{i32 38, i32 3, metadata !48, null}
!52 = metadata !{i32 17}
!53 = metadata !{i32 39, i32 3, metadata !48, null}
!54 = metadata !{i32 18}
!55 = metadata !{i32 19}
!56 = metadata !{i32 40, i32 3, metadata !48, null}
!57 = metadata !{i32 20}
!58 = metadata !{i32 21}
!59 = metadata !{i32 22}
!60 = metadata !{i32 23}
!61 = metadata !{i32 24}
!62 = metadata !{i32 25}
!63 = metadata !{i32 26}
!64 = metadata !{i32 27}
!65 = metadata !{i32 28}
!66 = metadata !{i32 721152, metadata !67, metadata !"t0", metadata !6, i32 45, metadata !68, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!67 = metadata !{i32 720907, metadata !13, i32 44, i32 1, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!68 = metadata !{i32 720918, null, metadata !"pthread_t", metadata !6, i32 60, i64 0, i64 0, i64 0, i32 0, metadata !69} ; [ DW_TAG_typedef ]
!69 = metadata !{i32 720932, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!70 = metadata !{i32 45, i32 13, metadata !67, null}
!71 = metadata !{i32 29}
!72 = metadata !{i32 721152, metadata !67, metadata !"t1", metadata !6, i32 45, metadata !68, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!73 = metadata !{i32 45, i32 17, metadata !67, null}
!74 = metadata !{i32 30}
!75 = metadata !{i32 721152, metadata !67, metadata !"EAX0", metadata !6, i32 46, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!76 = metadata !{i32 46, i32 12, metadata !67, null}
!77 = metadata !{i32 31}
!78 = metadata !{i32 721152, metadata !67, metadata !"EAX1", metadata !6, i32 46, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!79 = metadata !{i32 46, i32 18, metadata !67, null}
!80 = metadata !{i32 32}
!81 = metadata !{i32 48, i32 3, metadata !67, null}
!82 = metadata !{i32 33}
!83 = metadata !{i32 49, i32 3, metadata !67, null}
!84 = metadata !{i32 34}
!85 = metadata !{i32 51, i32 3, metadata !67, null}
!86 = metadata !{i32 35}
!87 = metadata !{i32 36}
!88 = metadata !{i32 37}
!89 = metadata !{i32 52, i32 3, metadata !67, null}
!90 = metadata !{i32 38}
!91 = metadata !{i32 39}
!92 = metadata !{i32 40}
!93 = metadata !{i32 55, i32 3, metadata !67, null}
!94 = metadata !{i32 41}
!95 = metadata !{i32 42}
!96 = metadata !{i32 43}
!97 = metadata !{i32 44}
!98 = metadata !{i32 45}
!99 = metadata !{i32 46}
!100 = metadata !{i32 56, i32 5, metadata !101, null}
!101 = metadata !{i32 720907, metadata !67, i32 55, i32 27, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!102 = metadata !{i32 47}
!103 = metadata !{i32 57, i32 5, metadata !101, null}
!104 = metadata !{i32 48}
!105 = metadata !{i32 58, i32 3, metadata !101, null}
!106 = metadata !{i32 49}
!107 = metadata !{i32 59, i32 3, metadata !67, null}
!108 = metadata !{i32 50}
!109 = metadata !{i32 51}
!110 = metadata !{i32 52}
!111 = metadata !{i32 61, i32 3, metadata !67, null}
!112 = metadata !{i32 53}
