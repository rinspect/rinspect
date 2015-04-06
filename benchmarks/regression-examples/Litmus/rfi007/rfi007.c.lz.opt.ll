; ModuleID = '/home/naling/src/examples/tso/regression-examples/rfi007/rfi007.c.lz.opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%union.pthread_attr_t = type { i32, [32 x i8] }

@x = common global i32 0, align 4
@y = common global i32 0, align 4
@.str = private unnamed_addr constant [31 x i8] c"\0A %%%% (EAX1=%d, EBX1=%d) %%%%\00", align 1
@.str1 = private unnamed_addr constant [37 x i8] c"\0A@@@CLAP: There is a SC violation! \0A\00", align 1
@.str2 = private unnamed_addr constant [30 x i8] c"\1B[1;31m SC Violation!!! \1B[0m\0A\00", align 1
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
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 8)
  store i32 1, i32* @x, align 4, !dbg !37, !clap !38
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 8)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 9)
  store i32 1, i32* @y, align 4, !dbg !39, !clap !40
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 9)
  ret i8* null, !dbg !41, !clap !42
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

define i8* @P1(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !43
  %EAX = alloca i32, align 4, !clap !44
  %EBX = alloca i32, align 4, !clap !45
  store i8* %arg, i8** %arg.addr, align 4, !clap !46
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !47), !dbg !48, !clap !49
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !50), !dbg !52, !clap !53
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !54), !dbg !55, !clap !56
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 2, i32 0, i32 32, i32 18)
  store i32 2, i32* @y, align 4, !dbg !57, !clap !58
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 2, i32 0, i32 32, i32 18)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 19)
  %tmp = load i32* @y, align 4, !dbg !59, !clap !60
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 19)
  store i32 %tmp, i32* %EAX, align 4, !dbg !59, !clap !61
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 21)
  %tmp1 = load i32* @x, align 4, !dbg !62, !clap !63
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 21)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !62, !clap !64
  %tmp2 = load i32* %EAX, align 4, !dbg !65, !clap !66
  %tmp3 = load i32* %EBX, align 4, !dbg !65, !clap !67
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([31 x i8]* @.str, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !65, !clap !68
  %tmp4 = load i32* %EAX, align 4, !dbg !69, !clap !70
  %cmp = icmp eq i32 %tmp4, 2, !dbg !69, !clap !71
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !69, !clap !72

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !69, !clap !73
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !69, !clap !74
  br label %land.end, !clap !75

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !76
  %land.ext = zext i1 %tmp6 to i32, !clap !77
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !78
  ret i8* %tmp7, !dbg !79, !clap !80
}

declare i32 @printf(i8*, ...)

define i32 @main() nounwind {
entry:
  %retval = alloca i32, align 4, !clap !81
  %t0 = alloca i32, align 4, !clap !82
  %t1 = alloca i32, align 4, !clap !83
  %t2 = alloca i32, align 4, !clap !84
  %t3 = alloca i32, align 4, !clap !85
  %cond0 = alloca i32, align 4, !clap !86
  %cond1 = alloca i32, align 4, !clap !87
  %cond2 = alloca i32, align 4, !clap !88
  %cond3 = alloca i32, align 4, !clap !89
  store i32 0, i32* %retval, !clap !90
  call void @llvm.dbg.declare(metadata !{i32* %t0}, metadata !91), !dbg !95, !clap !96
  call void @llvm.dbg.declare(metadata !{i32* %t1}, metadata !97), !dbg !98, !clap !99
  call void @llvm.dbg.declare(metadata !{i32* %t2}, metadata !100), !dbg !101, !clap !102
  call void @llvm.dbg.declare(metadata !{i32* %t3}, metadata !103), !dbg !104, !clap !105
  call void @llvm.dbg.declare(metadata !{i32* %cond0}, metadata !106), !dbg !107, !clap !108
  call void @llvm.dbg.declare(metadata !{i32* %cond1}, metadata !109), !dbg !110, !clap !111
  call void @llvm.dbg.declare(metadata !{i32* %cond2}, metadata !112), !dbg !113, !clap !114
  call void @llvm.dbg.declare(metadata !{i32* %cond3}, metadata !115), !dbg !116, !clap !117
  %call = call i32 @clap_thread_create(i32* %t0, %union.pthread_attr_t* null, i8* (i8*)* @P0, i8* null) nounwind, !dbg !118, !clap !119
  %call1 = call i32 @clap_thread_create(i32* %t1, %union.pthread_attr_t* null, i8* (i8*)* @P1, i8* null) nounwind, !dbg !120, !clap !121
  %tmp = load i32* %t0, align 4, !dbg !122, !clap !123
  %call2 = call i32 @clap_thread_join(i32 %tmp, i8** null), !dbg !122, !clap !124
  %tmp1 = load i32* %t1, align 4, !dbg !125, !clap !126
  %tmp2 = bitcast i32* %cond1 to i8**, !dbg !125, !clap !127
  %call3 = call i32 @clap_thread_join(i32 %tmp1, i8** %tmp2), !dbg !125, !clap !128
  %tmp3 = load i32* %cond1, align 4, !dbg !129, !clap !130
  %tobool = icmp ne i32 %tmp3, 0, !dbg !129, !clap !131
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !129, !clap !132

land.lhs.true:                                    ; preds = %entry
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 64)
  %tmp4 = load i32* @y, align 4, !dbg !129, !clap !133
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 64)
  %cmp = icmp eq i32 %tmp4, 2, !dbg !129, !clap !134
  br i1 %cmp, label %if.then, label %if.end, !dbg !129, !clap !135

