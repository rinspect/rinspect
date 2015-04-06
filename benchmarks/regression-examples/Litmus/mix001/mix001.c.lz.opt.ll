; ModuleID = '../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c.lz.opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%union.pthread_attr_t = type { i32, [32 x i8] }

@z = common global i32 0, align 4
@x = common global i32 0, align 4
@.str = private unnamed_addr constant [32 x i8] c"\0A %%%% (EAX0=%d, EBX0=%d) %%%%\0A\00", align 1
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
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @z, i32 0, i32 32, i32 9)
  %tmp = load i32* @z, align 4, !dbg !40, !clap !41
  call void (i32, ...)* @clap_load_post(i32 4, i32* @z, i32 0, i32 32, i32 9)
  store i32 %tmp, i32* %EAX, align 4, !dbg !40, !clap !42
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 11)
  %tmp1 = load i32* @x, align 4, !dbg !43, !clap !44
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 11)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !43, !clap !45
  %tmp2 = load i32* %EAX, align 4, !dbg !46, !clap !47
  %tmp3 = load i32* %EBX, align 4, !dbg !46, !clap !48
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([32 x i8]* @.str, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !46, !clap !49
  %tmp4 = load i32* %EAX, align 4, !dbg !50, !clap !51
  %cmp = icmp eq i32 %tmp4, 1, !dbg !50, !clap !52
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !50, !clap !53

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !50, !clap !54
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !50, !clap !55
  br label %land.end, !clap !56

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !57
  %land.ext = zext i1 %tmp6 to i32, !clap !58
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !59
  ret i8* %tmp7, !dbg !60, !clap !61
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare i32 @printf(i8*, ...)

define i8* @P1(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !62
  %EAX = alloca i32, align 4, !clap !63
  %EBX = alloca i32, align 4, !clap !64
  store i8* %arg, i8** %arg.addr, align 4, !clap !65
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !66), !dbg !67, !clap !68
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !69), !dbg !71, !clap !72
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !73), !dbg !74, !clap !75
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 33)
  store i32 1, i32* @x, align 4, !dbg !76, !clap !77
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 33)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 34)
  %tmp = load i32* @x, align 4, !dbg !78, !clap !79
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 34)
  store i32 %tmp, i32* %EAX, align 4, !dbg !78, !clap !80
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 36)
  %tmp1 = load i32* @y, align 4, !dbg !81, !clap !82
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 36)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !81, !clap !83
  %tmp2 = load i32* %EAX, align 4, !dbg !84, !clap !85
  %tmp3 = load i32* %EBX, align 4, !dbg !84, !clap !86
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([32 x i8]* @.str1, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !84, !clap !87
  %tmp4 = load i32* %EAX, align 4, !dbg !88, !clap !89
  %cmp = icmp eq i32 %tmp4, 1, !dbg !88, !clap !90
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !88, !clap !91

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !88, !clap !92
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !88, !clap !93
  br label %land.end, !clap !94

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !95
  %land.ext = zext i1 %tmp6 to i32, !clap !96
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !97
  ret i8* %tmp7, !dbg !98, !clap !99
}

define i8* @P2(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !100
  %EAX = alloca i32, align 4, !clap !101
  %EBX = alloca i32, align 4, !clap !102
  store i8* %arg, i8** %arg.addr, align 4, !clap !103
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !104), !dbg !105, !clap !106
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !107), !dbg !109, !clap !110
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !111), !dbg !112, !clap !113
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 58)
  store i32 1, i32* @y, align 4, !dbg !114, !clap !115
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 58)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 59)
  %tmp = load i32* @y, align 4, !dbg !116, !clap !117
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 59)
  store i32 %tmp, i32* %EAX, align 4, !dbg !116, !clap !118
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @z, i32 0, i32 32, i32 61)
  %tmp1 = load i32* @z, align 4, !dbg !119, !clap !120
  call void (i32, ...)* @clap_load_post(i32 4, i32* @z, i32 0, i32 32, i32 61)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !119, !clap !121
  %tmp2 = load i32* %EAX, align 4, !dbg !122, !clap !123
  %tmp3 = load i32* %EBX, align 4, !dbg !122, !clap !124
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([32 x i8]* @.str2, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !122, !clap !125
  %tmp4 = load i32* %EAX, align 4, !dbg !126, !clap !127
  %cmp = icmp eq i32 %tmp4, 1, !dbg !126, !clap !128
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !126, !clap !129

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !126, !clap !130
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !126, !clap !131
  br label %land.end, !clap !132

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !133
  %land.ext = zext i1 %tmp6 to i32, !clap !134
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !135
  ret i8* %tmp7, !dbg !136, !clap !137
}

