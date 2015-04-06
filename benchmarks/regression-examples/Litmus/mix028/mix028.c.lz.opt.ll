; ModuleID = '/home/naling/src/examples/tso/regression-examples/mix028/mix028.c.lz.opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%union.pthread_attr_t = type { i32, [32 x i8] }

@z = common global i32 0, align 4
@x = common global i32 0, align 4
@y = common global i32 0, align 4
@.str = private unnamed_addr constant [31 x i8] c"\0A %%%% (EAX2=%d, EBX2=%d) %%%%\00", align 1
@.str1 = private unnamed_addr constant [37 x i8] c"\0A@@@CLAP: There is a SC violation! \0A\00", align 1
@.str2 = private unnamed_addr constant [30 x i8] c"\1B[1;31m SC Violation!!! \1B[0m\0A\00", align 1
@a = common global i32 0, align 4

define i8* @P1(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !25
  %EAX = alloca i32, align 4, !clap !26
  %EBX = alloca i32, align 4, !clap !27
  store i8* %arg, i8** %arg.addr, align 4, !clap !28
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !29), !dbg !30, !clap !31
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !32), !dbg !34, !clap !35
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !36), !dbg !37, !clap !38
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @z, i32 1, i32 0, i32 32, i32 8)
  store i32 1, i32* @z, align 4, !dbg !39, !clap !40
  call void (i32, ...)* @clap_store_post(i32 5, i32* @z, i32 1, i32 0, i32 32, i32 8)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 9)
  store i32 1, i32* @x, align 4, !dbg !41, !clap !42
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 9)
  ret i8* inttoptr (i32 1 to i8*), !dbg !43, !clap !44
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

define i8* @P0(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !45
  %EAX = alloca i32, align 4, !clap !46
  %EBX = alloca i32, align 4, !clap !47
  store i8* %arg, i8** %arg.addr, align 4, !clap !48
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !49), !dbg !50, !clap !51
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !52), !dbg !54, !clap !55
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !56), !dbg !57, !clap !58
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 2, i32 0, i32 32, i32 18)
  store i32 2, i32* @x, align 4, !dbg !59, !clap !60
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 2, i32 0, i32 32, i32 18)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 19)
  store i32 1, i32* @y, align 4, !dbg !61, !clap !62
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 19)
  ret i8* inttoptr (i32 1 to i8*), !dbg !63, !clap !64
}

define i8* @P2(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !65
  %EAX = alloca i32, align 4, !clap !66
  %EBX = alloca i32, align 4, !clap !67
  store i8* %arg, i8** %arg.addr, align 4, !clap !68
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !69), !dbg !70, !clap !71
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !72), !dbg !74, !clap !75
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !76), !dbg !77, !clap !78
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 2, i32 0, i32 32, i32 28)
  store i32 2, i32* @y, align 4, !dbg !79, !clap !80
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 2, i32 0, i32 32, i32 28)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 29)
  %tmp = load i32* @y, align 4, !dbg !81, !clap !82
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 29)
  store i32 %tmp, i32* %EAX, align 4, !dbg !81, !clap !83
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @z, i32 0, i32 32, i32 31)
  %tmp1 = load i32* @z, align 4, !dbg !84, !clap !85
  call void (i32, ...)* @clap_load_post(i32 4, i32* @z, i32 0, i32 32, i32 31)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !84, !clap !86
  %tmp2 = load i32* %EAX, align 4, !dbg !87, !clap !88
  %tmp3 = load i32* %EBX, align 4, !dbg !87, !clap !89
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([31 x i8]* @.str, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !87, !clap !90
  %tmp4 = load i32* %EAX, align 4, !dbg !91, !clap !92
  %cmp = icmp eq i32 %tmp4, 2, !dbg !91, !clap !93
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !91, !clap !94

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !91, !clap !95
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !91, !clap !96
  br label %land.end, !clap !97

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !98
  %land.ext = zext i1 %tmp6 to i32, !clap !99
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !100
  ret i8* %tmp7, !dbg !101, !clap !102
}

declare i32 @printf(i8*, ...)

