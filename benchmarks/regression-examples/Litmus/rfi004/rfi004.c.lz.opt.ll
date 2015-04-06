; ModuleID = '../examples/tso/regression-examples/rfi004/rfi004.c.lz.opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%union.pthread_attr_t = type { i32, [32 x i8] }

@x = common global i32 0, align 4
@k = common global i32 0, align 4
@y = common global i32 0, align 4
@.str = private unnamed_addr constant [22 x i8] c"\0A %%%% (EAX1=%d) %%%%\00", align 1
@z = common global i32 0, align 4
@.str1 = private unnamed_addr constant [31 x i8] c"\0A %%%% (EAX1=%d, EBX1=%d) %%%%\00", align 1
@.str2 = private unnamed_addr constant [37 x i8] c"\0A@@@CLAP: There is a SC violation! \0A\00", align 1
@.str3 = private unnamed_addr constant [30 x i8] c"\1B[1;31m SC Violation!!! \1B[0m\0A\00", align 1

define i8* @P0(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !24
  %EAX = alloca i32, align 4, !clap !25
  %EBX = alloca i32, align 4, !clap !26
  store i8* %arg, i8** %arg.addr, align 4, !clap !27
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !28), !dbg !29, !clap !30
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !31), !dbg !33, !clap !34
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !35), !dbg !36, !clap !37
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 8)
  store i32 1, i32* @x, align 4, !dbg !38, !clap !39
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 8)
  call void (i32, ...)* @clap_atomicrmw_pre(i32 5, i32* @k, i32 0, i32 7, i32 32, i32 9)
  %tmp = atomicrmw add i32* @k, i32 0 seq_cst, !dbg !40, !clap !41
  call void (i32, ...)* @clap_atomicrmw_post(i32 5, i32* @k, i32 0, i32 7, i32 32, i32 9)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 10)
  %tmp1 = load i32* @y, align 4, !dbg !42, !clap !43
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 10)
  store i32 %tmp1, i32* %EAX, align 4, !dbg !42, !clap !44
  %tmp2 = load i32* %EAX, align 4, !dbg !45, !clap !46
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([22 x i8]* @.str, i32 0, i32 0), i32 %tmp2), !dbg !45, !clap !47
  %tmp3 = load i32* %EAX, align 4, !dbg !48, !clap !49
  %cmp = icmp eq i32 %tmp3, 0, !dbg !48, !clap !50
  %conv = zext i1 %cmp to i32, !dbg !48, !clap !51
  %tmp4 = inttoptr i32 %conv to i8*, !dbg !48, !clap !52
  ret i8* %tmp4, !dbg !48, !clap !53
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare i32 @printf(i8*, ...)

define i8* @P1(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !54
  %EAX = alloca i32, align 4, !clap !55
  %EBX = alloca i32, align 4, !clap !56
  store i8* %arg, i8** %arg.addr, align 4, !clap !57
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !58), !dbg !59, !clap !60
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !61), !dbg !63, !clap !64
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !65), !dbg !66, !clap !67
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 26)
  store i32 1, i32* @y, align 4, !dbg !68, !clap !69
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 26)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @z, i32 1, i32 0, i32 32, i32 27)
  store i32 1, i32* @z, align 4, !dbg !70, !clap !71
  call void (i32, ...)* @clap_store_post(i32 5, i32* @z, i32 1, i32 0, i32 32, i32 27)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @z, i32 0, i32 32, i32 28)
  %tmp = load i32* @z, align 4, !dbg !72, !clap !73
  call void (i32, ...)* @clap_load_post(i32 4, i32* @z, i32 0, i32 32, i32 28)
  store i32 %tmp, i32* %EAX, align 4, !dbg !72, !clap !74
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 30)
  %tmp1 = load i32* @x, align 4, !dbg !75, !clap !76
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 30)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !75, !clap !77
  %tmp2 = load i32* %EAX, align 4, !dbg !78, !clap !79
  %tmp3 = load i32* %EBX, align 4, !dbg !78, !clap !80
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([31 x i8]* @.str1, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !78, !clap !81
  %tmp4 = load i32* %EAX, align 4, !dbg !82, !clap !83
  %cmp = icmp eq i32 %tmp4, 1, !dbg !82, !clap !84
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !82, !clap !85

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !82, !clap !86
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !82, !clap !87
  br label %land.end, !clap !88

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !89
  %land.ext = zext i1 %tmp6 to i32, !clap !90
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !91
  ret i8* %tmp7, !dbg !92, !clap !93
}

