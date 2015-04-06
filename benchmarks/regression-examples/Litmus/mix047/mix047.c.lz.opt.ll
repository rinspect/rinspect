; ModuleID = '/home/naling/src/examples/tso/regression-examples/mix047/mix047.c.lz.opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%union.pthread_attr_t = type { i32, [32 x i8] }

@b = common global i32 0, align 4
@x = common global i32 0, align 4
@y = common global i32 0, align 4
@z = common global i32 0, align 4
@a = common global i32 0, align 4
@.str = private unnamed_addr constant [32 x i8] c"\0A %%%% (EAX3=%d, EBX3=%d) %%%%\0A\00", align 1
@.str1 = private unnamed_addr constant [37 x i8] c"\0A@@@CLAP: There is a SC violation! \0A\00", align 1
@.str2 = private unnamed_addr constant [30 x i8] c"\1B[1;31m SC Violation!!! \1B[0m\0A\00", align 1

define i8* @P0(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !27
  %EAX = alloca i32, align 4, !clap !28
  %EBX = alloca i32, align 4, !clap !29
  store i8* %arg, i8** %arg.addr, align 4, !clap !30
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !31), !dbg !32, !clap !33
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !34), !dbg !36, !clap !37
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !38), !dbg !39, !clap !40
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @b, i32 1, i32 0, i32 32, i32 8)
  store i32 1, i32* @b, align 4, !dbg !41, !clap !42
  call void (i32, ...)* @clap_store_post(i32 5, i32* @b, i32 1, i32 0, i32 32, i32 8)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 9)
  store i32 1, i32* @x, align 4, !dbg !43, !clap !44
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 9)
  ret i8* inttoptr (i32 1 to i8*), !dbg !45, !clap !46
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

define i8* @P1(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !47
  %EAX = alloca i32, align 4, !clap !48
  %EBX = alloca i32, align 4, !clap !49
  store i8* %arg, i8** %arg.addr, align 4, !clap !50
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !51), !dbg !52, !clap !53
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !54), !dbg !56, !clap !57
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !58), !dbg !59, !clap !60
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 2, i32 0, i32 32, i32 18)
  store i32 2, i32* @x, align 4, !dbg !61, !clap !62
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 2, i32 0, i32 32, i32 18)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 19)
  store i32 1, i32* @y, align 4, !dbg !63, !clap !64
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 19)
  ret i8* inttoptr (i32 1 to i8*), !dbg !65, !clap !66
}

define i8* @P2(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !67
  %EAX = alloca i32, align 4, !clap !68
  %EBX = alloca i32, align 4, !clap !69
  store i8* %arg, i8** %arg.addr, align 4, !clap !70
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !71), !dbg !72, !clap !73
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !74), !dbg !76, !clap !77
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !78), !dbg !79, !clap !80
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 2, i32 0, i32 32, i32 28)
  store i32 2, i32* @y, align 4, !dbg !81, !clap !82
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 2, i32 0, i32 32, i32 28)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @z, i32 1, i32 0, i32 32, i32 29)
  store i32 1, i32* @z, align 4, !dbg !83, !clap !84
  call void (i32, ...)* @clap_store_post(i32 5, i32* @z, i32 1, i32 0, i32 32, i32 29)
  ret i8* inttoptr (i32 1 to i8*), !dbg !85, !clap !86
}

