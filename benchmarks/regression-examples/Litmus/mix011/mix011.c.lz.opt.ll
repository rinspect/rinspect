; ModuleID = '/home/naling/src/examples/tso/regression-examples/mix011/mix011.c.lz.opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%union.pthread_attr_t = type { i32, [32 x i8] }

@a = common global i32 0, align 4
@x = common global i32 0, align 4
@y = common global i32 0, align 4
@z = common global i32 0, align 4
@.str = private unnamed_addr constant [32 x i8] c"\0A %%%% (EAX1=%d, EBX1=%d) %%%%\0A\00", align 1
@.str1 = private unnamed_addr constant [32 x i8] c"\0A %%%% (EAX2=%d, EBX2=%d) %%%%\0A\00", align 1
@.str2 = private unnamed_addr constant [37 x i8] c"\0A@@@CLAP: There is a SC violation! \0A\00", align 1
@.str3 = private unnamed_addr constant [30 x i8] c"\1B[1;31m SC Violation!!! \1B[0m\0A\00", align 1

define i8* @P0(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !25
  %EAX = alloca i32, align 4, !clap !26
  %EBX = alloca i32, align 4, !clap !27
  store i8* %arg, i8** %arg.addr, align 4, !clap !28
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !29), !dbg !30, !clap !31
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !32), !dbg !34, !clap !35
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !36), !dbg !37, !clap !38
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @a, i32 1, i32 0, i32 32, i32 8)
  store i32 1, i32* @a, align 4, !dbg !39, !clap !40
  call void (i32, ...)* @clap_store_post(i32 5, i32* @a, i32 1, i32 0, i32 32, i32 8)
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 9)
  store i32 1, i32* @x, align 4, !dbg !41, !clap !42
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 9)
  ret i8* inttoptr (i32 1 to i8*), !dbg !43, !clap !44
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

define i8* @P1(i8* %arg) nounwind {
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
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 20)
  %tmp = load i32* @y, align 4, !dbg !63, !clap !64
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 20)
  store i32 %tmp, i32* %EAX, align 4, !dbg !63, !clap !65
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @z, i32 0, i32 32, i32 22)
  %tmp1 = load i32* @z, align 4, !dbg !66, !clap !67
  call void (i32, ...)* @clap_load_post(i32 4, i32* @z, i32 0, i32 32, i32 22)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !66, !clap !68
  %tmp2 = load i32* %EAX, align 4, !dbg !69, !clap !70
  %tmp3 = load i32* %EBX, align 4, !dbg !69, !clap !71
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([32 x i8]* @.str, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !69, !clap !72
  %tmp4 = load i32* %EAX, align 4, !dbg !73, !clap !74
  %cmp = icmp eq i32 %tmp4, 1, !dbg !73, !clap !75
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !73, !clap !76

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !73, !clap !77
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !73, !clap !78
  br label %land.end, !clap !79

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !80
  %land.ext = zext i1 %tmp6 to i32, !clap !81
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !82
  ret i8* %tmp7, !dbg !83, !clap !84
}

declare i32 @printf(i8*, ...)

define i8* @P2(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !85
  %EAX = alloca i32, align 4, !clap !86
  %EBX = alloca i32, align 4, !clap !87
  store i8* %arg, i8** %arg.addr, align 4, !clap !88
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !89), !dbg !90, !clap !91
  call void @llvm.dbg.declare(metadata !{i32* %EAX}, metadata !92), !dbg !94, !clap !95
  call void @llvm.dbg.declare(metadata !{i32* %EBX}, metadata !96), !dbg !97, !clap !98
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @z, i32 1, i32 0, i32 32, i32 44)
  store i32 1, i32* @z, align 4, !dbg !99, !clap !100
  call void (i32, ...)* @clap_store_post(i32 5, i32* @z, i32 1, i32 0, i32 32, i32 44)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @z, i32 0, i32 32, i32 45)
  %tmp = load i32* @z, align 4, !dbg !101, !clap !102
  call void (i32, ...)* @clap_load_post(i32 4, i32* @z, i32 0, i32 32, i32 45)
  store i32 %tmp, i32* %EAX, align 4, !dbg !101, !clap !103
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @a, i32 0, i32 32, i32 47)
  %tmp1 = load i32* @a, align 4, !dbg !104, !clap !105
  call void (i32, ...)* @clap_load_post(i32 4, i32* @a, i32 0, i32 32, i32 47)
  store i32 %tmp1, i32* %EBX, align 4, !dbg !104, !clap !106
  %tmp2 = load i32* %EAX, align 4, !dbg !107, !clap !108
  %tmp3 = load i32* %EBX, align 4, !dbg !107, !clap !109
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([32 x i8]* @.str1, i32 0, i32 0), i32 %tmp2, i32 %tmp3), !dbg !107, !clap !110
  %tmp4 = load i32* %EAX, align 4, !dbg !111, !clap !112
  %cmp = icmp eq i32 %tmp4, 1, !dbg !111, !clap !113
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !111, !clap !114