if.then:                                          ; preds = %land.lhs.true
  %call4 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([37 x i8]* @.str1, i32 0, i32 0)), !dbg !136, !clap !138
  %call5 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([30 x i8]* @.str2, i32 0, i32 0)), !dbg !139, !clap !140
  br label %if.end, !dbg !141, !clap !142

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  ret i32 0, !dbg !143, !clap !144
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

!0 = metadata !{i32 720913, i32 0, i32 12, metadata !"/home/naling/src/examples/tso/regression-examples/rfi007/rfi007.c", metadata !"/home/naling/src/inspect-0.3", metadata !"clang version 3.0 (tags/RELEASE_30/final)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !17} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !12, metadata !13}
!5 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P0", metadata !"P0", metadata !"", metadata !6, i32 30, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P0, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 720937, metadata !"/home/naling/src/examples/tso/regression-examples/rfi007/rfi007.c", metadata !"/home/naling/src/inspect-0.3", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{metadata !9}
!9 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ]
!10 = metadata !{metadata !11}
!11 = metadata !{i32 720932}                      ; [ DW_TAG_base_type ]
!12 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P1", metadata !"P1", metadata !"", metadata !6, i32 38, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P1, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!13 = metadata !{i32 720942, i32 0, metadata !6, metadata !"main", metadata !"main", metadata !"", metadata !6, i32 51, metadata !14, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i32 ()* @main, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!14 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !15, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!15 = metadata !{metadata !16}
!16 = metadata !{i32 720932, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!17 = metadata !{metadata !18}
!18 = metadata !{metadata !19, metadata !21, metadata !22}
!19 = metadata !{i32 720948, i32 0, null, metadata !"x", metadata !"x", metadata !"", metadata !6, i32 27, metadata !20, i32 0, i32 1, i32* @x} ; [ DW_TAG_variable ]
!20 = metadata !{i32 720932, null, metadata !"long int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!21 = metadata !{i32 720948, i32 0, null, metadata !"y", metadata !"y", metadata !"", metadata !6, i32 27, metadata !20, i32 0, i32 1, i32* @y} ; [ DW_TAG_variable ]
!22 = metadata !{i32 720948, i32 0, null, metadata !"z", metadata !"z", metadata !"", metadata !6, i32 27, metadata !20, i32 0, i32 1, i32* @z} ; [ DW_TAG_variable ]
!23 = metadata !{i32 1}
!24 = metadata !{i32 2}
!25 = metadata !{i32 3}
!26 = metadata !{i32 4}
!27 = metadata !{i32 721153, metadata !5, metadata !"arg", metadata !6, i32 16777245, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!28 = metadata !{i32 29, i32 16, metadata !5, null}
!29 = metadata !{i32 5}
!30 = metadata !{i32 721152, metadata !31, metadata !"EAX", metadata !6, i32 31, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!31 = metadata !{i32 720907, metadata !5, i32 30, i32 1, metadata !6, i32 0} ; [ DW_TAG_lexical_block ]
!32 = metadata !{i32 31, i32 12, metadata !31, null}
!33 = metadata !{i32 6}
!34 = metadata !{i32 721152, metadata !31, metadata !"EBX", metadata !6, i32 31, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!35 = metadata !{i32 31, i32 17, metadata !31, null}
!36 = metadata !{i32 7}
!37 = metadata !{i32 32, i32 3, metadata !31, null}
!38 = metadata !{i32 8}
!39 = metadata !{i32 33, i32 3, metadata !31, null}
!40 = metadata !{i32 9}
!41 = metadata !{i32 34, i32 3, metadata !31, null}
!42 = metadata !{i32 10}
!43 = metadata !{i32 11}
!44 = metadata !{i32 12}
!45 = metadata !{i32 13}
!46 = metadata !{i32 14}
!47 = metadata !{i32 721153, metadata !12, metadata !"arg", metadata !6, i32 16777253, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!48 = metadata !{i32 37, i32 16, metadata !12, null}
!49 = metadata !{i32 15}
!50 = metadata !{i32 721152, metadata !51, metadata !"EAX", metadata !6, i32 39, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!51 = metadata !{i32 720907, metadata !12, i32 38, i32 1, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!52 = metadata !{i32 39, i32 12, metadata !51, null}
!53 = metadata !{i32 16}
!54 = metadata !{i32 721152, metadata !51, metadata !"EBX", metadata !6, i32 39, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!55 = metadata !{i32 39, i32 17, metadata !51, null}
!56 = metadata !{i32 17}
!57 = metadata !{i32 40, i32 3, metadata !51, null}
!58 = metadata !{i32 18}
!59 = metadata !{i32 41, i32 3, metadata !51, null}
!60 = metadata !{i32 19}
!61 = metadata !{i32 20}
!62 = metadata !{i32 42, i32 3, metadata !51, null}
!63 = metadata !{i32 21}
!64 = metadata !{i32 22}
!65 = metadata !{i32 43, i32 3, metadata !51, null}
!66 = metadata !{i32 23}
!67 = metadata !{i32 24}
!68 = metadata !{i32 25}
!69 = metadata !{i32 44, i32 3, metadata !51, null}
!70 = metadata !{i32 26}
!71 = metadata !{i32 27}
!72 = metadata !{i32 28}
!73 = metadata !{i32 29}
!74 = metadata !{i32 30}
!75 = metadata !{i32 31}
!76 = metadata !{i32 32}
!77 = metadata !{i32 33}
!78 = metadata !{i32 34}
!79 = metadata !{i32 45, i32 1, metadata !12, null}
!80 = metadata !{i32 35}
!81 = metadata !{i32 36}
!82 = metadata !{i32 37}
!83 = metadata !{i32 38}
!84 = metadata !{i32 39}
!85 = metadata !{i32 40}
!86 = metadata !{i32 41}
!87 = metadata !{i32 42}
!88 = metadata !{i32 43}
!89 = metadata !{i32 44}
!90 = metadata !{i32 45}
!91 = metadata !{i32 721152, metadata !92, metadata !"t0", metadata !6, i32 52, metadata !93, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!92 = metadata !{i32 720907, metadata !13, i32 51, i32 1, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!93 = metadata !{i32 720918, null, metadata !"pthread_t", metadata !6, i32 60, i64 0, i64 0, i64 0, i32 0, metadata !94} ; [ DW_TAG_typedef ]
!94 = metadata !{i32 720932, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!95 = metadata !{i32 52, i32 13, metadata !92, null}
!96 = metadata !{i32 46}
!97 = metadata !{i32 721152, metadata !92, metadata !"t1", metadata !6, i32 52, metadata !93, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!98 = metadata !{i32 52, i32 17, metadata !92, null}
!99 = metadata !{i32 47}
!100 = metadata !{i32 721152, metadata !92, metadata !"t2", metadata !6, i32 52, metadata !93, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!101 = metadata !{i32 52, i32 21, metadata !92, null}
!102 = metadata !{i32 48}
!103 = metadata !{i32 721152, metadata !92, metadata !"t3", metadata !6, i32 52, metadata !93, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!104 = metadata !{i32 52, i32 25, metadata !92, null}
!105 = metadata !{i32 49}
!106 = metadata !{i32 721152, metadata !92, metadata !"cond0", metadata !6, i32 53, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!107 = metadata !{i32 53, i32 12, metadata !92, null}
!108 = metadata !{i32 50}
!109 = metadata !{i32 721152, metadata !92, metadata !"cond1", metadata !6, i32 53, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!110 = metadata !{i32 53, i32 19, metadata !92, null}
!111 = metadata !{i32 51}
!112 = metadata !{i32 721152, metadata !92, metadata !"cond2", metadata !6, i32 53, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!113 = metadata !{i32 53, i32 26, metadata !92, null}
!114 = metadata !{i32 52}
!115 = metadata !{i32 721152, metadata !92, metadata !"cond3", metadata !6, i32 53, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!116 = metadata !{i32 53, i32 33, metadata !92, null}
!117 = metadata !{i32 53}
!118 = metadata !{i32 55, i32 3, metadata !92, null}
!119 = metadata !{i32 54}
!120 = metadata !{i32 56, i32 3, metadata !92, null}
!121 = metadata !{i32 55}
!122 = metadata !{i32 58, i32 3, metadata !92, null}
!123 = metadata !{i32 56}
!124 = metadata !{i32 57}
!125 = metadata !{i32 59, i32 3, metadata !92, null}
!126 = metadata !{i32 58}
!127 = metadata !{i32 59}
!128 = metadata !{i32 60}
!129 = metadata !{i32 61, i32 3, metadata !92, null}
!130 = metadata !{i32 61}
!131 = metadata !{i32 62}
!132 = metadata !{i32 63}
!133 = metadata !{i32 64}
!134 = metadata !{i32 65}
!135 = metadata !{i32 66}
!136 = metadata !{i32 62, i32 5, metadata !137, null}
!137 = metadata !{i32 720907, metadata !92, i32 61, i32 24, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!138 = metadata !{i32 67}
!139 = metadata !{i32 63, i32 5, metadata !137, null}
!140 = metadata !{i32 68}
!141 = metadata !{i32 64, i32 3, metadata !137, null}
!142 = metadata !{i32 69}
!143 = metadata !{i32 66, i32 3, metadata !92, null}
!144 = metadata !{i32 70}
