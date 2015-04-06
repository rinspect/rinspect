; ModuleID = '/home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c.lz.opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%union.pthread_attr_t = type { i32, [32 x i8] }

@latch1 = global i32 1, align 4
@flag1 = global i32 1, align 4
@dummy = common global i32 0, align 4
@.str = private unnamed_addr constant [17 x i8] c"!latch1 || flag1\00", align 1
@.str1 = private unnamed_addr constant [100 x i8] c"/home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c\00", align 1
@__PRETTY_FUNCTION__.worker_1 = private unnamed_addr constant [23 x i8] c"void *worker_1(void *)\00", align 1
@flag2 = common global i32 0, align 4
@latch2 = common global i32 0, align 4
@.str2 = private unnamed_addr constant [17 x i8] c"!latch2 || flag2\00", align 1
@__PRETTY_FUNCTION__.worker_2 = private unnamed_addr constant [23 x i8] c"void *worker_2(void *)\00", align 1
@__unbuffered_tmp2 = common global i32 0, align 4

define void @MFENCE() nounwind {
entry:
  call void (i32, ...)* @clap_atomicrmw_pre(i32 5, i32* @dummy, i32 0, i32 7, i32 32, i32 1)
  %tmp = atomicrmw add i32* @dummy, i32 0 seq_cst, !dbg !28, !clap !30
  call void (i32, ...)* @clap_atomicrmw_post(i32 5, i32* @dummy, i32 0, i32 7, i32 32, i32 1)
  ret void, !dbg !31, !clap !32
}

define i8* @worker_1(i8* %arg) nounwind {
entry:
  %retval = alloca i8*, align 4, !clap !33
  %arg.addr = alloca i8*, align 4, !clap !34
  %n1 = alloca i32, align 4, !clap !35
  %n2 = alloca i32, align 4, !clap !36
  %n3 = alloca i32, align 4, !clap !37
  store i8* %arg, i8** %arg.addr, align 4, !clap !38
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !39), !dbg !40, !clap !41
  call void @llvm.dbg.declare(metadata !{i32* %n1}, metadata !42), !dbg !44, !clap !45
  store i32 0, i32* %n1, align 4, !dbg !46, !clap !47
  call void @llvm.dbg.declare(metadata !{i32* %n2}, metadata !48), !dbg !49, !clap !50
  store i32 0, i32* %n2, align 4, !dbg !51, !clap !52
  call void @llvm.dbg.declare(metadata !{i32* %n3}, metadata !53), !dbg !54, !clap !55
  store i32 0, i32* %n3, align 4, !dbg !51, !clap !56
  br label %for.cond, !dbg !57, !clap !59

for.cond:                                         ; preds = %if.end7, %entry
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @latch1, i32 0, i32 32, i32 17)
  %tmp = load i32* @latch1, align 4, !dbg !60, !clap !62
  call void (i32, ...)* @clap_load_post(i32 4, i32* @latch1, i32 0, i32 32, i32 17)
  %tobool = icmp ne i32 %tmp, 0, !dbg !60, !clap !63
  br i1 %tobool, label %if.end, label %if.then, !dbg !60, !clap !64

if.then:                                          ; preds = %for.cond
  br label %for.end, !dbg !65, !clap !67

if.end:                                           ; preds = %for.cond
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @latch1, i32 0, i32 32, i32 21)
  %tmp1 = load i32* @latch1, align 4, !dbg !68, !clap !69
  call void (i32, ...)* @clap_load_post(i32 4, i32* @latch1, i32 0, i32 32, i32 21)
  %tobool1 = icmp ne i32 %tmp1, 0, !dbg !68, !clap !70
  br i1 %tobool1, label %lor.lhs.false, label %cond.true, !dbg !68, !clap !71

lor.lhs.false:                                    ; preds = %if.end
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag1, i32 0, i32 32, i32 24)
  %tmp2 = load i32* @flag1, align 4, !dbg !68, !clap !72
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag1, i32 0, i32 32, i32 24)
  %tobool2 = icmp ne i32 %tmp2, 0, !dbg !68, !clap !73
  br i1 %tobool2, label %cond.true, label %cond.false, !dbg !68, !clap !74