land.rhs:                                         ; preds = %entry
  %tmp5 = load i32* %EBX, align 4, !dbg !111, !clap !115
  %cmp1 = icmp eq i32 %tmp5, 0, !dbg !111, !clap !116
  br label %land.end, !clap !117

land.end:                                         ; preds = %land.rhs, %entry
  %tmp6 = phi i1 [ false, %entry ], [ %cmp1, %land.rhs ], !clap !118
  %land.ext = zext i1 %tmp6 to i32, !clap !119
  %tmp7 = inttoptr i32 %land.ext to i8*, !clap !120
  ret i8* %tmp7, !dbg !121, !clap !122
}

define i32 @main() nounwind {
entry:
  %retval = alloca i32, align 4, !clap !123
  %t0 = alloca i32, align 4, !clap !124
  %t1 = alloca i32, align 4, !clap !125
  %t2 = alloca i32, align 4, !clap !126
  %cond0 = alloca i32, align 4, !clap !127
  %cond1 = alloca i32, align 4, !clap !128
  %cond2 = alloca i32, align 4, !clap !129
  store i32 0, i32* %retval, !clap !130
  call void @llvm.dbg.declare(metadata !{i32* %t0}, metadata !131), !dbg !135, !clap !136
  call void @llvm.dbg.declare(metadata !{i32* %t1}, metadata !137), !dbg !138, !clap !139
  call void @llvm.dbg.declare(metadata !{i32* %t2}, metadata !140), !dbg !141, !clap !142
  call void @llvm.dbg.declare(metadata !{i32* %cond0}, metadata !143), !dbg !144, !clap !145
  call void @llvm.dbg.declare(metadata !{i32* %cond1}, metadata !146), !dbg !147, !clap !148
  call void @llvm.dbg.declare(metadata !{i32* %cond2}, metadata !149), !dbg !150, !clap !151
  %call = call i32 @clap_thread_create(i32* %t0, %union.pthread_attr_t* null, i8* (i8*)* @P0, i8* null) nounwind, !dbg !152, !clap !153
  %call1 = call i32 @clap_thread_create(i32* %t1, %union.pthread_attr_t* null, i8* (i8*)* @P1, i8* null) nounwind, !dbg !154, !clap !155
  %call2 = call i32 @clap_thread_create(i32* %t2, %union.pthread_attr_t* null, i8* (i8*)* @P2, i8* null) nounwind, !dbg !156, !clap !157
  %tmp = load i32* %t0, align 4, !dbg !158, !clap !159
  %tmp1 = bitcast i32* %cond0 to i8**, !dbg !158, !clap !160
  %call3 = call i32 @clap_thread_join(i32 %tmp, i8** %tmp1), !dbg !158, !clap !161
  %tmp2 = load i32* %t1, align 4, !dbg !162, !clap !163
  %tmp3 = bitcast i32* %cond1 to i8**, !dbg !162, !clap !164
  %call4 = call i32 @clap_thread_join(i32 %tmp2, i8** %tmp3), !dbg !162, !clap !165
  %tmp4 = load i32* %t2, align 4, !dbg !166, !clap !167
  %tmp5 = bitcast i32* %cond2 to i8**, !dbg !166, !clap !168
  %call5 = call i32 @clap_thread_join(i32 %tmp4, i8** %tmp5), !dbg !166, !clap !169
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 88)
  %tmp6 = load i32* @x, align 4, !dbg !170, !clap !171
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 88)
  %cmp = icmp eq i32 %tmp6, 2, !dbg !170, !clap !172
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !170, !clap !173