define i32 @main() nounwind {
entry:
  %retval = alloca i32, align 4, !clap !138
  %t0 = alloca i32, align 4, !clap !139
  %t1 = alloca i32, align 4, !clap !140
  %t2 = alloca i32, align 4, !clap !141
  %cond0 = alloca i32, align 4, !clap !142
  %cond1 = alloca i32, align 4, !clap !143
  %cond2 = alloca i32, align 4, !clap !144
  store i32 0, i32* %retval, !clap !145
  call void @llvm.dbg.declare(metadata !{i32* %t0}, metadata !146), !dbg !150, !clap !151
  call void @llvm.dbg.declare(metadata !{i32* %t1}, metadata !152), !dbg !153, !clap !154
  call void @llvm.dbg.declare(metadata !{i32* %t2}, metadata !155), !dbg !156, !clap !157
  call void @llvm.dbg.declare(metadata !{i32* %cond0}, metadata !158), !dbg !159, !clap !160
  call void @llvm.dbg.declare(metadata !{i32* %cond1}, metadata !161), !dbg !162, !clap !163
  call void @llvm.dbg.declare(metadata !{i32* %cond2}, metadata !164), !dbg !165, !clap !166
  %call = call i32 @clap_thread_create(i32* %t0, %union.pthread_attr_t* null, i8* (i8*)* @P1, i8* null) nounwind, !dbg !167, !clap !168
  %call1 = call i32 @clap_thread_create(i32* %t1, %union.pthread_attr_t* null, i8* (i8*)* @P0, i8* null) nounwind, !dbg !169, !clap !170
  %call2 = call i32 @clap_thread_create(i32* %t2, %union.pthread_attr_t* null, i8* (i8*)* @P2, i8* null) nounwind, !dbg !171, !clap !172
  %tmp = load i32* %t0, align 4, !dbg !173, !clap !174
  %tmp1 = bitcast i32* %cond0 to i8**, !dbg !173, !clap !175
  %call3 = call i32 @clap_thread_join(i32 %tmp, i8** %tmp1), !dbg !173, !clap !176
  %tmp2 = load i32* %t1, align 4, !dbg !177, !clap !178
  %tmp3 = bitcast i32* %cond1 to i8**, !dbg !177, !clap !179
  %call4 = call i32 @clap_thread_join(i32 %tmp2, i8** %tmp3), !dbg !177, !clap !180
  %tmp4 = load i32* %t2, align 4, !dbg !181, !clap !182
  %tmp5 = bitcast i32* %cond2 to i8**, !dbg !181, !clap !183
  %call5 = call i32 @clap_thread_join(i32 %tmp4, i8** %tmp5), !dbg !181, !clap !184
  %tmp6 = load i32* %cond0, align 4, !dbg !185, !clap !186
  %tobool = icmp ne i32 %tmp6, 0, !dbg !185, !clap !187
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !185, !clap !188

land.lhs.true:                                    ; preds = %entry
  %tmp7 = load i32* %cond1, align 4, !dbg !185, !clap !189
  %tobool6 = icmp ne i32 %tmp7, 0, !dbg !185, !clap !190
  br i1 %tobool6, label %land.lhs.true7, label %if.end, !dbg !185, !clap !191

land.lhs.true7:                                   ; preds = %land.lhs.true
  %tmp8 = load i32* %cond2, align 4, !dbg !185, !clap !192
  %tobool8 = icmp ne i32 %tmp8, 0, !dbg !185, !clap !193
  br i1 %tobool8, label %if.then, label %if.end, !dbg !185, !clap !194

if.then:                                          ; preds = %land.lhs.true7
  %call9 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([37 x i8]* @.str3, i32 0, i32 0)), !dbg !195, !clap !197
  %call10 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([30 x i8]* @.str4, i32 0, i32 0)), !dbg !198, !clap !199
  br label %if.end, !dbg !200, !clap !201

if.end:                                           ; preds = %if.then, %land.lhs.true7, %land.lhs.true, %entry
  ret i32 0, !dbg !202, !clap !203
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

