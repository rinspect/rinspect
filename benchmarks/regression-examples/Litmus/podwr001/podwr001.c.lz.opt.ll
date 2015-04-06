; ModuleID = '/home/naling/src/examples/tso/regression-examples/podwr001/podwr001.c.lz.opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%union.pthread_attr_t = type { i32, [32 x i8] }

@z = common global i32 0, align 4
@x = common global i32 0, align 4
@y = common global i32 0, align 4
@.str = private unnamed_addr constant [36 x i8] c"@@@CLAP: There is a SC violation! \0A\00", align 1
@.str1 = private unnamed_addr constant [32 x i8] c"\1B[1;31m  SC Violation!!!  \1B[0m\0A\00", align 1
@.str2 = private unnamed_addr constant [50 x i8] c"\0A%%%%%%%% EAX0=%ld, EAX1=%ld, EAX2=%ld %%%%%%%% \0A\00", align 1

define i8* @P0(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !24
  %EAX0 = alloca i32, align 4, !clap !25
  store i8* %arg, i8** %arg.addr, align 4, !clap !26
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !27), !dbg !28, !clap !29
  call void @llvm.dbg.declare(metadata !{i32* %EAX0}, metadata !30), !dbg !32, !clap !33
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @z, i32 1, i32 0, i32 32, i32 6)
  store i32 1, i32* @z, align 4, !dbg !34, !clap !35
  call void (i32, ...)* @clap_store_post(i32 5, i32* @z, i32 1, i32 0, i32 32, i32 6)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @x, i32 0, i32 32, i32 7)
  %tmp = load i32* @x, align 4, !dbg !36, !clap !37
  call void (i32, ...)* @clap_load_post(i32 4, i32* @x, i32 0, i32 32, i32 7)
  store i32 %tmp, i32* %EAX0, align 4, !dbg !36, !clap !38
  %tmp1 = load i32* %EAX0, align 4, !dbg !39, !clap !40
  %tmp2 = inttoptr i32 %tmp1 to i8*, !dbg !39, !clap !41
  ret i8* %tmp2, !dbg !39, !clap !42
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

define i8* @P1(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !43
  %EAX1 = alloca i32, align 4, !clap !44
  store i8* %arg, i8** %arg.addr, align 4, !clap !45
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !46), !dbg !47, !clap !48
  call void @llvm.dbg.declare(metadata !{i32* %EAX1}, metadata !49), !dbg !51, !clap !52
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 17)
  store i32 1, i32* @x, align 4, !dbg !53, !clap !54
  call void (i32, ...)* @clap_store_post(i32 5, i32* @x, i32 1, i32 0, i32 32, i32 17)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @y, i32 0, i32 32, i32 18)
  %tmp = load i32* @y, align 4, !dbg !55, !clap !56
  call void (i32, ...)* @clap_load_post(i32 4, i32* @y, i32 0, i32 32, i32 18)
  store i32 %tmp, i32* %EAX1, align 4, !dbg !55, !clap !57
  %tmp1 = load i32* %EAX1, align 4, !dbg !58, !clap !59
  %tmp2 = inttoptr i32 %tmp1 to i8*, !dbg !58, !clap !60
  ret i8* %tmp2, !dbg !58, !clap !61
}

define i8* @P2(i8* %arg) nounwind {
entry:
  %arg.addr = alloca i8*, align 4, !clap !62
  %EAX2 = alloca i32, align 4, !clap !63
  store i8* %arg, i8** %arg.addr, align 4, !clap !64
  call void @llvm.dbg.declare(metadata !{i8** %arg.addr}, metadata !65), !dbg !66, !clap !67
  call void @llvm.dbg.declare(metadata !{i32* %EAX2}, metadata !68), !dbg !70, !clap !71
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 28)
  store i32 1, i32* @y, align 4, !dbg !72, !clap !73
  call void (i32, ...)* @clap_store_post(i32 5, i32* @y, i32 1, i32 0, i32 32, i32 28)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @z, i32 0, i32 32, i32 29)
  %tmp = load i32* @z, align 4, !dbg !74, !clap !75
  call void (i32, ...)* @clap_load_post(i32 4, i32* @z, i32 0, i32 32, i32 29)
  store i32 %tmp, i32* %EAX2, align 4, !dbg !74, !clap !76
  %tmp1 = load i32* %EAX2, align 4, !dbg !77, !clap !78
  %tmp2 = inttoptr i32 %tmp1 to i8*, !dbg !77, !clap !79
  ret i8* %tmp2, !dbg !77, !clap !80
}