define i32 @main() nounwind {
entry:
  %retval = alloca i32, align 4, !clap !94
  %t0 = alloca i32, align 4, !clap !95
  %t1 = alloca i32, align 4, !clap !96
  %t2 = alloca i32, align 4, !clap !97
  %t3 = alloca i32, align 4, !clap !98
  %cond0 = alloca i32, align 4, !clap !99
  %cond1 = alloca i32, align 4, !clap !100
  %cond2 = alloca i32, align 4, !clap !101
  %cond3 = alloca i32, align 4, !clap !102
  store i32 0, i32* %retval, !clap !103
  call void @llvm.dbg.declare(metadata !{i32* %t0}, metadata !104), !dbg !108, !clap !109
  call void @llvm.dbg.declare(metadata !{i32* %t1}, metadata !110), !dbg !111, !clap !112
  call void @llvm.dbg.declare(metadata !{i32* %t2}, metadata !113), !dbg !114, !clap !115
  call void @llvm.dbg.declare(metadata !{i32* %t3}, metadata !116), !dbg !117, !clap !118
  call void @llvm.dbg.declare(metadata !{i32* %cond0}, metadata !119), !dbg !120, !clap !121
  call void @llvm.dbg.declare(metadata !{i32* %cond1}, metadata !122), !dbg !123, !clap !124
  call void @llvm.dbg.declare(metadata !{i32* %cond2}, metadata !125), !dbg !126, !clap !127
  call void @llvm.dbg.declare(metadata !{i32* %cond3}, metadata !128), !dbg !129, !clap !130
  %call = call i32 @clap_thread_create(i32* %t0, %union.pthread_attr_t* null, i8* (i8*)* @P0, i8* null) nounwind, !dbg !131, !clap !132
  %call1 = call i32 @clap_thread_create(i32* %t1, %union.pthread_attr_t* null, i8* (i8*)* @P1, i8* null) nounwind, !dbg !133, !clap !134
  %tmp = load i32* %t0, align 4, !dbg !135, !clap !136
  %tmp1 = bitcast i32* %cond0 to i8**, !dbg !135, !clap !137
  %call2 = call i32 @clap_thread_join(i32 %tmp, i8** %tmp1), !dbg !135, !clap !138
  %tmp2 = load i32* %t1, align 4, !dbg !139, !clap !140
  %tmp3 = bitcast i32* %cond1 to i8**, !dbg !139, !clap !141
  %call3 = call i32 @clap_thread_join(i32 %tmp2, i8** %tmp3), !dbg !139, !clap !142
  %tmp4 = load i32* %cond0, align 4, !dbg !143, !clap !144
  %tobool = icmp ne i32 %tmp4, 0, !dbg !143, !clap !145
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !143, !clap !146

land.lhs.true:                                    ; preds = %entry
  %tmp5 = load i32* %cond1, align 4, !dbg !143, !clap !147
  %tobool4 = icmp ne i32 %tmp5, 0, !dbg !143, !clap !148
  br i1 %tobool4, label %if.then, label %if.end, !dbg !143, !clap !149

if.then:                                          ; preds = %land.lhs.true
  %call5 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([37 x i8]* @.str2, i32 0, i32 0)), !dbg !150, !clap !152
  %call6 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([30 x i8]* @.str3, i32 0, i32 0)), !dbg !153, !clap !154
  br label %if.end, !dbg !155, !clap !156

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  ret i32 0, !dbg !157, !clap !158
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

