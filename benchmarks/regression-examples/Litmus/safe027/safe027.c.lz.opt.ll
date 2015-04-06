; ModuleID = '../examples/tso/regression-examples/safe027/safe027.c.lz.opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%union.pthread_attr_t = type { i32, [32 x i8] }

@y = common global i32 0, align 4
@x = common global i32 0, align 4
@.str = private unnamed_addr constant [23 x i8] c"\0A (EAX0=%d, EBX0=%d) \0A\00", align 1
@.str1 = private unnamed_addr constant [23 x i8] c"\0A (EAX2=%d, EBX2=%d) \0A\00", align 1
@.str2 = private unnamed_addr constant [37 x i8] c"\0A@@@CLAP: There is a SC violation! \0A\00", align 1
@.str3 = private unnamed_addr constant [30 x i8] c"\1B[1;31m SC Violation!!! \1B[0m\0A\00", align 1
@z = common global i32 0, align 4

define void @MFENCE() nounwind {
entry:
  ret void, !dbg !28, !clap !30
}

define i8* @P0(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !31
  %EAX = alloca i32, align 4, !clap !32
  %EBX = alloca i32, align 4, !clap !33
  store i8* %arg, i8** %arg.addr, align 4, !clap !34
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !35), !dbg !36, !clap !37
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !38), !dbg !40, !clap !41
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !42), !dbg !43, !clap !44
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 9)
  %tmp = load i32* @y, align 4, !dbg !45, !clap !46
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 9)
  store i32 %tmp, i32* %EAX, align 4, !dbg !45, !clap !47
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 11)
  %tmp1 = load i32* @x, align 4, !dbg !48, !clap !49
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 11)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !48, !clap !50
  %tmp2 = load i32* %EAX, align 4, !dbg !51, !clap !52
  %tmp3 = load i32* %EBX, align 4, !dbg !51, !clap !53
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([23 x i8]* @.str, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !51, !clap !54
  %tmp4 = load i32* %EAX, align 4, !dbg !55, !clap !56
  %cmp = icmp eq i32 %tmp4, 1, !dbg !55, !clap !57
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !55, !clap !58

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !55, !clap !59
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !55, !clap !60
  br label %land.end, !clap !61

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !62
  %land.ext = zext i1 %tmp6 to i32, !clap !63
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !64
  ret i8* %tmp7, !dbg !65, !clap !66
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare i32 @printf(i8*, ...)

define i8* @P1(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !67
  %EAX = alloca i32, align 4, !clap !68
  %EBX = alloca i32, align 4, !clap !69
  store i8* %arg, i8** %arg.addr, align 4, !clap !70
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !71), !dbg !72, !clap !73
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !74), !dbg !76, !clap !77
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !78), !dbg !79, !clap !80
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 33)
  store i32 1, i32* @x, align 4, !dbg !81, !clap !82
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 33)
  ret i8* inttoptr (i32 1 to i8*), !dbg !83, !clap !84
}

define i8* @P2(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !85
  %EAX = alloca i32, align 4, !clap !86
  %EBX = alloca i32, align 4, !clap !87
  store i8* %arg, i8** %arg.addr, align 4, !clap !88
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !89), !dbg !90, !clap !91
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !92), !dbg !94, !clap !95
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !96), !dbg !97, !clap !98
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 42)
  %tmp = load i32* @x, align 4, !dbg !99, !clap !100
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 42)
  store i32 %tmp, i32* %EAX, align 4, !dbg !99, !clap !101
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 44)
  %tmp1 = load i32* @y, align 4, !dbg !102, !clap !103
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 44)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !102, !clap !104
  %tmp2 = load i32* %EAX, align 4, !dbg !105, !clap !106
  %tmp3 = load i32* %EBX, align 4, !dbg !105, !clap !107
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([23 x i8]* @.str1, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !105, !clap !108
  %tmp4 = load i32* %EAX, align 4, !dbg !109, !clap !110
  %cmp = icmp eq i32 %tmp4, 1, !dbg !109, !clap !111
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !109, !clap !112

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !109, !clap !113
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !109, !clap !114
  br label %land.end, !clap !115

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !116
  %land.ext = zext i1 %tmp6 to i32, !clap !117
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !118
  ret i8* %tmp7, !dbg !119, !clap !120
}

