; ModuleID = '/home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c.lz.opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%union.pthread_attr_t = type { i32, [32 x i8] }

@latch1 = global i32 1, align 4
@flag1 = global i32 1, align 4
@latch2 = global i32 0, align 4
@flag2 = global i32 0, align 4
@dummy = common global i32 0, align 4
@.str = private unnamed_addr constant [8 x i8] c"worker1\00", align 1
@.str1 = private unnamed_addr constant [8 x i8] c"worker2\00", align 1
@__unbuffered_tmp2 = common global i32 0, align 4

define void @MFENCE() nounwind {
entry:
  call void (i32, ...)* @clap_atomicrmw_pre(i32 5, i32* @dummy, i32 0, i32 7, i32 32, i32 1)
  %tmp = atomicrmw add i32* @dummy, i32 0 seq_cst, !dbg !35, !clap !37
  call void (i32, ...)* @clap_atomicrmw_post(i32 5, i32* @dummy, i32 0, i32 7, i32 32, i32 1)
  ret void, !dbg !38, !clap !39
}

define i8* @worker_1(i8* %arg) nounwind {
entry:
  %retval = alloca i8*, align 4, !clap !40
  %arg.addr = alloca i8*, align 4, !clap !41
  %n1 = alloca i32, align 4, !clap !42
  %n2 = alloca i32, align 4, !clap !43
  %n3 = alloca i32, align 4, !clap !44
  store i8* %arg, i8** %arg.addr, align 4, !clap !45
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !46), !dbg !47, !clap !48
  call void @llvm.dbg.declare(metadata !{i32* %n1}, metadata !49), !dbg !51, !clap !52
  store i32 0, i32* %n1, align 4, !dbg !53, !clap !54
  call void @llvm.dbg.declare(metadata !{i32* %n2}, metadata !55), !dbg !56, !clap !57
  store i32 0, i32* %n2, align 4, !dbg !58, !clap !59
  call void @llvm.dbg.declare(metadata !{i32* %n3}, metadata !60), !dbg !61, !clap !62
  store i32 0, i32* %n3, align 4, !dbg !58, !clap !63
  br label %for.cond, !dbg !64, !clap !66

for.cond:                                         ; preds = %if.end9, %entry
  br label %while.cond, !dbg !67, !clap !69

while.cond:                                       ; preds = %while.body, %for.cond
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @latch1, i32 0, i32 32, i32 18)
  %tmp = load i32* @latch1, align 4, !dbg !67, !clap !70
  call void (i32, ...)* @clap_load_post(i32 4, i32* @latch1, i32 0, i32 32, i32 18)
  %tobool = icmp ne i32 %tmp, 0, !dbg !67, !clap !71
  %lnot = xor i1 %tobool, true, !dbg !67, !clap !72
  br i1 %lnot, label %while.body, label %while.end, !dbg !67, !clap !73

while.body:                                       ; preds = %while.cond
  br label %while.cond, !dbg !74, !clap !76

while.end:                                        ; preds = %while.cond
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @latch1, i32 0, i32 32, i32 23)
  %tmp1 = load i32* @latch1, align 4, !dbg !77, !clap !78
  call void (i32, ...)* @clap_load_post(i32 4, i32* @latch1, i32 0, i32 32, i32 23)
  %tobool1 = icmp ne i32 %tmp1, 0, !dbg !77, !clap !79
  %lnot2 = xor i1 %tobool1, true, !dbg !77, !clap !80
  %lnot.ext = zext i1 %lnot2 to i32, !dbg !77, !clap !81
  %cmp = icmp eq i32 %lnot.ext, 0, !dbg !77, !clap !82
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !77, !clap !83

land.lhs.true:                                    ; preds = %while.end
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag1, i32 0, i32 32, i32 29)
  %tmp2 = load i32* @flag1, align 4, !dbg !77, !clap !84
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag1, i32 0, i32 32, i32 29)
  %cmp3 = icmp eq i32 %tmp2, 0, !dbg !77, !clap !85
  br i1 %cmp3, label %if.then, label %if.end, !dbg !77, !clap !86