!0 = metadata !{i32 720913, i32 0, i32 12, metadata !"../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c", metadata !"/home/naling/src/inspect-0.3", metadata !"clang version 3.0 (tags/RELEASE_30/final)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !18} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !12, metadata !13, metadata !14}
!5 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P0", metadata !"P0", metadata !"", metadata !6, i32 32, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P0, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 720937, metadata !"../examples/tso/Benchmarks-for-Rinspect/regression-examples/mix001/mix001.c", metadata !"/home/naling/src/inspect-0.3", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{metadata !9}
!9 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ]
!10 = metadata !{metadata !11}
!11 = metadata !{i32 720932}                      ; [ DW_TAG_base_type ]
!12 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P1", metadata !"P1", metadata !"", metadata !6, i32 42, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P1, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!13 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P2", metadata !"P2", metadata !"", metadata !6, i32 52, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P2, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!14 = metadata !{i32 720942, i32 0, metadata !6, metadata !"main", metadata !"main", metadata !"", metadata !6, i32 62, metadata !15, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i32 ()* @main, null, null, metadata !10} ; [ DW_TAG_subprogram ]
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
!50 = metadata !{i32 38, i32 3, metadata !32, null}
!51 = metadata !{i32 16}
!52 = metadata !{i32 17}
!53 = metadata !{i32 18}
!54 = metadata !{i32 19}
!55 = metadata !{i32 20}
!56 = metadata !{i32 21}
!57 = metadata !{i32 22}
!58 = metadata !{i32 23}
!59 = metadata !{i32 24}
!60 = metadata !{i32 39, i32 1, metadata !5, null}
!61 = metadata !{i32 25}
!62 = metadata !{i32 26}
!63 = metadata !{i32 27}
!64 = metadata !{i32 28}
!65 = metadata !{i32 29}
!66 = metadata !{i32 721153, metadata !12, metadata !"arg", metadata !6, i32 16777257, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!67 = metadata !{i32 41, i32 16, metadata !12, null}
!68 = metadata !{i32 30}
!69 = metadata !{i32 721152, metadata !70, metadata !"EAX", metadata !6, i32 43, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!70 = metadata !{i32 720907, metadata !12, i32 42, i32 1, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!71 = metadata !{i32 43, i32 12, metadata !70, null}
!72 = metadata !{i32 31}
!73 = metadata !{i32 721152, metadata !70, metadata !"EBX", metadata !6, i32 43, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!74 = metadata !{i32 43, i32 17, metadata !70, null}
!75 = metadata !{i32 32}
!76 = metadata !{i32 44, i32 3, metadata !70, null}
!77 = metadata !{i32 33}
!78 = metadata !{i32 45, i32 3, metadata !70, null}
!79 = metadata !{i32 34}
!80 = metadata !{i32 35}
!81 = metadata !{i32 46, i32 3, metadata !70, null}
!82 = metadata !{i32 36}
!83 = metadata !{i32 37}
!84 = metadata !{i32 47, i32 3, metadata !70, null}
!85 = metadata !{i32 38}
!86 = metadata !{i32 39}
!87 = metadata !{i32 40}
!88 = metadata !{i32 48, i32 3, metadata !70, null}
!89 = metadata !{i32 41}
!90 = metadata !{i32 42}
!91 = metadata !{i32 43}
!92 = metadata !{i32 44}
!93 = metadata !{i32 45}
!94 = metadata !{i32 46}
!95 = metadata !{i32 47}
!96 = metadata !{i32 48}
!97 = metadata !{i32 49}
!98 = metadata !{i32 49, i32 1, metadata !12, null}
!99 = metadata !{i32 50}
!100 = metadata !{i32 51}
!101 = metadata !{i32 52}
!102 = metadata !{i32 53}
!103 = metadata !{i32 54}
!104 = metadata !{i32 721153, metadata !13, metadata !"arg", metadata !6, i32 16777267, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!105 = metadata !{i32 51, i32 16, metadata !13, null}
!106 = metadata !{i32 55}
!107 = metadata !{i32 721152, metadata !108, metadata !"EAX", metadata !6, i32 53, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!108 = metadata !{i32 720907, metadata !13, i32 52, i32 1, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!109 = metadata !{i32 53, i32 12, metadata !108, null}
!110 = metadata !{i32 56}
!111 = metadata !{i32 721152, metadata !108, metadata !"EBX", metadata !6, i32 53, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!112 = metadata !{i32 53, i32 17, metadata !108, null}
!113 = metadata !{i32 57}
!114 = metadata !{i32 54, i32 3, metadata !108, null}
!115 = metadata !{i32 58}
!116 = metadata !{i32 55, i32 3, metadata !108, null}
!117 = metadata !{i32 59}
!118 = metadata !{i32 60}
!119 = metadata !{i32 56, i32 3, metadata !108, null}
!120 = metadata !{i32 61}
!121 = metadata !{i32 62}
!122 = metadata !{i32 57, i32 3, metadata !108, null}
!123 = metadata !{i32 63}
!124 = metadata !{i32 64}
!125 = metadata !{i32 65}
!126 = metadata !{i32 58, i32 3, metadata !108, null}
!127 = metadata !{i32 66}
!128 = metadata !{i32 67}
!129 = metadata !{i32 68}
!130 = metadata !{i32 69}
!131 = metadata !{i32 70}
!132 = metadata !{i32 71}
!133 = metadata !{i32 72}
!134 = metadata !{i32 73}
!135 = metadata !{i32 74}
!136 = metadata !{i32 59, i32 1, metadata !13, null}
!137 = metadata !{i32 75}
!138 = metadata !{i32 76}
!139 = metadata !{i32 77}
!140 = metadata !{i32 78}
!141 = metadata !{i32 79}
!142 = metadata !{i32 80}
!143 = metadata !{i32 81}
!144 = metadata !{i32 82}
!145 = metadata !{i32 83}
!146 = metadata !{i32 721152, metadata !147, metadata !"t0", metadata !6, i32 63, metadata !148, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!147 = metadata !{i32 720907, metadata !14, i32 62, i32 1, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!148 = metadata !{i32 720918, null, metadata !"pthread_t", metadata !6, i32 60, i64 0, i64 0, i64 0, i32 0, metadata !149} ; [ DW_TAG_typedef ]
!149 = metadata !{i32 720932, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!150 = metadata !{i32 63, i32 13, metadata !147, null}
!151 = metadata !{i32 84}
!152 = metadata !{i32 721152, metadata !147, metadata !"t1", metadata !6, i32 63, metadata !148, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!153 = metadata !{i32 63, i32 17, metadata !147, null}
!154 = metadata !{i32 85}
!155 = metadata !{i32 721152, metadata !147, metadata !"t2", metadata !6, i32 63, metadata !148, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!156 = metadata !{i32 63, i32 21, metadata !147, null}
!157 = metadata !{i32 86}
!158 = metadata !{i32 721152, metadata !147, metadata !"cond0", metadata !6, i32 64, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!159 = metadata !{i32 64, i32 12, metadata !147, null}
!160 = metadata !{i32 87}
!161 = metadata !{i32 721152, metadata !147, metadata !"cond1", metadata !6, i32 64, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!162 = metadata !{i32 64, i32 19, metadata !147, null}
!163 = metadata !{i32 88}
!164 = metadata !{i32 721152, metadata !147, metadata !"cond2", metadata !6, i32 64, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!165 = metadata !{i32 64, i32 26, metadata !147, null}
!166 = metadata !{i32 89}
!167 = metadata !{i32 66, i32 3, metadata !147, null}
!168 = metadata !{i32 90}
!169 = metadata !{i32 67, i32 3, metadata !147, null}
!170 = metadata !{i32 91}
!171 = metadata !{i32 68, i32 3, metadata !147, null}
!172 = metadata !{i32 92}
!173 = metadata !{i32 70, i32 3, metadata !147, null}
!174 = metadata !{i32 93}
!175 = metadata !{i32 94}
!176 = metadata !{i32 95}
!177 = metadata !{i32 71, i32 3, metadata !147, null}
!178 = metadata !{i32 96}
!179 = metadata !{i32 97}
!180 = metadata !{i32 98}
!181 = metadata !{i32 72, i32 3, metadata !147, null}
!182 = metadata !{i32 99}
!183 = metadata !{i32 100}
!184 = metadata !{i32 101}
!185 = metadata !{i32 75, i32 3, metadata !147, null}
!186 = metadata !{i32 102}
!187 = metadata !{i32 103}
!188 = metadata !{i32 104}
!189 = metadata !{i32 105}
!190 = metadata !{i32 106}
!191 = metadata !{i32 107}
!192 = metadata !{i32 108}
!193 = metadata !{i32 109}
!194 = metadata !{i32 110}
!195 = metadata !{i32 76, i32 5, metadata !196, null}
!196 = metadata !{i32 720907, metadata !147, i32 75, i32 33, metadata !6, i32 4} ; [ DW_TAG_lexical_block ]
!197 = metadata !{i32 111}
!198 = metadata !{i32 77, i32 5, metadata !196, null}
!199 = metadata !{i32 112}
!200 = metadata !{i32 78, i32 3, metadata !196, null}
!201 = metadata !{i32 113}
!202 = metadata !{i32 80, i32 3, metadata !147, null}
!203 = metadata !{i32 114}