define i8* @P3(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !87
  %EAX = alloca i32, align 4, !clap !88
  %EBX = alloca i32, align 4, !clap !89
  store i8* %arg, i8** %arg.addr, align 4, !clap !90
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !91), !dbg !92, !clap !93
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !94), !dbg !96, !clap !97
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !98), !dbg !99, !clap !100
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @z, i32 2, i32 0, i32 32, i32 38)
  store i32 2, i32* @z, align 4, !dbg !101, !clap !102
  call void (i32, ...)* @clap_store_post(i32 5, i32* @z, i32 2, i32 0, i32 32, i32 38)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @a, i32 1, i32 0, i32 32, i32 39)
  store i32 1, i32* @a, align 4, !dbg !103, !clap !104
  call void (i32, ...)* @clap_store_post(i32 5, i32* @a, i32 1, i32 0, i32 32, i32 39)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @a, i32 0, i32 32, i32 40)
  %tmp = load i32* @a, align 4, !dbg !105, !clap !106
  call void (i32, ...)* @clap_load_post(i32 4, i32* @a, i32 0, i32 32, i32 40)
  store i32 %tmp, i32* %EAX, align 4, !dbg !105, !clap !107
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @b, i32 0, i32 32, i32 42)
  %tmp1 = load i32* @b, align 4, !dbg !108, !clap !109
  call void (i32, ...)* @clap_load_post(i32 4, i32* @b, i32 0, i32 32, i32 42)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !108, !clap !110
  %tmp2 = load i32* %EAX, align 4, !dbg !111, !clap !112
  %tmp3 = load i32* %EBX, align 4, !dbg !111, !clap !113
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([32 x i8]* @.str, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !111, !clap !114
  %tmp4 = load i32* %EAX, align 4, !dbg !115, !clap !116
  %cmp = icmp eq i32 %tmp4, 1, !dbg !115, !clap !117
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !115, !clap !118

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !115, !clap !119
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !115, !clap !120
  br label %land.end, !clap !121

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !122
  %land.ext = zext i1 %tmp6 to i32, !clap !123
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !124
  ret i8* %tmp7, !dbg !125, !clap !126
}

declare i32 @printf(i8*, ...)

define i32 @main() nounwind {
entry:
  %retval = alloca i32, align 4, !clap !127
  %t0 = alloca i32, align 4, !clap !128
  %t1 = alloca i32, align 4, !clap !129
  %t2 = alloca i32, align 4, !clap !130
  %t3 = alloca i32, align 4, !clap !131
  %cond0 = alloca i32, align 4, !clap !132
  %cond1 = alloca i32, align 4, !clap !133
  %cond2 = alloca i32, align 4, !clap !134
  %cond3 = alloca i32, align 4, !clap !135
  store i32 0, i32* %retval, !clap !136
  call void @llvm.dbg.declare(metadata !{i32* %t0}, metadata !137), !dbg !141, !clap !142
  call void @llvm.dbg.declare(metadata !{i32* %t1}, metadata !143), !dbg !144, !clap !145
  call void @llvm.dbg.declare(metadata !{i32* %t2}, metadata !146), !dbg !147, !clap !148
  call void @llvm.dbg.declare(metadata !{i32* %t3}, metadata !149), !dbg !150, !clap !151
  call void @llvm.dbg.declare(metadata !{i32* %cond0}, metadata !152), !dbg !153, !clap !154
  call void @llvm.dbg.declare(metadata !{i32* %cond1}, metadata !155), !dbg !156, !clap !157
  call void @llvm.dbg.declare(metadata !{i32* %cond2}, metadata !158), !dbg !159, !clap !160
  call void @llvm.dbg.declare(metadata !{i32* %cond3}, metadata !161), !dbg !162, !clap !163
  %call = call i32 @clap_thread_create(i32* %t0, %union.pthread_attr_t* null, i8* (i8*)* @P0, i8* null) nounwind, !dbg !164, !clap !165
  %call1 = call i32 @clap_thread_create(i32* %t1, %union.pthread_attr_t* null, i8* (i8*)* @P1, i8* null) nounwind, !dbg !166, !clap !167
  %call2 = call i32 @clap_thread_create(i32* %t2, %union.pthread_attr_t* null, i8* (i8*)* @P2, i8* null) nounwind, !dbg !168, !clap !169
  %call3 = call i32 @clap_thread_create(i32* %t3, %union.pthread_attr_t* null, i8* (i8*)* @P3, i8* null) nounwind, !dbg !170, !clap !171
  %tmp = load i32* %t0, align 4, !dbg !172, !clap !173
  %tmp1 = bitcast i32* %cond0 to i8**, !dbg !172, !clap !174
  %call4 = call i32 @clap_thread_join(i32 %tmp, i8** %tmp1), !dbg !172, !clap !175
  %tmp2 = load i32* %t1, align 4, !dbg !176, !clap !177
  %tmp3 = bitcast i32* %cond1 to i8**, !dbg !176, !clap !178
  %call5 = call i32 @clap_thread_join(i32 %tmp2, i8** %tmp3), !dbg !176, !clap !179
  %tmp4 = load i32* %t2, align 4, !dbg !180, !clap !181
  %tmp5 = bitcast i32* %cond2 to i8**, !dbg !180, !clap !182
  %call6 = call i32 @clap_thread_join(i32 %tmp4, i8** %tmp5), !dbg !180, !clap !183
  %tmp6 = load i32* %t3, align 4, !dbg !184, !clap !185
  %tmp7 = bitcast i32* %cond3 to i8**, !dbg !184, !clap !186
  %call7 = call i32 @clap_thread_join(i32 %tmp6, i8** %tmp7), !dbg !184, !clap !187
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 91)
  %tmp8 = load i32* @x, align 4, !dbg !188, !clap !189
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 91)
  %cmp = icmp eq i32 %tmp8, 2, !dbg !188, !clap !190
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !188, !clap !191