define i32 @main() nounwind {
entry:
  %retval = alloca i32, align 4, !clap !103
  %t0 = alloca i32, align 4, !clap !104
  %t1 = alloca i32, align 4, !clap !105
  %t2 = alloca i32, align 4, !clap !106
  %t3 = alloca i32, align 4, !clap !107
  %cond0 = alloca i32, align 4, !clap !108
  %cond1 = alloca i32, align 4, !clap !109
  %cond2 = alloca i32, align 4, !clap !110
  %cond3 = alloca i32, align 4, !clap !111
  store i32 0, i32* %retval, !clap !112
  call void @llvm.dbg.declare(metadata !{i32* %t0}, metadata !113), !dbg !117, !clap !118
  call void @llvm.dbg.declare(metadata !{i32* %t1}, metadata !119), !dbg !120, !clap !121
  call void @llvm.dbg.declare(metadata !{i32* %t2}, metadata !122), !dbg !123, !clap !124
  call void @llvm.dbg.declare(metadata !{i32* %t3}, metadata !125), !dbg !126, !clap !127
  call void @llvm.dbg.declare(metadata !{i32* %cond0}, metadata !128), !dbg !129, !clap !130
  call void @llvm.dbg.declare(metadata !{i32* %cond1}, metadata !131), !dbg !132, !clap !133
  call void @llvm.dbg.declare(metadata !{i32* %cond2}, metadata !134), !dbg !135, !clap !136
  call void @llvm.dbg.declare(metadata !{i32* %cond3}, metadata !137), !dbg !138, !clap !139
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @z, i32 0, i32 0, i32 32, i32 64)
  store i32 0, i32* @z, align 4, !dbg !140, !clap !141
  call void (i32, ...)* @clap_store_post(i32 5, i32* @z, i32 0, i32 0, i32 32, i32 64)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 0, i32 0, i32 32, i32 65)
  store i32 0, i32* @y, align 4, !dbg !140, !clap !142
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 0, i32 0, i32 32, i32 65)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 0, i32 0, i32 32, i32 66)
  store i32 0, i32* @x, align 4, !dbg !140, !clap !143
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 0, i32 0, i32 32, i32 66)
  %call = call i32 @clap_thread_create(i32* %t0, %union.pthread_attr_t* null, i8* (i8*)* @P0, i8* null) nounwind, !dbg !144, !clap !145
  %call1 = call i32 @clap_thread_create(i32* %t1, %union.pthread_attr_t* null, i8* (i8*)* @P1, i8* null) nounwind, !dbg !146, !clap !147
  %call2 = call i32 @clap_thread_create(i32* %t2, %union.pthread_attr_t* null, i8* (i8*)* @P2, i8* null) nounwind, !dbg !148, !clap !149
  %tmp = load i32* %t0, align 4, !dbg !150, !clap !151
  %tmp1 = bitcast i32* %cond0 to i8**, !dbg !150, !clap !152
  %call3 = call i32 @clap_thread_join(i32 %tmp, i8** %tmp1), !dbg !150, !clap !153
  %tmp2 = load i32* %t1, align 4, !dbg !154, !clap !155
  %tmp3 = bitcast i32* %cond1 to i8**, !dbg !154, !clap !156
  %call4 = call i32 @clap_thread_join(i32 %tmp2, i8** %tmp3), !dbg !154, !clap !157
  %tmp4 = load i32* %t2, align 4, !dbg !158, !clap !159
  %tmp5 = bitcast i32* %cond2 to i8**, !dbg !158, !clap !160
  %call5 = call i32 @clap_thread_join(i32 %tmp4, i8** %tmp5), !dbg !158, !clap !161
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 79)
  %tmp6 = load i32* @x, align 4, !dbg !162, !clap !163
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 79)
  %cmp = icmp eq i32 %tmp6, 2, !dbg !162, !clap !164
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !162, !clap !165

land.lhs.true:                                    ; preds = %entry
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 82)
  %tmp7 = load i32* @y, align 4, !dbg !162, !clap !166
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 82)
  %cmp6 = icmp eq i32 %tmp7, 2, !dbg !162, !clap !167
  br i1 %cmp6, label %land.lhs.true7, label %if.end, !dbg !162, !clap !168