cond.true:                                        ; preds = %lor.lhs.false, %if.end
  br label %cond.end, !dbg !68, !clap !75

cond.false:                                       ; preds = %lor.lhs.false
  call void @clap___assert_fail(i8* getelementptr inbounds ([17 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([100 x i8]* @.str1, i32 0, i32 0), i32 58, i8* getelementptr inbounds ([23 x i8]* @__PRETTY_FUNCTION__.worker_1, i32 0, i32 0)) noreturn nounwind, !dbg !68, !clap !76
  unreachable, !dbg !68, !clap !77

bb:                                               ; No predecessors!
  br label %cond.end, !dbg !68, !clap !78

cond.end:                                         ; preds = %bb, %cond.true
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @latch1, i32 0, i32 0, i32 32, i32 31)
  store i32 0, i32* @latch1, align 4, !dbg !79, !clap !80
  call void (i32, ...)* @clap_store_post(i32 5, i32* @latch1, i32 0, i32 0, i32 32, i32 31)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag1, i32 0, i32 32, i32 32)
  %tmp3 = load i32* @flag1, align 4, !dbg !81, !clap !82
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag1, i32 0, i32 32, i32 32)
  %tobool3 = icmp ne i32 %tmp3, 0, !dbg !81, !clap !83
  br i1 %tobool3, label %if.then4, label %if.end5, !dbg !81, !clap !84

if.then4:                                         ; preds = %cond.end
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @flag1, i32 0, i32 0, i32 32, i32 35)
  store i32 0, i32* @flag1, align 4, !dbg !85, !clap !87
  call void (i32, ...)* @clap_store_post(i32 5, i32* @flag1, i32 0, i32 0, i32 32, i32 35)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @flag2, i32 1, i32 0, i32 32, i32 36)
  store i32 1, i32* @flag2, align 4, !dbg !88, !clap !89
  call void (i32, ...)* @clap_store_post(i32 5, i32* @flag2, i32 1, i32 0, i32 32, i32 36)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @latch2, i32 1, i32 0, i32 32, i32 37)
  store i32 1, i32* @latch2, align 4, !dbg !90, !clap !91
  call void (i32, ...)* @clap_store_post(i32 5, i32* @latch2, i32 1, i32 0, i32 32, i32 37)
  br label %if.end5, !dbg !92, !clap !93

if.end5:                                          ; preds = %if.then4, %cond.end
  %tmp4 = load i32* %n1, align 4, !dbg !94, !clap !95
  %inc = add nsw i32 %tmp4, 1, !dbg !94, !clap !96
  store i32 %inc, i32* %n1, align 4, !dbg !94, !clap !97
  %cmp = icmp sgt i32 %tmp4, 1, !dbg !94, !clap !98
  br i1 %cmp, label %if.then6, label %if.end7, !dbg !94, !clap !99

if.then6:                                         ; preds = %if.end5
  br label %for.end, !dbg !100, !clap !101

if.end7:                                          ; preds = %if.end5
  br label %for.cond, !dbg !102, !clap !103

for.end:                                          ; preds = %if.then6, %if.then
  %tmp5 = load i8** %retval, !dbg !104, !clap !105
  ret i8* %tmp5, !dbg !104, !clap !106
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @clap___assert_fail(i8*, i8*, i32, i8*) noreturn nounwind

define i8* @worker_2(i8* %arg) nounwind {
entry:
  %retval = alloca i8*, align 4, !clap !107
  %arg.addr = alloca i8*, align 4, !clap !108
  %n1 = alloca i32, align 4, !clap !109
  %n2 = alloca i32, align 4, !clap !110
  %n3 = alloca i32, align 4, !clap !111
  store i8* %arg, i8** %arg.addr, align 4, !clap !112
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !113), !dbg !114, !clap !115
  call void @llvm.dbg.declare(metadata !{i32* %n1}, metadata !116), !dbg !118, !clap !119
  store i32 0, i32* %n1, align 4, !dbg !120, !clap !121
  call void @llvm.dbg.declare(metadata !{i32* %n2}, metadata !122), !dbg !123, !clap !124
  store i32 0, i32* %n2, align 4, !dbg !125, !clap !126
  call void @llvm.dbg.declare(metadata !{i32* %n3}, metadata !127), !dbg !128, !clap !129
  store i32 0, i32* %n3, align 4, !dbg !125, !clap !130
  br label %for.cond, !dbg !131, !clap !133

