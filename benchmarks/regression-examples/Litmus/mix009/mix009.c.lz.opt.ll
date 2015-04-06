; ModuleID = '../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix009/mix009.c.lz.opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%union.pthread_attr_t = type { i32, [32 x i8] }

@z = common global i32 0, align 4
@x = common global i32 0, align 4
@y = common global i32 0, align 4
@.str = private unnamed_addr constant [33 x i8] c"\0A %%%% (EAX0=%d, EBX0=%d) %%%% \0A\00", align 1
@.str1 = private unnamed_addr constant [33 x i8] c"\0A %%%% (EAX1=%d, EBX1=%d) %%%% \0A\00", align 1
@.str2 = private unnamed_addr constant [37 x i8] c"\0A@@@CLAP: There is a SC violation! \0A\00", align 1
@.str3 = private unnamed_addr constant [32 x i8] c"\0A \1B[1;31m SC Violation!!! \1B[0m\0A\00", align 1

define i8* @P0(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !23
  %EAX = alloca i32, align 4, !clap !24
  %EBX = alloca i32, align 4, !clap !25
  store i8* %arg, i8** %arg.addr, align 4, !clap !26
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !27), !dbg !28, !clap !29
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !30), !dbg !32, !clap !33
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !34), !dbg !35, !clap !36
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @z, i32 1, i32 0, i32 32, i32 8)
  store i32 1, i32* @z, align 4, !dbg !37, !clap !38
  call void (i32, ...)* @clap_store_post(i32 5, i32* @z, i32 1, i32 0, i32 32, i32 8)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 9)
  store i32 1, i32* @x, align 4, !dbg !39, !clap !40
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 9)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 10)
  %tmp = load i32* @x, align 4, !dbg !41, !clap !42
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 10)
  store i32 %tmp, i32* %EAX, align 4, !dbg !41, !clap !43
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 12)
  %tmp1 = load i32* @y, align 4, !dbg !44, !clap !45
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 12)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !44, !clap !46
  %tmp2 = load i32* %EAX, align 4, !dbg !47, !clap !48
  %tmp3 = load i32* %EBX, align 4, !dbg !47, !clap !49
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([33 x i8]* @.str, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !47, !clap !50
  %tmp4 = load i32* %EAX, align 4, !dbg !51, !clap !52
  %cmp = icmp eq i32 %tmp4, 1, !dbg !51, !clap !53
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !51, !clap !54

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !51, !clap !55
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !51, !clap !56
  br label %land.end, !clap !57

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !58
  %land.ext = zext i1 %tmp6 to i32, !clap !59
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !60
  ret i8* %tmp7, !dbg !61, !clap !62
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare i32 @printf(i8*, ...)

define i8* @P1(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !63
  %EAX = alloca i32, align 4, !clap !64
  %EBX = alloca i32, align 4, !clap !65
  store i8* %arg, i8** %arg.addr, align 4, !clap !66
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !67), !dbg !68, !clap !69
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !70), !dbg !72, !clap !73
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !74), !dbg !75, !clap !76
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 34)
  store i32 1, i32* @y, align 4, !dbg !77, !clap !78
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 34)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 35)
  %tmp = load i32* @y, align 4, !dbg !79, !clap !80
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 35)
  store i32 %tmp, i32* %EAX, align 4, !dbg !79, !clap !81
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @z, i32 0, i32 32, i32 37)
  %tmp1 = load i32* @z, align 4, !dbg !82, !clap !83
  call void (i32, ...)* @clap_load_post(i32 4, i32* @z, i32 0, i32 32, i32 37)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !82, !clap !84
  %tmp2 = load i32* %EAX, align 4, !dbg !85, !clap !86
  %tmp3 = load i32* %EBX, align 4, !dbg !85, !clap !87
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([33 x i8]* @.str1, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !85, !clap !88
  %tmp4 = load i32* %EAX, align 4, !dbg !89, !clap !90
  %cmp = icmp eq i32 %tmp4, 1, !dbg !89, !clap !91
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !89, !clap !92

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !89, !clap !93
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !89, !clap !94
  br label %land.end, !clap !95

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !96
  %land.ext = zext i1 %tmp6 to i32, !clap !97
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !98
  ret i8* %tmp7, !dbg !99, !clap !100
}