land.lhs.true7:                                   ; preds = %land.lhs.true
  %tmp8 = load i32* %cond2, align 4, !dbg !162, !clap !169
  %tobool = icmp ne i32 %tmp8, 0, !dbg !162, !clap !170
  br i1 %tobool, label %if.then, label %if.end, !dbg !162, !clap !171

if.then:                                          ; preds = %land.lhs.true7
  %call8 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([37 x i8]* @.str1, i32 0, i32 0)), !dbg !172, !clap !174
  %call9 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([30 x i8]* @.str2, i32 0, i32 0)), !dbg !175, !clap !176
  br label %if.end, !dbg !177, !clap !178

if.end:                                           ; preds = %if.then, %land.lhs.true7, %land.lhs.true, %entry
  ret i32 0, !dbg !179, !clap !180
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

!0 = metadata !{i32 720913, i32 0, i32 12, metadata !"/home/naling/src/examples/tso/regression-examples/mix028/mix028.c", metadata !"/home/naling/src/inspect-0.3", metadata !"clang version 3.0 (tags/RELEASE_30/final)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !18} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !12, metadata !13, metadata !14}
!5 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P1", metadata !"P1", metadata !"", metadata !6, i32 32, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P1, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 720937, metadata !"/home/naling/src/examples/tso/regression-examples/mix028/mix028.c", metadata !"/home/naling/src/inspect-0.3", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{metadata !9}
!9 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ]
!10 = metadata !{metadata !11}
!11 = metadata !{i32 720932}                      ; [ DW_TAG_base_type ]
!12 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P0", metadata !"P0", metadata !"", metadata !6, i32 40, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P0, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!13 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P2", metadata !"P2", metadata !"", metadata !6, i32 48, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P2, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!14 = metadata !{i32 720942, i32 0, metadata !6, metadata !"main", metadata !"main", metadata !"", metadata !6, i32 58, metadata !15, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i32 ()* @main, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!15 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !16, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!16 = metadata !{metadata !17}
!17 = metadata !{i32 720932, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!18 = metadata !{metadata !19}
!19 = metadata !{metadata !20, metadata !22, metadata !23, metadata !24}
!20 = metadata !{i32 720948, i32 0, null, metadata !"a", metadata !"a", metadata !"", metadata !6, i32 29, metadata !21, i32 0, i32 1, i32* @a} ; [ DW_TAG_variable ]
!21 = metadata !{i32 720932, null, metadata !"long int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!22 = metadata !{i32 720948, i32 0, null, metadata !"x", metadata !"x", metadata !"", metadata !6, i32 29, metadata !21, i32 0, i32 1, i32* @x} ; [ DW_TAG_variable ]
!23 = metadata !{i32 720948, i32 0, null, metadata !"y", metadata !"y", metadata !"", metadata !6, i32 29, metadata !21, i32 0, i32 1, i32* @y} ; [ DW_TAG_variable ]
!24 = metadata !{i32 720948, i32 0, null, metadata !"z", metadata !"z", metadata !"", metadata !6, i32 29, metadata !21, i32 0, i32 1, i32* @z} ; [ DW_TAG_variable ]
!25 = metadata !{i32 1}
!26 = metadata !{i32 2}
!27 = metadata !{i32 3}
!28 = metadata !{i32 4}
!29 = metadata !{i32 721153, metadata !5, metadata !"arg", metadata !6, i32 16777247, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!30 = metadata !{i32 31, i32 16, metadata !5, null}
!31 = metadata !{i32 5}
!32 = metadata !{i32 721152, metadata !33, metadata !"EAX", metadata !6, i32 33, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!33 = metadata !{i32 720907, metadata !5, i32 32, i32 1, metadata !6, i32 0} ; [ DW_TAG_lexical_block ]
!34 = metadata !{i32 33, i32 12, metadata !33, null}
!35 = metadata !{i32 6}
!36 = metadata !{i32 721152, metadata !33, metadata !"EBX", metadata !6, i32 33, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!37 = metadata !{i32 33, i32 17, metadata !33, null}
!38 = metadata !{i32 7}
!39 = metadata !{i32 34, i32 3, metadata !33, null}
!40 = metadata !{i32 8}
!41 = metadata !{i32 35, i32 3, metadata !33, null}
!42 = metadata !{i32 9}
!43 = metadata !{i32 36, i32 3, metadata !33, null}
!44 = metadata !{i32 10}
!45 = metadata !{i32 11}
!46 = metadata !{i32 12}
!47 = metadata !{i32 13}
!48 = metadata !{i32 14}
!49 = metadata !{i32 721153, metadata !12, metadata !"arg", metadata !6, i32 16777255, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!50 = metadata !{i32 39, i32 16, metadata !12, null}
!51 = metadata !{i32 15}
!52 = metadata !{i32 721152, metadata !53, metadata !"EAX", metadata !6, i32 41, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!53 = metadata !{i32 720907, metadata !12, i32 40, i32 1, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!54 = metadata !{i32 41, i32 12, metadata !53, null}
!55 = metadata !{i32 16}
!56 = metadata !{i32 721152, metadata !53, metadata !"EBX", metadata !6, i32 41, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!57 = metadata !{i32 41, i32 17, metadata !53, null}
!58 = metadata !{i32 17}
!59 = metadata !{i32 42, i32 3, metadata !53, null}
!60 = metadata !{i32 18}
!61 = metadata !{i32 43, i32 3, metadata !53, null}
!62 = metadata !{i32 19}
!63 = metadata !{i32 44, i32 3, metadata !53, null}
!64 = metadata !{i32 20}
!65 = metadata !{i32 21}
!66 = metadata !{i32 22}
!67 = metadata !{i32 23}
!68 = metadata !{i32 24}
!69 = metadata !{i32 721153, metadata !13, metadata !"arg", metadata !6, i32 16777263, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!70 = metadata !{i32 47, i32 16, metadata !13, null}
!71 = metadata !{i32 25}
!72 = metadata !{i32 721152, metadata !73, metadata !"EAX", metadata !6, i32 49, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!73 = metadata !{i32 720907, metadata !13, i32 48, i32 1, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!74 = metadata !{i32 49, i32 12, metadata !73, null}
!75 = metadata !{i32 26}
!76 = metadata !{i32 721152, metadata !73, metadata !"EBX", metadata !6, i32 49, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!77 = metadata !{i32 49, i32 17, metadata !73, null}
!78 = metadata !{i32 27}
!79 = metadata !{i32 50, i32 3, metadata !73, null}
!80 = metadata !{i32 28}
!81 = metadata !{i32 51, i32 3, metadata !73, null}
!82 = metadata !{i32 29}
!83 = metadata !{i32 30}
!84 = metadata !{i32 52, i32 3, metadata !73, null}
!85 = metadata !{i32 31}
!86 = metadata !{i32 32}
!87 = metadata !{i32 53, i32 3, metadata !73, null}
!88 = metadata !{i32 33}
!89 = metadata !{i32 34}
!90 = metadata !{i32 35}
!91 = metadata !{i32 54, i32 3, metadata !73, null}
!92 = metadata !{i32 36}
!93 = metadata !{i32 37}
!94 = metadata !{i32 38}
!95 = metadata !{i32 39}
!96 = metadata !{i32 40}
!97 = metadata !{i32 41}
!98 = metadata !{i32 42}
!99 = metadata !{i32 43}
!100 = metadata !{i32 44}
!101 = metadata !{i32 55, i32 1, metadata !13, null}
!102 = metadata !{i32 45}
!103 = metadata !{i32 46}
!104 = metadata !{i32 47}
!105 = metadata !{i32 48}
!106 = metadata !{i32 49}
!107 = metadata !{i32 50}
!108 = metadata !{i32 51}
!109 = metadata !{i32 52}
!110 = metadata !{i32 53}
!111 = metadata !{i32 54}
!112 = metadata !{i32 55}
!113 = metadata !{i32 721152, metadata !114, metadata !"t0", metadata !6, i32 59, metadata !115, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!114 = metadata !{i32 720907, metadata !14, i32 58, i32 1, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!115 = metadata !{i32 720918, null, metadata !"pthread_t", metadata !6, i32 60, i64 0, i64 0, i64 0, i32 0, metadata !116} ; [ DW_TAG_typedef ]
!116 = metadata !{i32 720932, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!117 = metadata !{i32 59, i32 13, metadata !114, null}
!118 = metadata !{i32 56}
!119 = metadata !{i32 721152, metadata !114, metadata !"t1", metadata !6, i32 59, metadata !115, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!120 = metadata !{i32 59, i32 17, metadata !114, null}
!121 = metadata !{i32 57}
!122 = metadata !{i32 721152, metadata !114, metadata !"t2", metadata !6, i32 59, metadata !115, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!123 = metadata !{i32 59, i32 21, metadata !114, null}
!124 = metadata !{i32 58}
!125 = metadata !{i32 721152, metadata !114, metadata !"t3", metadata !6, i32 59, metadata !115, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!126 = metadata !{i32 59, i32 25, metadata !114, null}
!127 = metadata !{i32 59}
!128 = metadata !{i32 721152, metadata !114, metadata !"cond0", metadata !6, i32 60, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!129 = metadata !{i32 60, i32 12, metadata !114, null}
!130 = metadata !{i32 60}
!131 = metadata !{i32 721152, metadata !114, metadata !"cond1", metadata !6, i32 60, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!132 = metadata !{i32 60, i32 19, metadata !114, null}
!133 = metadata !{i32 61}
!134 = metadata !{i32 721152, metadata !114, metadata !"cond2", metadata !6, i32 60, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!135 = metadata !{i32 60, i32 26, metadata !114, null}
!136 = metadata !{i32 62}
!137 = metadata !{i32 721152, metadata !114, metadata !"cond3", metadata !6, i32 60, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!138 = metadata !{i32 60, i32 33, metadata !114, null}
!139 = metadata !{i32 63}
!140 = metadata !{i32 61, i32 3, metadata !114, null}
!141 = metadata !{i32 64}
!142 = metadata !{i32 65}
!143 = metadata !{i32 66}
!144 = metadata !{i32 63, i32 3, metadata !114, null}
!145 = metadata !{i32 67}
!146 = metadata !{i32 64, i32 3, metadata !114, null}
!147 = metadata !{i32 68}
!148 = metadata !{i32 65, i32 3, metadata !114, null}
!149 = metadata !{i32 69}
!150 = metadata !{i32 67, i32 3, metadata !114, null}
!151 = metadata !{i32 70}
!152 = metadata !{i32 71}
!153 = metadata !{i32 72}
!154 = metadata !{i32 68, i32 3, metadata !114, null}
!155 = metadata !{i32 73}
!156 = metadata !{i32 74}
!157 = metadata !{i32 75}
!158 = metadata !{i32 69, i32 3, metadata !114, null}
!159 = metadata !{i32 76}
!160 = metadata !{i32 77}
!161 = metadata !{i32 78}
!162 = metadata !{i32 72, i32 3, metadata !114, null}
!163 = metadata !{i32 79}
!164 = metadata !{i32 80}
!165 = metadata !{i32 81}
!166 = metadata !{i32 82}
!167 = metadata !{i32 83}
!168 = metadata !{i32 84}
!169 = metadata !{i32 85}
!170 = metadata !{i32 86}
!171 = metadata !{i32 87}
!172 = metadata !{i32 73, i32 5, metadata !173, null}
!173 = metadata !{i32 720907, metadata !114, i32 72, i32 32, metadata !6, i32 4} ; [ DW_TAG_lexical_block ]
!174 = metadata !{i32 88}
!175 = metadata !{i32 74, i32 5, metadata !173, null}
!176 = metadata !{i32 89}
!177 = metadata !{i32 75, i32 3, metadata !173, null}
!178 = metadata !{i32 90}
!179 = metadata !{i32 77, i32 3, metadata !114, null}
!180 = metadata !{i32 91}