define i8* @P3(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !121
  %EAX = alloca i32, align 4, !clap !122
  %EBX = alloca i32, align 4, !clap !123
  store i8* %arg, i8** %arg.addr, align 4, !clap !124
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !125), !dbg !126, !clap !127
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !128), !dbg !130, !clap !131
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !132), !dbg !133, !clap !134
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 66)
  store i32 1, i32* @y, align 4, !dbg !135, !clap !136
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 66)
  ret i8* inttoptr (i32 1 to i8*), !dbg !137, !clap !138
}

define i32 @main() nounwind {
entry:
  %retval = alloca i32, align 4, !clap !139
  %t0 = alloca i32, align 4, !clap !140
  %t1 = alloca i32, align 4, !clap !141
  %t2 = alloca i32, align 4, !clap !142
  %t3 = alloca i32, align 4, !clap !143
  %cond0 = alloca i32, align 4, !clap !144
  %cond1 = alloca i32, align 4, !clap !145
  %cond2 = alloca i32, align 4, !clap !146
  %cond3 = alloca i32, align 4, !clap !147
  store i32 0, i32* %retval, !clap !148
  call void @llvm.dbg.declare(metadata !{i32* %t0}, metadata !149), !dbg !153, !clap !154
  call void @llvm.dbg.declare(metadata !{i32* %t1}, metadata !155), !dbg !156, !clap !157
  call void @llvm.dbg.declare(metadata !{i32* %t2}, metadata !158), !dbg !159, !clap !160
  call void @llvm.dbg.declare(metadata !{i32* %t3}, metadata !161), !dbg !162, !clap !163
  call void @llvm.dbg.declare(metadata !{i32* %cond0}, metadata !164), !dbg !165, !clap !166
  call void @llvm.dbg.declare(metadata !{i32* %cond1}, metadata !167), !dbg !168, !clap !169
  call void @llvm.dbg.declare(metadata !{i32* %cond2}, metadata !170), !dbg !171, !clap !172
  call void @llvm.dbg.declare(metadata !{i32* %cond3}, metadata !173), !dbg !174, !clap !175
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 0, i32 0, i32 32, i32 86)
  store i32 0, i32* @y, align 4, !dbg !176, !clap !177
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 0, i32 0, i32 32, i32 86)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 0, i32 0, i32 32, i32 87)
  store i32 0, i32* @x, align 4, !dbg !176, !clap !178
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 0, i32 0, i32 32, i32 87)
  %call = call i32 @clap_thread_create(i32* %t0, %union.pthread_attr_t* null, i8* (i8*)* @P0, i8* null) nounwind, !dbg !179, !clap !180
  %call1 = call i32 @clap_thread_create(i32* %t1, %union.pthread_attr_t* null, i8* (i8*)* @P1, i8* null) nounwind, !dbg !181, !clap !182
  %call2 = call i32 @clap_thread_create(i32* %t2, %union.pthread_attr_t* null, i8* (i8*)* @P2, i8* null) nounwind, !dbg !183, !clap !184
  %call3 = call i32 @clap_thread_create(i32* %t3, %union.pthread_attr_t* null, i8* (i8*)* @P3, i8* null) nounwind, !dbg !185, !clap !186
  %tmp = load i32* %t0, align 4, !dbg !187, !clap !188
  %tmp1 = bitcast i32* %cond0 to i8**, !dbg !187, !clap !189
  %call4 = call i32 @clap_thread_join(i32 %tmp, i8** %tmp1), !dbg !187, !clap !190
  %tmp2 = load i32* %t1, align 4, !dbg !191, !clap !192
  %tmp3 = bitcast i32* %cond1 to i8**, !dbg !191, !clap !193
  %call5 = call i32 @clap_thread_join(i32 %tmp2, i8** %tmp3), !dbg !191, !clap !194
  %tmp4 = load i32* %t2, align 4, !dbg !195, !clap !196
  %tmp5 = bitcast i32* %cond2 to i8**, !dbg !195, !clap !197
  %call6 = call i32 @clap_thread_join(i32 %tmp4, i8** %tmp5), !dbg !195, !clap !198
  %tmp6 = load i32* %t3, align 4, !dbg !199, !clap !200
  %tmp7 = bitcast i32* %cond3 to i8**, !dbg !199, !clap !201
  %call7 = call i32 @clap_thread_join(i32 %tmp6, i8** %tmp7), !dbg !199, !clap !202
  %tmp8 = load i32* %cond0, align 4, !dbg !203, !clap !204
  %tobool = icmp ne i32 %tmp8, 0, !dbg !203, !clap !205
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !203, !clap !206

