; ModuleID = '../examples/tso/regression-examples/mix006/mix006.c.lz.opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%union.pthread_attr_t = type { i32, [32 x i8] }

@z = common global i32 0, align 4
@x = common global i32 0, align 4
@y = common global i32 0, align 4
@.str = private unnamed_addr constant [32 x i8] c"\0A %%%% (EAX1=%d, EBX1=%d) %%%%\0A\00", align 1
@.str1 = private unnamed_addr constant [32 x i8] c"\0A %%%% (EAX2=%d, EBX2=%d) %%%%\0A\00", align 1
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
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @z, i32 1, i32 0, i32 32, i32 8)
  store i32 1, i32* @z, align 4, !dbg !38, !clap !39
  call void (i32, ...)* @clap_store_post(i32 5, i32* @z, i32 1, i32 0, i32 32, i32 8)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 9)
  store i32 1, i32* @x, align 4, !dbg !40, !clap !41
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 9)
  ret i8* inttoptr (i32 1 to i8*), !dbg !42, !clap !43
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

define i8* @P1(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !44
  %EAX = alloca i32, align 4, !clap !45
  %EBX = alloca i32, align 4, !clap !46
  store i8* %arg, i8** %arg.addr, align 4, !clap !47
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !48), !dbg !49, !clap !50
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !51), !dbg !53, !clap !54
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !55), !dbg !56, !clap !57
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 2, i32 0, i32 32, i32 18)
  store i32 2, i32* @x, align 4, !dbg !58, !clap !59
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 2, i32 0, i32 32, i32 18)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 19)
  %tmp = load i32* @x, align 4, !dbg !60, !clap !61
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 19)
  store i32 %tmp, i32* %EAX, align 4, !dbg !60, !clap !62
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 21)
  %tmp1 = load i32* @y, align 4, !dbg !63, !clap !64
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 21)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !63, !clap !65
  %tmp2 = load i32* %EAX, align 4, !dbg !66, !clap !67
  %tmp3 = load i32* %EBX, align 4, !dbg !66, !clap !68
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([32 x i8]* @.str, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !66, !clap !69
  %tmp4 = load i32* %EAX, align 4, !dbg !70, !clap !71
  %cmp = icmp eq i32 %tmp4, 2, !dbg !70, !clap !72
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !70, !clap !73

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !70, !clap !74
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !70, !clap !75
  br label %land.end, !clap !76

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !77
  %land.ext = zext i1 %tmp6 to i32, !clap !78
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !79
  ret i8* %tmp7, !dbg !80, !clap !81
}

declare i32 @printf(i8*, ...)

define i8* @P2(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !82
  %EAX = alloca i32, align 4, !clap !83
  %EBX = alloca i32, align 4, !clap !84
  store i8* %arg, i8** %arg.addr, align 4, !clap !85
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !86), !dbg !87, !clap !88
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !89), !dbg !91, !clap !92
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !93), !dbg !94, !clap !95
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 43)
  store i32 1, i32* @y, align 4, !dbg !96, !clap !97
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 43)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 44)
  %tmp = load i32* @y, align 4, !dbg !98, !clap !99
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 44)
  store i32 %tmp, i32* %EAX, align 4, !dbg !98, !clap !100
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @z, i32 0, i32 32, i32 46)
  %tmp1 = load i32* @z, align 4, !dbg !101, !clap !102
  call void (i32, ...)* @clap_load_post(i32 4, i32* @z, i32 0, i32 32, i32 46)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !101, !clap !103
  %tmp2 = load i32* %EAX, align 4, !dbg !104, !clap !105
  %tmp3 = load i32* %EBX, align 4, !dbg !104, !clap !106
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([32 x i8]* @.str1, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !104, !clap !107
  %tmp4 = load i32* %EAX, align 4, !dbg !108, !clap !109
  %cmp = icmp eq i32 %tmp4, 1, !dbg !108, !clap !110
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !108, !clap !111

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !108, !clap !112
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !108, !clap !113
  br label %land.end, !clap !114

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !115
  %land.ext = zext i1 %tmp6 to i32, !clap !116
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !117
  ret i8* %tmp7, !dbg !118, !clap !119
}

