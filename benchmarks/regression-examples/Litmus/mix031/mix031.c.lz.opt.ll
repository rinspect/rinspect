; ModuleID = '/home/naling/src/examples/tso/regression-examples/mix031/mix031.c.lz.opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%union.pthread_attr_t = type { i32, [32 x i8] }

@a = common global i32 0, align 4
@x = common global i32 0, align 4
@y = common global i32 0, align 4
@.str = private unnamed_addr constant [32 x i8] c"\0A %%%% (EAX0=%d, EBX0=%d) %%%%\0A\00", align 1
@z = common global i32 0, align 4
@.str1 = private unnamed_addr constant [32 x i8] c"\0A %%%% (EAX1=%d, EBX1=%d) %%%%\0A\00", align 1
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
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @a, i32 1, i32 0, i32 32, i32 8)
  store i32 1, i32* @a, align 4, !dbg !38, !clap !39
  call void (i32, ...)* @clap_store_post(i32 5, i32* @a, i32 1, i32 0, i32 32, i32 8)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 9)
  store i32 1, i32* @x, align 4, !dbg !40, !clap !41
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 9)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 10)
  %tmp = load i32* @x, align 4, !dbg !42, !clap !43
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 10)
  store i32 %tmp, i32* %EAX, align 4, !dbg !42, !clap !44
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 12)
  %tmp1 = load i32* @y, align 4, !dbg !45, !clap !46
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 12)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !45, !clap !47
  %tmp2 = load i32* %EAX, align 4, !dbg !48, !clap !49
  %tmp3 = load i32* %EBX, align 4, !dbg !48, !clap !50
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([32 x i8]* @.str, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !48, !clap !51
  %tmp4 = load i32* %EAX, align 4, !dbg !52, !clap !53
  %cmp = icmp eq i32 %tmp4, 1, !dbg !52, !clap !54
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !52, !clap !55

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !52, !clap !56
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !52, !clap !57
  br label %land.end, !clap !58

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !59
  %land.ext = zext i1 %tmp6 to i32, !clap !60
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !61
  ret i8* %tmp7, !dbg !62, !clap !63
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare i32 @printf(i8*, ...)

define i8* @P1(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !64
  %EAX = alloca i32, align 4, !clap !65
  %EBX = alloca i32, align 4, !clap !66
  store i8* %arg, i8** %arg.addr, align 4, !clap !67
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !68), !dbg !69, !clap !70
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !71), !dbg !73, !clap !74
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !75), !dbg !76, !clap !77
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 34)
  store i32 1, i32* @y, align 4, !dbg !78, !clap !79
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 34)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @z, i32 1, i32 0, i32 32, i32 35)
  store i32 1, i32* @z, align 4, !dbg !80, !clap !81
  call void (i32, ...)* @clap_store_post(i32 5, i32* @z, i32 1, i32 0, i32 32, i32 35)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @z, i32 0, i32 32, i32 36)
  %tmp = load i32* @z, align 4, !dbg !82, !clap !83
  call void (i32, ...)* @clap_load_post(i32 4, i32* @z, i32 0, i32 32, i32 36)
  store i32 %tmp, i32* %EAX, align 4, !dbg !82, !clap !84
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @a, i32 0, i32 32, i32 38)
  %tmp1 = load i32* @a, align 4, !dbg !85, !clap !86
  call void (i32, ...)* @clap_load_post(i32 4, i32* @a, i32 0, i32 32, i32 38)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !85, !clap !87
  %tmp2 = load i32* %EAX, align 4, !dbg !88, !clap !89
  %tmp3 = load i32* %EBX, align 4, !dbg !88, !clap !90
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([32 x i8]* @.str1, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !88, !clap !91
  %tmp4 = load i32* %EAX, align 4, !dbg !92, !clap !93
  %cmp = icmp eq i32 %tmp4, 1, !dbg !92, !clap !94
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !92, !clap !95

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !92, !clap !96
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !92, !clap !97
  br label %land.end, !clap !98

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !99
  %land.ext = zext i1 %tmp6 to i32, !clap !100
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !101
  ret i8* %tmp7, !dbg !102, !clap !103
}

