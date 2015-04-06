; ModuleID = '/home/naling/src/examples/tso/regression-examples/mix003/mix003.c.lz.opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%union.pthread_attr_t = type { i32, [32 x i8] }

@z = common global i32 0, align 4
@x = common global i32 0, align 4
@.str = private unnamed_addr constant [23 x i8] c"\0A %%%% (EAX0=%d) %%%%\0A\00", align 1
@y = common global i32 0, align 4
@.str1 = private unnamed_addr constant [32 x i8] c"\0A %%%% (EAX1=%d, EBX1=%d) %%%%\0A\00", align 1
@.str2 = private unnamed_addr constant [32 x i8] c"\0A %%%% (EAX2=%d, EBX2=%d) %%%%\0A\00", align 1
@.str3 = private unnamed_addr constant [37 x i8] c"\0A@@@CLAP: There is a SC violation! \0A\00", align 1
@.str4 = private unnamed_addr constant [30 x i8] c"\1B[1;31m SC Violation!!! \1B[0m\0A\00", align 1

define i8* @P0(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !24
  %EAX = alloca i32, align 4, !clap !25
  %EBX = alloca i32, align 4, !clap !26
  store i8* %arg, i8** %arg.addr, align 4, !clap !27
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !28), !dbg !29, !clap !30
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !31), !dbg !33, !clap !34
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !35), !dbg !36, !clap !37
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @z, i32 1, i32 0, i32 32, i32 8)
  store i32 1, i32* @z, align 4, !dbg !38, !clap !39
  call void (i32, ...)* @clap_store_post(i32 5, i32* @z, i32 1, i32 0, i32 32, i32 8)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 9)
  %tmp = load i32* @x, align 4, !dbg !40, !clap !41
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 9)
  store i32 %tmp, i32* %EAX, align 4, !dbg !40, !clap !42
  %tmp1 = load i32* %EAX, align 4, !dbg !43, !clap !44
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([23 x i8]* @.str, i32 0, i32 0), i32 %tmp1), !dbg !43, !clap !45
  %tmp2 = load i32* %EAX, align 4, !dbg !46, !clap !47
  %cmp = icmp eq i32 %tmp2, 0, !dbg !46, !clap !48
  %conv = zext i1 %cmp to i32, !dbg !46, !clap !49
  %tmp3 = inttoptr i32 %conv to i8*, !dbg !46, !clap !50
  ret i8* %tmp3, !dbg !46, !clap !51
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare i32 @printf(i8*, ...)

define i8* @P1(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !52
  %EAX = alloca i32, align 4, !clap !53
  %EBX = alloca i32, align 4, !clap !54
  store i8* %arg, i8** %arg.addr, align 4, !clap !55
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !56), !dbg !57, !clap !58
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !59), !dbg !61, !clap !62
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !63), !dbg !64, !clap !65
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 25)
  store i32 1, i32* @x, align 4, !dbg !66, !clap !67
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 25)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 26)
  %tmp = load i32* @x, align 4, !dbg !68, !clap !69
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 26)
  store i32 %tmp, i32* %EAX, align 4, !dbg !68, !clap !70
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 28)
  %tmp1 = load i32* @y, align 4, !dbg !71, !clap !72
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 28)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !71, !clap !73
  %tmp2 = load i32* %EAX, align 4, !dbg !74, !clap !75
  %tmp3 = load i32* %EBX, align 4, !dbg !74, !clap !76
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([32 x i8]* @.str1, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !74, !clap !77
  %tmp4 = load i32* %EAX, align 4, !dbg !78, !clap !79
  %cmp = icmp eq i32 %tmp4, 1, !dbg !78, !clap !80
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !78, !clap !81

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !78, !clap !82
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !78, !clap !83
  br label %land.end, !clap !84

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !85
  %land.ext = zext i1 %tmp6 to i32, !clap !86
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !87
  ret i8* %tmp7, !dbg !88, !clap !89
}