land.lhs.true:                                    ; preds = %entry
  %tmp9 = load i32* %cond2, align 4, !dbg !203, !clap !207
  %tobool8 = icmp ne i32 %tmp9, 0, !dbg !203, !clap !208
  br i1 %tobool8, label %if.then, label %if.end, !dbg !203, !clap !209

if.then:                                          ; preds = %land.lhs.true
  %call9 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([37 x i8]* @.str2, i32 0, i32 0)), !dbg !210, !clap !212
  %call10 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([30 x i8]* @.str3, i32 0, i32 0)), !dbg !213, !clap !214
  br label %if.end, !dbg !215, !clap !216

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  ret i32 0, !dbg !217, !clap !218
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

!0 = metadata !{i32 720913, i32 0, i32 12, metadata !"../examples/tso/regression-examples/safe027/safe027.c", metadata !"/home/naling/src/inspect-0.3", metadata !"clang version 3.0 (tags/RELEASE_30/final)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !22} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !11, metadata !15, metadata !16, metadata !17, metadata !18}
!5 = metadata !{i32 720942, i32 0, metadata !6, metadata !"MFENCE", metadata !"MFENCE", metadata !"", metadata !6, i32 30, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 0, i1 false, void ()* @MFENCE, null, null, metadata !9} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 720937, metadata !"../examples/tso/regression-examples/safe027/safe027.c", metadata !"/home/naling/src/inspect-0.3", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{null}
!9 = metadata !{metadata !10}
!10 = metadata !{i32 720932}                      ; [ DW_TAG_base_type ]
!11 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P0", metadata !"P0", metadata !"", metadata !6, i32 33, metadata !12, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P0, null, null, metadata !9} ; [ DW_TAG_subprogram ]
!12 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !13, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!13 = metadata !{metadata !14}
!14 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ]
!15 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P1", metadata !"P1", metadata !"", metadata !6, i32 42, metadata !12, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P1, null, null, metadata !9} ; [ DW_TAG_subprogram ]
!16 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P2", metadata !"P2", metadata !"", metadata !6, i32 49, metadata !12, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P2, null, null, metadata !9} ; [ DW_TAG_subprogram ]
!17 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P3", metadata !"P3", metadata !"", metadata !6, i32 58, metadata !12, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P3, null, null, metadata !9} ; [ DW_TAG_subprogram ]
!18 = metadata !{i32 720942, i32 0, metadata !6, metadata !"main", metadata !"main", metadata !"", metadata !6, i32 65, metadata !19, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i32 ()* @main, null, null, metadata !9} ; [ DW_TAG_subprogram ]
!19 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !20, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!20 = metadata !{metadata !21}
!21 = metadata !{i32 720932, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!22 = metadata !{metadata !23}
!23 = metadata !{metadata !24, metadata !26, metadata !27}
!24 = metadata !{i32 720948, i32 0, null, metadata !"x", metadata !"x", metadata !"", metadata !6, i32 28, metadata !25, i32 0, i32 1, i32* @x} ; [ DW_TAG_variable ]
!25 = metadata !{i32 720932, null, metadata !"long int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!26 = metadata !{i32 720948, i32 0, null, metadata !"y", metadata !"y", metadata !"", metadata !6, i32 28, metadata !25, i32 0, i32 1, i32* @y} ; [ DW_TAG_variable ]
!27 = metadata !{i32 720948, i32 0, null, metadata !"z", metadata !"z", metadata !"", metadata !6, i32 28, metadata !25, i32 0, i32 1, i32* @z} ; [ DW_TAG_variable ]
!28 = metadata !{i32 30, i32 15, metadata !29, null}
!29 = metadata !{i32 720907, metadata !5, i32 30, i32 14, metadata !6, i32 0} ; [ DW_TAG_lexical_block ]
!30 = metadata !{i32 1}
!31 = metadata !{i32 2}
!32 = metadata !{i32 3}
!33 = metadata !{i32 4}
!34 = metadata !{i32 5}
!35 = metadata !{i32 721153, metadata !11, metadata !"arg", metadata !6, i32 16777248, metadata !14, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!36 = metadata !{i32 32, i32 16, metadata !11, null}
!37 = metadata !{i32 6}
!38 = metadata !{i32 721152, metadata !39, metadata !"EAX", metadata !6, i32 34, metadata !25, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!39 = metadata !{i32 720907, metadata !11, i32 33, i32 1, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!40 = metadata !{i32 34, i32 12, metadata !39, null}
!41 = metadata !{i32 7}
!42 = metadata !{i32 721152, metadata !39, metadata !"EBX", metadata !6, i32 34, metadata !25, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!43 = metadata !{i32 34, i32 17, metadata !39, null}
!44 = metadata !{i32 8}
!45 = metadata !{i32 35, i32 3, metadata !39, null}
!46 = metadata !{i32 9}
!47 = metadata !{i32 10}
!48 = metadata !{i32 36, i32 3, metadata !39, null}
!49 = metadata !{i32 11}
!50 = metadata !{i32 12}
!51 = metadata !{i32 37, i32 3, metadata !39, null}
!52 = metadata !{i32 13}
!53 = metadata !{i32 14}
!54 = metadata !{i32 15}
!55 = metadata !{i32 38, i32 3, metadata !39, null}
!56 = metadata !{i32 16}
!57 = metadata !{i32 17}
!58 = metadata !{i32 18}
!59 = metadata !{i32 19}
!60 = metadata !{i32 20}
!61 = metadata !{i32 21}
!62 = metadata !{i32 22}
!63 = metadata !{i32 23}
!64 = metadata !{i32 24}
!65 = metadata !{i32 39, i32 1, metadata !11, null}
!66 = metadata !{i32 25}
!67 = metadata !{i32 26}
!68 = metadata !{i32 27}
!69 = metadata !{i32 28}
!70 = metadata !{i32 29}
!71 = metadata !{i32 721153, metadata !15, metadata !"arg", metadata !6, i32 16777257, metadata !14, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!72 = metadata !{i32 41, i32 16, metadata !15, null}
!73 = metadata !{i32 30}
!74 = metadata !{i32 721152, metadata !75, metadata !"EAX", metadata !6, i32 43, metadata !25, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!75 = metadata !{i32 720907, metadata !15, i32 42, i32 1, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!76 = metadata !{i32 43, i32 12, metadata !75, null}
!77 = metadata !{i32 31}
!78 = metadata !{i32 721152, metadata !75, metadata !"EBX", metadata !6, i32 43, metadata !25, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!79 = metadata !{i32 43, i32 17, metadata !75, null}
!80 = metadata !{i32 32}
!81 = metadata !{i32 44, i32 3, metadata !75, null}
!82 = metadata !{i32 33}
!83 = metadata !{i32 45, i32 3, metadata !75, null}
!84 = metadata !{i32 34}
!85 = metadata !{i32 35}
!86 = metadata !{i32 36}
!87 = metadata !{i32 37}
!88 = metadata !{i32 38}
!89 = metadata !{i32 721153, metadata !16, metadata !"arg", metadata !6, i32 16777264, metadata !14, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!90 = metadata !{i32 48, i32 16, metadata !16, null}
!91 = metadata !{i32 39}
!92 = metadata !{i32 721152, metadata !93, metadata !"EAX", metadata !6, i32 50, metadata !25, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!93 = metadata !{i32 720907, metadata !16, i32 49, i32 1, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!94 = metadata !{i32 50, i32 12, metadata !93, null}
!95 = metadata !{i32 40}
!96 = metadata !{i32 721152, metadata !93, metadata !"EBX", metadata !6, i32 50, metadata !25, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!97 = metadata !{i32 50, i32 17, metadata !93, null}
!98 = metadata !{i32 41}
!99 = metadata !{i32 51, i32 3, metadata !93, null}
!100 = metadata !{i32 42}
!101 = metadata !{i32 43}
!102 = metadata !{i32 52, i32 3, metadata !93, null}
!103 = metadata !{i32 44}
!104 = metadata !{i32 45}
!105 = metadata !{i32 53, i32 3, metadata !93, null}
!106 = metadata !{i32 46}
!107 = metadata !{i32 47}
!108 = metadata !{i32 48}
!109 = metadata !{i32 54, i32 3, metadata !93, null}
!110 = metadata !{i32 49}
!111 = metadata !{i32 50}
!112 = metadata !{i32 51}
!113 = metadata !{i32 52}
!114 = metadata !{i32 53}
!115 = metadata !{i32 54}
!116 = metadata !{i32 55}
!117 = metadata !{i32 56}
!118 = metadata !{i32 57}
!119 = metadata !{i32 55, i32 1, metadata !16, null}
!120 = metadata !{i32 58}
!121 = metadata !{i32 59}
!122 = metadata !{i32 60}
!123 = metadata !{i32 61}
!124 = metadata !{i32 62}
!125 = metadata !{i32 721153, metadata !17, metadata !"arg", metadata !6, i32 16777273, metadata !14, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!126 = metadata !{i32 57, i32 16, metadata !17, null}
!127 = metadata !{i32 63}
!128 = metadata !{i32 721152, metadata !129, metadata !"EAX", metadata !6, i32 59, metadata !25, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!129 = metadata !{i32 720907, metadata !17, i32 58, i32 1, metadata !6, i32 4} ; [ DW_TAG_lexical_block ]
!130 = metadata !{i32 59, i32 12, metadata !129, null}
!131 = metadata !{i32 64}
!132 = metadata !{i32 721152, metadata !129, metadata !"EBX", metadata !6, i32 59, metadata !25, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!133 = metadata !{i32 59, i32 17, metadata !129, null}
!134 = metadata !{i32 65}
!135 = metadata !{i32 60, i32 3, metadata !129, null}
!136 = metadata !{i32 66}
!137 = metadata !{i32 61, i32 3, metadata !129, null}
!138 = metadata !{i32 67}
!139 = metadata !{i32 68}
!140 = metadata !{i32 69}
!141 = metadata !{i32 70}
!142 = metadata !{i32 71}
!143 = metadata !{i32 72}
!144 = metadata !{i32 73}
!145 = metadata !{i32 74}
!146 = metadata !{i32 75}
!147 = metadata !{i32 76}
!148 = metadata !{i32 77}
!149 = metadata !{i32 721152, metadata !150, metadata !"t0", metadata !6, i32 66, metadata !151, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!150 = metadata !{i32 720907, metadata !18, i32 65, i32 1, metadata !6, i32 5} ; [ DW_TAG_lexical_block ]
!151 = metadata !{i32 720918, null, metadata !"pthread_t", metadata !6, i32 60, i64 0, i64 0, i64 0, i32 0, metadata !152} ; [ DW_TAG_typedef ]
!152 = metadata !{i32 720932, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!153 = metadata !{i32 66, i32 13, metadata !150, null}
!154 = metadata !{i32 78}
!155 = metadata !{i32 721152, metadata !150, metadata !"t1", metadata !6, i32 66, metadata !151, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!156 = metadata !{i32 66, i32 17, metadata !150, null}
!157 = metadata !{i32 79}
!158 = metadata !{i32 721152, metadata !150, metadata !"t2", metadata !6, i32 66, metadata !151, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!159 = metadata !{i32 66, i32 21, metadata !150, null}
!160 = metadata !{i32 80}
!161 = metadata !{i32 721152, metadata !150, metadata !"t3", metadata !6, i32 66, metadata !151, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!162 = metadata !{i32 66, i32 25, metadata !150, null}
!163 = metadata !{i32 81}
!164 = metadata !{i32 721152, metadata !150, metadata !"cond0", metadata !6, i32 67, metadata !25, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!165 = metadata !{i32 67, i32 12, metadata !150, null}
!166 = metadata !{i32 82}
!167 = metadata !{i32 721152, metadata !150, metadata !"cond1", metadata !6, i32 67, metadata !25, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!168 = metadata !{i32 67, i32 19, metadata !150, null}
!169 = metadata !{i32 83}
!170 = metadata !{i32 721152, metadata !150, metadata !"cond2", metadata !6, i32 67, metadata !25, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!171 = metadata !{i32 67, i32 26, metadata !150, null}
!172 = metadata !{i32 84}
!173 = metadata !{i32 721152, metadata !150, metadata !"cond3", metadata !6, i32 67, metadata !25, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!174 = metadata !{i32 67, i32 33, metadata !150, null}
!175 = metadata !{i32 85}
!176 = metadata !{i32 69, i32 3, metadata !150, null}
!177 = metadata !{i32 86}
!178 = metadata !{i32 87}
!179 = metadata !{i32 71, i32 3, metadata !150, null}
!180 = metadata !{i32 88}
!181 = metadata !{i32 72, i32 3, metadata !150, null}
!182 = metadata !{i32 89}
!183 = metadata !{i32 73, i32 3, metadata !150, null}
!184 = metadata !{i32 90}
!185 = metadata !{i32 74, i32 3, metadata !150, null}
!186 = metadata !{i32 91}
!187 = metadata !{i32 76, i32 3, metadata !150, null}
!188 = metadata !{i32 92}
!189 = metadata !{i32 93}
!190 = metadata !{i32 94}
!191 = metadata !{i32 77, i32 3, metadata !150, null}
!192 = metadata !{i32 95}
!193 = metadata !{i32 96}
!194 = metadata !{i32 97}
!195 = metadata !{i32 78, i32 3, metadata !150, null}
!196 = metadata !{i32 98}
!197 = metadata !{i32 99}
!198 = metadata !{i32 100}
!199 = metadata !{i32 79, i32 3, metadata !150, null}
!200 = metadata !{i32 101}
!201 = metadata !{i32 102}
!202 = metadata !{i32 103}
!203 = metadata !{i32 82, i32 3, metadata !150, null}
!204 = metadata !{i32 104}
!205 = metadata !{i32 105}
!206 = metadata !{i32 106}
!207 = metadata !{i32 107}
!208 = metadata !{i32 108}
!209 = metadata !{i32 109}
!210 = metadata !{i32 83, i32 5, metadata !211, null}
!211 = metadata !{i32 720907, metadata !150, i32 82, i32 25, metadata !6, i32 6} ; [ DW_TAG_lexical_block ]
!212 = metadata !{i32 110}
!213 = metadata !{i32 84, i32 5, metadata !211, null}
!214 = metadata !{i32 111}
!215 = metadata !{i32 85, i32 3, metadata !211, null}
!216 = metadata !{i32 112}
!217 = metadata !{i32 87, i32 3, metadata !150, null}
!218 = metadata !{i32 113}