define i32 @main() nounwind {
entry:
  %retval = alloca i32, align 4, !clap !104
  %t0 = alloca i32, align 4, !clap !105
  %t1 = alloca i32, align 4, !clap !106
  %t2 = alloca i32, align 4, !clap !107
  %cond0 = alloca i32, align 4, !clap !108
  %cond1 = alloca i32, align 4, !clap !109
  %cond2 = alloca i32, align 4, !clap !110
  store i32 0, i32* %retval, !clap !111
  call void @llvm.dbg.declare(metadata !{i32* %t0}, metadata !112), !dbg !116, !clap !117
  call void @llvm.dbg.declare(metadata !{i32* %t1}, metadata !118), !dbg !119, !clap !120
  call void @llvm.dbg.declare(metadata !{i32* %t2}, metadata !121), !dbg !122, !clap !123
  call void @llvm.dbg.declare(metadata !{i32* %cond0}, metadata !124), !dbg !125, !clap !126
  call void @llvm.dbg.declare(metadata !{i32* %cond1}, metadata !127), !dbg !128, !clap !129
  call void @llvm.dbg.declare(metadata !{i32* %cond2}, metadata !130), !dbg !131, !clap !132
  %call = call i32 @clap_thread_create(i32* %t0, %union.pthread_attr_t* null, i8* (i8*)* @P0, i8* null) nounwind, !dbg !133, !clap !134
  %call1 = call i32 @clap_thread_create(i32* %t1, %union.pthread_attr_t* null, i8* (i8*)* @P1, i8* null) nounwind, !dbg !135, !clap !136
  %tmp = load i32* %t0, align 4, !dbg !137, !clap !138
  %tmp1 = bitcast i32* %cond0 to i8**, !dbg !137, !clap !139
  %call2 = call i32 @clap_thread_join(i32 %tmp, i8** %tmp1), !dbg !137, !clap !140
  %tmp2 = load i32* %t1, align 4, !dbg !141, !clap !142
  %tmp3 = bitcast i32* %cond1 to i8**, !dbg !141, !clap !143
  %call3 = call i32 @clap_thread_join(i32 %tmp2, i8** %tmp3), !dbg !141, !clap !144
  %tmp4 = load i32* %cond0, align 4, !dbg !145, !clap !146
  %tobool = icmp ne i32 %tmp4, 0, !dbg !145, !clap !147
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !145, !clap !148

land.lhs.true:                                    ; preds = %entry
  %tmp5 = load i32* %cond1, align 4, !dbg !145, !clap !149
  %tobool4 = icmp ne i32 %tmp5, 0, !dbg !145, !clap !150
  br i1 %tobool4, label %if.then, label %if.end, !dbg !145, !clap !151

if.then:                                          ; preds = %land.lhs.true
  %call5 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([37 x i8]* @.str2, i32 0, i32 0)), !dbg !152, !clap !154
  %call6 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([30 x i8]* @.str3, i32 0, i32 0)), !dbg !155, !clap !156
  br label %if.end, !dbg !157, !clap !158

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  ret i32 0, !dbg !159, !clap !160
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