if.then:                                          ; preds = %land.lhs.true
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([8 x i8]* @.str, i32 0, i32 0)), !dbg !87, !clap !89
  store i8* null, i8** %retval, !dbg !90, !clap !91
  br label %for.end, !dbg !90, !clap !92

if.end:                                           ; preds = %land.lhs.true, %while.end
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @latch1, i32 0, i32 0, i32 32, i32 35)
  store i32 0, i32* @latch1, align 4, !dbg !93, !clap !94
  call void (i32, ...)* @clap_store_post(i32 5, i32* @latch1, i32 0, i32 0, i32 32, i32 35)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag1, i32 0, i32 32, i32 36)
  %tmp3 = load i32* @flag1, align 4, !dbg !95, !clap !96
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag1, i32 0, i32 32, i32 36)
  %tobool4 = icmp ne i32 %tmp3, 0, !dbg !95, !clap !97
  br i1 %tobool4, label %if.then5, label %if.end6, !dbg !95, !clap !98

if.then5:                                         ; preds = %if.end
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @flag1, i32 0, i32 0, i32 32, i32 39)
  store i32 0, i32* @flag1, align 4, !dbg !99, !clap !101
  call void (i32, ...)* @clap_store_post(i32 5, i32* @flag1, i32 0, i32 0, i32 32, i32 39)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @flag2, i32 1, i32 0, i32 32, i32 40)
  store i32 1, i32* @flag2, align 4, !dbg !102, !clap !103
  call void (i32, ...)* @clap_store_post(i32 5, i32* @flag2, i32 1, i32 0, i32 32, i32 40)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @latch2, i32 1, i32 0, i32 32, i32 41)
  store i32 1, i32* @latch2, align 4, !dbg !104, !clap !105
  call void (i32, ...)* @clap_store_post(i32 5, i32* @latch2, i32 1, i32 0, i32 32, i32 41)
  br label %if.end6, !dbg !106, !clap !107

if.end6:                                          ; preds = %if.then5, %if.end
  %tmp4 = load i32* %n2, align 4, !dbg !108, !clap !109
  %inc = add nsw i32 %tmp4, 1, !dbg !108, !clap !110
  store i32 %inc, i32* %n2, align 4, !dbg !108, !clap !111
  %cmp7 = icmp sge i32 %tmp4, 1, !dbg !108, !clap !112
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !108, !clap !113

if.then8:                                         ; preds = %if.end6
  br label %for.end, !dbg !114, !clap !115

if.end9:                                          ; preds = %if.end6
  br label %for.cond, !dbg !116, !clap !117

for.end:                                          ; preds = %if.then8, %if.then
  %tmp5 = load i8** %retval, !dbg !118, !clap !119
  ret i8* %tmp5, !dbg !118, !clap !120
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare i32 @printf(i8*, ...)

define i8* @worker_2(i8* %arg) nounwind {
entry:
  %retval = alloca i8*, align 4, !clap !121
  %arg.addr = alloca i8*, align 4, !clap !122
  %n1 = alloca i32, align 4, !clap !123
  %n2 = alloca i32, align 4, !clap !124
  %n3 = alloca i32, align 4, !clap !125
  store i8* %arg, i8** %arg.addr, align 4, !clap !126
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !127), !dbg !128, !clap !129
  call void @llvm.dbg.declare(metadata !{i32* %n1}, metadata !130), !dbg !132, !clap !133
  store i32 0, i32* %n1, align 4, !dbg !134, !clap !135
  call void @llvm.dbg.declare(metadata !{i32* %n2}, metadata !136), !dbg !137, !clap !138
  store i32 0, i32* %n2, align 4, !dbg !139, !clap !140
  call void @llvm.dbg.declare(metadata !{i32* %n3}, metadata !141), !dbg !142, !clap !143
  store i32 0, i32* %n3, align 4, !dbg !139, !clap !144
  br label %for.cond, !dbg !145, !clap !147

