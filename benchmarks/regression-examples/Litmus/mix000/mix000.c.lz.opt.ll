; ModuleID = '/home/naling/src/examples/tso/regression-examples/mix000/mix000.c.lz.opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%union.pthread_attr_t = type { i32, [32 x i8] }

@y = common global i32 0, align 4
@x = common global i32 0, align 4
@.str = private unnamed_addr constant [37 x i8] c"\0A@@@CLAP: There is a SC violation! \0A\00", align 1
@.str1 = private unnamed_addr constant [30 x i8] c"\1B[1;31m SC Violation!!! \1B[0m\0A\00", align 1
@z = common global i32 0, align 4

define i8* @P0(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !23
  %EAX = alloca i32, align 4, !clap !24
  %EBX = alloca i32, align 4, !clap !25
  store i8* %arg, i8** %arg.addr, align 4, !clap !26
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !27), !dbg !28, !clap !29
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !30), !dbg !32, !clap !33
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !34), !dbg !35, !clap !36
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 8)
  store i32 1, i32* @y, align 4, !dbg !37, !clap !38
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 8)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 9)
  %tmp = load i32* @y, align 4, !dbg !39, !clap !40
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 9)
  store i32 %tmp, i32* %EAX, align 4, !dbg !39, !clap !41
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 11)
  %tmp1 = load i32* @x, align 4, !dbg !42, !clap !43
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 11)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !42, !clap !44
  %tmp2 = load i32* %EAX, align 4, !dbg !45, !clap !46
  %cmp = icmp eq i32 %tmp2, 1, !dbg !45, !clap !47
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !45, !clap !48

land.rhs:                                         ; preds = %entry
  %tmp3 = load i32* %EBX, align 4, !dbg !45, !clap !49
  %cmp1 = icmp eq i32 %tmp3, 0, !dbg !45, !clap !50
  br label %land.end, !clap !51

land.end:                                         ; preds = %land.rhs, %entry
  %tmp4 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !52
  %land.ext = zext i1 %tmp4 to i32, !clap !53
  %tmp5 = inttoptr i32 %land.ext to i8*, !clap !54
  ret i8* %tmp5, !dbg !55, !clap !56
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

define i8* @P1(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !57
  %EAX = alloca i32, align 4, !clap !58
  %EBX = alloca i32, align 4, !clap !59
  store i8* %arg, i8** %arg.addr, align 4, !clap !60
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !61), !dbg !62, !clap !63
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !64), !dbg !66, !clap !67
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !68), !dbg !69, !clap !70
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 30)
  store i32 1, i32* @x, align 4, !dbg !71, !clap !72
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 30)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 31)
  %tmp = load i32* @x, align 4, !dbg !73, !clap !74
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 31)
  store i32 %tmp, i32* %EAX, align 4, !dbg !73, !clap !75
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 33)
  %tmp1 = load i32* @y, align 4, !dbg !76, !clap !77
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 33)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !76, !clap !78
  %tmp2 = load i32* %EAX, align 4, !dbg !79, !clap !80
  %cmp = icmp eq i32 %tmp2, 1, !dbg !79, !clap !81
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !79, !clap !82

land.rhs:                                         ; preds = %entry
  %tmp3 = load i32* %EBX, align 4, !dbg !79, !clap !83
  %cmp1 = icmp eq i32 %tmp3, 0, !dbg !79, !clap !84
  br label %land.end, !clap !85

land.end:                                         ; preds = %land.rhs, %entry
  %tmp4 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !86
  %land.ext = zext i1 %tmp4 to i32, !clap !87
  %tmp5 = inttoptr i32 %land.ext to i8*, !clap !88
  ret i8* %tmp5, !dbg !89, !clap !90
}

define i32 @main() nounwind {
entry:
  %retval = alloca i32, align 4, !clap !91
  %t0 = alloca i32, align 4, !clap !92
  %t1 = alloca i32, align 4, !clap !93
  %cond0 = alloca i32, align 4, !clap !94
  %cond1 = alloca i32, align 4, !clap !95
  store i32 0, i32* %retval, !clap !96
  call void @llvm.dbg.declare(metadata !{i32* %t0}, metadata !97), !dbg !101, !clap !102
  call void @llvm.dbg.declare(metadata !{i32* %t1}, metadata !103), !dbg !104, !clap !105
  call void @llvm.dbg.declare(metadata !{i32* %cond0}, metadata !106), !dbg !107, !clap !108
  call void @llvm.dbg.declare(metadata !{i32* %cond1}, metadata !109), !dbg !110, !clap !111
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 0, i32 0, i32 32, i32 55)
  store i32 0, i32* @y, align 4, !dbg !112, !clap !113
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 0, i32 0, i32 32, i32 55)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 0, i32 0, i32 32, i32 56)
  store i32 0, i32* @x, align 4, !dbg !112, !clap !114
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 0, i32 0, i32 32, i32 56)
  %call = call i32 @clap_thread_create(i32* %t0, %union.pthread_attr_t* null, i8* (i8*)* @P0, i8* null) nounwind, !dbg !115, !clap !116
  %call1 = call i32 @clap_thread_create(i32* %t1, %union.pthread_attr_t* null, i8* (i8*)* @P1, i8* null) nounwind, !dbg !117, !clap !118
  %tmp = load i32* %t0, align 4, !dbg !119, !clap !120
  %tmp1 = bitcast i32* %cond0 to i8**, !dbg !119, !clap !121
  %call2 = call i32 @clap_thread_join(i32 %tmp, i8** %tmp1), !dbg !119, !clap !122
  %tmp2 = load i32* %t1, align 4, !dbg !123, !clap !124
  %tmp3 = bitcast i32* %cond1 to i8**, !dbg !123, !clap !125
  %call3 = call i32 @clap_thread_join(i32 %tmp2, i8** %tmp3), !dbg !123, !clap !126
  %tmp4 = load i32* %cond0, align 4, !dbg !127, !clap !128
  %tobool = icmp ne i32 %tmp4, 0, !dbg !127, !clap !129
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !127, !clap !130