!0 = metadata !{i32 720913, i32 0, i32 12, metadata !"/home/naling/src/examples/tso/regression-examples/mix031/mix031.c", metadata !"/home/naling/src/inspect-0.3", metadata !"clang version 3.0 (tags/RELEASE_30/final)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !17} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !12, metadata !13}
!5 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P0", metadata !"P0", metadata !"", metadata !6, i32 33, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P0, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 720937, metadata !"/home/naling/src/examples/tso/regression-examples/mix031/mix031.c", metadata !"/home/naling/src/inspect-0.3", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{metadata !9}
!9 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ]
!10 = metadata !{metadata !11}
!11 = metadata !{i32 720932}                      ; [ DW_TAG_base_type ]
!12 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P1", metadata !"P1", metadata !"", metadata !6, i32 44, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P1, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!13 = metadata !{i32 720942, i32 0, metadata !6, metadata !"main", metadata !"main", metadata !"", metadata !6, i32 55, metadata !14, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i32 ()* @main, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!14 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !15, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!15 = metadata !{metadata !16}
!16 = metadata !{i32 720932, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!17 = metadata !{metadata !18}
!18 = metadata !{metadata !19, metadata !21, metadata !22, metadata !23}
!19 = metadata !{i32 720948, i32 0, null, metadata !"a", metadata !"a", metadata !"", metadata !6, i32 30, metadata !20, i32 0, i32 1, i32* @a} ; [ DW_TAG_variable ]
!20 = metadata !{i32 720932, null, metadata !"long int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!21 = metadata !{i32 720948, i32 0, null, metadata !"x", metadata !"x", metadata !"", metadata !6, i32 30, metadata !20, i32 0, i32 1, i32* @x} ; [ DW_TAG_variable ]
!22 = metadata !{i32 720948, i32 0, null, metadata !"y", metadata !"y", metadata !"", metadata !6, i32 30, metadata !20, i32 0, i32 1, i32* @y} ; [ DW_TAG_variable ]
!23 = metadata !{i32 720948, i32 0, null, metadata !"z", metadata !"z", metadata !"", metadata !6, i32 30, metadata !20, i32 0, i32 1, i32* @z} ; [ DW_TAG_variable ]
!24 = metadata !{i32 1}
!25 = metadata !{i32 2}
!26 = metadata !{i32 3}
!27 = metadata !{i32 4}
!28 = metadata !{i32 721153, metadata !5, metadata !"arg", metadata !6, i32 16777248, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!29 = metadata !{i32 32, i32 16, metadata !5, null}
!30 = metadata !{i32 5}
!31 = metadata !{i32 721152, metadata !32, metadata !"EAX", metadata !6, i32 34, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!32 = metadata !{i32 720907, metadata !5, i32 33, i32 1, metadata !6, i32 0} ; [ DW_TAG_lexical_block ]
!33 = metadata !{i32 34, i32 12, metadata !32, null}
!34 = metadata !{i32 6}
!35 = metadata !{i32 721152, metadata !32, metadata !"EBX", metadata !6, i32 34, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!36 = metadata !{i32 34, i32 17, metadata !32, null}
!37 = metadata !{i32 7}
!38 = metadata !{i32 35, i32 3, metadata !32, null}
!39 = metadata !{i32 8}
!40 = metadata !{i32 36, i32 3, metadata !32, null}
!41 = metadata !{i32 9}
!42 = metadata !{i32 37, i32 3, metadata !32, null}
!43 = metadata !{i32 10}
!44 = metadata !{i32 11}
!45 = metadata !{i32 38, i32 3, metadata !32, null}
!46 = metadata !{i32 12}
!47 = metadata !{i32 13}
!48 = metadata !{i32 39, i32 3, metadata !32, null}
!49 = metadata !{i32 14}
!50 = metadata !{i32 15}
!51 = metadata !{i32 16}
!52 = metadata !{i32 40, i32 3, metadata !32, null}
!53 = metadata !{i32 17}
!54 = metadata !{i32 18}
!55 = metadata !{i32 19}
!56 = metadata !{i32 20}
!57 = metadata !{i32 21}
!58 = metadata !{i32 22}
!59 = metadata !{i32 23}
!60 = metadata !{i32 24}
!61 = metadata !{i32 25}
!62 = metadata !{i32 41, i32 1, metadata !5, null}
!63 = metadata !{i32 26}
!64 = metadata !{i32 27}
!65 = metadata !{i32 28}
!66 = metadata !{i32 29}
!67 = metadata !{i32 30}
!68 = metadata !{i32 721153, metadata !12, metadata !"arg", metadata !6, i32 16777259, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!69 = metadata !{i32 43, i32 16, metadata !12, null}
!70 = metadata !{i32 31}
!71 = metadata !{i32 721152, metadata !72, metadata !"EAX", metadata !6, i32 45, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!72 = metadata !{i32 720907, metadata !12, i32 44, i32 1, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!73 = metadata !{i32 45, i32 12, metadata !72, null}
!74 = metadata !{i32 32}
!75 = metadata !{i32 721152, metadata !72, metadata !"EBX", metadata !6, i32 45, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!76 = metadata !{i32 45, i32 17, metadata !72, null}
!77 = metadata !{i32 33}
!78 = metadata !{i32 46, i32 3, metadata !72, null}
!79 = metadata !{i32 34}
!80 = metadata !{i32 47, i32 3, metadata !72, null}
!81 = metadata !{i32 35}
!82 = metadata !{i32 48, i32 3, metadata !72, null}
!83 = metadata !{i32 36}
!84 = metadata !{i32 37}
!85 = metadata !{i32 49, i32 3, metadata !72, null}
!86 = metadata !{i32 38}
!87 = metadata !{i32 39}
!88 = metadata !{i32 50, i32 3, metadata !72, null}
!89 = metadata !{i32 40}
!90 = metadata !{i32 41}
!91 = metadata !{i32 42}
!92 = metadata !{i32 51, i32 3, metadata !72, null}
!93 = metadata !{i32 43}
!94 = metadata !{i32 44}
!95 = metadata !{i32 45}
!96 = metadata !{i32 46}
!97 = metadata !{i32 47}
!98 = metadata !{i32 48}
!99 = metadata !{i32 49}
!100 = metadata !{i32 50}
!101 = metadata !{i32 51}
!102 = metadata !{i32 52, i32 1, metadata !12, null}
!103 = metadata !{i32 52}
!104 = metadata !{i32 53}
!105 = metadata !{i32 54}
!106 = metadata !{i32 55}
!107 = metadata !{i32 56}
!108 = metadata !{i32 57}
!109 = metadata !{i32 58}
!110 = metadata !{i32 59}
!111 = metadata !{i32 60}
!112 = metadata !{i32 721152, metadata !113, metadata !"t0", metadata !6, i32 56, metadata !114, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!113 = metadata !{i32 720907, metadata !13, i32 55, i32 1, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!114 = metadata !{i32 720918, null, metadata !"pthread_t", metadata !6, i32 60, i64 0, i64 0, i64 0, i32 0, metadata !115} ; [ DW_TAG_typedef ]
!115 = metadata !{i32 720932, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!116 = metadata !{i32 56, i32 13, metadata !113, null}
!117 = metadata !{i32 61}
!118 = metadata !{i32 721152, metadata !113, metadata !"t1", metadata !6, i32 56, metadata !114, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!119 = metadata !{i32 56, i32 17, metadata !113, null}
!120 = metadata !{i32 62}
!121 = metadata !{i32 721152, metadata !113, metadata !"t2", metadata !6, i32 56, metadata !114, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!122 = metadata !{i32 56, i32 21, metadata !113, null}
!123 = metadata !{i32 63}
!124 = metadata !{i32 721152, metadata !113, metadata !"cond0", metadata !6, i32 57, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!125 = metadata !{i32 57, i32 12, metadata !113, null}
!126 = metadata !{i32 64}
!127 = metadata !{i32 721152, metadata !113, metadata !"cond1", metadata !6, i32 57, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!128 = metadata !{i32 57, i32 19, metadata !113, null}
!129 = metadata !{i32 65}
!130 = metadata !{i32 721152, metadata !113, metadata !"cond2", metadata !6, i32 57, metadata !20, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!131 = metadata !{i32 57, i32 26, metadata !113, null}
!132 = metadata !{i32 66}
!133 = metadata !{i32 59, i32 3, metadata !113, null}
!134 = metadata !{i32 67}
!135 = metadata !{i32 60, i32 3, metadata !113, null}
!136 = metadata !{i32 68}
!137 = metadata !{i32 62, i32 3, metadata !113, null}
!138 = metadata !{i32 69}
!139 = metadata !{i32 70}
!140 = metadata !{i32 71}
!141 = metadata !{i32 63, i32 3, metadata !113, null}
!142 = metadata !{i32 72}
!143 = metadata !{i32 73}
!144 = metadata !{i32 74}
!145 = metadata !{i32 66, i32 3, metadata !113, null}
!146 = metadata !{i32 75}
!147 = metadata !{i32 76}
!148 = metadata !{i32 77}
!149 = metadata !{i32 78}
!150 = metadata !{i32 79}
!151 = metadata !{i32 80}
!152 = metadata !{i32 67, i32 5, metadata !153, null}
!153 = metadata !{i32 720907, metadata !113, i32 66, i32 24, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!154 = metadata !{i32 81}
!155 = metadata !{i32 68, i32 5, metadata !153, null}
!156 = metadata !{i32 82}
!157 = metadata !{i32 69, i32 3, metadata !153, null}
!158 = metadata !{i32 83}
!159 = metadata !{i32 71, i32 3, metadata !113, null}
!160 = metadata !{i32 84}