for.cond:                                         ; preds = %if.end7, %entry
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @latch2, i32 0, i32 32, i32 62)
  %tmp = load i32* @latch2, align 4, !dbg !134, !clap !136
  call void (i32, ...)* @clap_load_post(i32 4, i32* @latch2, i32 0, i32 32, i32 62)
  %tobool = icmp ne i32 %tmp, 0, !dbg !134, !clap !137
  br i1 %tobool, label %if.end, label %if.then, !dbg !134, !clap !138

if.then:                                          ; preds = %for.cond
  br label %for.end, !dbg !139, !clap !141

if.end:                                           ; preds = %for.cond
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @latch2, i32 0, i32 32, i32 66)
  %tmp1 = load i32* @latch2, align 4, !dbg !142, !clap !143
  call void (i32, ...)* @clap_load_post(i32 4, i32* @latch2, i32 0, i32 32, i32 66)
  %tobool1 = icmp ne i32 %tmp1, 0, !dbg !142, !clap !144
  br i1 %tobool1, label %lor.lhs.false, label %cond.true, !dbg !142, !clap !145

lor.lhs.false:                                    ; preds = %if.end
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag2, i32 0, i32 32, i32 69)
  %tmp2 = load i32* @flag2, align 4, !dbg !142, !clap !146
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag2, i32 0, i32 32, i32 69)
  %tobool2 = icmp ne i32 %tmp2, 0, !dbg !142, !clap !147
  br i1 %tobool2, label %cond.true, label %cond.false, !dbg !142, !clap !148

cond.true:                                        ; preds = %lor.lhs.false, %if.end
  br label %cond.end, !dbg !142, !clap !149

cond.false:                                       ; preds = %lor.lhs.false
  call void @clap___assert_fail(i8* getelementptr inbounds ([17 x i8]* @.str2, i32 0, i32 0), i8* getelementptr inbounds ([100 x i8]* @.str1, i32 0, i32 0), i32 81, i8* getelementptr inbounds ([23 x i8]* @__PRETTY_FUNCTION__.worker_2, i32 0, i32 0)) noreturn nounwind, !dbg !142, !clap !150
  unreachable, !dbg !142, !clap !151

bb:                                               ; No predecessors!
  br label %cond.end, !dbg !142, !clap !152

cond.end:                                         ; preds = %bb, %cond.true
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @latch2, i32 0, i32 0, i32 32, i32 76)
  store i32 0, i32* @latch2, align 4, !dbg !153, !clap !154
  call void (i32, ...)* @clap_store_post(i32 5, i32* @latch2, i32 0, i32 0, i32 32, i32 76)
  call void @MFENCE(), !dbg !155, !clap !156
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag2, i32 0, i32 32, i32 78)
  %tmp3 = load i32* @flag2, align 4, !dbg !157, !clap !158
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag2, i32 0, i32 32, i32 78)
  %tobool3 = icmp ne i32 %tmp3, 0, !dbg !157, !clap !159
  br i1 %tobool3, label %if.then4, label %if.end5, !dbg !157, !clap !160

if.then4:                                         ; preds = %cond.end
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @flag2, i32 0, i32 0, i32 32, i32 81)
  store i32 0, i32* @flag2, align 4, !dbg !161, !clap !163
  call void (i32, ...)* @clap_store_post(i32 5, i32* @flag2, i32 0, i32 0, i32 32, i32 81)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @flag1, i32 1, i32 0, i32 32, i32 82)
  store i32 1, i32* @flag1, align 4, !dbg !164, !clap !165
  call void (i32, ...)* @clap_store_post(i32 5, i32* @flag1, i32 1, i32 0, i32 32, i32 82)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @latch1, i32 1, i32 0, i32 32, i32 83)
  store i32 1, i32* @latch1, align 4, !dbg !166, !clap !167
  call void (i32, ...)* @clap_store_post(i32 5, i32* @latch1, i32 1, i32 0, i32 32, i32 83)
  br label %if.end5, !dbg !168, !clap !169