define i8* @P2(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !90
  %EAX = alloca i32, align 4, !clap !91
  %EBX = alloca i32, align 4, !clap !92
  store i8* %arg, i8** %arg.addr, align 4, !clap !93
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !94), !dbg !95, !clap !96
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !97), !dbg !99, !clap !100
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !101), !dbg !102, !clap !103
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 50)
  store i32 1, i32* @y, align 4, !dbg !104, !clap !105
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 50)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 51)
  %tmp = load i32* @y, align 4, !dbg !106, !clap !107
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 51)
  store i32 %tmp, i32* %EAX, align 4, !dbg !106, !clap !108
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @z, i32 0, i32 32, i32 53)
  %tmp1 = load i32* @z, align 4, !dbg !109, !clap !110
  call void (i32, ...)* @clap_load_post(i32 4, i32* @z, i32 0, i32 32, i32 53)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !109, !clap !111
  %tmp2 = load i32* %EAX, align 4, !dbg !112, !clap !113
  %tmp3 = load i32* %EBX, align 4, !dbg !112, !clap !114
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([32 x i8]* @.str2, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !112, !clap !115
  %tmp4 = load i32* %EAX, align 4, !dbg !116, !clap !117
  %cmp = icmp eq i32 %tmp4, 1, !dbg !116, !clap !118
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !116, !clap !119

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !116, !clap !120
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !116, !clap !121
  br label %land.end, !clap !122

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !123
  %land.ext = zext i1 %tmp6 to i32, !clap !124
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !125
  ret i8* %tmp7, !dbg !126, !clap !127
}

define i32 @main() nounwind {
entry:
  %retval = alloca i32, align 4, !clap !128
  %t0 = alloca i32, align 4, !clap !129
  %t1 = alloca i32, align 4, !clap !130
  %t2 = alloca i32, align 4, !clap !131
  %cond0 = alloca i32, align 4, !clap !132
  %cond1 = alloca i32, align 4, !clap !133
  %cond2 = alloca i32, align 4, !clap !134
  store i32 0, i32* %retval, !clap !135
  call void @llvm.dbg.declare(metadata !{i32* %t0}, metadata !136), !dbg !140, !clap !141
  call void @llvm.dbg.declare(metadata !{i32* %t1}, metadata !142), !dbg !143, !clap !144
  call void @llvm.dbg.declare(metadata !{i32* %t2}, metadata !145), !dbg !146, !clap !147
  call void @llvm.dbg.declare(metadata !{i32* %cond0}, metadata !148), !dbg !149, !clap !150
  call void @llvm.dbg.declare(metadata !{i32* %cond1}, metadata !151), !dbg !152, !clap !153
  call void @llvm.dbg.declare(metadata !{i32* %cond2}, metadata !154), !dbg !155, !clap !156
  %call = call i32 @clap_thread_create(i32* %t0, %union.pthread_attr_t* null, i8* (i8*)* @P0, i8* null) nounwind, !dbg !157, !clap !158
  %call1 = call i32 @clap_thread_create(i32* %t1, %union.pthread_attr_t* null, i8* (i8*)* @P1, i8* null) nounwind, !dbg !159, !clap !160
  %call2 = call i32 @clap_thread_create(i32* %t2, %union.pthread_attr_t* null, i8* (i8*)* @P2, i8* null) nounwind, !dbg !161, !clap !162
  %tmp = load i32* %t0, align 4, !dbg !163, !clap !164
  %tmp1 = bitcast i32* %cond0 to i8**, !dbg !163, !clap !165
  %call3 = call i32 @clap_thread_join(i32 %tmp, i8** %tmp1), !dbg !163, !clap !166
  %tmp2 = load i32* %t1, align 4, !dbg !167, !clap !168
  %tmp3 = bitcast i32* %cond1 to i8**, !dbg !167, !clap !169
  %call4 = call i32 @clap_thread_join(i32 %tmp2, i8** %tmp3), !dbg !167, !clap !170
  %tmp4 = load i32* %t2, align 4, !dbg !171, !clap !172
  %tmp5 = bitcast i32* %cond2 to i8**, !dbg !171, !clap !173
  %call5 = call i32 @clap_thread_join(i32 %tmp4, i8** %tmp5), !dbg !171, !clap !174
  %tmp6 = load i32* %cond0, align 4, !dbg !175, !clap !176
  %tobool = icmp ne i32 %tmp6, 0, !dbg !175, !clap !177
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !175, !clap !178

land.lhs.true:                                    ; preds = %entry
  %tmp7 = load i32* %cond1, align 4, !dbg !175, !clap !179
  %tobool6 = icmp ne i32 %tmp7, 0, !dbg !175, !clap !180
  br i1 %tobool6, label %land.lhs.true7, label %if.end, !dbg !175, !clap !181

land.lhs.true7:                                   ; preds = %land.lhs.true
  %tmp8 = load i32* %cond2, align 4, !dbg !175, !clap !182
  %tobool8 = icmp ne i32 %tmp8, 0, !dbg !175, !clap !183
  br i1 %tobool8, label %if.then, label %if.end, !dbg !175, !clap !184

if.then:                                          ; preds = %land.lhs.true7
  %call9 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([37 x i8]* @.str3, i32 0, i32 0)), !dbg !185, !clap !187
  %call10 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([30 x i8]* @.str4, i32 0, i32 0)), !dbg !188, !clap !189
  br label %if.end, !dbg !190, !clap !191