define i32 @main() nounwind {
entry:
  %retval = alloca i32, align 4, !clap !120
  %t0 = alloca i32, align 4, !clap !121
  %t1 = alloca i32, align 4, !clap !122
  %t2 = alloca i32, align 4, !clap !123
  %cond0 = alloca i32, align 4, !clap !124
  %cond1 = alloca i32, align 4, !clap !125
  %cond2 = alloca i32, align 4, !clap !126
  store i32 0, i32* %retval, !clap !127
  call void @llvm.dbg.declare(metadata !{i32* %t0}, metadata !128), !dbg !132, !clap !133
  call void @llvm.dbg.declare(metadata !{i32* %t1}, metadata !134), !dbg !135, !clap !136
  call void @llvm.dbg.declare(metadata !{i32* %t2}, metadata !137), !dbg !138, !clap !139
  call void @llvm.dbg.declare(metadata !{i32* %cond0}, metadata !140), !dbg !141, !clap !142
  call void @llvm.dbg.declare(metadata !{i32* %cond1}, metadata !143), !dbg !144, !clap !145
  call void @llvm.dbg.declare(metadata !{i32* %cond2}, metadata !146), !dbg !147, !clap !148
  %call = call i32 @clap_thread_create(i32* %t0, %union.pthread_attr_t* null, i8* (i8*)* @P0, i8* null) nounwind, !dbg !149, !clap !150
  %call1 = call i32 @clap_thread_create(i32* %t1, %union.pthread_attr_t* null, i8* (i8*)* @P1, i8* null) nounwind, !dbg !151, !clap !152
  %call2 = call i32 @clap_thread_create(i32* %t2, %union.pthread_attr_t* null, i8* (i8*)* @P2, i8* null) nounwind, !dbg !153, !clap !154
  %tmp = load i32* %t0, align 4, !dbg !155, !clap !156
  %tmp1 = bitcast i32* %cond0 to i8**, !dbg !155, !clap !157
  %call3 = call i32 @clap_thread_join(i32 %tmp, i8** %tmp1), !dbg !155, !clap !158
  %tmp2 = load i32* %t1, align 4, !dbg !159, !clap !160
  %tmp3 = bitcast i32* %cond1 to i8**, !dbg !159, !clap !161
  %call4 = call i32 @clap_thread_join(i32 %tmp2, i8** %tmp3), !dbg !159, !clap !162
  %tmp4 = load i32* %t2, align 4, !dbg !163, !clap !164
  %tmp5 = bitcast i32* %cond2 to i8**, !dbg !163, !clap !165
  %call5 = call i32 @clap_thread_join(i32 %tmp4, i8** %tmp5), !dbg !163, !clap !166
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 87)
  %tmp6 = load i32* @x, align 4, !dbg !167, !clap !168
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 87)
  %cmp = icmp eq i32 %tmp6, 2, !dbg !167, !clap !169
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !167, !clap !170

land.lhs.true:                                    ; preds = %entry
  %tmp7 = load i32* %cond1, align 4, !dbg !167, !clap !171
  %tobool = icmp ne i32 %tmp7, 0, !dbg !167, !clap !172
  br i1 %tobool, label %land.lhs.true6, label %if.end, !dbg !167, !clap !173

land.lhs.true6:                                   ; preds = %land.lhs.true
  %tmp8 = load i32* %cond2, align 4, !dbg !167, !clap !174
  %tobool7 = icmp ne i32 %tmp8, 0, !dbg !167, !clap !175
  br i1 %tobool7, label %land.lhs.true8, label %if.end, !dbg !167, !clap !176

land.lhs.true8:                                   ; preds = %land.lhs.true6
  %tmp9 = load i32* %cond0, align 4, !dbg !167, !clap !177
  %tobool9 = icmp ne i32 %tmp9, 0, !dbg !167, !clap !178
  br i1 %tobool9, label %if.then, label %if.end, !dbg !167, !clap !179

if.then:                                          ; preds = %land.lhs.true8
  %call10 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([37 x i8]* @.str2, i32 0, i32 0)), !dbg !180, !clap !182
  %call11 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([30 x i8]* @.str3, i32 0, i32 0)), !dbg !183, !clap !184
  br label %if.end, !dbg !185, !clap !186

if.end:                                           ; preds = %if.then, %land.lhs.true8, %land.lhs.true6, %land.lhs.true, %entry
  ret i32 0, !dbg !187, !clap !188
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

