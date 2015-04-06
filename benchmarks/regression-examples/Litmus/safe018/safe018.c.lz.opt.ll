; ModuleID = '/home/naling/src/examples/tso/regression-examples/safe018/safe018.c.lz.opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%union.pthread_attr_t = type { i32, [32 x i8] }

@y = common global i32 0, align 4
@x = common global i32 0, align 4
@.str = private unnamed_addr constant [23 x i8] c"\0A (EAX0=%d, EBX0=%d) \0A\00", align 1
@.str1 = private unnamed_addr constant [14 x i8] c"\0A (EAX2=%d) \0A\00", align 1
@.str2 = private unnamed_addr constant [37 x i8] c"\0A@@@CLAP: There is a SC violation! \0A\00", align 1
@.str3 = private unnamed_addr constant [30 x i8] c"\1B[1;31m SC Violation!!! \1B[0m\0A\00", align 1
@z = common global i32 0, align 4

define i8* @P0(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !24
  %EAX = alloca i32, align 4, !clap !25
  %EBX = alloca i32, align 4, !clap !26
  store i8* %arg, i8** %arg.addr, align 4, !clap !27
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !28), !dbg !29, !clap !30
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !31), !dbg !33, !clap !34
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !35), !dbg !36, !clap !37
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 8)
  %tmp = load i32* @y, align 4, !dbg !38, !clap !39
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 8)
  store i32 %tmp, i32* %EAX, align 4, !dbg !38, !clap !40
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 10)
  %tmp1 = load i32* @x, align 4, !dbg !41, !clap !42
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 10)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !41, !clap !43
  %tmp2 = load i32* %EAX, align 4, !dbg !44, !clap !45
  %tmp3 = load i32* %EBX, align 4, !dbg !44, !clap !46
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([23 x i8]* @.str, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !44, !clap !47
  %tmp4 = load i32* %EAX, align 4, !dbg !48, !clap !49
  %cmp = icmp eq i32 %tmp4, 1, !dbg !48, !clap !50
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !48, !clap !51

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !48, !clap !52
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !48, !clap !53
  br label %land.end, !clap !54

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !55
  %land.ext = zext i1 %tmp6 to i32, !clap !56
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !57
  ret i8* %tmp7, !dbg !58, !clap !59
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare i32 @printf(i8*, ...)

define i8* @P1(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !60
  %EAX = alloca i32, align 4, !clap !61
  %EBX = alloca i32, align 4, !clap !62
  store i8* %arg, i8** %arg.addr, align 4, !clap !63
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !64), !dbg !65, !clap !66
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !67), !dbg !69, !clap !70
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !71), !dbg !72, !clap !73
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 32)
  store i32 1, i32* @x, align 4, !dbg !74, !clap !75
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 32)
  ret i8* inttoptr (i32 1 to i8*), !dbg !76, !clap !77
}

define i8* @P2(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !78
  %EAX = alloca i32, align 4, !clap !79
  %EBX = alloca i32, align 4, !clap !80
  store i8* %arg, i8** %arg.addr, align 4, !clap !81
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !82), !dbg !83, !clap !84
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !85), !dbg !87, !clap !88
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !89), !dbg !90, !clap !91
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 41)
  %tmp = load i32* @x, align 4, !dbg !92, !clap !93
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 41)
  store i32 %tmp, i32* %EAX, align 4, !dbg !92, !clap !94
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 43)
  store i32 1, i32* @y, align 4, !dbg !95, !clap !96
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 43)
  %tmp1 = load i32* %EAX, align 4, !dbg !97, !clap !98
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([14 x i8]* @.str1, i32 0, i32 0), i32 %tmp1), !dbg !97, !clap !99
  %tmp2 = load i32* %EAX, align 4, !dbg !100, !clap !101
  %cmp = icmp eq i32 %tmp2, 1, !dbg !100, !clap !102
  %conv = zext i1 %cmp to i32, !dbg !100, !clap !103
  %tmp3 = inttoptr i32 %conv to i8*, !dbg !100, !clap !104
  ret i8* %tmp3, !dbg !100, !clap !105
}