for.cond:                                         ; preds = %if.end9, %entry
  br label %while.cond, !dbg !148, !clap !150

while.cond:                                       ; preds = %while.body, %for.cond
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @latch2, i32 0, i32 32, i32 67)
  %tmp = load i32* @latch2, align 4, !dbg !148, !clap !151
  call void (i32, ...)* @clap_load_post(i32 4, i32* @latch2, i32 0, i32 32, i32 67)
  %tobool = icmp ne i32 %tmp, 0, !dbg !148, !clap !152
  %lnot = xor i1 %tobool, true, !dbg !148, !clap !153
  br i1 %lnot, label %while.body, label %while.end, !dbg !148, !clap !154

while.body:                                       ; preds = %while.cond
  br label %while.cond, !dbg !155, !clap !157

while.end:                                        ; preds = %while.cond
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @latch2, i32 0, i32 32, i32 72)
  %tmp1 = load i32* @latch2, align 4, !dbg !158, !clap !159
  call void (i32, ...)* @clap_load_post(i32 4, i32* @latch2, i32 0, i32 32, i32 72)
  %tobool1 = icmp ne i32 %tmp1, 0, !dbg !158, !clap !160
  %lnot2 = xor i1 %tobool1, true, !dbg !158, !clap !161
  %lnot.ext = zext i1 %lnot2 to i32, !dbg !158, !clap !162
  %cmp = icmp eq i32 %lnot.ext, 0, !dbg !158, !clap !163
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !158, !clap !164

land.lhs.true:                                    ; preds = %while.end
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag2, i32 0, i32 32, i32 78)
  %tmp2 = load i32* @flag2, align 4, !dbg !158, !clap !165
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag2, i32 0, i32 32, i32 78)
  %cmp3 = icmp eq i32 %tmp2, 0, !dbg !158, !clap !166
  br i1 %cmp3, label %if.then, label %if.end, !dbg !158, !clap !167

if.then:                                          ; preds = %land.lhs.true
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([8 x i8]* @.str1, i32 0, i32 0)), !dbg !168, !clap !170
  store i8* null, i8** %retval, !dbg !171, !clap !172
  br label %for.end, !dbg !171, !clap !173

if.end:                                           ; preds = %land.lhs.true, %while.end
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @latch2, i32 0, i32 0, i32 32, i32 84)
  store i32 0, i32* @latch2, align 4, !dbg !174, !clap !175
  call void (i32, ...)* @clap_store_post(i32 5, i32* @latch2, i32 0, i32 0, i32 32, i32 84)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @latch2, i32 0, i32 32, i32 85)
  %tmp3 = load i32* @latch2, align 4, !dbg !176, !clap !177
  call void (i32, ...)* @clap_load_post(i32 4, i32* @latch2, i32 0, i32 32, i32 85)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @latch2, i32 0, i32 32, i32 86)
  %tmp4 = load i32* @latch2, align 4, !dbg !176, !clap !178
  call void (i32, ...)* @clap_load_post(i32 4, i32* @latch2, i32 0, i32 32, i32 86)
  %xor = xor i32 %tmp3, %tmp4, !dbg !176, !clap !179
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @__unbuffered_tmp2, i32 %xor, i32 0, i32 32, i32 88)
  store i32 %xor, i32* @__unbuffered_tmp2, align 4, !dbg !176, !clap !180
  call void (i32, ...)* @clap_store_post(i32 5, i32* @__unbuffered_tmp2, i32 %xor, i32 0, i32 32, i32 88)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag2, i32 0, i32 32, i32 89)
  %tmp5 = load i32* @flag2, align 4, !dbg !181, !clap !182
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag2, i32 0, i32 32, i32 89)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @__unbuffered_tmp2, i32 0, i32 32, i32 90)
  %tmp6 = load i32* @__unbuffered_tmp2, align 4, !dbg !181, !clap !183
  call void (i32, ...)* @clap_load_post(i32 4, i32* @__unbuffered_tmp2, i32 0, i32 32, i32 90)
  %or = or i32 %tmp5, %tmp6, !dbg !181, !clap !184
  %tobool4 = icmp ne i32 %or, 0, !dbg !181, !clap !185
  br i1 %tobool4, label %if.then5, label %if.end6, !dbg !181, !clap !186