define i32 @main() nounwind {
entry:
  %retval = alloca i32, align 4, !clap !81
  %t0 = alloca i32, align 4, !clap !82
  %t1 = alloca i32, align 4, !clap !83
  %t2 = alloca i32, align 4, !clap !84
  %EAX0 = alloca i32, align 4, !clap !85
  %EAX1 = alloca i32, align 4, !clap !86
  %EAX2 = alloca i32, align 4, !clap !87
  store i32 0, i32* %retval, !clap !88
  call void @llvm.dbg.declare(metadata !{i32* %t0}, metadata !89), !dbg !93, !clap !94
  call void @llvm.dbg.declare(metadata !{i32* %t1}, metadata !95), !dbg !96, !clap !97
  call void @llvm.dbg.declare(metadata !{i32* %t2}, metadata !98), !dbg !99, !clap !100
  call void @llvm.dbg.declare(metadata !{i32* %EAX0}, metadata !101), !dbg !102, !clap !103
  call void @llvm.dbg.declare(metadata !{i32* %EAX1}, metadata !104), !dbg !105, !clap !106
  call void @llvm.dbg.declare(metadata !{i32* %EAX2}, metadata !107), !dbg !108, !clap !109
  %call = call i32 @clap_thread_create(i32* %t0, %union.pthread_attr_t* null, i8* (i8*)* @P0, i8* null) nounwind, !dbg !110, !clap !111
  %call1 = call i32 @clap_thread_create(i32* %t1, %union.pthread_attr_t* null, i8* (i8*)* @P1, i8* null) nounwind, !dbg !112, !clap !113
  %call2 = call i32 @clap_thread_create(i32* %t2, %union.pthread_attr_t* null, i8* (i8*)* @P2, i8* null) nounwind, !dbg !114, !clap !115
  %tmp = load i32* %t0, align 4, !dbg !116, !clap !117
  %tmp1 = bitcast i32* %EAX0 to i8**, !dbg !116, !clap !118
  %call3 = call i32 @clap_thread_join(i32 %tmp, i8** %tmp1), !dbg !116, !clap !119
  %tmp2 = load i32* %t1, align 4, !dbg !120, !clap !121
  %tmp3 = bitcast i32* %EAX1 to i8**, !dbg !120, !clap !122
  %call4 = call i32 @clap_thread_join(i32 %tmp2, i8** %tmp3), !dbg !120, !clap !123
  %tmp4 = load i32* %t2, align 4, !dbg !124, !clap !125
  %tmp5 = bitcast i32* %EAX2 to i8**, !dbg !124, !clap !126
  %call5 = call i32 @clap_thread_join(i32 %tmp4, i8** %tmp5), !dbg !124, !clap !127
  %tmp6 = load i32* %EAX0, align 4, !dbg !128, !clap !129
  %cmp = icmp eq i32 %tmp6, 0, !dbg !128, !clap !130
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !128, !clap !131

land.lhs.true:                                    ; preds = %entry
  %tmp7 = load i32* %EAX1, align 4, !dbg !128, !clap !132
  %cmp6 = icmp eq i32 %tmp7, 0, !dbg !128, !clap !133
  br i1 %cmp6, label %land.lhs.true7, label %if.end, !dbg !128, !clap !134

land.lhs.true7:                                   ; preds = %land.lhs.true
  %tmp8 = load i32* %EAX2, align 4, !dbg !128, !clap !135
  %cmp8 = icmp eq i32 %tmp8, 0, !dbg !128, !clap !136
  br i1 %cmp8, label %if.then, label %if.end, !dbg !128, !clap !137

if.then:                                          ; preds = %land.lhs.true7
  %call9 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([36 x i8]* @.str, i32 0, i32 0)), !dbg !138, !clap !140
  %call10 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([32 x i8]* @.str1, i32 0, i32 0)), !dbg !141, !clap !142
  br label %if.end, !dbg !143, !clap !144

if.end:                                           ; preds = %if.then, %land.lhs.true7, %land.lhs.true, %entry
  %tmp9 = load i32* %EAX0, align 4, !dbg !145, !clap !146
  %tmp10 = load i32* %EAX1, align 4, !dbg !145, !clap !147
  %tmp11 = load i32* %EAX2, align 4, !dbg !145, !clap !148
  %call11 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([50 x i8]* @.str2, i32 0, i32 0), i32 %tmp9, i32 %tmp10, i32 %tmp11), !dbg !145, !clap !149
  ret i32 0, !dbg !150, !clap !151
}

declare i32 @clap_thread_create(i32*, %union.pthread_attr_t*, i8* (i8*)*, i8*) nounwind

declare i32 @clap_thread_join(i32, i8**)

declare i32 @printf(i8*, ...)

declare void @clap_load_pre(i32, ...)

declare void @clap_load_post(i32, ...)

declare void @clap_store_pre(i32, ...)

declare void @clap_store_post(i32, ...)

declare void @clap_cmpxchg_pre(i32, ...)

declare void @clap_cmpxchg_post(i32, ...)

declare void @clap_atomicrmw_pre(i32, ...)