if.end5:                                          ; preds = %if.then4, %cond.end
  %tmp4 = load i32* %n1, align 4, !dbg !170, !clap !171
  %inc = add nsw i32 %tmp4, 1, !dbg !170, !clap !172
  store i32 %inc, i32* %n1, align 4, !dbg !170, !clap !173
  %cmp = icmp sgt i32 %tmp4, 1, !dbg !170, !clap !174
  br i1 %cmp, label %if.then6, label %if.end7, !dbg !170, !clap !175

if.then6:                                         ; preds = %if.end5
  br label %for.end, !dbg !176, !clap !177

if.end7:                                          ; preds = %if.end5
  br label %for.cond, !dbg !178, !clap !179

for.end:                                          ; preds = %if.then6, %if.then
  %tmp5 = load i8** %retval, !dbg !180, !clap !181
  ret i8* %tmp5, !dbg !180, !clap !182
}

define i32 @main() nounwind {
entry:
  %retval = alloca i32, align 4, !clap !183
  %t1 = alloca i32, align 4, !clap !184
  %t2 = alloca i32, align 4, !clap !185
  store i32 0, i32* %retval, !clap !186
  call void @llvm.dbg.declare(metadata !{i32* %t1}, metadata !187), !dbg !191, !clap !192
  call void @llvm.dbg.declare(metadata !{i32* %t2}, metadata !193), !dbg !194, !clap !195
  %call = call i32 @clap_thread_create(i32* %t1, %union.pthread_attr_t* null, i8* (i8*)* @worker_1, i8* null) nounwind, !dbg !196, !clap !197
  %call1 = call i32 @clap_thread_create(i32* %t2, %union.pthread_attr_t* null, i8* (i8*)* @worker_2, i8* null) nounwind, !dbg !198, !clap !199
  %tmp = load i32* %t1, align 4, !dbg !200, !clap !201
  %call2 = call i32 @clap_thread_join(i32 %tmp, i8** null), !dbg !200, !clap !202
  %tmp1 = load i32* %t2, align 4, !dbg !203, !clap !204
  %call3 = call i32 @clap_thread_join(i32 %tmp1, i8** null), !dbg !203, !clap !205
  ret i32 0, !dbg !206, !clap !207
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

!0 = metadata !{i32 720913, i32 0, i32 12, metadata !"/home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c", metadata !"/home/naling/src/inspect-0.3", metadata !"clang version 3.0 (tags/RELEASE_30/final)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !20} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !11, metadata !15, metadata !16}
!5 = metadata !{i32 720942, i32 0, metadata !6, metadata !"MFENCE", metadata !"MFENCE", metadata !"", metadata !6, i32 18, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 0, i1 false, void ()* @MFENCE, null, null, metadata !9} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 720937, metadata !"/home/naling/src/examples/tso/regression-examples/pgsql_two-developer-fix/pgsql_two-developer-fix.c", metadata !"/home/naling/src/inspect-0.3", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{null}
!9 = metadata !{metadata !10}
!10 = metadata !{i32 720932}                      ; [ DW_TAG_base_type ]
!11 = metadata !{i32 720942, i32 0, metadata !6, metadata !"worker_1", metadata !"worker_1", metadata !"", metadata !6, i32 49, metadata !12, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @worker_1, null, null, metadata !9} ; [ DW_TAG_subprogram ]
!12 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !13, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!13 = metadata !{metadata !14}
!14 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ]
!15 = metadata !{i32 720942, i32 0, metadata !6, metadata !"worker_2", metadata !"worker_2", metadata !"", metadata !6, i32 72, metadata !12, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @worker_2, null, null, metadata !9} ; [ DW_TAG_subprogram ]
!16 = metadata !{i32 720942, i32 0, metadata !6, metadata !"main", metadata !"main", metadata !"", metadata !6, i32 111, metadata !17, i1 false, i1 true, i32 0, i32 0, i32 0, i32 0, i1 false, i32 ()* @main, null, null, metadata !9} ; [ DW_TAG_subprogram ]
!17 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !18, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!18 = metadata !{metadata !19}
!19 = metadata !{i32 720932, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!20 = metadata !{metadata !21}
!21 = metadata !{metadata !22, metadata !23, metadata !24, metadata !25, metadata !26, metadata !27}
!22 = metadata !{i32 720948, i32 0, null, metadata !"latch1", metadata !"latch1", metadata !"", metadata !6, i32 11, metadata !19, i32 0, i32 1, i32* @latch1} ; [ DW_TAG_variable ]
!23 = metadata !{i32 720948, i32 0, null, metadata !"flag1", metadata !"flag1", metadata !"", metadata !6, i32 12, metadata !19, i32 0, i32 1, i32* @flag1} ; [ DW_TAG_variable ]
!24 = metadata !{i32 720948, i32 0, null, metadata !"latch2", metadata !"latch2", metadata !"", metadata !6, i32 13, metadata !19, i32 0, i32 1, i32* @latch2} ; [ DW_TAG_variable ]
!25 = metadata !{i32 720948, i32 0, null, metadata !"flag2", metadata !"flag2", metadata !"", metadata !6, i32 13, metadata !19, i32 0, i32 1, i32* @flag2} ; [ DW_TAG_variable ]
!26 = metadata !{i32 720948, i32 0, null, metadata !"dummy", metadata !"dummy", metadata !"", metadata !6, i32 18, metadata !19, i32 0, i32 1, i32* @dummy} ; [ DW_TAG_variable ]
!27 = metadata !{i32 720948, i32 0, null, metadata !"__unbuffered_tmp2", metadata !"__unbuffered_tmp2", metadata !"", metadata !6, i32 20, metadata !19, i32 0, i32 1, i32* @__unbuffered_tmp2} ; [ DW_TAG_variable ]
!28 = metadata !{i32 18, i32 27, metadata !29, null}
!29 = metadata !{i32 720907, metadata !5, i32 18, i32 25, metadata !6, i32 0} ; [ DW_TAG_lexical_block ]
!30 = metadata !{i32 1}
!31 = metadata !{i32 18, i32 59, metadata !29, null}
!32 = metadata !{i32 2}
!33 = metadata !{i32 3}
!34 = metadata !{i32 4}
!35 = metadata !{i32 5}
!36 = metadata !{i32 6}
!37 = metadata !{i32 7}
!38 = metadata !{i32 8}
!39 = metadata !{i32 721153, metadata !11, metadata !"arg", metadata !6, i32 16777264, metadata !14, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!40 = metadata !{i32 48, i32 22, metadata !11, null}
!41 = metadata !{i32 9}
!42 = metadata !{i32 721152, metadata !43, metadata !"n1", metadata !6, i32 50, metadata !19, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!43 = metadata !{i32 720907, metadata !11, i32 49, i32 1, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!44 = metadata !{i32 50, i32 9, metadata !43, null}
!45 = metadata !{i32 10}
!46 = metadata !{i32 50, i32 13, metadata !43, null}
!47 = metadata !{i32 11}
!48 = metadata !{i32 721152, metadata !43, metadata !"n2", metadata !6, i32 50, metadata !19, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!49 = metadata !{i32 50, i32 18, metadata !43, null}
!50 = metadata !{i32 12}
!51 = metadata !{i32 50, i32 27, metadata !43, null}
!52 = metadata !{i32 13}
!53 = metadata !{i32 721152, metadata !43, metadata !"n3", metadata !6, i32 50, metadata !19, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!54 = metadata !{i32 50, i32 23, metadata !43, null}
!55 = metadata !{i32 14}
!56 = metadata !{i32 15}
!57 = metadata !{i32 52, i32 5, metadata !58, null}
!58 = metadata !{i32 720907, metadata !43, i32 52, i32 5, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!59 = metadata !{i32 16}
!60 = metadata !{i32 55, i32 2, metadata !61, null}
!61 = metadata !{i32 720907, metadata !58, i32 53, i32 5, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!62 = metadata !{i32 17}
!63 = metadata !{i32 18}
!64 = metadata !{i32 19}
!65 = metadata !{i32 56, i32 6, metadata !66, null}
!66 = metadata !{i32 720907, metadata !61, i32 55, i32 13, metadata !6, i32 4} ; [ DW_TAG_lexical_block ]
!67 = metadata !{i32 20}
!68 = metadata !{i32 58, i32 2, metadata !61, null}
!69 = metadata !{i32 21}
!70 = metadata !{i32 22}
!71 = metadata !{i32 23}
!72 = metadata !{i32 24}
!73 = metadata !{i32 25}
!74 = metadata !{i32 26}
!75 = metadata !{i32 27}
!76 = metadata !{i32 28}
!77 = metadata !{i32 29}
!78 = metadata !{i32 30}
!79 = metadata !{i32 59, i32 2, metadata !61, null}
!80 = metadata !{i32 31}
!81 = metadata !{i32 60, i32 2, metadata !61, null}
!82 = metadata !{i32 32}
!83 = metadata !{i32 33}
!84 = metadata !{i32 34}
!85 = metadata !{i32 62, i32 6, metadata !86, null}
!86 = metadata !{i32 720907, metadata !61, i32 61, i32 2, metadata !6, i32 5} ; [ DW_TAG_lexical_block ]
!87 = metadata !{i32 35}
!88 = metadata !{i32 63, i32 6, metadata !86, null}
!89 = metadata !{i32 36}
!90 = metadata !{i32 64, i32 6, metadata !86, null}
!91 = metadata !{i32 37}
!92 = metadata !{i32 65, i32 2, metadata !86, null}
!93 = metadata !{i32 38}
!94 = metadata !{i32 66, i32 2, metadata !61, null}
!95 = metadata !{i32 39}
!96 = metadata !{i32 40}
!97 = metadata !{i32 41}
!98 = metadata !{i32 42}
!99 = metadata !{i32 43}
!100 = metadata !{i32 66, i32 14, metadata !61, null}
!101 = metadata !{i32 44}
!102 = metadata !{i32 68, i32 5, metadata !61, null}
!103 = metadata !{i32 45}
!104 = metadata !{i32 69, i32 1, metadata !43, null}
!105 = metadata !{i32 46}
!106 = metadata !{i32 47}
!107 = metadata !{i32 48}
!108 = metadata !{i32 49}
!109 = metadata !{i32 50}
!110 = metadata !{i32 51}
!111 = metadata !{i32 52}
!112 = metadata !{i32 53}
!113 = metadata !{i32 721153, metadata !15, metadata !"arg", metadata !6, i32 16777287, metadata !14, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!114 = metadata !{i32 71, i32 22, metadata !15, null}
!115 = metadata !{i32 54}
!116 = metadata !{i32 721152, metadata !117, metadata !"n1", metadata !6, i32 74, metadata !19, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!117 = metadata !{i32 720907, metadata !15, i32 72, i32 1, metadata !6, i32 6} ; [ DW_TAG_lexical_block ]
!118 = metadata !{i32 74, i32 9, metadata !117, null}
!119 = metadata !{i32 55}
!120 = metadata !{i32 74, i32 13, metadata !117, null}
!121 = metadata !{i32 56}
!122 = metadata !{i32 721152, metadata !117, metadata !"n2", metadata !6, i32 74, metadata !19, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!123 = metadata !{i32 74, i32 18, metadata !117, null}
!124 = metadata !{i32 57}
!125 = metadata !{i32 74, i32 27, metadata !117, null}
!126 = metadata !{i32 58}
!127 = metadata !{i32 721152, metadata !117, metadata !"n3", metadata !6, i32 74, metadata !19, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!128 = metadata !{i32 74, i32 23, metadata !117, null}
!129 = metadata !{i32 59}
!130 = metadata !{i32 60}
!131 = metadata !{i32 75, i32 5, metadata !132, null}
!132 = metadata !{i32 720907, metadata !117, i32 75, i32 5, metadata !6, i32 7} ; [ DW_TAG_lexical_block ]
!133 = metadata !{i32 61}
!134 = metadata !{i32 78, i32 2, metadata !135, null}
!135 = metadata !{i32 720907, metadata !132, i32 76, i32 5, metadata !6, i32 8} ; [ DW_TAG_lexical_block ]
!136 = metadata !{i32 62}
!137 = metadata !{i32 63}
!138 = metadata !{i32 64}
!139 = metadata !{i32 79, i32 6, metadata !140, null}
!140 = metadata !{i32 720907, metadata !135, i32 78, i32 13, metadata !6, i32 9} ; [ DW_TAG_lexical_block ]
!141 = metadata !{i32 65}
!142 = metadata !{i32 81, i32 2, metadata !135, null}
!143 = metadata !{i32 66}
!144 = metadata !{i32 67}
!145 = metadata !{i32 68}
!146 = metadata !{i32 69}
!147 = metadata !{i32 70}
!148 = metadata !{i32 71}
!149 = metadata !{i32 72}
!150 = metadata !{i32 73}
!151 = metadata !{i32 74}
!152 = metadata !{i32 75}
!153 = metadata !{i32 82, i32 2, metadata !135, null}
!154 = metadata !{i32 76}
!155 = metadata !{i32 84, i32 2, metadata !135, null}
!156 = metadata !{i32 77}
!157 = metadata !{i32 86, i32 2, metadata !135, null}
!158 = metadata !{i32 78}
!159 = metadata !{i32 79}
!160 = metadata !{i32 80}
!161 = metadata !{i32 88, i32 6, metadata !162, null}
!162 = metadata !{i32 720907, metadata !135, i32 87, i32 2, metadata !6, i32 10} ; [ DW_TAG_lexical_block ]
!163 = metadata !{i32 81}
!164 = metadata !{i32 89, i32 6, metadata !162, null}
!165 = metadata !{i32 82}
!166 = metadata !{i32 91, i32 6, metadata !162, null}
!167 = metadata !{i32 83}
!168 = metadata !{i32 92, i32 2, metadata !162, null}
!169 = metadata !{i32 84}
!170 = metadata !{i32 93, i32 2, metadata !135, null}
!171 = metadata !{i32 85}
!172 = metadata !{i32 86}
!173 = metadata !{i32 87}
!174 = metadata !{i32 88}
!175 = metadata !{i32 89}
!176 = metadata !{i32 93, i32 14, metadata !135, null}
!177 = metadata !{i32 90}
!178 = metadata !{i32 96, i32 5, metadata !135, null}
!179 = metadata !{i32 91}
!180 = metadata !{i32 97, i32 1, metadata !117, null}
!181 = metadata !{i32 92}
!182 = metadata !{i32 93}
!183 = metadata !{i32 94}
!184 = metadata !{i32 95}
!185 = metadata !{i32 96}
!186 = metadata !{i32 97}
!187 = metadata !{i32 721152, metadata !188, metadata !"t1", metadata !6, i32 114, metadata !189, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!188 = metadata !{i32 720907, metadata !16, i32 111, i32 1, metadata !6, i32 11} ; [ DW_TAG_lexical_block ]
!189 = metadata !{i32 720918, null, metadata !"pthread_t", metadata !6, i32 60, i64 0, i64 0, i64 0, i32 0, metadata !190} ; [ DW_TAG_typedef ]
!190 = metadata !{i32 720932, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!191 = metadata !{i32 114, i32 15, metadata !188, null}
!192 = metadata !{i32 98}
!193 = metadata !{i32 721152, metadata !188, metadata !"t2", metadata !6, i32 114, metadata !189, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!194 = metadata !{i32 114, i32 19, metadata !188, null}
!195 = metadata !{i32 99}
!196 = metadata !{i32 116, i32 5, metadata !188, null}
!197 = metadata !{i32 100}
!198 = metadata !{i32 117, i32 5, metadata !188, null}
!199 = metadata !{i32 101}
!200 = metadata !{i32 119, i32 5, metadata !188, null}
!201 = metadata !{i32 102}
!202 = metadata !{i32 103}
!203 = metadata !{i32 120, i32 5, metadata !188, null}
!204 = metadata !{i32 104}
!205 = metadata !{i32 105}
!206 = metadata !{i32 128, i32 3, metadata !188, null}
!207 = metadata !{i32 106}