if.then5:                                         ; preds = %if.end
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @flag2, i32 0, i32 0, i32 32, i32 94)
  store i32 0, i32* @flag2, align 4, !dbg !187, !clap !189
  call void (i32, ...)* @clap_store_post(i32 5, i32* @flag2, i32 0, i32 0, i32 32, i32 94)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @flag1, i32 1, i32 0, i32 32, i32 95)
  store i32 1, i32* @flag1, align 4, !dbg !190, !clap !191
  call void (i32, ...)* @clap_store_post(i32 5, i32* @flag1, i32 1, i32 0, i32 32, i32 95)
  call void @MFENCE(), !dbg !192, !clap !193
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @latch1, i32 1, i32 0, i32 32, i32 97)
  store i32 1, i32* @latch1, align 4, !dbg !194, !clap !195
  call void (i32, ...)* @clap_store_post(i32 5, i32* @latch1, i32 1, i32 0, i32 32, i32 97)
  br label %if.end6, !dbg !196, !clap !197

if.end6:                                          ; preds = %if.then5, %if.end
  %tmp7 = load i32* %n2, align 4, !dbg !198, !clap !199
  %inc = add nsw i32 %tmp7, 1, !dbg !198, !clap !200
  store i32 %inc, i32* %n2, align 4, !dbg !198, !clap !201
  %cmp7 = icmp sge i32 %tmp7, 1, !dbg !198, !clap !202
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !198, !clap !203

if.then8:                                         ; preds = %if.end6
  br label %for.end, !dbg !204, !clap !205

if.end9:                                          ; preds = %if.end6
  br label %for.cond, !dbg !206, !clap !207

for.end:                                          ; preds = %if.then8, %if.then
  %tmp8 = load i8** %retval, !dbg !208, !clap !209
  ret i8* %tmp8, !dbg !208, !clap !210
}