define i32 @main() nounwind {
entry:
  %retval = alloca i32, align 4, !clap !106
  %t0 = alloca i32, align 4, !clap !107
  %t1 = alloca i32, align 4, !clap !108
  %t2 = alloca i32, align 4, !clap !109
  %t3 = alloca i32, align 4, !clap !110
  %cond0 = alloca i32, align 4, !clap !111
  %cond1 = alloca i32, align 4, !clap !112
  %cond2 = alloca i32, align 4, !clap !113
  %cond3 = alloca i32, align 4, !clap !114
  store i32 0, i32* %retval, !clap !115
  call void @llvm.dbg.declare(metadata !{i32* %t0}, metadata !116), !dbg !120, !clap !121
  call void @llvm.dbg.declare(metadata !{i32* %t1}, metadata !122), !dbg !123, !clap !124
  call void @llvm.dbg.declare(metadata !{i32* %t2}, metadata !125), !dbg !126, !clap !127
  call void @llvm.dbg.declare(metadata !{i32* %t3}, metadata !128), !dbg !129, !clap !130
  call void @llvm.dbg.declare(metadata !{i32* %cond0}, metadata !131), !dbg !132, !clap !133
  call void @llvm.dbg.declare(metadata !{i32* %cond1}, metadata !134), !dbg !135, !clap !136
  call void @llvm.dbg.declare(metadata !{i32* %cond2}, metadata !137), !dbg !138, !clap !139
  call void @llvm.dbg.declare(metadata !{i32* %cond3}, metadata !140), !dbg !141, !clap !142
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 0, i32 0, i32 32, i32 69)
  store i32 0, i32* @y, align 4, !dbg !143, !clap !144
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 0, i32 0, i32 32, i32 69)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 0, i32 0, i32 32, i32 70)
  store i32 0, i32* @x, align 4, !dbg !143, !clap !145
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 0, i32 0, i32 32, i32 70)
  %call = call i32 @clap_thread_create(i32* %t0, %union.pthread_attr_t* null, i8* (i8*)* @P0, i8* null) nounwind, !dbg !146, !clap !147
  %call1 = call i32 @clap_thread_create(i32* %t1, %union.pthread_attr_t* null, i8* (i8*)* @P1, i8* null) nounwind, !dbg !148, !clap !149
  %call2 = call i32 @clap_thread_create(i32* %t2, %union.pthread_attr_t* null, i8* (i8*)* @P2, i8* null) nounwind, !dbg !150, !clap !151
  %tmp = load i32* %t0, align 4, !dbg !152, !clap !153
  %tmp1 = bitcast i32* %cond0 to i8**, !dbg !152, !clap !154
  %call3 = call i32 @clap_thread_join(i32 %tmp, i8** %tmp1), !dbg !152, !clap !155
  %tmp2 = load i32* %t1, align 4, !dbg !156, !clap !157
  %tmp3 = bitcast i32* %cond1 to i8**, !dbg !156, !clap !158
  %call4 = call i32 @clap_thread_join(i32 %tmp2, i8** %tmp3), !dbg !156, !clap !159
  %tmp4 = load i32* %t2, align 4, !dbg !160, !clap !161
  %tmp5 = bitcast i32* %cond2 to i8**, !dbg !160, !clap !162
  %call5 = call i32 @clap_thread_join(i32 %tmp4, i8** %tmp5), !dbg !160, !clap !163
  %tmp6 = load i32* %cond0, align 4, !dbg !164, !clap !165
  %tobool = icmp ne i32 %tmp6, 0, !dbg !164, !clap !166
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !164, !clap !167