if.end:                                           ; preds = %if.then, %land.lhs.true7, %land.lhs.true, %entry
  ret i32 0, !dbg !192, !clap !193
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

!0 = metadata !{i32 720913, i32 0, i32 12, metadata !"/home/naling/src/examples/tso/regression-examples/mix003/mix003.c", metadata !"/home/naling/src/inspect-0.3", metadata !"clang version 3.0 (tags/RELEASE_30/final)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !18} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !12, metadata !13, metadata !14}
!5 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P0", metadata !"P0", metadata !"", metadata !6, i32 32, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P0, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 720937, metadata !"/home/naling/src/examples/tso/regression-examples/mix003/mix003.c", metadata !"/home/naling/src/inspect-0.3", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{metadata !9}
!9 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ]
!10 = metadata !{metadata !11}
!11 = metadata !{i32 720932}                      ; [ DW_TAG_base_type ]
!12 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P1", metadata !"P1", metadata !"", metadata !6, i32 41, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P1, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!13 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P2", metadata !"P2", metadata !"", metadata !6, i32 51, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P2, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!14 = metadata !{i32 720942, i32 0, metadata !6, metadata !"main", metadata !"main", metadata !"", metadata !6, i32 61, metadata !15, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i32 ()* @main, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!15 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !16, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!16 = metadata !{metadata !17}
!17 = metadata !{i32 720932, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!18 = metadata !{metadata !19}
!19 = metadata !{metadata !20, metadata !22, metadata !23}
!20 = metadata !{i32 720948, i32 0, null, metadata !"x", metadata !"x", metadata !"", metadata !6, i32 29, metadata !21, i32 0, i32 1, i32* @x} ; [ DW_TAG_variable ]
!21 = metadata !{i32 720932, null, metadata !"long int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!22 = metadata !{i32 720948, i32 0, null, metadata !"y", metadata !"y", metadata !"", metadata !6, i32 29, metadata !21, i32 0, i32 1, i32* @y} ; [ DW_TAG_variable ]
!23 = metadata !{i32 720948, i32 0, null, metadata !"z", metadata !"z", metadata !"", metadata !6, i32 29, metadata !21, i32 0, i32 1, i32* @z} ; [ DW_TAG_variable ]
!24 = metadata !{i32 1}
!25 = metadata !{i32 2}
!26 = metadata !{i32 3}
!27 = metadata !{i32 4}
!28 = metadata !{i32 721153, metadata !5, metadata !"arg", metadata !6, i32 16777247, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!29 = metadata !{i32 31, i32 16, metadata !5, null}
!30 = metadata !{i32 5}
!31 = metadata !{i32 721152, metadata !32, metadata !"EAX", metadata !6, i32 33, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!32 = metadata !{i32 720907, metadata !5, i32 32, i32 1, metadata !6, i32 0} ; [ DW_TAG_lexical_block ]
!33 = metadata !{i32 33, i32 12, metadata !32, null}
!34 = metadata !{i32 6}
!35 = metadata !{i32 721152, metadata !32, metadata !"EBX", metadata !6, i32 33, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!36 = metadata !{i32 33, i32 17, metadata !32, null}
!37 = metadata !{i32 7}
!38 = metadata !{i32 34, i32 3, metadata !32, null}
!39 = metadata !{i32 8}
!40 = metadata !{i32 35, i32 3, metadata !32, null}
!41 = metadata !{i32 9}
!42 = metadata !{i32 10}
!43 = metadata !{i32 36, i32 3, metadata !32, null}
!44 = metadata !{i32 11}
!45 = metadata !{i32 12}
!46 = metadata !{i32 37, i32 3, metadata !32, null}
!47 = metadata !{i32 13}
!48 = metadata !{i32 14}
!49 = metadata !{i32 15}
!50 = metadata !{i32 16}
!51 = metadata !{i32 17}
!52 = metadata !{i32 18}
!53 = metadata !{i32 19}
!54 = metadata !{i32 20}
!55 = metadata !{i32 21}
!56 = metadata !{i32 721153, metadata !12, metadata !"arg", metadata !6, i32 16777256, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!57 = metadata !{i32 40, i32 16, metadata !12, null}
!58 = metadata !{i32 22}
!59 = metadata !{i32 721152, metadata !60, metadata !"EAX", metadata !6, i32 42, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!60 = metadata !{i32 720907, metadata !12, i32 41, i32 1, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!61 = metadata !{i32 42, i32 12, metadata !60, null}
!62 = metadata !{i32 23}
!63 = metadata !{i32 721152, metadata !60, metadata !"EBX", metadata !6, i32 42, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!64 = metadata !{i32 42, i32 17, metadata !60, null}
!65 = metadata !{i32 24}
!66 = metadata !{i32 43, i32 3, metadata !60, null}
!67 = metadata !{i32 25}
!68 = metadata !{i32 44, i32 3, metadata !60, null}
!69 = metadata !{i32 26}
!70 = metadata !{i32 27}
!71 = metadata !{i32 45, i32 3, metadata !60, null}
!72 = metadata !{i32 28}
!73 = metadata !{i32 29}
!74 = metadata !{i32 46, i32 3, metadata !60, null}
!75 = metadata !{i32 30}
!76 = metadata !{i32 31}
!77 = metadata !{i32 32}
!78 = metadata !{i32 47, i32 3, metadata !60, null}
!79 = metadata !{i32 33}
!80 = metadata !{i32 34}
!81 = metadata !{i32 35}
!82 = metadata !{i32 36}
!83 = metadata !{i32 37}
!84 = metadata !{i32 38}
!85 = metadata !{i32 39}
!86 = metadata !{i32 40}
!87 = metadata !{i32 41}
!88 = metadata !{i32 48, i32 1, metadata !12, null}
!89 = metadata !{i32 42}
!90 = metadata !{i32 43}
!91 = metadata !{i32 44}
!92 = metadata !{i32 45}
!93 = metadata !{i32 46}
!94 = metadata !{i32 721153, metadata !13, metadata !"arg", metadata !6, i32 16777266, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!95 = metadata !{i32 50, i32 16, metadata !13, null}
!96 = metadata !{i32 47}
!97 = metadata !{i32 721152, metadata !98, metadata !"EAX", metadata !6, i32 52, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!98 = metadata !{i32 720907, metadata !13, i32 51, i32 1, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!99 = metadata !{i32 52, i32 12, metadata !98, null}
!100 = metadata !{i32 48}
!101 = metadata !{i32 721152, metadata !98, metadata !"EBX", metadata !6, i32 52, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!102 = metadata !{i32 52, i32 17, metadata !98, null}
!103 = metadata !{i32 49}
!104 = metadata !{i32 53, i32 3, metadata !98, null}
!105 = metadata !{i32 50}
!106 = metadata !{i32 54, i32 3, metadata !98, null}
!107 = metadata !{i32 51}
!108 = metadata !{i32 52}
!109 = metadata !{i32 55, i32 3, metadata !98, null}
!110 = metadata !{i32 53}
!111 = metadata !{i32 54}
!112 = metadata !{i32 56, i32 3, metadata !98, null}
!113 = metadata !{i32 55}
!114 = metadata !{i32 56}
!115 = metadata !{i32 57}
!116 = metadata !{i32 57, i32 3, metadata !98, null}
!117 = metadata !{i32 58}
!118 = metadata !{i32 59}
!119 = metadata !{i32 60}
!120 = metadata !{i32 61}
!121 = metadata !{i32 62}
!122 = metadata !{i32 63}
!123 = metadata !{i32 64}
!124 = metadata !{i32 65}
!125 = metadata !{i32 66}
!126 = metadata !{i32 58, i32 1, metadata !13, null}
!127 = metadata !{i32 67}
!128 = metadata !{i32 68}
!129 = metadata !{i32 69}
!130 = metadata !{i32 70}
!131 = metadata !{i32 71}
!132 = metadata !{i32 72}
!133 = metadata !{i32 73}
!134 = metadata !{i32 74}
!135 = metadata !{i32 75}
!136 = metadata !{i32 721152, metadata !137, metadata !"t0", metadata !6, i32 62, metadata !138, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!137 = metadata !{i32 720907, metadata !14, i32 61, i32 1, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!138 = metadata !{i32 720918, null, metadata !"pthread_t", metadata !6, i32 60, i64 0, i64 0, i64 0, i32 0, metadata !139} ; [ DW_TAG_typedef ]
!139 = metadata !{i32 720932, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!140 = metadata !{i32 62, i32 13, metadata !137, null}
!141 = metadata !{i32 76}
!142 = metadata !{i32 721152, metadata !137, metadata !"t1", metadata !6, i32 62, metadata !138, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!143 = metadata !{i32 62, i32 17, metadata !137, null}
!144 = metadata !{i32 77}
!145 = metadata !{i32 721152, metadata !137, metadata !"t2", metadata !6, i32 62, metadata !138, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!146 = metadata !{i32 62, i32 21, metadata !137, null}
!147 = metadata !{i32 78}
!148 = metadata !{i32 721152, metadata !137, metadata !"cond0", metadata !6, i32 63, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!149 = metadata !{i32 63, i32 12, metadata !137, null}
!150 = metadata !{i32 79}
!151 = metadata !{i32 721152, metadata !137, metadata !"cond1", metadata !6, i32 63, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!152 = metadata !{i32 63, i32 19, metadata !137, null}
!153 = metadata !{i32 80}
!154 = metadata !{i32 721152, metadata !137, metadata !"cond2", metadata !6, i32 63, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!155 = metadata !{i32 63, i32 26, metadata !137, null}
!156 = metadata !{i32 81}
!157 = metadata !{i32 65, i32 3, metadata !137, null}
!158 = metadata !{i32 82}
!159 = metadata !{i32 66, i32 3, metadata !137, null}
!160 = metadata !{i32 83}
!161 = metadata !{i32 67, i32 3, metadata !137, null}
!162 = metadata !{i32 84}
!163 = metadata !{i32 69, i32 3, metadata !137, null}
!164 = metadata !{i32 85}
!165 = metadata !{i32 86}
!166 = metadata !{i32 87}
!167 = metadata !{i32 70, i32 3, metadata !137, null}
!168 = metadata !{i32 88}
!169 = metadata !{i32 89}
!170 = metadata !{i32 90}
!171 = metadata !{i32 71, i32 3, metadata !137, null}
!172 = metadata !{i32 91}
!173 = metadata !{i32 92}
!174 = metadata !{i32 93}
!175 = metadata !{i32 74, i32 3, metadata !137, null}
!176 = metadata !{i32 94}
!177 = metadata !{i32 95}
!178 = metadata !{i32 96}
!179 = metadata !{i32 97}
!180 = metadata !{i32 98}
!181 = metadata !{i32 99}
!182 = metadata !{i32 100}
!183 = metadata !{i32 101}
!184 = metadata !{i32 102}
!185 = metadata !{i32 75, i32 5, metadata !186, null}
!186 = metadata !{i32 720907, metadata !137, i32 74, i32 33, metadata !6, i32 4} ; [ DW_TAG_lexical_block ]
!187 = metadata !{i32 103}
!188 = metadata !{i32 76, i32 5, metadata !186, null}
!189 = metadata !{i32 104}
!190 = metadata !{i32 77, i32 3, metadata !186, null}
!191 = metadata !{i32 105}
!192 = metadata !{i32 79, i32 3, metadata !137, null}
!193 = metadata !{i32 106}