define i32 @main() nounwind {
entry:
  %retval = alloca i32, align 4, !clap !211
  %t1 = alloca i32, align 4, !clap !212
  %t2 = alloca i32, align 4, !clap !213
  store i32 0, i32* %retval, !clap !214
  call void @llvm.dbg.declare(metadata !{i32* %t1}, metadata !215), !dbg !219, !clap !220
  call void @llvm.dbg.declare(metadata !{i32* %t2}, metadata !221), !dbg !222, !clap !223
  %call = call i32 @clap_thread_create(i32* %t1, %union.pthread_attr_t* null, i8* (i8*)* @worker_1, i8* null) nounwind, !dbg !224, !clap !225
  %call1 = call i32 @clap_thread_create(i32* %t2, %union.pthread_attr_t* null, i8* (i8*)* @worker_2, i8* null) nounwind, !dbg !226, !clap !227
  %tmp = load i32* %t1, align 4, !dbg !228, !clap !229
  %call2 = call i32 @clap_thread_join(i32 %tmp, i8** null), !dbg !228, !clap !230
  %tmp1 = load i32* %t2, align 4, !dbg !231, !clap !232
  %call3 = call i32 @clap_thread_join(i32 %tmp1, i8** null), !dbg !231, !clap !233
  ret i32 0, !dbg !234, !clap !235
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

!0 = metadata !{i32 720913, i32 0, i32 12, metadata !"/home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c", metadata !"/home/naling/src/inspect-0.3", metadata !"clang version 3.0 (tags/RELEASE_30/final)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !8, metadata !10, metadata !26} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{metadata !3}
!3 = metadata !{i32 720900, null, metadata !"", metadata !4, i32 9, i64 32, i64 32, i32 0, i32 0, i32 0, metadata !5, i32 0, i32 0} ; [ DW_TAG_enumeration_type ]
!4 = metadata !{i32 720937, metadata !"/home/naling/src/examples/tso/regression-examples/pgsql_two_fix/pgsql_two_fix.c", metadata !"/home/naling/src/inspect-0.3", null} ; [ DW_TAG_file_type ]
!5 = metadata !{metadata !6, metadata !7}
!6 = metadata !{i32 720936, metadata !"false", i64 0} ; [ DW_TAG_enumerator ]
!7 = metadata !{i32 720936, metadata !"true", i64 1} ; [ DW_TAG_enumerator ]
!8 = metadata !{metadata !9}
!9 = metadata !{i32 0}
!10 = metadata !{metadata !11}
!11 = metadata !{metadata !12, metadata !17, metadata !21, metadata !22}
!12 = metadata !{i32 720942, i32 0, metadata !4, metadata !"MFENCE", metadata !"MFENCE", metadata !"", metadata !4, i32 24, metadata !13, i1 false, i1 true, i32 0, i32 0, i32 0, i32 0, i1 false, void ()* @MFENCE, null, null, metadata !15} ; [ DW_TAG_subprogram ]
!13 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !14, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!14 = metadata !{null}
!15 = metadata !{metadata !16}
!16 = metadata !{i32 720932}                      ; [ DW_TAG_base_type ]
!17 = metadata !{i32 720942, i32 0, metadata !4, metadata !"worker_1", metadata !"worker_1", metadata !"", metadata !4, i32 53, metadata !18, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @worker_1, null, null, metadata !15} ; [ DW_TAG_subprogram ]
!18 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !19, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!19 = metadata !{metadata !20}
!20 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ]
!21 = metadata !{i32 720942, i32 0, metadata !4, metadata !"worker_2", metadata !"worker_2", metadata !"", metadata !4, i32 78, metadata !18, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @worker_2, null, null, metadata !15} ; [ DW_TAG_subprogram ]
!22 = metadata !{i32 720942, i32 0, metadata !4, metadata !"main", metadata !"main", metadata !"", metadata !4, i32 117, metadata !23, i1 false, i1 true, i32 0, i32 0, i32 0, i32 0, i1 false, i32 ()* @main, null, null, metadata !15} ; [ DW_TAG_subprogram ]
!23 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !24, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!24 = metadata !{metadata !25}
!25 = metadata !{i32 720932, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!26 = metadata !{metadata !27}
!27 = metadata !{metadata !28, metadata !29, metadata !30, metadata !31, metadata !32, metadata !34}
!28 = metadata !{i32 720948, i32 0, null, metadata !"latch1", metadata !"latch1", metadata !"", metadata !4, i32 12, metadata !25, i32 0, i32 1, i32* @latch1} ; [ DW_TAG_variable ]
!29 = metadata !{i32 720948, i32 0, null, metadata !"flag1", metadata !"flag1", metadata !"", metadata !4, i32 13, metadata !25, i32 0, i32 1, i32* @flag1} ; [ DW_TAG_variable ]
!30 = metadata !{i32 720948, i32 0, null, metadata !"latch2", metadata !"latch2", metadata !"", metadata !4, i32 14, metadata !25, i32 0, i32 1, i32* @latch2} ; [ DW_TAG_variable ]
!31 = metadata !{i32 720948, i32 0, null, metadata !"flag2", metadata !"flag2", metadata !"", metadata !4, i32 15, metadata !25, i32 0, i32 1, i32* @flag2} ; [ DW_TAG_variable ]
!32 = metadata !{i32 720948, i32 0, null, metadata !"__unbuffered_tmp2", metadata !"__unbuffered_tmp2", metadata !"", metadata !4, i32 22, metadata !33, i32 0, i32 1, i32* @__unbuffered_tmp2} ; [ DW_TAG_variable ]
!33 = metadata !{i32 720918, null, metadata !"bool", metadata !4, i32 9, i64 0, i64 0, i64 0, i32 0, metadata !3} ; [ DW_TAG_typedef ]
!34 = metadata !{i32 720948, i32 0, null, metadata !"dummy", metadata !"dummy", metadata !"", metadata !4, i32 23, metadata !25, i32 0, i32 1, i32* @dummy} ; [ DW_TAG_variable ]
!35 = metadata !{i32 24, i32 16, metadata !36, null}
!36 = metadata !{i32 720907, metadata !12, i32 24, i32 14, metadata !4, i32 0} ; [ DW_TAG_lexical_block ]
!37 = metadata !{i32 1}
!38 = metadata !{i32 24, i32 48, metadata !36, null}
!39 = metadata !{i32 2}
!40 = metadata !{i32 3}
!41 = metadata !{i32 4}
!42 = metadata !{i32 5}
!43 = metadata !{i32 6}
!44 = metadata !{i32 7}
!45 = metadata !{i32 8}
!46 = metadata !{i32 721153, metadata !17, metadata !"arg", metadata !4, i32 16777268, metadata !20, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!47 = metadata !{i32 52, i32 22, metadata !17, null}
!48 = metadata !{i32 9}
!49 = metadata !{i32 721152, metadata !50, metadata !"n1", metadata !4, i32 55, metadata !25, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!50 = metadata !{i32 720907, metadata !17, i32 53, i32 1, metadata !4, i32 1} ; [ DW_TAG_lexical_block ]
!51 = metadata !{i32 55, i32 9, metadata !50, null}
!52 = metadata !{i32 10}
!53 = metadata !{i32 55, i32 13, metadata !50, null}
!54 = metadata !{i32 11}
!55 = metadata !{i32 721152, metadata !50, metadata !"n2", metadata !4, i32 55, metadata !25, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!56 = metadata !{i32 55, i32 18, metadata !50, null}
!57 = metadata !{i32 12}
!58 = metadata !{i32 55, i32 27, metadata !50, null}
!59 = metadata !{i32 13}
!60 = metadata !{i32 721152, metadata !50, metadata !"n3", metadata !4, i32 55, metadata !25, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!61 = metadata !{i32 55, i32 23, metadata !50, null}
!62 = metadata !{i32 14}
!63 = metadata !{i32 15}
!64 = metadata !{i32 56, i32 5, metadata !65, null}
!65 = metadata !{i32 720907, metadata !50, i32 56, i32 5, metadata !4, i32 2} ; [ DW_TAG_lexical_block ]
!66 = metadata !{i32 16}
!67 = metadata !{i32 58, i32 2, metadata !68, null}
!68 = metadata !{i32 720907, metadata !65, i32 57, i32 5, metadata !4, i32 3} ; [ DW_TAG_lexical_block ]
!69 = metadata !{i32 17}
!70 = metadata !{i32 18}
!71 = metadata !{i32 19}
!72 = metadata !{i32 20}
!73 = metadata !{i32 21}
!74 = metadata !{i32 58, i32 18, metadata !75, null}
!75 = metadata !{i32 720907, metadata !68, i32 58, i32 17, metadata !4, i32 4} ; [ DW_TAG_lexical_block ]
!76 = metadata !{i32 22}
!77 = metadata !{i32 63, i32 2, metadata !68, null}
!78 = metadata !{i32 23}
!79 = metadata !{i32 24}
!80 = metadata !{i32 25}
!81 = metadata !{i32 26}
!82 = metadata !{i32 27}
!83 = metadata !{i32 28}
!84 = metadata !{i32 29}
!85 = metadata !{i32 30}
!86 = metadata !{i32 31}
!87 = metadata !{i32 63, i32 30, metadata !88, null}
!88 = metadata !{i32 720907, metadata !68, i32 63, i32 29, metadata !4, i32 5} ; [ DW_TAG_lexical_block ]
!89 = metadata !{i32 32}
!90 = metadata !{i32 63, i32 49, metadata !88, null}
!91 = metadata !{i32 33}
!92 = metadata !{i32 34}
!93 = metadata !{i32 64, i32 2, metadata !68, null}
!94 = metadata !{i32 35}
!95 = metadata !{i32 65, i32 2, metadata !68, null}
!96 = metadata !{i32 36}
!97 = metadata !{i32 37}
!98 = metadata !{i32 38}
!99 = metadata !{i32 67, i32 6, metadata !100, null}
!100 = metadata !{i32 720907, metadata !68, i32 66, i32 2, metadata !4, i32 6} ; [ DW_TAG_lexical_block ]
!101 = metadata !{i32 39}
!102 = metadata !{i32 68, i32 6, metadata !100, null}
!103 = metadata !{i32 40}
!104 = metadata !{i32 69, i32 6, metadata !100, null}
!105 = metadata !{i32 41}
!106 = metadata !{i32 71, i32 2, metadata !100, null}
!107 = metadata !{i32 42}
!108 = metadata !{i32 72, i32 2, metadata !68, null}
!109 = metadata !{i32 43}
!110 = metadata !{i32 44}
!111 = metadata !{i32 45}
!112 = metadata !{i32 46}
!113 = metadata !{i32 47}
!114 = metadata !{i32 72, i32 16, metadata !68, null}
!115 = metadata !{i32 48}
!116 = metadata !{i32 74, i32 5, metadata !68, null}
!117 = metadata !{i32 49}
!118 = metadata !{i32 75, i32 1, metadata !50, null}
!119 = metadata !{i32 50}
!120 = metadata !{i32 51}
!121 = metadata !{i32 52}
!122 = metadata !{i32 53}
!123 = metadata !{i32 54}
!124 = metadata !{i32 55}
!125 = metadata !{i32 56}
!126 = metadata !{i32 57}
!127 = metadata !{i32 721153, metadata !21, metadata !"arg", metadata !4, i32 16777293, metadata !20, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!128 = metadata !{i32 77, i32 22, metadata !21, null}
!129 = metadata !{i32 58}
!130 = metadata !{i32 721152, metadata !131, metadata !"n1", metadata !4, i32 80, metadata !25, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!131 = metadata !{i32 720907, metadata !21, i32 78, i32 1, metadata !4, i32 7} ; [ DW_TAG_lexical_block ]
!132 = metadata !{i32 80, i32 9, metadata !131, null}
!133 = metadata !{i32 59}
!134 = metadata !{i32 80, i32 13, metadata !131, null}
!135 = metadata !{i32 60}
!136 = metadata !{i32 721152, metadata !131, metadata !"n2", metadata !4, i32 80, metadata !25, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!137 = metadata !{i32 80, i32 18, metadata !131, null}
!138 = metadata !{i32 61}
!139 = metadata !{i32 80, i32 27, metadata !131, null}
!140 = metadata !{i32 62}
!141 = metadata !{i32 721152, metadata !131, metadata !"n3", metadata !4, i32 80, metadata !25, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!142 = metadata !{i32 80, i32 23, metadata !131, null}
!143 = metadata !{i32 63}
!144 = metadata !{i32 64}
!145 = metadata !{i32 81, i32 5, metadata !146, null}
!146 = metadata !{i32 720907, metadata !131, i32 81, i32 5, metadata !4, i32 8} ; [ DW_TAG_lexical_block ]
!147 = metadata !{i32 65}
!148 = metadata !{i32 83, i32 2, metadata !149, null}
!149 = metadata !{i32 720907, metadata !146, i32 82, i32 5, metadata !4, i32 9} ; [ DW_TAG_lexical_block ]
!150 = metadata !{i32 66}
!151 = metadata !{i32 67}
!152 = metadata !{i32 68}
!153 = metadata !{i32 69}
!154 = metadata !{i32 70}
!155 = metadata !{i32 83, i32 18, metadata !156, null}
!156 = metadata !{i32 720907, metadata !149, i32 83, i32 17, metadata !4, i32 10} ; [ DW_TAG_lexical_block ]
!157 = metadata !{i32 71}
!158 = metadata !{i32 88, i32 2, metadata !149, null}
!159 = metadata !{i32 72}
!160 = metadata !{i32 73}
!161 = metadata !{i32 74}
!162 = metadata !{i32 75}
!163 = metadata !{i32 76}
!164 = metadata !{i32 77}
!165 = metadata !{i32 78}
!166 = metadata !{i32 79}
!167 = metadata !{i32 80}
!168 = metadata !{i32 88, i32 30, metadata !169, null}
!169 = metadata !{i32 720907, metadata !149, i32 88, i32 29, metadata !4, i32 11} ; [ DW_TAG_lexical_block ]
!170 = metadata !{i32 81}
!171 = metadata !{i32 88, i32 49, metadata !169, null}
!172 = metadata !{i32 82}
!173 = metadata !{i32 83}
!174 = metadata !{i32 89, i32 2, metadata !149, null}
!175 = metadata !{i32 84}
!176 = metadata !{i32 91, i32 2, metadata !149, null}
!177 = metadata !{i32 85}
!178 = metadata !{i32 86}
!179 = metadata !{i32 87}
!180 = metadata !{i32 88}
!181 = metadata !{i32 92, i32 2, metadata !149, null}
!182 = metadata !{i32 89}
!183 = metadata !{i32 90}
!184 = metadata !{i32 91}
!185 = metadata !{i32 92}
!186 = metadata !{i32 93}
!187 = metadata !{i32 94, i32 6, metadata !188, null}
!188 = metadata !{i32 720907, metadata !149, i32 93, i32 2, metadata !4, i32 12} ; [ DW_TAG_lexical_block ]
!189 = metadata !{i32 94}
!190 = metadata !{i32 95, i32 6, metadata !188, null}
!191 = metadata !{i32 95}
!192 = metadata !{i32 97, i32 6, metadata !188, null}
!193 = metadata !{i32 96}
!194 = metadata !{i32 98, i32 6, metadata !188, null}
!195 = metadata !{i32 97}
!196 = metadata !{i32 99, i32 2, metadata !188, null}
!197 = metadata !{i32 98}
!198 = metadata !{i32 100, i32 2, metadata !149, null}
!199 = metadata !{i32 99}
!200 = metadata !{i32 100}
!201 = metadata !{i32 101}
!202 = metadata !{i32 102}
!203 = metadata !{i32 103}
!204 = metadata !{i32 100, i32 16, metadata !149, null}
!205 = metadata !{i32 104}
!206 = metadata !{i32 102, i32 5, metadata !149, null}
!207 = metadata !{i32 105}
!208 = metadata !{i32 103, i32 1, metadata !131, null}
!209 = metadata !{i32 106}
!210 = metadata !{i32 107}
!211 = metadata !{i32 108}
!212 = metadata !{i32 109}
!213 = metadata !{i32 110}
!214 = metadata !{i32 111}
!215 = metadata !{i32 721152, metadata !216, metadata !"t1", metadata !4, i32 120, metadata !217, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!216 = metadata !{i32 720907, metadata !22, i32 117, i32 1, metadata !4, i32 13} ; [ DW_TAG_lexical_block ]
!217 = metadata !{i32 720918, null, metadata !"pthread_t", metadata !4, i32 60, i64 0, i64 0, i64 0, i32 0, metadata !218} ; [ DW_TAG_typedef ]
!218 = metadata !{i32 720932, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!219 = metadata !{i32 120, i32 15, metadata !216, null}
!220 = metadata !{i32 112}
!221 = metadata !{i32 721152, metadata !216, metadata !"t2", metadata !4, i32 120, metadata !217, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!222 = metadata !{i32 120, i32 19, metadata !216, null}
!223 = metadata !{i32 113}
!224 = metadata !{i32 122, i32 5, metadata !216, null}
!225 = metadata !{i32 114}
!226 = metadata !{i32 123, i32 5, metadata !216, null}
!227 = metadata !{i32 115}
!228 = metadata !{i32 125, i32 5, metadata !216, null}
!229 = metadata !{i32 116}
!230 = metadata !{i32 117}
!231 = metadata !{i32 126, i32 5, metadata !216, null}
!232 = metadata !{i32 118}
!233 = metadata !{i32 119}
!234 = metadata !{i32 134, i32 5, metadata !216, null}
!235 = metadata !{i32 120}