land.lhs.true:                                    ; preds = %entry
  %tmp7 = load i32* %cond2, align 4, !dbg !164, !clap !168
  %tobool6 = icmp ne i32 %tmp7, 0, !dbg !164, !clap !169
  br i1 %tobool6, label %if.then, label %if.end, !dbg !164, !clap !170

if.then:                                          ; preds = %land.lhs.true
  %call7 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([37 x i8]* @.str2, i32 0, i32 0)), !dbg !171, !clap !173
  %call8 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([30 x i8]* @.str3, i32 0, i32 0)), !dbg !174, !clap !175
  br label %if.end, !dbg !176, !clap !177

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  ret i32 0, !dbg !178, !clap !179
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

!0 = metadata !{i32 720913, i32 0, i32 12, metadata !"/home/naling/src/examples/tso/regression-examples/safe018/safe018.c", metadata !"/home/naling/src/inspect-0.3", metadata !"clang version 3.0 (tags/RELEASE_30/final)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !18} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !12, metadata !13, metadata !14}
!5 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P0", metadata !"P0", metadata !"", metadata !6, i32 33, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P0, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 720937, metadata !"/home/naling/src/examples/tso/regression-examples/safe018/safe018.c", metadata !"/home/naling/src/inspect-0.3", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{metadata !9}
!9 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ]
!10 = metadata !{metadata !11}
!11 = metadata !{i32 720932}                      ; [ DW_TAG_base_type ]
!12 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P1", metadata !"P1", metadata !"", metadata !6, i32 42, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P1, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!13 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P2", metadata !"P2", metadata !"", metadata !6, i32 49, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P2, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!14 = metadata !{i32 720942, i32 0, metadata !6, metadata !"main", metadata !"main", metadata !"", metadata !6, i32 58, metadata !15, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i32 ()* @main, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!15 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !16, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!16 = metadata !{metadata !17}
!17 = metadata !{i32 720932, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!18 = metadata !{metadata !19}
!19 = metadata !{metadata !20, metadata !22, metadata !23}
!20 = metadata !{i32 720948, i32 0, null, metadata !"x", metadata !"x", metadata !"", metadata !6, i32 28, metadata !21, i32 0, i32 1, i32* @x} ; [ DW_TAG_variable ]
!21 = metadata !{i32 720932, null, metadata !"long int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!22 = metadata !{i32 720948, i32 0, null, metadata !"y", metadata !"y", metadata !"", metadata !6, i32 28, metadata !21, i32 0, i32 1, i32* @y} ; [ DW_TAG_variable ]
!23 = metadata !{i32 720948, i32 0, null, metadata !"z", metadata !"z", metadata !"", metadata !6, i32 28, metadata !21, i32 0, i32 1, i32* @z} ; [ DW_TAG_variable ]
!24 = metadata !{i32 1}
!25 = metadata !{i32 2}
!26 = metadata !{i32 3}
!27 = metadata !{i32 4}
!28 = metadata !{i32 721153, metadata !5, metadata !"arg", metadata !6, i32 16777248, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!29 = metadata !{i32 32, i32 16, metadata !5, null}
!30 = metadata !{i32 5}
!31 = metadata !{i32 721152, metadata !32, metadata !"EAX", metadata !6, i32 34, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!32 = metadata !{i32 720907, metadata !5, i32 33, i32 1, metadata !6, i32 0} ; [ DW_TAG_lexical_block ]
!33 = metadata !{i32 34, i32 12, metadata !32, null}
!34 = metadata !{i32 6}
!35 = metadata !{i32 721152, metadata !32, metadata !"EBX", metadata !6, i32 34, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!36 = metadata !{i32 34, i32 17, metadata !32, null}
!37 = metadata !{i32 7}
!38 = metadata !{i32 35, i32 3, metadata !32, null}
!39 = metadata !{i32 8}
!40 = metadata !{i32 9}
!41 = metadata !{i32 36, i32 3, metadata !32, null}
!42 = metadata !{i32 10}
!43 = metadata !{i32 11}
!44 = metadata !{i32 37, i32 3, metadata !32, null}
!45 = metadata !{i32 12}
!46 = metadata !{i32 13}
!47 = metadata !{i32 14}
!48 = metadata !{i32 38, i32 3, metadata !32, null}
!49 = metadata !{i32 15}
!50 = metadata !{i32 16}
!51 = metadata !{i32 17}
!52 = metadata !{i32 18}
!53 = metadata !{i32 19}
!54 = metadata !{i32 20}
!55 = metadata !{i32 21}
!56 = metadata !{i32 22}
!57 = metadata !{i32 23}
!58 = metadata !{i32 39, i32 1, metadata !5, null}
!59 = metadata !{i32 24}
!60 = metadata !{i32 25}
!61 = metadata !{i32 26}
!62 = metadata !{i32 27}
!63 = metadata !{i32 28}
!64 = metadata !{i32 721153, metadata !12, metadata !"arg", metadata !6, i32 16777257, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!65 = metadata !{i32 41, i32 16, metadata !12, null}
!66 = metadata !{i32 29}
!67 = metadata !{i32 721152, metadata !68, metadata !"EAX", metadata !6, i32 43, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!68 = metadata !{i32 720907, metadata !12, i32 42, i32 1, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!69 = metadata !{i32 43, i32 12, metadata !68, null}
!70 = metadata !{i32 30}
!71 = metadata !{i32 721152, metadata !68, metadata !"EBX", metadata !6, i32 43, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!72 = metadata !{i32 43, i32 17, metadata !68, null}
!73 = metadata !{i32 31}
!74 = metadata !{i32 44, i32 3, metadata !68, null}
!75 = metadata !{i32 32}
!76 = metadata !{i32 45, i32 3, metadata !68, null}
!77 = metadata !{i32 33}
!78 = metadata !{i32 34}
!79 = metadata !{i32 35}
!80 = metadata !{i32 36}
!81 = metadata !{i32 37}
!82 = metadata !{i32 721153, metadata !13, metadata !"arg", metadata !6, i32 16777264, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!83 = metadata !{i32 48, i32 16, metadata !13, null}
!84 = metadata !{i32 38}
!85 = metadata !{i32 721152, metadata !86, metadata !"EAX", metadata !6, i32 50, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!86 = metadata !{i32 720907, metadata !13, i32 49, i32 1, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!87 = metadata !{i32 50, i32 12, metadata !86, null}
!88 = metadata !{i32 39}
!89 = metadata !{i32 721152, metadata !86, metadata !"EBX", metadata !6, i32 50, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!90 = metadata !{i32 50, i32 17, metadata !86, null}
!91 = metadata !{i32 40}
!92 = metadata !{i32 51, i32 3, metadata !86, null}
!93 = metadata !{i32 41}
!94 = metadata !{i32 42}
!95 = metadata !{i32 52, i32 3, metadata !86, null}
!96 = metadata !{i32 43}
!97 = metadata !{i32 53, i32 3, metadata !86, null}
!98 = metadata !{i32 44}
!99 = metadata !{i32 45}
!100 = metadata !{i32 54, i32 3, metadata !86, null}
!101 = metadata !{i32 46}
!102 = metadata !{i32 47}
!103 = metadata !{i32 48}
!104 = metadata !{i32 49}
!105 = metadata !{i32 50}
!106 = metadata !{i32 51}
!107 = metadata !{i32 52}
!108 = metadata !{i32 53}
!109 = metadata !{i32 54}
!110 = metadata !{i32 55}
!111 = metadata !{i32 56}
!112 = metadata !{i32 57}
!113 = metadata !{i32 58}
!114 = metadata !{i32 59}
!115 = metadata !{i32 60}
!116 = metadata !{i32 721152, metadata !117, metadata !"t0", metadata !6, i32 59, metadata !118, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!117 = metadata !{i32 720907, metadata !14, i32 58, i32 1, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!118 = metadata !{i32 720918, null, metadata !"pthread_t", metadata !6, i32 60, i64 0, i64 0, i64 0, i32 0, metadata !119} ; [ DW_TAG_typedef ]
!119 = metadata !{i32 720932, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!120 = metadata !{i32 59, i32 13, metadata !117, null}
!121 = metadata !{i32 61}
!122 = metadata !{i32 721152, metadata !117, metadata !"t1", metadata !6, i32 59, metadata !118, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!123 = metadata !{i32 59, i32 17, metadata !117, null}
!124 = metadata !{i32 62}
!125 = metadata !{i32 721152, metadata !117, metadata !"t2", metadata !6, i32 59, metadata !118, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!126 = metadata !{i32 59, i32 21, metadata !117, null}
!127 = metadata !{i32 63}
!128 = metadata !{i32 721152, metadata !117, metadata !"t3", metadata !6, i32 59, metadata !118, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!129 = metadata !{i32 59, i32 25, metadata !117, null}
!130 = metadata !{i32 64}
!131 = metadata !{i32 721152, metadata !117, metadata !"cond0", metadata !6, i32 60, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!132 = metadata !{i32 60, i32 12, metadata !117, null}
!133 = metadata !{i32 65}
!134 = metadata !{i32 721152, metadata !117, metadata !"cond1", metadata !6, i32 60, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!135 = metadata !{i32 60, i32 19, metadata !117, null}
!136 = metadata !{i32 66}
!137 = metadata !{i32 721152, metadata !117, metadata !"cond2", metadata !6, i32 60, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!138 = metadata !{i32 60, i32 26, metadata !117, null}
!139 = metadata !{i32 67}
!140 = metadata !{i32 721152, metadata !117, metadata !"cond3", metadata !6, i32 60, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!141 = metadata !{i32 60, i32 33, metadata !117, null}
!142 = metadata !{i32 68}
!143 = metadata !{i32 62, i32 3, metadata !117, null}
!144 = metadata !{i32 69}
!145 = metadata !{i32 70}
!146 = metadata !{i32 64, i32 3, metadata !117, null}
!147 = metadata !{i32 71}
!148 = metadata !{i32 65, i32 3, metadata !117, null}
!149 = metadata !{i32 72}
!150 = metadata !{i32 66, i32 3, metadata !117, null}
!151 = metadata !{i32 73}
!152 = metadata !{i32 68, i32 3, metadata !117, null}
!153 = metadata !{i32 74}
!154 = metadata !{i32 75}
!155 = metadata !{i32 76}
!156 = metadata !{i32 69, i32 3, metadata !117, null}
!157 = metadata !{i32 77}
!158 = metadata !{i32 78}
!159 = metadata !{i32 79}
!160 = metadata !{i32 70, i32 3, metadata !117, null}
!161 = metadata !{i32 80}
!162 = metadata !{i32 81}
!163 = metadata !{i32 82}
!164 = metadata !{i32 73, i32 3, metadata !117, null}
!165 = metadata !{i32 83}
!166 = metadata !{i32 84}
!167 = metadata !{i32 85}
!168 = metadata !{i32 86}
!169 = metadata !{i32 87}
!170 = metadata !{i32 88}
!171 = metadata !{i32 74, i32 5, metadata !172, null}
!172 = metadata !{i32 720907, metadata !117, i32 73, i32 25, metadata !6, i32 4} ; [ DW_TAG_lexical_block ]
!173 = metadata !{i32 89}
!174 = metadata !{i32 75, i32 5, metadata !172, null}
!175 = metadata !{i32 90}
!176 = metadata !{i32 76, i32 3, metadata !172, null}
!177 = metadata !{i32 91}
!178 = metadata !{i32 78, i32 3, metadata !117, null}
!179 = metadata !{i32 92}