define i32 @main() nounwind {
entry:
  %retval = alloca i32, align 4, !clap !101
  %t0 = alloca i32, align 4, !clap !102
  %t1 = alloca i32, align 4, !clap !103
  %cond0 = alloca i32, align 4, !clap !104
  %cond1 = alloca i32, align 4, !clap !105
  store i32 0, i32* %retval, !clap !106
  call void @llvm.dbg.declare(metadata !{i32* %t0}, metadata !107), !dbg !111, !clap !112
  call void @llvm.dbg.declare(metadata !{i32* %t1}, metadata !113), !dbg !114, !clap !115
  call void @llvm.dbg.declare(metadata !{i32* %cond0}, metadata !116), !dbg !117, !clap !118
  call void @llvm.dbg.declare(metadata !{i32* %cond1}, metadata !119), !dbg !120, !clap !121
  %call = call i32 @clap_thread_create(i32* %t0, %union.pthread_attr_t* null, i8* (i8*)* @P0, i8* null) nounwind, !dbg !122, !clap !123
  %call1 = call i32 @clap_thread_create(i32* %t1, %union.pthread_attr_t* null, i8* (i8*)* @P1, i8* null) nounwind, !dbg !124, !clap !125
  %tmp = load i32* %t0, align 4, !dbg !126, !clap !127
  %tmp1 = bitcast i32* %cond0 to i8**, !dbg !126, !clap !128
  %call2 = call i32 @clap_thread_join(i32 %tmp, i8** %tmp1), !dbg !126, !clap !129
  %tmp2 = load i32* %t1, align 4, !dbg !130, !clap !131
  %tmp3 = bitcast i32* %cond1 to i8**, !dbg !130, !clap !132
  %call3 = call i32 @clap_thread_join(i32 %tmp2, i8** %tmp3), !dbg !130, !clap !133
  %tmp4 = load i32* %cond0, align 4, !dbg !134, !clap !135
  %tobool = icmp ne i32 %tmp4, 0, !dbg !134, !clap !136
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !134, !clap !137

land.lhs.true:                                    ; preds = %entry
  %tmp5 = load i32* %cond1, align 4, !dbg !134, !clap !138
  %tobool4 = icmp ne i32 %tmp5, 0, !dbg !134, !clap !139
  br i1 %tobool4, label %if.then, label %if.end, !dbg !134, !clap !140

if.then:                                          ; preds = %land.lhs.true
  %call5 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([37 x i8]* @.str2, i32 0, i32 0)), !dbg !141, !clap !143
  %call6 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([32 x i8]* @.str3, i32 0, i32 0)), !dbg !144, !clap !145
  br label %if.end, !dbg !146, !clap !147

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  ret i32 0, !dbg !148, !clap !149
}

declare i32 @clap_thread_create(i32*, %union.pthread_attr_t*, i8* (i8*)*, i8*) nounwind

declare i32 @clap_thread_join(i32, i8**)

declare void @clap_load_pre(i32, ...)

declare void @clap_load_post(i32, ...)

declare void @clap_store_pre(i32, ...)

declare void @clap_store_post(i32, ...)

declare void @clap_cmpxchg_pre(i32, ...)

declare void @clap_cmpxchg_post(i32, ...)

declare void @clap_atomicrmw_pre(i32, ...)