!0 = metadata !{i32 720913, i32 0, i32 12, metadata !"../examples/tso/regression-examples/rfi004/rfi004.c", metadata !"/home/naling/src/inspect-0.3", metadata !"clang version 3.0 (tags/RELEASE_30/final)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !17} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !12, metadata !13}
!5 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P0", metadata !"P0", metadata !"", metadata !6, i32 31, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P0, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 720937, metadata !"../examples/tso/regression-examples/rfi004/rfi004.c", metadata !"/home/naling/src/inspect-0.3", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{metadata !9}
!9 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ]
!10 = metadata !{metadata !11}
!11 = metadata !{i32 720932}                      ; [ DW_TAG_base_type ]
!12 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P1", metadata !"P1", metadata !"", metadata !6, i32 42, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P1, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!13 = metadata !{i32 720942, i32 0, metadata !6, metadata !"main", metadata !"main", metadata !"", metadata !6, i32 56, metadata !14, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i32 ()* @main, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!14 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !15, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!15 = metadata !{metadata !16}
!16 = metadata !{i32 720932, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!17 = metadata !{metadata !18}
!18 = metadata !{metadata !19, metadata !21, metadata !22, metadata !23}
!19 = metadata !{i32 720948, i32 0, null, metadata !"x", metadata !"x", metadata !"", metadata !6, i32 28, metadata !20, i32 0, i32 1, i32* @x} ; [ DW_TAG_variable ]
!20 = metadata !{i32 720932, null, metadata !"long int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!21 = metadata !{i32 720948, i32 0, null, metadata !"y", metadata !"y", metadata !"", metadata !6, i32 28, metadata !20, i32 0, i32 1, i32* @y} ; [ DW_TAG_variable ]
!22 = metadata !{i32 720948, i32 0, null, metadata !"z", metadata !"z", metadata !"", metadata !6, i32 28, metadata !20, i32 0, i32 1, i32* @z} ; [ DW_TAG_variable ]
!23 = metadata !{i32 720948, i32 0, null, metadata !"k", metadata !"k", metadata !"", metadata !6, i32 29, metadata !16, i32 0, i32 1, i32* @k} ; [ DW_TAG_variable ]
!24 = metadata !{i32 1}
!25 = metadata !{i32 2}
!26 = metadata !{i32 3}
!27 = metadata !{i32 4}
!28 = metadata !{i32 721153, metadata !5, metadata !"arg", metadata !6, i32 16777246, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!29 = metadata !{i32 30, i32 16, metadata !5, null}
!30 = metadata !{i32 5}
!31 = metadata !{i32 721152, metadata !32, metadata !"EAX", metadata !6, i32 32, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!32 = metadata !{i32 720907, metadata !5, i32 31, i32 1, metadata !6, i32 0} ; [ DW_TAG_lexical_block ]
!33 = metadata !{i32 32, i32 12, metadata !32, null}
!34 = metadata !{i32 6}
!35 = metadata !{i32 721152, metadata !32, metadata !"EBX", metadata !6, i32 32, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!36 = metadata !{i32 32, i32 17, metadata !32, null}
!37 = metadata !{i32 7}
!38 = metadata !{i32 33, i32 3, metadata !32, null}
!39 = metadata !{i32 8}
!40 = metadata !{i32 35, i32 2, metadata !32, null}
!41 = metadata !{i32 9}
!42 = metadata !{i32 36, i32 3, metadata !32, null}
!43 = metadata !{i32 10}
!44 = metadata !{i32 11}
!45 = metadata !{i32 37, i32 1, metadata !32, null}
!46 = metadata !{i32 12}
!47 = metadata !{i32 13}
!48 = metadata !{i32 38, i32 3, metadata !32, null}
!49 = metadata !{i32 14}
!50 = metadata !{i32 15}
!51 = metadata !{i32 16}
!52 = metadata !{i32 17}
!53 = metadata !{i32 18}
!54 = metadata !{i32 19}
!55 = metadata !{i32 20}
!56 = metadata !{i32 21}
!57 = metadata !{i32 22}
!58 = metadata !{i32 721153, metadata !12, metadata !"arg", metadata !6, i32 16777257, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!59 = metadata !{i32 41, i32 16, metadata !12, null}
!60 = metadata !{i32 23}
!61 = metadata !{i32 721152, metadata !62, metadata !"EAX", metadata !6, i32 43, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!62 = metadata !{i32 720907, metadata !12, i32 42, i32 1, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!63 = metadata !{i32 43, i32 12, metadata !62, null}
!64 = metadata !{i32 24}
!65 = metadata !{i32 721152, metadata !62, metadata !"EBX", metadata !6, i32 43, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!66 = metadata !{i32 43, i32 17, metadata !62, null}
!67 = metadata !{i32 25}
!68 = metadata !{i32 44, i32 3, metadata !62, null}
!69 = metadata !{i32 26}
!70 = metadata !{i32 45, i32 3, metadata !62, null}
!71 = metadata !{i32 27}
!72 = metadata !{i32 46, i32 3, metadata !62, null}
!73 = metadata !{i32 28}
!74 = metadata !{i32 29}
!75 = metadata !{i32 47, i32 3, metadata !62, null}
!76 = metadata !{i32 30}
!77 = metadata !{i32 31}
!78 = metadata !{i32 48, i32 3, metadata !62, null}
!79 = metadata !{i32 32}
!80 = metadata !{i32 33}
!81 = metadata !{i32 34}
!82 = metadata !{i32 49, i32 3, metadata !62, null}
!83 = metadata !{i32 35}
!84 = metadata !{i32 36}
!85 = metadata !{i32 37}
!86 = metadata !{i32 38}
!87 = metadata !{i32 39}
!88 = metadata !{i32 40}
!89 = metadata !{i32 41}
!90 = metadata !{i32 42}
!91 = metadata !{i32 43}
!92 = metadata !{i32 50, i32 1, metadata !12, null}
!93 = metadata !{i32 44}
!94 = metadata !{i32 45}
!95 = metadata !{i32 46}
!96 = metadata !{i32 47}
!97 = metadata !{i32 48}
!98 = metadata !{i32 49}
!99 = metadata !{i32 50}
!100 = metadata !{i32 51}
!101 = metadata !{i32 52}
!102 = metadata !{i32 53}
!103 = metadata !{i32 54}
!104 = metadata !{i32 721152, metadata !105, metadata !"t0", metadata !6, i32 57, metadata !106, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!105 = metadata !{i32 720907, metadata !13, i32 56, i32 1, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!106 = metadata !{i32 720918, null, metadata !"pthread_t", metadata !6, i32 60, i64 0, i64 0, i64 0, i32 0, metadata !107} ; [ DW_TAG_typedef ]
!107 = metadata !{i32 720932, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!108 = metadata !{i32 57, i32 13, metadata !105, null}
!109 = metadata !{i32 55}
!110 = metadata !{i32 721152, metadata !105, metadata !"t1", metadata !6, i32 57, metadata !106, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!111 = metadata !{i32 57, i32 17, metadata !105, null}
!112 = metadata !{i32 56}
!113 = metadata !{i32 721152, metadata !105, metadata !"t2", metadata !6, i32 57, metadata !106, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!114 = metadata !{i32 57, i32 21, metadata !105, null}
!115 = metadata !{i32 57}
!116 = metadata !{i32 721152, metadata !105, metadata !"t3", metadata !6, i32 57, metadata !106, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!117 = metadata !{i32 57, i32 25, metadata !105, null}
!118 = metadata !{i32 58}
!119 = metadata !{i32 721152, metadata !105, metadata !"cond0", metadata !6, i32 58, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!120 = metadata !{i32 58, i32 12, metadata !105, null}
!121 = metadata !{i32 59}
!122 = metadata !{i32 721152, metadata !105, metadata !"cond1", metadata !6, i32 58, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!123 = metadata !{i32 58, i32 19, metadata !105, null}
!124 = metadata !{i32 60}
!125 = metadata !{i32 721152, metadata !105, metadata !"cond2", metadata !6, i32 58, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!126 = metadata !{i32 58, i32 26, metadata !105, null}
!127 = metadata !{i32 61}
!128 = metadata !{i32 721152, metadata !105, metadata !"cond3", metadata !6, i32 58, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!129 = metadata !{i32 58, i32 33, metadata !105, null}
!130 = metadata !{i32 62}
!131 = metadata !{i32 60, i32 3, metadata !105, null}
!132 = metadata !{i32 63}
!133 = metadata !{i32 61, i32 3, metadata !105, null}
!134 = metadata !{i32 64}
!135 = metadata !{i32 63, i32 3, metadata !105, null}
!136 = metadata !{i32 65}
!137 = metadata !{i32 66}
!138 = metadata !{i32 67}
!139 = metadata !{i32 64, i32 3, metadata !105, null}
!140 = metadata !{i32 68}
!141 = metadata !{i32 69}
!142 = metadata !{i32 70}
!143 = metadata !{i32 66, i32 3, metadata !105, null}
!144 = metadata !{i32 71}
!145 = metadata !{i32 72}
!146 = metadata !{i32 73}
!147 = metadata !{i32 74}
!148 = metadata !{i32 75}
!149 = metadata !{i32 76}
!150 = metadata !{i32 67, i32 5, metadata !151, null}
!151 = metadata !{i32 720907, metadata !105, i32 66, i32 25, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!152 = metadata !{i32 77}
!153 = metadata !{i32 68, i32 5, metadata !151, null}
!154 = metadata !{i32 78}
!155 = metadata !{i32 69, i32 3, metadata !151, null}
!156 = metadata !{i32 79}
!157 = metadata !{i32 71, i32 3, metadata !105, null}
!158 = metadata !{i32 80}