land.lhs.true:                                    ; preds = %entry
  %tmp7 = load i32* %cond1, align 4, !dbg !170, !clap !174
  %tobool = icmp ne i32 %tmp7, 0, !dbg !170, !clap !175
  br i1 %tobool, label %land.lhs.true6, label %if.end, !dbg !170, !clap !176

land.lhs.true6:                                   ; preds = %land.lhs.true
  %tmp8 = load i32* %cond2, align 4, !dbg !170, !clap !177
  %tobool7 = icmp ne i32 %tmp8, 0, !dbg !170, !clap !178
  br i1 %tobool7, label %if.then, label %if.end, !dbg !170, !clap !179

if.then:                                          ; preds = %land.lhs.true6
  %call8 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([37 x i8]* @.str2, i32 0, i32 0)), !dbg !180, !clap !182
  %call9 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([30 x i8]* @.str3, i32 0, i32 0)), !dbg !183, !clap !184
  br label %if.end, !dbg !185, !clap !186

if.end:                                           ; preds = %if.then, %land.lhs.true6, %land.lhs.true, %entry
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

!0 = metadata !{i32 720913, i32 0, i32 12, metadata !"/home/naling/src/examples/tso/regression-examples/mix011/mix011.c", metadata !"/home/naling/src/inspect-0.3", metadata !"clang version 3.0 (tags/RELEASE_30/final)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !18} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !12, metadata !13, metadata !14}
!5 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P0", metadata !"P0", metadata !"", metadata !6, i32 33, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P0, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 720937, metadata !"/home/naling/src/examples/tso/regression-examples/mix011/mix011.c", metadata !"/home/naling/src/inspect-0.3", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{metadata !9}
!9 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ]
!10 = metadata !{metadata !11}
!11 = metadata !{i32 720932}                      ; [ DW_TAG_base_type ]
!12 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P1", metadata !"P1", metadata !"", metadata !6, i32 41, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P1, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!13 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P2", metadata !"P2", metadata !"", metadata !6, i32 52, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P2, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!14 = metadata !{i32 720942, i32 0, metadata !6, metadata !"main", metadata !"main", metadata !"", metadata !6, i32 62, metadata !15, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i32 ()* @main, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!15 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !16, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!16 = metadata !{metadata !17}
!17 = metadata !{i32 720932, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!18 = metadata !{metadata !19}
!19 = metadata !{metadata !20, metadata !22, metadata !23, metadata !24}
!20 = metadata !{i32 720948, i32 0, null, metadata !"a", metadata !"a", metadata !"", metadata !6, i32 30, metadata !21, i32 0, i32 1, i32* @a} ; [ DW_TAG_variable ]
!21 = metadata !{i32 720932, null, metadata !"long int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!22 = metadata !{i32 720948, i32 0, null, metadata !"x", metadata !"x", metadata !"", metadata !6, i32 30, metadata !21, i32 0, i32 1, i32* @x} ; [ DW_TAG_variable ]
!23 = metadata !{i32 720948, i32 0, null, metadata !"y", metadata !"y", metadata !"", metadata !6, i32 30, metadata !21, i32 0, i32 1, i32* @y} ; [ DW_TAG_variable ]
!24 = metadata !{i32 720948, i32 0, null, metadata !"z", metadata !"z", metadata !"", metadata !6, i32 30, metadata !21, i32 0, i32 1, i32* @z} ; [ DW_TAG_variable ]
!25 = metadata !{i32 1}
!26 = metadata !{i32 2}
!27 = metadata !{i32 3}
!28 = metadata !{i32 4}
!29 = metadata !{i32 721153, metadata !5, metadata !"arg", metadata !6, i32 16777248, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!30 = metadata !{i32 32, i32 16, metadata !5, null}
!31 = metadata !{i32 5}
!32 = metadata !{i32 721152, metadata !33, metadata !"EAX", metadata !6, i32 34, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!33 = metadata !{i32 720907, metadata !5, i32 33, i32 1, metadata !6, i32 0} ; [ DW_TAG_lexical_block ]
!34 = metadata !{i32 34, i32 12, metadata !33, null}
!35 = metadata !{i32 6}
!36 = metadata !{i32 721152, metadata !33, metadata !"EBX", metadata !6, i32 34, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!37 = metadata !{i32 34, i32 17, metadata !33, null}
!38 = metadata !{i32 7}
!39 = metadata !{i32 35, i32 3, metadata !33, null}
!40 = metadata !{i32 8}
!41 = metadata !{i32 36, i32 3, metadata !33, null}
!42 = metadata !{i32 9}
!43 = metadata !{i32 37, i32 3, metadata !33, null}
!44 = metadata !{i32 10}
!45 = metadata !{i32 11}
!46 = metadata !{i32 12}
!47 = metadata !{i32 13}
!48 = metadata !{i32 14}
!49 = metadata !{i32 721153, metadata !12, metadata !"arg", metadata !6, i32 16777256, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!50 = metadata !{i32 40, i32 16, metadata !12, null}
!51 = metadata !{i32 15}
!52 = metadata !{i32 721152, metadata !53, metadata !"EAX", metadata !6, i32 42, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!53 = metadata !{i32 720907, metadata !12, i32 41, i32 1, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!54 = metadata !{i32 42, i32 12, metadata !53, null}
!55 = metadata !{i32 16}
!56 = metadata !{i32 721152, metadata !53, metadata !"EBX", metadata !6, i32 42, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!57 = metadata !{i32 42, i32 17, metadata !53, null}
!58 = metadata !{i32 17}
!59 = metadata !{i32 43, i32 3, metadata !53, null}
!60 = metadata !{i32 18}
!61 = metadata !{i32 44, i32 3, metadata !53, null}
!62 = metadata !{i32 19}
!63 = metadata !{i32 45, i32 3, metadata !53, null}
!64 = metadata !{i32 20}
!65 = metadata !{i32 21}
!66 = metadata !{i32 46, i32 3, metadata !53, null}
!67 = metadata !{i32 22}
!68 = metadata !{i32 23}
!69 = metadata !{i32 47, i32 3, metadata !53, null}
!70 = metadata !{i32 24}
!71 = metadata !{i32 25}
!72 = metadata !{i32 26}
!73 = metadata !{i32 48, i32 3, metadata !53, null}
!74 = metadata !{i32 27}
!75 = metadata !{i32 28}
!76 = metadata !{i32 29}
!77 = metadata !{i32 30}
!78 = metadata !{i32 31}
!79 = metadata !{i32 32}
!80 = metadata !{i32 33}
!81 = metadata !{i32 34}
!82 = metadata !{i32 35}
!83 = metadata !{i32 49, i32 1, metadata !12, null}
!84 = metadata !{i32 36}
!85 = metadata !{i32 37}
!86 = metadata !{i32 38}
!87 = metadata !{i32 39}
!88 = metadata !{i32 40}
!89 = metadata !{i32 721153, metadata !13, metadata !"arg", metadata !6, i32 16777267, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!90 = metadata !{i32 51, i32 16, metadata !13, null}
!91 = metadata !{i32 41}
!92 = metadata !{i32 721152, metadata !93, metadata !"EAX", metadata !6, i32 53, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!93 = metadata !{i32 720907, metadata !13, i32 52, i32 1, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!94 = metadata !{i32 53, i32 12, metadata !93, null}
!95 = metadata !{i32 42}
!96 = metadata !{i32 721152, metadata !93, metadata !"EBX", metadata !6, i32 53, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!97 = metadata !{i32 53, i32 17, metadata !93, null}
!98 = metadata !{i32 43}
!99 = metadata !{i32 54, i32 3, metadata !93, null}
!100 = metadata !{i32 44}
!101 = metadata !{i32 55, i32 3, metadata !93, null}
!102 = metadata !{i32 45}
!103 = metadata !{i32 46}
!104 = metadata !{i32 56, i32 3, metadata !93, null}
!105 = metadata !{i32 47}
!106 = metadata !{i32 48}
!107 = metadata !{i32 57, i32 3, metadata !93, null}
!108 = metadata !{i32 49}
!109 = metadata !{i32 50}
!110 = metadata !{i32 51}
!111 = metadata !{i32 58, i32 3, metadata !93, null}
!112 = metadata !{i32 52}
!113 = metadata !{i32 53}
!114 = metadata !{i32 54}
!115 = metadata !{i32 55}
!116 = metadata !{i32 56}
!117 = metadata !{i32 57}
!118 = metadata !{i32 58}
!119 = metadata !{i32 59}
!120 = metadata !{i32 60}
!121 = metadata !{i32 59, i32 1, metadata !13, null}
!122 = metadata !{i32 61}
!123 = metadata !{i32 62}
!124 = metadata !{i32 63}
!125 = metadata !{i32 64}
!126 = metadata !{i32 65}
!127 = metadata !{i32 66}
!128 = metadata !{i32 67}
!129 = metadata !{i32 68}
!130 = metadata !{i32 69}
!131 = metadata !{i32 721152, metadata !132, metadata !"t0", metadata !6, i32 63, metadata !133, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!132 = metadata !{i32 720907, metadata !14, i32 62, i32 1, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!133 = metadata !{i32 720918, null, metadata !"pthread_t", metadata !6, i32 60, i64 0, i64 0, i64 0, i32 0, metadata !134} ; [ DW_TAG_typedef ]
!134 = metadata !{i32 720932, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!135 = metadata !{i32 63, i32 13, metadata !132, null}
!136 = metadata !{i32 70}
!137 = metadata !{i32 721152, metadata !132, metadata !"t1", metadata !6, i32 63, metadata !133, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!138 = metadata !{i32 63, i32 17, metadata !132, null}
!139 = metadata !{i32 71}
!140 = metadata !{i32 721152, metadata !132, metadata !"t2", metadata !6, i32 63, metadata !133, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!141 = metadata !{i32 63, i32 21, metadata !132, null}
!142 = metadata !{i32 72}
!143 = metadata !{i32 721152, metadata !132, metadata !"cond0", metadata !6, i32 64, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!144 = metadata !{i32 64, i32 12, metadata !132, null}
!145 = metadata !{i32 73}
!146 = metadata !{i32 721152, metadata !132, metadata !"cond1", metadata !6, i32 64, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!147 = metadata !{i32 64, i32 19, metadata !132, null}
!148 = metadata !{i32 74}
!149 = metadata !{i32 721152, metadata !132, metadata !"cond2", metadata !6, i32 64, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!150 = metadata !{i32 64, i32 26, metadata !132, null}
!151 = metadata !{i32 75}
!152 = metadata !{i32 66, i32 3, metadata !132, null}
!153 = metadata !{i32 76}
!154 = metadata !{i32 67, i32 3, metadata !132, null}
!155 = metadata !{i32 77}
!156 = metadata !{i32 68, i32 3, metadata !132, null}
!157 = metadata !{i32 78}
!158 = metadata !{i32 70, i32 3, metadata !132, null}
!159 = metadata !{i32 79}
!160 = metadata !{i32 80}
!161 = metadata !{i32 81}
!162 = metadata !{i32 71, i32 3, metadata !132, null}
!163 = metadata !{i32 82}
!164 = metadata !{i32 83}
!165 = metadata !{i32 84}
!166 = metadata !{i32 72, i32 3, metadata !132, null}
!167 = metadata !{i32 85}
!168 = metadata !{i32 86}
!169 = metadata !{i32 87}
!170 = metadata !{i32 75, i32 3, metadata !132, null}
!171 = metadata !{i32 88}
!172 = metadata !{i32 89}
!173 = metadata !{i32 90}
!174 = metadata !{i32 91}
!175 = metadata !{i32 92}
!176 = metadata !{i32 93}
!177 = metadata !{i32 94}
!178 = metadata !{i32 95}
!179 = metadata !{i32 96}
!180 = metadata !{i32 76, i32 5, metadata !181, null}
!181 = metadata !{i32 720907, metadata !132, i32 75, i32 33, metadata !6, i32 4} ; [ DW_TAG_lexical_block ]
!182 = metadata !{i32 97}
!183 = metadata !{i32 77, i32 5, metadata !181, null}
!184 = metadata !{i32 98}
!185 = metadata !{i32 78, i32 3, metadata !181, null}
!186 = metadata !{i32 99}
!187 = metadata !{i32 80, i32 3, metadata !132, null}
!188 = metadata !{i32 100}