land.lhs.true:                                    ; preds = %entry
  %tmp5 = load i32* %cond1, align 4, !dbg !127, !clap !131
  %tobool4 = icmp ne i32 %tmp5, 0, !dbg !127, !clap !132
  br i1 %tobool4, label %if.then, label %if.end, !dbg !127, !clap !133

if.then:                                          ; preds = %land.lhs.true
  %call5 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([37 x i8]* @.str, i32 0, i32 0)), !dbg !134, !clap !136
  %call6 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([30 x i8]* @.str1, i32 0, i32 0)), !dbg !137, !clap !138
  br label %if.end, !dbg !139, !clap !140

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  ret i32 0, !dbg !141, !clap !142
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

!0 = metadata !{i32 720913, i32 0, i32 12, metadata !"/home/naling/src/examples/tso/regression-examples/mix000/mix000.c", metadata !"/home/naling/src/inspect-0.3", metadata !"clang version 3.0 (tags/RELEASE_30/final)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !17} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !12, metadata !13}
!5 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P0", metadata !"P0", metadata !"", metadata !6, i32 32, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P0, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 720937, metadata !"/home/naling/src/examples/tso/regression-examples/mix000/mix000.c", metadata !"/home/naling/src/inspect-0.3", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{metadata !9}
!9 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ]
!10 = metadata !{metadata !11}
!11 = metadata !{i32 720932}                      ; [ DW_TAG_base_type ]
!12 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P1", metadata !"P1", metadata !"", metadata !6, i32 42, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P1, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!13 = metadata !{i32 720942, i32 0, metadata !6, metadata !"main", metadata !"main", metadata !"", metadata !6, i32 52, metadata !14, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i32 ()* @main, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!14 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !15, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!15 = metadata !{metadata !16}
!16 = metadata !{i32 720932, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!17 = metadata !{metadata !18}
!18 = metadata !{metadata !19, metadata !21, metadata !22}
!19 = metadata !{i32 720948, i32 0, null, metadata !"x", metadata !"x", metadata !"", metadata !6, i32 29, metadata !20, i32 0, i32 1, i32* @x} ; [ DW_TAG_variable ]
!20 = metadata !{i32 720932, null, metadata !"long int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!21 = metadata !{i32 720948, i32 0, null, metadata !"y", metadata !"y", metadata !"", metadata !6, i32 29, metadata !20, i32 0, i32 1, i32* @y} ; [ DW_TAG_variable ]
!22 = metadata !{i32 720948, i32 0, null, metadata !"z", metadata !"z", metadata !"", metadata !6, i32 29, metadata !20, i32 0, i32 1, i32* @z} ; [ DW_TAG_variable ]
!23 = metadata !{i32 1}
!24 = metadata !{i32 2}
!25 = metadata !{i32 3}
!26 = metadata !{i32 4}
!27 = metadata !{i32 721153, metadata !5, metadata !"arg", metadata !6, i32 16777247, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!28 = metadata !{i32 31, i32 16, metadata !5, null}
!29 = metadata !{i32 5}
!30 = metadata !{i32 721152, metadata !31, metadata !"EAX", metadata !6, i32 33, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!31 = metadata !{i32 720907, metadata !5, i32 32, i32 1, metadata !6, i32 0} ; [ DW_TAG_lexical_block ]
!32 = metadata !{i32 33, i32 12, metadata !31, null}
!33 = metadata !{i32 6}
!34 = metadata !{i32 721152, metadata !31, metadata !"EBX", metadata !6, i32 33, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!35 = metadata !{i32 33, i32 17, metadata !31, null}
!36 = metadata !{i32 7}
!37 = metadata !{i32 34, i32 3, metadata !31, null}
!38 = metadata !{i32 8}
!39 = metadata !{i32 35, i32 3, metadata !31, null}
!40 = metadata !{i32 9}
!41 = metadata !{i32 10}
!42 = metadata !{i32 36, i32 3, metadata !31, null}
!43 = metadata !{i32 11}
!44 = metadata !{i32 12}
!45 = metadata !{i32 38, i32 3, metadata !31, null}
!46 = metadata !{i32 13}
!47 = metadata !{i32 14}
!48 = metadata !{i32 15}
!49 = metadata !{i32 16}
!50 = metadata !{i32 17}
!51 = metadata !{i32 18}
!52 = metadata !{i32 19}
!53 = metadata !{i32 20}
!54 = metadata !{i32 21}
!55 = metadata !{i32 39, i32 1, metadata !5, null}
!56 = metadata !{i32 22}
!57 = metadata !{i32 23}
!58 = metadata !{i32 24}
!59 = metadata !{i32 25}
!60 = metadata !{i32 26}
!61 = metadata !{i32 721153, metadata !12, metadata !"arg", metadata !6, i32 16777257, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!62 = metadata !{i32 41, i32 16, metadata !12, null}
!63 = metadata !{i32 27}
!64 = metadata !{i32 721152, metadata !65, metadata !"EAX", metadata !6, i32 43, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!65 = metadata !{i32 720907, metadata !12, i32 42, i32 1, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!66 = metadata !{i32 43, i32 12, metadata !65, null}
!67 = metadata !{i32 28}
!68 = metadata !{i32 721152, metadata !65, metadata !"EBX", metadata !6, i32 43, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!69 = metadata !{i32 43, i32 17, metadata !65, null}
!70 = metadata !{i32 29}
!71 = metadata !{i32 44, i32 3, metadata !65, null}
!72 = metadata !{i32 30}
!73 = metadata !{i32 45, i32 3, metadata !65, null}
!74 = metadata !{i32 31}
!75 = metadata !{i32 32}
!76 = metadata !{i32 46, i32 3, metadata !65, null}
!77 = metadata !{i32 33}
!78 = metadata !{i32 34}
!79 = metadata !{i32 48, i32 3, metadata !65, null}
!80 = metadata !{i32 35}
!81 = metadata !{i32 36}
!82 = metadata !{i32 37}
!83 = metadata !{i32 38}
!84 = metadata !{i32 39}
!85 = metadata !{i32 40}
!86 = metadata !{i32 41}
!87 = metadata !{i32 42}
!88 = metadata !{i32 43}
!89 = metadata !{i32 49, i32 1, metadata !12, null}
!90 = metadata !{i32 44}
!91 = metadata !{i32 45}
!92 = metadata !{i32 46}
!93 = metadata !{i32 47}
!94 = metadata !{i32 48}
!95 = metadata !{i32 49}
!96 = metadata !{i32 50}
!97 = metadata !{i32 721152, metadata !98, metadata !"t0", metadata !6, i32 53, metadata !99, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!98 = metadata !{i32 720907, metadata !13, i32 52, i32 1, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!99 = metadata !{i32 720918, null, metadata !"pthread_t", metadata !6, i32 60, i64 0, i64 0, i64 0, i32 0, metadata !100} ; [ DW_TAG_typedef ]
!100 = metadata !{i32 720932, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!101 = metadata !{i32 53, i32 13, metadata !98, null}
!102 = metadata !{i32 51}
!103 = metadata !{i32 721152, metadata !98, metadata !"t1", metadata !6, i32 53, metadata !99, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!104 = metadata !{i32 53, i32 17, metadata !98, null}
!105 = metadata !{i32 52}
!106 = metadata !{i32 721152, metadata !98, metadata !"cond0", metadata !6, i32 54, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!107 = metadata !{i32 54, i32 12, metadata !98, null}
!108 = metadata !{i32 53}
!109 = metadata !{i32 721152, metadata !98, metadata !"cond1", metadata !6, i32 54, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!110 = metadata !{i32 54, i32 19, metadata !98, null}
!111 = metadata !{i32 54}
!112 = metadata !{i32 56, i32 3, metadata !98, null}
!113 = metadata !{i32 55}
!114 = metadata !{i32 56}
!115 = metadata !{i32 58, i32 3, metadata !98, null}
!116 = metadata !{i32 57}
!117 = metadata !{i32 59, i32 3, metadata !98, null}
!118 = metadata !{i32 58}
!119 = metadata !{i32 61, i32 3, metadata !98, null}
!120 = metadata !{i32 59}
!121 = metadata !{i32 60}
!122 = metadata !{i32 61}
!123 = metadata !{i32 62, i32 3, metadata !98, null}
!124 = metadata !{i32 62}
!125 = metadata !{i32 63}
!126 = metadata !{i32 64}
!127 = metadata !{i32 65, i32 3, metadata !98, null}
!128 = metadata !{i32 65}
!129 = metadata !{i32 66}
!130 = metadata !{i32 67}
!131 = metadata !{i32 68}
!132 = metadata !{i32 69}
!133 = metadata !{i32 70}
!134 = metadata !{i32 66, i32 5, metadata !135, null}
!135 = metadata !{i32 720907, metadata !98, i32 65, i32 25, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!136 = metadata !{i32 71}
!137 = metadata !{i32 67, i32 5, metadata !135, null}
!138 = metadata !{i32 72}
!139 = metadata !{i32 68, i32 3, metadata !135, null}
!140 = metadata !{i32 73}
!141 = metadata !{i32 70, i32 3, metadata !98, null}
!142 = metadata !{i32 74}