land.lhs.true:                                    ; preds = %entry
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 94)
  %tmp9 = load i32* @y, align 4, !dbg !188, !clap !192
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 94)
  %cmp8 = icmp eq i32 %tmp9, 2, !dbg !188, !clap !193
  br i1 %cmp8, label %land.lhs.true9, label %if.end, !dbg !188, !clap !194

land.lhs.true9:                                   ; preds = %land.lhs.true
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @z, i32 0, i32 32, i32 97)
  %tmp10 = load i32* @z, align 4, !dbg !188, !clap !195
  call void (i32, ...)* @clap_load_post(i32 4, i32* @z, i32 0, i32 32, i32 97)
  %cmp10 = icmp eq i32 %tmp10, 2, !dbg !188, !clap !196
  br i1 %cmp10, label %land.lhs.true11, label %if.end, !dbg !188, !clap !197

land.lhs.true11:                                  ; preds = %land.lhs.true9
  %tmp11 = load i32* %cond3, align 4, !dbg !188, !clap !198
  %tobool = icmp ne i32 %tmp11, 0, !dbg !188, !clap !199
  br i1 %tobool, label %if.then, label %if.end, !dbg !188, !clap !200

if.then:                                          ; preds = %land.lhs.true11
  %call12 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([37 x i8]* @.str1, i32 0, i32 0)), !dbg !201, !clap !203
  %call13 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([30 x i8]* @.str2, i32 0, i32 0)), !dbg !204, !clap !205
  br label %if.end, !dbg !206, !clap !207

if.end:                                           ; preds = %if.then, %land.lhs.true11, %land.lhs.true9, %land.lhs.true, %entry
  ret i32 0, !dbg !208, !clap !209
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