declare void @clap_atomicrmw_post(i32, ...)

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 720913, i32 0, i32 12, metadata !"../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix009/mix009.c", metadata !"/home/naling/src/inspect-0.3", metadata !"clang version 3.0 (tags/RELEASE_30/final)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !17} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !12, metadata !13}
!5 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P0", metadata !"P0", metadata !"", metadata !6, i32 33, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P0, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 720937, metadata !"../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix009/mix009.c", metadata !"/home/naling/src/inspect-0.3", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{metadata !9}
!9 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ]
!10 = metadata !{metadata !11}
!11 = metadata !{i32 720932}                      ; [ DW_TAG_base_type ]
!12 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P1", metadata !"P1", metadata !"", metadata !6, i32 44, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P1, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!13 = metadata !{i32 720942, i32 0, metadata !6, metadata !"main", metadata !"main", metadata !"", metadata !6, i32 54, metadata !14, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i32 ()* @main, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!14 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !15, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!15 = metadata !{metadata !16}
!16 = metadata !{i32 720932, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!17 = metadata !{metadata !18}
!18 = metadata !{metadata !19, metadata !21, metadata !22}
!19 = metadata !{i32 720948, i32 0, null, metadata !"x", metadata !"x", metadata !"", metadata !6, i32 30, metadata !20, i32 0, i32 1, i32* @x} ; [ DW_TAG_variable ]
!20 = metadata !{i32 720932, null, metadata !"long int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!21 = metadata !{i32 720948, i32 0, null, metadata !"y", metadata !"y", metadata !"", metadata !6, i32 30, metadata !20, i32 0, i32 1, i32* @y} ; [ DW_TAG_variable ]
!22 = metadata !{i32 720948, i32 0, null, metadata !"z", metadata !"z", metadata !"", metadata !6, i32 30, metadata !20, i32 0, i32 1, i32* @z} ; [ DW_TAG_variable ]
!23 = metadata !{i32 1}
!24 = metadata !{i32 2}
!25 = metadata !{i32 3}
!26 = metadata !{i32 4}
!27 = metadata !{i32 721153, metadata !5, metadata !"arg", metadata !6, i32 16777248, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!28 = metadata !{i32 32, i32 16, metadata !5, null}
!29 = metadata !{i32 5}
!30 = metadata !{i32 721152, metadata !31, metadata !"EAX", metadata !6, i32 34, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!31 = metadata !{i32 720907, metadata !5, i32 33, i32 1, metadata !6, i32 0} ; [ DW_TAG_lexical_block ]
!32 = metadata !{i32 34, i32 12, metadata !31, null}
!33 = metadata !{i32 6}
!34 = metadata !{i32 721152, metadata !31, metadata !"EBX", metadata !6, i32 34, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!35 = metadata !{i32 34, i32 17, metadata !31, null}
!36 = metadata !{i32 7}
!37 = metadata !{i32 35, i32 3, metadata !31, null}
!38 = metadata !{i32 8}
!39 = metadata !{i32 36, i32 3, metadata !31, null}
!40 = metadata !{i32 9}
!41 = metadata !{i32 37, i32 3, metadata !31, null}
!42 = metadata !{i32 10}
!43 = metadata !{i32 11}
!44 = metadata !{i32 38, i32 3, metadata !31, null}
!45 = metadata !{i32 12}
!46 = metadata !{i32 13}
!47 = metadata !{i32 39, i32 3, metadata !31, null}
!48 = metadata !{i32 14}
!49 = metadata !{i32 15}
!50 = metadata !{i32 16}
!51 = metadata !{i32 40, i32 3, metadata !31, null}
!52 = metadata !{i32 17}
!53 = metadata !{i32 18}
!54 = metadata !{i32 19}
!55 = metadata !{i32 20}
!56 = metadata !{i32 21}
!57 = metadata !{i32 22}
!58 = metadata !{i32 23}
!59 = metadata !{i32 24}
!60 = metadata !{i32 25}
!61 = metadata !{i32 41, i32 1, metadata !5, null}
!62 = metadata !{i32 26}
!63 = metadata !{i32 27}
!64 = metadata !{i32 28}
!65 = metadata !{i32 29}
!66 = metadata !{i32 30}
!67 = metadata !{i32 721153, metadata !12, metadata !"arg", metadata !6, i32 16777259, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!68 = metadata !{i32 43, i32 16, metadata !12, null}
!69 = metadata !{i32 31}
!70 = metadata !{i32 721152, metadata !71, metadata !"EAX", metadata !6, i32 45, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!71 = metadata !{i32 720907, metadata !12, i32 44, i32 1, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!72 = metadata !{i32 45, i32 12, metadata !71, null}
!73 = metadata !{i32 32}
!74 = metadata !{i32 721152, metadata !71, metadata !"EBX", metadata !6, i32 45, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!75 = metadata !{i32 45, i32 17, metadata !71, null}
!76 = metadata !{i32 33}
!77 = metadata !{i32 46, i32 3, metadata !71, null}
!78 = metadata !{i32 34}
!79 = metadata !{i32 47, i32 3, metadata !71, null}
!80 = metadata !{i32 35}
!81 = metadata !{i32 36}
!82 = metadata !{i32 48, i32 3, metadata !71, null}
!83 = metadata !{i32 37}
!84 = metadata !{i32 38}
!85 = metadata !{i32 49, i32 3, metadata !71, null}
!86 = metadata !{i32 39}
!87 = metadata !{i32 40}
!88 = metadata !{i32 41}
!89 = metadata !{i32 50, i32 3, metadata !71, null}
!90 = metadata !{i32 42}
!91 = metadata !{i32 43}
!92 = metadata !{i32 44}
!93 = metadata !{i32 45}
!94 = metadata !{i32 46}
!95 = metadata !{i32 47}
!96 = metadata !{i32 48}
!97 = metadata !{i32 49}
!98 = metadata !{i32 50}
!99 = metadata !{i32 51, i32 1, metadata !12, null}
!100 = metadata !{i32 51}
!101 = metadata !{i32 52}
!102 = metadata !{i32 53}
!103 = metadata !{i32 54}
!104 = metadata !{i32 55}
!105 = metadata !{i32 56}
!106 = metadata !{i32 57}
!107 = metadata !{i32 721152, metadata !108, metadata !"t0", metadata !6, i32 55, metadata !109, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!108 = metadata !{i32 720907, metadata !13, i32 54, i32 1, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!109 = metadata !{i32 720918, null, metadata !"pthread_t", metadata !6, i32 60, i64 0, i64 0, i64 0, i32 0, metadata !110} ; [ DW_TAG_typedef ]
!110 = metadata !{i32 720932, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!111 = metadata !{i32 55, i32 13, metadata !108, null}
!112 = metadata !{i32 58}
!113 = metadata !{i32 721152, metadata !108, metadata !"t1", metadata !6, i32 55, metadata !109, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!114 = metadata !{i32 55, i32 17, metadata !108, null}
!115 = metadata !{i32 59}
!116 = metadata !{i32 721152, metadata !108, metadata !"cond0", metadata !6, i32 56, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!117 = metadata !{i32 56, i32 12, metadata !108, null}
!118 = metadata !{i32 60}
!119 = metadata !{i32 721152, metadata !108, metadata !"cond1", metadata !6, i32 56, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!120 = metadata !{i32 56, i32 19, metadata !108, null}
!121 = metadata !{i32 61}
!122 = metadata !{i32 58, i32 3, metadata !108, null}
!123 = metadata !{i32 62}
!124 = metadata !{i32 59, i32 3, metadata !108, null}
!125 = metadata !{i32 63}
!126 = metadata !{i32 61, i32 3, metadata !108, null}
!127 = metadata !{i32 64}
!128 = metadata !{i32 65}
!129 = metadata !{i32 66}
!130 = metadata !{i32 62, i32 3, metadata !108, null}
!131 = metadata !{i32 67}
!132 = metadata !{i32 68}
!133 = metadata !{i32 69}
!134 = metadata !{i32 65, i32 3, metadata !108, null}
!135 = metadata !{i32 70}
!136 = metadata !{i32 71}
!137 = metadata !{i32 72}
!138 = metadata !{i32 73}
!139 = metadata !{i32 74}
!140 = metadata !{i32 75}
!141 = metadata !{i32 66, i32 5, metadata !142, null}
!142 = metadata !{i32 720907, metadata !108, i32 65, i32 25, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!143 = metadata !{i32 76}
!144 = metadata !{i32 67, i32 5, metadata !142, null}
!145 = metadata !{i32 77}
!146 = metadata !{i32 68, i32 3, metadata !142, null}
!147 = metadata !{i32 78}
!148 = metadata !{i32 70, i32 3, metadata !108, null}
!149 = metadata !{i32 79}