declare void @clap_atomicrmw_post(i32, ...)

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 720913, i32 0, i32 12, metadata !"/home/naling/src/examples/tso/regression-examples/podwr001/podwr001.c", metadata !"/home/naling/src/inspect-0.3", metadata !"clang version 3.0 (tags/RELEASE_30/final)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !18} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !12, metadata !13, metadata !14}
!5 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P0", metadata !"P0", metadata !"", metadata !6, i32 28, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P0, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 720937, metadata !"/home/naling/src/examples/tso/regression-examples/podwr001/podwr001.c", metadata !"/home/naling/src/inspect-0.3", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{metadata !9}
!9 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ]
!10 = metadata !{metadata !11}
!11 = metadata !{i32 720932}                      ; [ DW_TAG_base_type ]
!12 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P1", metadata !"P1", metadata !"", metadata !6, i32 36, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P1, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!13 = metadata !{i32 720942, i32 0, metadata !6, metadata !"P2", metadata !"P2", metadata !"", metadata !6, i32 44, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i8* (i8*)* @P2, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!14 = metadata !{i32 720942, i32 0, metadata !6, metadata !"main", metadata !"main", metadata !"", metadata !6, i32 52, metadata !15, i1 false, i1 true, i32 0, i32 0, i32 0, i32 256, i1 false, i32 ()* @main, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!15 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !16, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!16 = metadata !{metadata !17}
!17 = metadata !{i32 720932, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!18 = metadata !{metadata !19}
!19 = metadata !{metadata !20, metadata !22, metadata !23}
!20 = metadata !{i32 720948, i32 0, null, metadata !"x", metadata !"x", metadata !"", metadata !6, i32 25, metadata !21, i32 0, i32 1, i32* @x} ; [ DW_TAG_variable ]
!21 = metadata !{i32 720932, null, metadata !"long int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!22 = metadata !{i32 720948, i32 0, null, metadata !"y", metadata !"y", metadata !"", metadata !6, i32 25, metadata !21, i32 0, i32 1, i32* @y} ; [ DW_TAG_variable ]
!23 = metadata !{i32 720948, i32 0, null, metadata !"z", metadata !"z", metadata !"", metadata !6, i32 25, metadata !21, i32 0, i32 1, i32* @z} ; [ DW_TAG_variable ]
!24 = metadata !{i32 1}
!25 = metadata !{i32 2}
!26 = metadata !{i32 3}
!27 = metadata !{i32 721153, metadata !5, metadata !"arg", metadata !6, i32 16777243, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!28 = metadata !{i32 27, i32 16, metadata !5, null}
!29 = metadata !{i32 4}
!30 = metadata !{i32 721152, metadata !31, metadata !"EAX0", metadata !6, i32 29, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!31 = metadata !{i32 720907, metadata !5, i32 28, i32 1, metadata !6, i32 0} ; [ DW_TAG_lexical_block ]
!32 = metadata !{i32 29, i32 12, metadata !31, null}
!33 = metadata !{i32 5}
!34 = metadata !{i32 30, i32 3, metadata !31, null}
!35 = metadata !{i32 6}
!36 = metadata !{i32 31, i32 3, metadata !31, null}
!37 = metadata !{i32 7}
!38 = metadata !{i32 8}
!39 = metadata !{i32 32, i32 3, metadata !31, null}
!40 = metadata !{i32 9}
!41 = metadata !{i32 10}
!42 = metadata !{i32 11}
!43 = metadata !{i32 12}
!44 = metadata !{i32 13}
!45 = metadata !{i32 14}
!46 = metadata !{i32 721153, metadata !12, metadata !"arg", metadata !6, i32 16777251, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!47 = metadata !{i32 35, i32 16, metadata !12, null}
!48 = metadata !{i32 15}
!49 = metadata !{i32 721152, metadata !50, metadata !"EAX1", metadata !6, i32 37, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!50 = metadata !{i32 720907, metadata !12, i32 36, i32 1, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!51 = metadata !{i32 37, i32 12, metadata !50, null}
!52 = metadata !{i32 16}
!53 = metadata !{i32 38, i32 3, metadata !50, null}
!54 = metadata !{i32 17}
!55 = metadata !{i32 39, i32 3, metadata !50, null}
!56 = metadata !{i32 18}
!57 = metadata !{i32 19}
!58 = metadata !{i32 40, i32 3, metadata !50, null}
!59 = metadata !{i32 20}
!60 = metadata !{i32 21}
!61 = metadata !{i32 22}
!62 = metadata !{i32 23}
!63 = metadata !{i32 24}
!64 = metadata !{i32 25}
!65 = metadata !{i32 721153, metadata !13, metadata !"arg", metadata !6, i32 16777259, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ]
!66 = metadata !{i32 43, i32 16, metadata !13, null}
!67 = metadata !{i32 26}
!68 = metadata !{i32 721152, metadata !69, metadata !"EAX2", metadata !6, i32 45, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!69 = metadata !{i32 720907, metadata !13, i32 44, i32 1, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!70 = metadata !{i32 45, i32 12, metadata !69, null}
!71 = metadata !{i32 27}
!72 = metadata !{i32 46, i32 3, metadata !69, null}
!73 = metadata !{i32 28}
!74 = metadata !{i32 47, i32 3, metadata !69, null}
!75 = metadata !{i32 29}
!76 = metadata !{i32 30}
!77 = metadata !{i32 48, i32 3, metadata !69, null}
!78 = metadata !{i32 31}
!79 = metadata !{i32 32}
!80 = metadata !{i32 33}
!81 = metadata !{i32 34}
!82 = metadata !{i32 35}
!83 = metadata !{i32 36}
!84 = metadata !{i32 37}
!85 = metadata !{i32 38}
!86 = metadata !{i32 39}
!87 = metadata !{i32 40}
!88 = metadata !{i32 41}
!89 = metadata !{i32 721152, metadata !90, metadata !"t0", metadata !6, i32 53, metadata !91, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!90 = metadata !{i32 720907, metadata !14, i32 52, i32 1, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!91 = metadata !{i32 720918, null, metadata !"pthread_t", metadata !6, i32 60, i64 0, i64 0, i64 0, i32 0, metadata !92} ; [ DW_TAG_typedef ]
!92 = metadata !{i32 720932, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!93 = metadata !{i32 53, i32 13, metadata !90, null}
!94 = metadata !{i32 42}
!95 = metadata !{i32 721152, metadata !90, metadata !"t1", metadata !6, i32 53, metadata !91, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!96 = metadata !{i32 53, i32 17, metadata !90, null}
!97 = metadata !{i32 43}
!98 = metadata !{i32 721152, metadata !90, metadata !"t2", metadata !6, i32 53, metadata !91, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!99 = metadata !{i32 53, i32 21, metadata !90, null}
!100 = metadata !{i32 44}
!101 = metadata !{i32 721152, metadata !90, metadata !"EAX0", metadata !6, i32 54, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!102 = metadata !{i32 54, i32 12, metadata !90, null}
!103 = metadata !{i32 45}
!104 = metadata !{i32 721152, metadata !90, metadata !"EAX1", metadata !6, i32 54, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!105 = metadata !{i32 54, i32 18, metadata !90, null}
!106 = metadata !{i32 46}
!107 = metadata !{i32 721152, metadata !90, metadata !"EAX2", metadata !6, i32 54, metadata !21, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!108 = metadata !{i32 54, i32 24, metadata !90, null}
!109 = metadata !{i32 47}
!110 = metadata !{i32 56, i32 3, metadata !90, null}
!111 = metadata !{i32 48}
!112 = metadata !{i32 57, i32 3, metadata !90, null}
!113 = metadata !{i32 49}
!114 = metadata !{i32 58, i32 3, metadata !90, null}
!115 = metadata !{i32 50}
!116 = metadata !{i32 60, i32 3, metadata !90, null}
!117 = metadata !{i32 51}
!118 = metadata !{i32 52}
!119 = metadata !{i32 53}
!120 = metadata !{i32 61, i32 3, metadata !90, null}
!121 = metadata !{i32 54}
!122 = metadata !{i32 55}
!123 = metadata !{i32 56}
!124 = metadata !{i32 62, i32 3, metadata !90, null}
!125 = metadata !{i32 57}
!126 = metadata !{i32 58}
!127 = metadata !{i32 59}
!128 = metadata !{i32 65, i32 3, metadata !90, null}
!129 = metadata !{i32 60}
!130 = metadata !{i32 61}
!131 = metadata !{i32 62}
!132 = metadata !{i32 63}
!133 = metadata !{i32 64}
!134 = metadata !{i32 65}
!135 = metadata !{i32 66}
!136 = metadata !{i32 67}
!137 = metadata !{i32 68}
!138 = metadata !{i32 66, i32 5, metadata !139, null}
!139 = metadata !{i32 720907, metadata !90, i32 65, i32 38, metadata !6, i32 4} ; [ DW_TAG_lexical_block ]
!140 = metadata !{i32 69}
!141 = metadata !{i32 67, i32 5, metadata !139, null}
!142 = metadata !{i32 70}
!143 = metadata !{i32 68, i32 3, metadata !139, null}
!144 = metadata !{i32 71}
!145 = metadata !{i32 69, i32 3, metadata !90, null}
!146 = metadata !{i32 72}
!147 = metadata !{i32 73}
!148 = metadata !{i32 74}
!149 = metadata !{i32 75}
!150 = metadata !{i32 71, i32 3, metadata !90, null}
!151 = metadata !{i32 76}