!0 = metadata !{i32 720913, i32 0, i32 12, metadata !"../examples/tso/regression-examples/mix006/mix006.c", metadata !"/home/naling/src/inspect-0.3", metadata !"clang version 3.0 (tags/RELEASE_30/final)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !18} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !12, metadata !13, metadata !14}
!5 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P0", metadata !"P0", metadata !"", metadata !6, i32 32, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P0, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 720937, metadata !"../examples/tso/regression-examples/mix006/mix006.c", metadata !"/home/naling/src/inspect-0.3", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{metadata !9}
!9 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ]
!10 = metadata !{metadata !11}
!11 = metadata !{i32 720932}                      ; [ DW_TAG_base_type ]
!12 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P1", metadata !"P1", metadata !"", metadata !6, i32 40, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P1, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!13 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P2", metadata !"P2", metadata !"", metadata !6, i32 50, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P2, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!14 = metadata !{i32 720942, i32 0, metadata !6, metadata !"main", metadata !"main", metadata !"", metadata !6, i32 60, metadata !15, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i32 ()* @main, null, null, metadata !10} ; [ DW_TAG_subprogram ]
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
!42 = metadata !{i32 36, i32 3, metadata !32, null}
!43 = metadata !{i32 10}
!44 = metadata !{i32 11}
!45 = metadata !{i32 12}
!46 = metadata !{i32 13}
!47 = metadata !{i32 14}
!48 = metadata !{i32 721153, metadata !12, metadata !"arg", metadata !6, i32 16777255, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!49 = metadata !{i32 39, i32 16, metadata !12, null}
!50 = metadata !{i32 15}
!51 = metadata !{i32 721152, metadata !52, metadata !"EAX", metadata !6, i32 41, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!52 = metadata !{i32 720907, metadata !12, i32 40, i32 1, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!53 = metadata !{i32 41, i32 12, metadata !52, null}
!54 = metadata !{i32 16}
!55 = metadata !{i32 721152, metadata !52, metadata !"EBX", metadata !6, i32 41, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!56 = metadata !{i32 41, i32 17, metadata !52, null}
!57 = metadata !{i32 17}
!58 = metadata !{i32 42, i32 3, metadata !52, null}
!59 = metadata !{i32 18}
!60 = metadata !{i32 43, i32 3, metadata !52, null}
!61 = metadata !{i32 19}
!62 = metadata !{i32 20}
!63 = metadata !{i32 44, i32 3, metadata !52, null}
!64 = metadata !{i32 21}
!65 = metadata !{i32 22}
!66 = metadata !{i32 45, i32 3, metadata !52, null}
!67 = metadata !{i32 23}
!68 = metadata !{i32 24}
!69 = metadata !{i32 25}
!70 = metadata !{i32 46, i32 3, metadata !52, null}
!71 = metadata !{i32 26}
!72 = metadata !{i32 27}
!73 = metadata !{i32 28}
!74 = metadata !{i32 29}
!75 = metadata !{i32 30}
!76 = metadata !{i32 31}
!77 = metadata !{i32 32}
!78 = metadata !{i32 33}
!79 = metadata !{i32 34}
!80 = metadata !{i32 47, i32 1, metadata !12, null}
!81 = metadata !{i32 35}
!82 = metadata !{i32 36}
!83 = metadata !{i32 37}
!84 = metadata !{i32 38}
!85 = metadata !{i32 39}
!86 = metadata !{i32 721153, metadata !13, metadata !"arg", metadata !6, i32 16777265, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!87 = metadata !{i32 49, i32 16, metadata !13, null}
!88 = metadata !{i32 40}
!89 = metadata !{i32 721152, metadata !90, metadata !"EAX", metadata !6, i32 51, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!90 = metadata !{i32 720907, metadata !13, i32 50, i32 1, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!91 = metadata !{i32 51, i32 12, metadata !90, null}
!92 = metadata !{i32 41}
!93 = metadata !{i32 721152, metadata !90, metadata !"EBX", metadata !6, i32 51, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!94 = metadata !{i32 51, i32 17, metadata !90, null}
!95 = metadata !{i32 42}
!96 = metadata !{i32 52, i32 3, metadata !90, null}
!97 = metadata !{i32 43}
!98 = metadata !{i32 53, i32 3, metadata !90, null}
!99 = metadata !{i32 44}
!100 = metadata !{i32 45}
!101 = metadata !{i32 54, i32 3, metadata !90, null}
!102 = metadata !{i32 46}
!103 = metadata !{i32 47}
!104 = metadata !{i32 55, i32 3, metadata !90, null}
!105 = metadata !{i32 48}
!106 = metadata !{i32 49}
!107 = metadata !{i32 50}
!108 = metadata !{i32 56, i32 3, metadata !90, null}
!109 = metadata !{i32 51}
!110 = metadata !{i32 52}
!111 = metadata !{i32 53}
!112 = metadata !{i32 54}
!113 = metadata !{i32 55}
!114 = metadata !{i32 56}
!115 = metadata !{i32 57}
!116 = metadata !{i32 58}
!117 = metadata !{i32 59}
!118 = metadata !{i32 57, i32 1, metadata !13, null}
!119 = metadata !{i32 60}
!120 = metadata !{i32 61}
!121 = metadata !{i32 62}
!122 = metadata !{i32 63}
!123 = metadata !{i32 64}
!124 = metadata !{i32 65}
!125 = metadata !{i32 66}
!126 = metadata !{i32 67}
!127 = metadata !{i32 68}
!128 = metadata !{i32 721152, metadata !129, metadata !"t0", metadata !6, i32 61, metadata !130, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!129 = metadata !{i32 720907, metadata !14, i32 60, i32 1, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!130 = metadata !{i32 720918, null, metadata !"pthread_t", metadata !6, i32 60, i64 0, i64 0, i64 0, i32 0, metadata !131} ; [ DW_TAG_typedef ]
!131 = metadata !{i32 720932, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!132 = metadata !{i32 61, i32 13, metadata !129, null}
!133 = metadata !{i32 69}
!134 = metadata !{i32 721152, metadata !129, metadata !"t1", metadata !6, i32 61, metadata !130, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!135 = metadata !{i32 61, i32 17, metadata !129, null}
!136 = metadata !{i32 70}
!137 = metadata !{i32 721152, metadata !129, metadata !"t2", metadata !6, i32 61, metadata !130, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!138 = metadata !{i32 61, i32 21, metadata !129, null}
!139 = metadata !{i32 71}
!140 = metadata !{i32 721152, metadata !129, metadata !"cond0", metadata !6, i32 62, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!141 = metadata !{i32 62, i32 12, metadata !129, null}
!142 = metadata !{i32 72}
!143 = metadata !{i32 721152, metadata !129, metadata !"cond1", metadata !6, i32 62, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!144 = metadata !{i32 62, i32 19, metadata !129, null}
!145 = metadata !{i32 73}
!146 = metadata !{i32 721152, metadata !129, metadata !"cond2", metadata !6, i32 62, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!147 = metadata !{i32 62, i32 26, metadata !129, null}
!148 = metadata !{i32 74}
!149 = metadata !{i32 64, i32 3, metadata !129, null}
!150 = metadata !{i32 75}
!151 = metadata !{i32 65, i32 3, metadata !129, null}
!152 = metadata !{i32 76}
!153 = metadata !{i32 66, i32 3, metadata !129, null}
!154 = metadata !{i32 77}
!155 = metadata !{i32 68, i32 3, metadata !129, null}
!156 = metadata !{i32 78}
!157 = metadata !{i32 79}
!158 = metadata !{i32 80}
!159 = metadata !{i32 69, i32 3, metadata !129, null}
!160 = metadata !{i32 81}
!161 = metadata !{i32 82}
!162 = metadata !{i32 83}
!163 = metadata !{i32 70, i32 3, metadata !129, null}
!164 = metadata !{i32 84}
!165 = metadata !{i32 85}
!166 = metadata !{i32 86}
!167 = metadata !{i32 73, i32 3, metadata !129, null}
!168 = metadata !{i32 87}
!169 = metadata !{i32 88}
!170 = metadata !{i32 89}
!171 = metadata !{i32 90}
!172 = metadata !{i32 91}
!173 = metadata !{i32 92}
!174 = metadata !{i32 93}
!175 = metadata !{i32 94}
!176 = metadata !{i32 95}
!177 = metadata !{i32 96}
!178 = metadata !{i32 97}
!179 = metadata !{i32 98}
!180 = metadata !{i32 74, i32 5, metadata !181, null}
!181 = metadata !{i32 720907, metadata !129, i32 73, i32 42, metadata !6, i32 4} ; [ DW_TAG_lexical_block ]
!182 = metadata !{i32 99}
!183 = metadata !{i32 75, i32 5, metadata !181, null}
!184 = metadata !{i32 100}
!185 = metadata !{i32 76, i32 3, metadata !181, null}
!186 = metadata !{i32 101}
!187 = metadata !{i32 78, i32 3, metadata !129, null}
!188 = metadata !{i32 102}