!0 = metadata !{i32 720913, i32 0, i32 12, metadata !"/home/naling/src/examples/tso/regression-examples/mix047/mix047.c", metadata !"/home/naling/src/inspect-0.3", metadata !"clang version 3.0 (tags/RELEASE_30/final)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !19} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !12, metadata !13, metadata !14, metadata !15}
!5 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P0", metadata !"P0", metadata !"", metadata !6, i32 33, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P0, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 720937, metadata !"/home/naling/src/examples/tso/regression-examples/mix047/mix047.c", metadata !"/home/naling/src/inspect-0.3", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{metadata !9}
!9 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ]
!10 = metadata !{metadata !11}
!11 = metadata !{i32 720932}                      ; [ DW_TAG_base_type ]
!12 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P1", metadata !"P1", metadata !"", metadata !6, i32 41, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P1, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!13 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P2", metadata !"P2", metadata !"", metadata !6, i32 49, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P2, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!14 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P3", metadata !"P3", metadata !"", metadata !6, i32 57, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P3, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!15 = metadata !{i32 720942, i32 0, metadata !6, metadata !"main", metadata !"main", metadata !"", metadata !6, i32 68, metadata !16, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i32 ()* @main, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!16 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !17, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!17 = metadata !{metadata !18}
!18 = metadata !{i32 720932, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!19 = metadata !{metadata !20}
!20 = metadata !{metadata !21, metadata !23, metadata !24, metadata !25, metadata !26}
!21 = metadata !{i32 720948, i32 0, null, metadata !"a", metadata !"a", metadata !"", metadata !6, i32 30, metadata !22, i32 0, i32 1, i32* @a} ; [ DW_TAG_variable ]
!22 = metadata !{i32 720932, null, metadata !"long int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!23 = metadata !{i32 720948, i32 0, null, metadata !"b", metadata !"b", metadata !"", metadata !6, i32 30, metadata !22, i32 0, i32 1, i32* @b} ; [ DW_TAG_variable ]
!24 = metadata !{i32 720948, i32 0, null, metadata !"x", metadata !"x", metadata !"", metadata !6, i32 30, metadata !22, i32 0, i32 1, i32* @x} ; [ DW_TAG_variable ]
!25 = metadata !{i32 720948, i32 0, null, metadata !"y", metadata !"y", metadata !"", metadata !6, i32 30, metadata !22, i32 0, i32 1, i32* @y} ; [ DW_TAG_variable ]
!26 = metadata !{i32 720948, i32 0, null, metadata !"z", metadata !"z", metadata !"", metadata !6, i32 30, metadata !22, i32 0, i32 1, i32* @z} ; [ DW_TAG_variable ]
!27 = metadata !{i32 1}
!28 = metadata !{i32 2}
!29 = metadata !{i32 3}
!30 = metadata !{i32 4}
!31 = metadata !{i32 721153, metadata !5, metadata !"arg", metadata !6, i32 16777248, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!32 = metadata !{i32 32, i32 16, metadata !5, null}
!33 = metadata !{i32 5}
!34 = metadata !{i32 721152, metadata !35, metadata !"EAX", metadata !6, i32 34, metadata !22, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!35 = metadata !{i32 720907, metadata !5, i32 33, i32 1, metadata !6, i32 0} ; [ DW_TAG_lexical_block ]
!36 = metadata !{i32 34, i32 12, metadata !35, null}
!37 = metadata !{i32 6}
!38 = metadata !{i32 721152, metadata !35, metadata !"EBX", metadata !6, i32 34, metadata !22, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!39 = metadata !{i32 34, i32 17, metadata !35, null}
!40 = metadata !{i32 7}
!41 = metadata !{i32 35, i32 3, metadata !35, null}
!42 = metadata !{i32 8}
!43 = metadata !{i32 36, i32 3, metadata !35, null}
!44 = metadata !{i32 9}
!45 = metadata !{i32 37, i32 3, metadata !35, null}
!46 = metadata !{i32 10}
!47 = metadata !{i32 11}
!48 = metadata !{i32 12}
!49 = metadata !{i32 13}
!50 = metadata !{i32 14}
!51 = metadata !{i32 721153, metadata !12, metadata !"arg", metadata !6, i32 16777256, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!52 = metadata !{i32 40, i32 16, metadata !12, null}
!53 = metadata !{i32 15}
!54 = metadata !{i32 721152, metadata !55, metadata !"EAX", metadata !6, i32 42, metadata !22, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!55 = metadata !{i32 720907, metadata !12, i32 41, i32 1, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!56 = metadata !{i32 42, i32 12, metadata !55, null}
!57 = metadata !{i32 16}
!58 = metadata !{i32 721152, metadata !55, metadata !"EBX", metadata !6, i32 42, metadata !22, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!59 = metadata !{i32 42, i32 17, metadata !55, null}
!60 = metadata !{i32 17}
!61 = metadata !{i32 43, i32 3, metadata !55, null}
!62 = metadata !{i32 18}
!63 = metadata !{i32 44, i32 3, metadata !55, null}
!64 = metadata !{i32 19}
!65 = metadata !{i32 45, i32 3, metadata !55, null}
!66 = metadata !{i32 20}
!67 = metadata !{i32 21}
!68 = metadata !{i32 22}
!69 = metadata !{i32 23}
!70 = metadata !{i32 24}
!71 = metadata !{i32 721153, metadata !13, metadata !"arg", metadata !6, i32 16777264, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!72 = metadata !{i32 48, i32 16, metadata !13, null}
!73 = metadata !{i32 25}
!74 = metadata !{i32 721152, metadata !75, metadata !"EAX", metadata !6, i32 50, metadata !22, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!75 = metadata !{i32 720907, metadata !13, i32 49, i32 1, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!76 = metadata !{i32 50, i32 12, metadata !75, null}
!77 = metadata !{i32 26}
!78 = metadata !{i32 721152, metadata !75, metadata !"EBX", metadata !6, i32 50, metadata !22, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!79 = metadata !{i32 50, i32 17, metadata !75, null}
!80 = metadata !{i32 27}
!81 = metadata !{i32 51, i32 3, metadata !75, null}
!82 = metadata !{i32 28}
!83 = metadata !{i32 52, i32 3, metadata !75, null}
!84 = metadata !{i32 29}
!85 = metadata !{i32 53, i32 3, metadata !75, null}
!86 = metadata !{i32 30}
!87 = metadata !{i32 31}
!88 = metadata !{i32 32}
!89 = metadata !{i32 33}
!90 = metadata !{i32 34}
!91 = metadata !{i32 721153, metadata !14, metadata !"arg", metadata !6, i32 16777272, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!92 = metadata !{i32 56, i32 16, metadata !14, null}
!93 = metadata !{i32 35}
!94 = metadata !{i32 721152, metadata !95, metadata !"EAX", metadata !6, i32 58, metadata !22, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!95 = metadata !{i32 720907, metadata !14, i32 57, i32 1, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!96 = metadata !{i32 58, i32 12, metadata !95, null}
!97 = metadata !{i32 36}
!98 = metadata !{i32 721152, metadata !95, metadata !"EBX", metadata !6, i32 58, metadata !22, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!99 = metadata !{i32 58, i32 17, metadata !95, null}
!100 = metadata !{i32 37}
!101 = metadata !{i32 59, i32 3, metadata !95, null}
!102 = metadata !{i32 38}
!103 = metadata !{i32 60, i32 3, metadata !95, null}
!104 = metadata !{i32 39}
!105 = metadata !{i32 61, i32 3, metadata !95, null}
!106 = metadata !{i32 40}
!107 = metadata !{i32 41}
!108 = metadata !{i32 62, i32 3, metadata !95, null}
!109 = metadata !{i32 42}
!110 = metadata !{i32 43}
!111 = metadata !{i32 63, i32 3, metadata !95, null}
!112 = metadata !{i32 44}
!113 = metadata !{i32 45}
!114 = metadata !{i32 46}
!115 = metadata !{i32 64, i32 3, metadata !95, null}
!116 = metadata !{i32 47}
!117 = metadata !{i32 48}
!118 = metadata !{i32 49}
!119 = metadata !{i32 50}
!120 = metadata !{i32 51}
!121 = metadata !{i32 52}
!122 = metadata !{i32 53}
!123 = metadata !{i32 54}
!124 = metadata !{i32 55}
!125 = metadata !{i32 65, i32 1, metadata !14, null}
!126 = metadata !{i32 56}
!127 = metadata !{i32 57}
!128 = metadata !{i32 58}
!129 = metadata !{i32 59}
!130 = metadata !{i32 60}
!131 = metadata !{i32 61}
!132 = metadata !{i32 62}
!133 = metadata !{i32 63}
!134 = metadata !{i32 64}
!135 = metadata !{i32 65}
!136 = metadata !{i32 66}
!137 = metadata !{i32 721152, metadata !138, metadata !"t0", metadata !6, i32 69, metadata !139, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!138 = metadata !{i32 720907, metadata !15, i32 68, i32 1, metadata !6, i32 4} ; [ DW_TAG_lexical_block ]
!139 = metadata !{i32 720918, null, metadata !"pthread_t", metadata !6, i32 60, i64 0, i64 0, i64 0, i32 0, metadata !140} ; [ DW_TAG_typedef ]
!140 = metadata !{i32 720932, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!141 = metadata !{i32 69, i32 13, metadata !138, null}
!142 = metadata !{i32 67}
!143 = metadata !{i32 721152, metadata !138, metadata !"t1", metadata !6, i32 69, metadata !139, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!144 = metadata !{i32 69, i32 17, metadata !138, null}
!145 = metadata !{i32 68}
!146 = metadata !{i32 721152, metadata !138, metadata !"t2", metadata !6, i32 69, metadata !139, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!147 = metadata !{i32 69, i32 21, metadata !138, null}
!148 = metadata !{i32 69}
!149 = metadata !{i32 721152, metadata !138, metadata !"t3", metadata !6, i32 69, metadata !139, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!150 = metadata !{i32 69, i32 25, metadata !138, null}
!151 = metadata !{i32 70}
!152 = metadata !{i32 721152, metadata !138, metadata !"cond0", metadata !6, i32 70, metadata !22, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!153 = metadata !{i32 70, i32 12, metadata !138, null}
!154 = metadata !{i32 71}
!155 = metadata !{i32 721152, metadata !138, metadata !"cond1", metadata !6, i32 70, metadata !22, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!156 = metadata !{i32 70, i32 19, metadata !138, null}
!157 = metadata !{i32 72}
!158 = metadata !{i32 721152, metadata !138, metadata !"cond2", metadata !6, i32 70, metadata !22, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!159 = metadata !{i32 70, i32 26, metadata !138, null}
!160 = metadata !{i32 73}
!161 = metadata !{i32 721152, metadata !138, metadata !"cond3", metadata !6, i32 70, metadata !22, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!162 = metadata !{i32 70, i32 33, metadata !138, null}
!163 = metadata !{i32 74}
!164 = metadata !{i32 72, i32 3, metadata !138, null}
!165 = metadata !{i32 75}
!166 = metadata !{i32 73, i32 3, metadata !138, null}
!167 = metadata !{i32 76}
!168 = metadata !{i32 74, i32 3, metadata !138, null}
!169 = metadata !{i32 77}
!170 = metadata !{i32 75, i32 3, metadata !138, null}
!171 = metadata !{i32 78}
!172 = metadata !{i32 77, i32 3, metadata !138, null}
!173 = metadata !{i32 79}
!174 = metadata !{i32 80}
!175 = metadata !{i32 81}
!176 = metadata !{i32 78, i32 3, metadata !138, null}
!177 = metadata !{i32 82}
!178 = metadata !{i32 83}
!179 = metadata !{i32 84}
!180 = metadata !{i32 79, i32 3, metadata !138, null}
!181 = metadata !{i32 85}
!182 = metadata !{i32 86}
!183 = metadata !{i32 87}
!184 = metadata !{i32 80, i32 3, metadata !138, null}
!185 = metadata !{i32 88}
!186 = metadata !{i32 89}
!187 = metadata !{i32 90}
!188 = metadata !{i32 83, i32 3, metadata !138, null}
!189 = metadata !{i32 91}
!190 = metadata !{i32 92}
!191 = metadata !{i32 93}
!192 = metadata !{i32 94}
!193 = metadata !{i32 95}
!194 = metadata !{i32 96}
!195 = metadata !{i32 97}
!196 = metadata !{i32 98}
!197 = metadata !{i32 99}
!198 = metadata !{i32 100}
!199 = metadata !{i32 101}
!200 = metadata !{i32 102}
!201 = metadata !{i32 84, i32 5, metadata !202, null}
!202 = metadata !{i32 720907, metadata !138, i32 83, i32 38, metadata !6, i32 5} ; [ DW_TAG_lexical_block ]
!203 = metadata !{i32 103}
!204 = metadata !{i32 85, i32 5, metadata !202, null}
!205 = metadata !{i32 104}
!206 = metadata !{i32 86, i32 3, metadata !202, null}
!207 = metadata !{i32 105}
!208 = metadata !{i32 88, i32 3, metadata !138, null}
!209 = metadata !{i32 106}
