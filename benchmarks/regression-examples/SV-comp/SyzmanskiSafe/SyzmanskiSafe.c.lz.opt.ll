; ModuleID = '/home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c.lz.opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%union.pthread_attr_t = type { i32, [32 x i8] }

@flag1 = global i32 0, align 4
@flag2 = global i32 0, align 4
@x = common global i32 0, align 4

define i8* @thr1() nounwind {
entry:
  %n1 = alloca i32, align 4, !clap !22
  %n2 = alloca i32, align 4, !clap !23
  %n3 = alloca i32, align 4, !clap !24
  %n4 = alloca i32, align 4, !clap !25
  call void @llvm.dbg.declare(metadata !{i32* %n1}, metadata !26), !dbg !28, !clap !29
  store i32 0, i32* %n1, align 4, !dbg !30, !clap !31
  call void @llvm.dbg.declare(metadata !{i32* %n2}, metadata !32), !dbg !33, !clap !34
  store i32 0, i32* %n2, align 4, !dbg !35, !clap !36
  call void @llvm.dbg.declare(metadata !{i32* %n3}, metadata !37), !dbg !38, !clap !39
  store i32 0, i32* %n3, align 4, !dbg !40, !clap !41
  call void @llvm.dbg.declare(metadata !{i32* %n4}, metadata !42), !dbg !43, !clap !44
  store i32 0, i32* %n4, align 4, !dbg !45, !clap !46
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @flag1, i32 1, i32 0, i32 32, i32 13)
  store i32 1, i32* @flag1, align 4, !dbg !47, !clap !48
  call void (i32, ...)* @clap_store_post(i32 5, i32* @flag1, i32 1, i32 0, i32 32, i32 13)
  br label %while.cond, !dbg !49, !clap !50

while.cond:                                       ; preds = %if.end, %entry
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag2, i32 0, i32 32, i32 15)
  %tmp = load i32* @flag2, align 4, !dbg !49, !clap !51
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag2, i32 0, i32 32, i32 15)
  %cmp = icmp sge i32 %tmp, 3, !dbg !49, !clap !52
  br i1 %cmp, label %while.body, label %while.end, !dbg !49, !clap !53

while.body:                                       ; preds = %while.cond
  %tmp1 = load i32* %n1, align 4, !dbg !54, !clap !56
  %inc = add nsw i32 %tmp1, 1, !dbg !54, !clap !57
  store i32 %inc, i32* %n1, align 4, !dbg !54, !clap !58
  %cmp1 = icmp sge i32 %tmp1, 1, !dbg !54, !clap !59
  br i1 %cmp1, label %if.then, label %if.end, !dbg !54, !clap !60

if.then:                                          ; preds = %while.body
  br label %while.end, !dbg !61, !clap !62

if.end:                                           ; preds = %while.body
  br label %while.cond, !dbg !63, !clap !64

while.end:                                        ; preds = %if.then, %while.cond
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @flag1, i32 3, i32 0, i32 32, i32 25)
  store i32 3, i32* @flag1, align 4, !dbg !65, !clap !66
  call void (i32, ...)* @clap_store_post(i32 5, i32* @flag1, i32 3, i32 0, i32 32, i32 25)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag2, i32 0, i32 32, i32 26)
  %tmp2 = load i32* @flag2, align 4, !dbg !67, !clap !68
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag2, i32 0, i32 32, i32 26)
  %cmp2 = icmp eq i32 %tmp2, 1, !dbg !67, !clap !69
  br i1 %cmp2, label %if.then3, label %if.end12, !dbg !67, !clap !70

if.then3:                                         ; preds = %while.end
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @flag1, i32 2, i32 0, i32 32, i32 29)
  store i32 2, i32* @flag1, align 4, !dbg !71, !clap !73
  call void (i32, ...)* @clap_store_post(i32 5, i32* @flag1, i32 2, i32 0, i32 32, i32 29)
  br label %while.cond4, !dbg !74, !clap !75

while.cond4:                                      ; preds = %if.end10, %if.then3
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag2, i32 0, i32 32, i32 31)
  %tmp3 = load i32* @flag2, align 4, !dbg !74, !clap !76
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag2, i32 0, i32 32, i32 31)
  %cmp5 = icmp ne i32 %tmp3, 4, !dbg !74, !clap !77
  br i1 %cmp5, label %while.body6, label %while.end11, !dbg !74, !clap !78

while.body6:                                      ; preds = %while.cond4
  %tmp4 = load i32* %n2, align 4, !dbg !79, !clap !81
  %inc7 = add nsw i32 %tmp4, 1, !dbg !79, !clap !82
  store i32 %inc7, i32* %n2, align 4, !dbg !79, !clap !83
  %cmp8 = icmp sge i32 %tmp4, 1, !dbg !79, !clap !84
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !79, !clap !85

if.then9:                                         ; preds = %while.body6
  br label %while.end11, !dbg !86, !clap !87

if.end10:                                         ; preds = %while.body6
  br label %while.cond4, !dbg !88, !clap !89

while.end11:                                      ; preds = %if.then9, %while.cond4
  br label %if.end12, !dbg !90, !clap !91

if.end12:                                         ; preds = %while.end11, %while.end
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @flag1, i32 4, i32 0, i32 32, i32 42)
  store i32 4, i32* @flag1, align 4, !dbg !92, !clap !93
  call void (i32, ...)* @clap_store_post(i32 5, i32* @flag1, i32 4, i32 0, i32 32, i32 42)
  br label %while.cond13, !dbg !94, !clap !95

while.cond13:                                     ; preds = %if.end19, %if.end12
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag2, i32 0, i32 32, i32 44)
  %tmp5 = load i32* @flag2, align 4, !dbg !94, !clap !96
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag2, i32 0, i32 32, i32 44)
  %cmp14 = icmp sge i32 %tmp5, 2, !dbg !94, !clap !97
  br i1 %cmp14, label %while.body15, label %while.end20, !dbg !94, !clap !98

while.body15:                                     ; preds = %while.cond13
  %tmp6 = load i32* %n3, align 4, !dbg !99, !clap !101
  %inc16 = add nsw i32 %tmp6, 1, !dbg !99, !clap !102
  store i32 %inc16, i32* %n3, align 4, !dbg !99, !clap !103
  %cmp17 = icmp sge i32 %tmp6, 1, !dbg !99, !clap !104
  br i1 %cmp17, label %if.then18, label %if.end19, !dbg !99, !clap !105

if.then18:                                        ; preds = %while.body15
  br label %while.end20, !dbg !106, !clap !107

if.end19:                                         ; preds = %while.body15
  br label %while.cond13, !dbg !108, !clap !109

while.end20:                                      ; preds = %if.then18, %while.cond13
  br label %while.cond21, !dbg !110, !clap !111

while.cond21:                                     ; preds = %if.end28, %while.end20
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag2, i32 0, i32 32, i32 55)
  %tmp7 = load i32* @flag2, align 4, !dbg !110, !clap !112
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag2, i32 0, i32 32, i32 55)
  %cmp22 = icmp sle i32 2, %tmp7, !dbg !110, !clap !113
  br i1 %cmp22, label %land.rhs, label %land.end, !dbg !110, !clap !114

land.rhs:                                         ; preds = %while.cond21
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag2, i32 0, i32 32, i32 58)
  %tmp8 = load i32* @flag2, align 4, !dbg !110, !clap !115
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag2, i32 0, i32 32, i32 58)
  %cmp23 = icmp sle i32 %tmp8, 3, !dbg !110, !clap !116
  br label %land.end, !clap !117

land.end:                                         ; preds = %land.rhs, %while.cond21
  %tmp9 = phi i1 [ false, %while.cond21 ], [ %cmp23, %land.rhs ], !clap !118
  br i1 %tmp9, label %while.body24, label %while.end29, !clap !119

while.body24:                                     ; preds = %land.end
  %tmp10 = load i32* %n4, align 4, !dbg !120, !clap !122
  %inc25 = add nsw i32 %tmp10, 1, !dbg !120, !clap !123
  store i32 %inc25, i32* %n4, align 4, !dbg !120, !clap !124
  %cmp26 = icmp sge i32 %tmp10, 1, !dbg !120, !clap !125
  br i1 %cmp26, label %if.then27, label %if.end28, !dbg !120, !clap !126

if.then27:                                        ; preds = %while.body24
  br label %while.end29, !dbg !127, !clap !128

if.end28:                                         ; preds = %while.body24
  br label %while.cond21, !dbg !129, !clap !130

while.end29:                                      ; preds = %if.then27, %land.end
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @flag1, i32 0, i32 0, i32 32, i32 70)
  store i32 0, i32* @flag1, align 4, !dbg !131, !clap !132
  call void (i32, ...)* @clap_store_post(i32 5, i32* @flag1, i32 0, i32 0, i32 32, i32 70)
  ret i8* null, !dbg !133, !clap !134
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

define i8* @thr2() nounwind {
entry:
  %n1 = alloca i32, align 4, !clap !135
  %n2 = alloca i32, align 4, !clap !136
  %n3 = alloca i32, align 4, !clap !137
  %n4 = alloca i32, align 4, !clap !138
  call void @llvm.dbg.declare(metadata !{i32* %n1}, metadata !139), !dbg !141, !clap !142
  store i32 0, i32* %n1, align 4, !dbg !143, !clap !144
  call void @llvm.dbg.declare(metadata !{i32* %n2}, metadata !145), !dbg !146, !clap !147
  store i32 0, i32* %n2, align 4, !dbg !148, !clap !149
  call void @llvm.dbg.declare(metadata !{i32* %n3}, metadata !150), !dbg !151, !clap !152
  store i32 0, i32* %n3, align 4, !dbg !153, !clap !154
  call void @llvm.dbg.declare(metadata !{i32* %n4}, metadata !155), !dbg !156, !clap !157
  store i32 0, i32* %n4, align 4, !dbg !158, !clap !159
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @flag2, i32 1, i32 0, i32 32, i32 84)
  store i32 1, i32* @flag2, align 4, !dbg !160, !clap !161
  call void (i32, ...)* @clap_store_post(i32 5, i32* @flag2, i32 1, i32 0, i32 32, i32 84)
  br label %while.cond, !dbg !162, !clap !163

while.cond:                                       ; preds = %if.end, %entry
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag1, i32 0, i32 32, i32 86)
  %tmp = load i32* @flag1, align 4, !dbg !162, !clap !164
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag1, i32 0, i32 32, i32 86)
  %cmp = icmp sge i32 %tmp, 3, !dbg !162, !clap !165
  br i1 %cmp, label %while.body, label %while.end, !dbg !162, !clap !166

while.body:                                       ; preds = %while.cond
  %tmp1 = load i32* %n1, align 4, !dbg !167, !clap !169
  %inc = add nsw i32 %tmp1, 1, !dbg !167, !clap !170
  store i32 %inc, i32* %n1, align 4, !dbg !167, !clap !171
  %cmp1 = icmp sge i32 %tmp1, 1, !dbg !167, !clap !172
  br i1 %cmp1, label %if.then, label %if.end, !dbg !167, !clap !173

if.then:                                          ; preds = %while.body
  br label %while.end, !dbg !174, !clap !175

if.end:                                           ; preds = %while.body
  br label %while.cond, !dbg !176, !clap !177

while.end:                                        ; preds = %if.then, %while.cond
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @flag2, i32 3, i32 0, i32 32, i32 96)
  store i32 3, i32* @flag2, align 4, !dbg !178, !clap !179
  call void (i32, ...)* @clap_store_post(i32 5, i32* @flag2, i32 3, i32 0, i32 32, i32 96)
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag1, i32 0, i32 32, i32 97)
  %tmp2 = load i32* @flag1, align 4, !dbg !180, !clap !181
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag1, i32 0, i32 32, i32 97)
  %cmp2 = icmp eq i32 %tmp2, 1, !dbg !180, !clap !182
  br i1 %cmp2, label %if.then3, label %if.end12, !dbg !180, !clap !183

if.then3:                                         ; preds = %while.end
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @flag2, i32 2, i32 0, i32 32, i32 100)
  store i32 2, i32* @flag2, align 4, !dbg !184, !clap !186
  call void (i32, ...)* @clap_store_post(i32 5, i32* @flag2, i32 2, i32 0, i32 32, i32 100)
  br label %while.cond4, !dbg !187, !clap !188

while.cond4:                                      ; preds = %if.end10, %if.then3
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag1, i32 0, i32 32, i32 102)
  %tmp3 = load i32* @flag1, align 4, !dbg !187, !clap !189
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag1, i32 0, i32 32, i32 102)
  %cmp5 = icmp ne i32 %tmp3, 4, !dbg !187, !clap !190
  br i1 %cmp5, label %while.body6, label %while.end11, !dbg !187, !clap !191

while.body6:                                      ; preds = %while.cond4
  %tmp4 = load i32* %n2, align 4, !dbg !192, !clap !194
  %inc7 = add nsw i32 %tmp4, 1, !dbg !192, !clap !195
  store i32 %inc7, i32* %n2, align 4, !dbg !192, !clap !196
  %cmp8 = icmp sge i32 %tmp4, 1, !dbg !192, !clap !197
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !192, !clap !198

if.then9:                                         ; preds = %while.body6
  br label %while.end11, !dbg !199, !clap !200

if.end10:                                         ; preds = %while.body6
  br label %while.cond4, !dbg !201, !clap !202

while.end11:                                      ; preds = %if.then9, %while.cond4
  br label %if.end12, !dbg !203, !clap !204

if.end12:                                         ; preds = %while.end11, %while.end
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @flag2, i32 4, i32 0, i32 32, i32 113)
  store i32 4, i32* @flag2, align 4, !dbg !205, !clap !206
  call void (i32, ...)* @clap_store_post(i32 5, i32* @flag2, i32 4, i32 0, i32 32, i32 113)
  br label %while.cond13, !dbg !207, !clap !208

while.cond13:                                     ; preds = %if.end19, %if.end12
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag1, i32 0, i32 32, i32 115)
  %tmp5 = load i32* @flag1, align 4, !dbg !207, !clap !209
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag1, i32 0, i32 32, i32 115)
  %cmp14 = icmp sge i32 %tmp5, 2, !dbg !207, !clap !210
  br i1 %cmp14, label %while.body15, label %while.end20, !dbg !207, !clap !211

while.body15:                                     ; preds = %while.cond13
  %tmp6 = load i32* %n3, align 4, !dbg !212, !clap !214
  %inc16 = add nsw i32 %tmp6, 1, !dbg !212, !clap !215
  store i32 %inc16, i32* %n3, align 4, !dbg !212, !clap !216
  %cmp17 = icmp sge i32 %tmp6, 1, !dbg !212, !clap !217
  br i1 %cmp17, label %if.then18, label %if.end19, !dbg !212, !clap !218

if.then18:                                        ; preds = %while.body15
  br label %while.end20, !dbg !219, !clap !220

if.end19:                                         ; preds = %while.body15
  br label %while.cond13, !dbg !221, !clap !222

while.end20:                                      ; preds = %if.then18, %while.cond13
  br label %while.cond21, !dbg !223, !clap !224

while.cond21:                                     ; preds = %if.end28, %while.end20
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag1, i32 0, i32 32, i32 126)
  %tmp7 = load i32* @flag1, align 4, !dbg !223, !clap !225
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag1, i32 0, i32 32, i32 126)
  %cmp22 = icmp sle i32 2, %tmp7, !dbg !223, !clap !226
  br i1 %cmp22, label %land.rhs, label %land.end, !dbg !223, !clap !227

land.rhs:                                         ; preds = %while.cond21
  call void (i32, ...)* @clap_load_pre(i32 4, i32* @flag1, i32 0, i32 32, i32 129)
  %tmp8 = load i32* @flag1, align 4, !dbg !223, !clap !228
  call void (i32, ...)* @clap_load_post(i32 4, i32* @flag1, i32 0, i32 32, i32 129)
  %cmp23 = icmp sle i32 %tmp8, 3, !dbg !223, !clap !229
  br label %land.end, !clap !230

land.end:                                         ; preds = %land.rhs, %while.cond21
  %tmp9 = phi i1 [ false, %while.cond21 ], [ %cmp23, %land.rhs ], !clap !231
  br i1 %tmp9, label %while.body24, label %while.end29, !clap !232

while.body24:                                     ; preds = %land.end
  %tmp10 = load i32* %n4, align 4, !dbg !233, !clap !235
  %inc25 = add nsw i32 %tmp10, 1, !dbg !233, !clap !236
  store i32 %inc25, i32* %n4, align 4, !dbg !233, !clap !237
  %cmp26 = icmp sge i32 %tmp10, 1, !dbg !233, !clap !238
  br i1 %cmp26, label %if.then27, label %if.end28, !dbg !233, !clap !239

if.then27:                                        ; preds = %while.body24
  br label %while.end29, !dbg !240, !clap !241

if.end28:                                         ; preds = %while.body24
  br label %while.cond21, !dbg !242, !clap !243

while.end29:                                      ; preds = %if.then27, %land.end
  call void (i32, ...)* @clap_store_pre(i32 5, i32* @flag2, i32 0, i32 0, i32 32, i32 141)
  store i32 0, i32* @flag2, align 4, !dbg !244, !clap !245
  call void (i32, ...)* @clap_store_post(i32 5, i32* @flag2, i32 0, i32 0, i32 32, i32 141)
  ret i8* null, !dbg !246, !clap !247
}

define i32 @main() nounwind {
entry:
  %retval = alloca i32, align 4, !clap !248
  %t1 = alloca i32, align 4, !clap !249
  %t2 = alloca i32, align 4, !clap !250
  store i32 0, i32* %retval, !clap !251
  call void @llvm.dbg.declare(metadata !{i32* %t1}, metadata !252), !dbg !256, !clap !257
  call void @llvm.dbg.declare(metadata !{i32* %t2}, metadata !258), !dbg !259, !clap !260
  %call = call i32 @clap_thread_create(i32* %t1, %union.pthread_attr_t* null, i8* (i8*)* bitcast (i8* ()* @thr1 to i8* (i8*)*), i8* null) nounwind, !dbg !261, !clap !262
  %call1 = call i32 @clap_thread_create(i32* %t2, %union.pthread_attr_t* null, i8* (i8*)* bitcast (i8* ()* @thr2 to i8* (i8*)*), i8* null) nounwind, !dbg !263, !clap !264
  %tmp = load i32* %t1, align 4, !dbg !265, !clap !266
  %call2 = call i32 @clap_thread_join(i32 %tmp, i8** null), !dbg !265, !clap !267
  %tmp1 = load i32* %t2, align 4, !dbg !268, !clap !269
  %call3 = call i32 @clap_thread_join(i32 %tmp1, i8** null), !dbg !268, !clap !270
  ret i32 0, !dbg !271, !clap !272
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

!0 = metadata !{i32 720913, i32 0, i32 12, metadata !"/home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c", metadata !"/home/naling/src/inspect-0.3", metadata !"clang version 3.0 (tags/RELEASE_30/final)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !17} ; [ DW_TAG_compile_unit ]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !12, metadata !13}
!5 = metadata !{i32 720942, i32 0, metadata !6, metadata !"thr1", metadata !"thr1", metadata !"", metadata !6, i32 10, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 0, i1 false, i8* ()* @thr1, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!6 = metadata !{i32 720937, metadata !"/home/naling/src/examples/tso/regression-examples/SyzmanskiSafe/SyzmanskiSafe.c", metadata !"/home/naling/src/inspect-0.3", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!8 = metadata !{metadata !9}
!9 = metadata !{i32 720911, null, metadata !"", null, i32 0, i64 32, i64 32, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ]
!10 = metadata !{metadata !11}
!11 = metadata !{i32 720932}                      ; [ DW_TAG_base_type ]
!12 = metadata !{i32 720942, i32 0, metadata !6, metadata !"thr2", metadata !"thr2", metadata !"", metadata !6, i32 36, metadata !7, i1 false, i1 true, i32 0, i32 0, i32 0, i32 0, i1 false, i8* ()* @thr2, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!13 = metadata !{i32 720942, i32 0, metadata !6, metadata !"main", metadata !"main", metadata !"", metadata !6, i32 60, metadata !14, i1 false, i1 true, i32 0, i32 0, i32 0, i32 0, i1 false, i32 ()* @main, null, null, metadata !10} ; [ DW_TAG_subprogram ]
!14 = metadata !{i32 720917, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i32 0, i32 0, i32 0, metadata !15, i32 0, i32 0} ; [ DW_TAG_subroutine_type ]
!15 = metadata !{metadata !16}
!16 = metadata !{i32 720932, null, metadata !"int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ]
!17 = metadata !{metadata !18}
!18 = metadata !{metadata !19, metadata !20, metadata !21}
!19 = metadata !{i32 720948, i32 0, null, metadata !"flag1", metadata !"flag1", metadata !"", metadata !6, i32 7, metadata !16, i32 0, i32 1, i32* @flag1} ; [ DW_TAG_variable ]
!20 = metadata !{i32 720948, i32 0, null, metadata !"flag2", metadata !"flag2", metadata !"", metadata !6, i32 7, metadata !16, i32 0, i32 1, i32* @flag2} ; [ DW_TAG_variable ]
!21 = metadata !{i32 720948, i32 0, null, metadata !"x", metadata !"x", metadata !"", metadata !6, i32 8, metadata !16, i32 0, i32 1, i32* @x} ; [ DW_TAG_variable ]
!22 = metadata !{i32 1}
!23 = metadata !{i32 2}
!24 = metadata !{i32 3}
!25 = metadata !{i32 4}
!26 = metadata !{i32 721152, metadata !27, metadata !"n1", metadata !6, i32 11, metadata !16, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!27 = metadata !{i32 720907, metadata !5, i32 10, i32 14, metadata !6, i32 0} ; [ DW_TAG_lexical_block ]
!28 = metadata !{i32 11, i32 9, metadata !27, null}
!29 = metadata !{i32 5}
!30 = metadata !{i32 11, i32 13, metadata !27, null}
!31 = metadata !{i32 6}
!32 = metadata !{i32 721152, metadata !27, metadata !"n2", metadata !6, i32 12, metadata !16, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!33 = metadata !{i32 12, i32 9, metadata !27, null}
!34 = metadata !{i32 7}
!35 = metadata !{i32 12, i32 13, metadata !27, null}
!36 = metadata !{i32 8}
!37 = metadata !{i32 721152, metadata !27, metadata !"n3", metadata !6, i32 13, metadata !16, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!38 = metadata !{i32 13, i32 9, metadata !27, null}
!39 = metadata !{i32 9}
!40 = metadata !{i32 13, i32 13, metadata !27, null}
!41 = metadata !{i32 10}
!42 = metadata !{i32 721152, metadata !27, metadata !"n4", metadata !6, i32 14, metadata !16, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!43 = metadata !{i32 14, i32 9, metadata !27, null}
!44 = metadata !{i32 11}
!45 = metadata !{i32 14, i32 13, metadata !27, null}
!46 = metadata !{i32 12}
!47 = metadata !{i32 15, i32 5, metadata !27, null}
!48 = metadata !{i32 13}
!49 = metadata !{i32 16, i32 5, metadata !27, null}
!50 = metadata !{i32 14}
!51 = metadata !{i32 15}
!52 = metadata !{i32 16}
!53 = metadata !{i32 17}
!54 = metadata !{i32 16, i32 24, metadata !55, null}
!55 = metadata !{i32 720907, metadata !27, i32 16, i32 23, metadata !6, i32 1} ; [ DW_TAG_lexical_block ]
!56 = metadata !{i32 18}
!57 = metadata !{i32 19}
!58 = metadata !{i32 20}
!59 = metadata !{i32 21}
!60 = metadata !{i32 22}
!61 = metadata !{i32 16, i32 39, metadata !55, null}
!62 = metadata !{i32 23}
!63 = metadata !{i32 16, i32 45, metadata !55, null}
!64 = metadata !{i32 24}
!65 = metadata !{i32 18, i32 5, metadata !27, null}
!66 = metadata !{i32 25}
!67 = metadata !{i32 19, i32 5, metadata !27, null}
!68 = metadata !{i32 26}
!69 = metadata !{i32 27}
!70 = metadata !{i32 28}
!71 = metadata !{i32 20, i32 2, metadata !72, null}
!72 = metadata !{i32 720907, metadata !27, i32 19, i32 21, metadata !6, i32 2} ; [ DW_TAG_lexical_block ]
!73 = metadata !{i32 29}
!74 = metadata !{i32 21, i32 2, metadata !72, null}
!75 = metadata !{i32 30}
!76 = metadata !{i32 31}
!77 = metadata !{i32 32}
!78 = metadata !{i32 33}
!79 = metadata !{i32 21, i32 21, metadata !80, null}
!80 = metadata !{i32 720907, metadata !72, i32 21, i32 20, metadata !6, i32 3} ; [ DW_TAG_lexical_block ]
!81 = metadata !{i32 34}
!82 = metadata !{i32 35}
!83 = metadata !{i32 36}
!84 = metadata !{i32 37}
!85 = metadata !{i32 38}
!86 = metadata !{i32 21, i32 36, metadata !80, null}
!87 = metadata !{i32 39}
!88 = metadata !{i32 21, i32 42, metadata !80, null}
!89 = metadata !{i32 40}
!90 = metadata !{i32 22, i32 5, metadata !72, null}
!91 = metadata !{i32 41}
!92 = metadata !{i32 23, i32 5, metadata !27, null}
!93 = metadata !{i32 42}
!94 = metadata !{i32 24, i32 5, metadata !27, null}
!95 = metadata !{i32 43}
!96 = metadata !{i32 44}
!97 = metadata !{i32 45}
!98 = metadata !{i32 46}
!99 = metadata !{i32 24, i32 24, metadata !100, null}
!100 = metadata !{i32 720907, metadata !27, i32 24, i32 23, metadata !6, i32 4} ; [ DW_TAG_lexical_block ]
!101 = metadata !{i32 47}
!102 = metadata !{i32 48}
!103 = metadata !{i32 49}
!104 = metadata !{i32 50}
!105 = metadata !{i32 51}
!106 = metadata !{i32 24, i32 39, metadata !100, null}
!107 = metadata !{i32 52}
!108 = metadata !{i32 24, i32 45, metadata !100, null}
!109 = metadata !{i32 53}
!110 = metadata !{i32 30, i32 5, metadata !27, null}
!111 = metadata !{i32 54}
!112 = metadata !{i32 55}
!113 = metadata !{i32 56}
!114 = metadata !{i32 57}
!115 = metadata !{i32 58}
!116 = metadata !{i32 59}
!117 = metadata !{i32 60}
!118 = metadata !{i32 61}
!119 = metadata !{i32 62}
!120 = metadata !{i32 30, i32 38, metadata !121, null}
!121 = metadata !{i32 720907, metadata !27, i32 30, i32 37, metadata !6, i32 5} ; [ DW_TAG_lexical_block ]
!122 = metadata !{i32 63}
!123 = metadata !{i32 64}
!124 = metadata !{i32 65}
!125 = metadata !{i32 66}
!126 = metadata !{i32 67}
!127 = metadata !{i32 30, i32 53, metadata !121, null}
!128 = metadata !{i32 68}
!129 = metadata !{i32 30, i32 59, metadata !121, null}
!130 = metadata !{i32 69}
!131 = metadata !{i32 31, i32 5, metadata !27, null}
!132 = metadata !{i32 70}
!133 = metadata !{i32 33, i32 5, metadata !27, null}
!134 = metadata !{i32 71}
!135 = metadata !{i32 72}
!136 = metadata !{i32 73}
!137 = metadata !{i32 74}
!138 = metadata !{i32 75}
!139 = metadata !{i32 721152, metadata !140, metadata !"n1", metadata !6, i32 37, metadata !16, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!140 = metadata !{i32 720907, metadata !12, i32 36, i32 14, metadata !6, i32 6} ; [ DW_TAG_lexical_block ]
!141 = metadata !{i32 37, i32 9, metadata !140, null}
!142 = metadata !{i32 76}
!143 = metadata !{i32 37, i32 13, metadata !140, null}
!144 = metadata !{i32 77}
!145 = metadata !{i32 721152, metadata !140, metadata !"n2", metadata !6, i32 38, metadata !16, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!146 = metadata !{i32 38, i32 9, metadata !140, null}
!147 = metadata !{i32 78}
!148 = metadata !{i32 38, i32 13, metadata !140, null}
!149 = metadata !{i32 79}
!150 = metadata !{i32 721152, metadata !140, metadata !"n3", metadata !6, i32 39, metadata !16, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!151 = metadata !{i32 39, i32 9, metadata !140, null}
!152 = metadata !{i32 80}
!153 = metadata !{i32 39, i32 13, metadata !140, null}
!154 = metadata !{i32 81}
!155 = metadata !{i32 721152, metadata !140, metadata !"n4", metadata !6, i32 40, metadata !16, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!156 = metadata !{i32 40, i32 9, metadata !140, null}
!157 = metadata !{i32 82}
!158 = metadata !{i32 40, i32 13, metadata !140, null}
!159 = metadata !{i32 83}
!160 = metadata !{i32 41, i32 5, metadata !140, null}
!161 = metadata !{i32 84}
!162 = metadata !{i32 42, i32 5, metadata !140, null}
!163 = metadata !{i32 85}
!164 = metadata !{i32 86}
!165 = metadata !{i32 87}
!166 = metadata !{i32 88}
!167 = metadata !{i32 42, i32 24, metadata !168, null}
!168 = metadata !{i32 720907, metadata !140, i32 42, i32 23, metadata !6, i32 7} ; [ DW_TAG_lexical_block ]
!169 = metadata !{i32 89}
!170 = metadata !{i32 90}
!171 = metadata !{i32 91}
!172 = metadata !{i32 92}
!173 = metadata !{i32 93}
!174 = metadata !{i32 42, i32 39, metadata !168, null}
!175 = metadata !{i32 94}
!176 = metadata !{i32 42, i32 45, metadata !168, null}
!177 = metadata !{i32 95}
!178 = metadata !{i32 43, i32 5, metadata !140, null}
!179 = metadata !{i32 96}
!180 = metadata !{i32 44, i32 5, metadata !140, null}
!181 = metadata !{i32 97}
!182 = metadata !{i32 98}
!183 = metadata !{i32 99}
!184 = metadata !{i32 45, i32 2, metadata !185, null}
!185 = metadata !{i32 720907, metadata !140, i32 44, i32 21, metadata !6, i32 8} ; [ DW_TAG_lexical_block ]
!186 = metadata !{i32 100}
!187 = metadata !{i32 46, i32 2, metadata !185, null}
!188 = metadata !{i32 101}
!189 = metadata !{i32 102}
!190 = metadata !{i32 103}
!191 = metadata !{i32 104}
!192 = metadata !{i32 46, i32 21, metadata !193, null}
!193 = metadata !{i32 720907, metadata !185, i32 46, i32 20, metadata !6, i32 9} ; [ DW_TAG_lexical_block ]
!194 = metadata !{i32 105}
!195 = metadata !{i32 106}
!196 = metadata !{i32 107}
!197 = metadata !{i32 108}
!198 = metadata !{i32 109}
!199 = metadata !{i32 46, i32 36, metadata !193, null}
!200 = metadata !{i32 110}
!201 = metadata !{i32 46, i32 42, metadata !193, null}
!202 = metadata !{i32 111}
!203 = metadata !{i32 47, i32 5, metadata !185, null}
!204 = metadata !{i32 112}
!205 = metadata !{i32 48, i32 5, metadata !140, null}
!206 = metadata !{i32 113}
!207 = metadata !{i32 49, i32 5, metadata !140, null}
!208 = metadata !{i32 114}
!209 = metadata !{i32 115}
!210 = metadata !{i32 116}
!211 = metadata !{i32 117}
!212 = metadata !{i32 49, i32 24, metadata !213, null}
!213 = metadata !{i32 720907, metadata !140, i32 49, i32 23, metadata !6, i32 10} ; [ DW_TAG_lexical_block ]
!214 = metadata !{i32 118}
!215 = metadata !{i32 119}
!216 = metadata !{i32 120}
!217 = metadata !{i32 121}
!218 = metadata !{i32 122}
!219 = metadata !{i32 49, i32 39, metadata !213, null}
!220 = metadata !{i32 123}
!221 = metadata !{i32 49, i32 45, metadata !213, null}
!222 = metadata !{i32 124}
!223 = metadata !{i32 55, i32 5, metadata !140, null}
!224 = metadata !{i32 125}
!225 = metadata !{i32 126}
!226 = metadata !{i32 127}
!227 = metadata !{i32 128}
!228 = metadata !{i32 129}
!229 = metadata !{i32 130}
!230 = metadata !{i32 131}
!231 = metadata !{i32 132}
!232 = metadata !{i32 133}
!233 = metadata !{i32 55, i32 38, metadata !234, null}
!234 = metadata !{i32 720907, metadata !140, i32 55, i32 37, metadata !6, i32 11} ; [ DW_TAG_lexical_block ]
!235 = metadata !{i32 134}
!236 = metadata !{i32 135}
!237 = metadata !{i32 136}
!238 = metadata !{i32 137}
!239 = metadata !{i32 138}
!240 = metadata !{i32 55, i32 53, metadata !234, null}
!241 = metadata !{i32 139}
!242 = metadata !{i32 55, i32 59, metadata !234, null}
!243 = metadata !{i32 140}
!244 = metadata !{i32 56, i32 5, metadata !140, null}
!245 = metadata !{i32 141}
!246 = metadata !{i32 57, i32 5, metadata !140, null}
!247 = metadata !{i32 142}
!248 = metadata !{i32 143}
!249 = metadata !{i32 144}
!250 = metadata !{i32 145}
!251 = metadata !{i32 146}
!252 = metadata !{i32 721152, metadata !253, metadata !"t1", metadata !6, i32 61, metadata !254, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!253 = metadata !{i32 720907, metadata !13, i32 60, i32 12, metadata !6, i32 12} ; [ DW_TAG_lexical_block ]
!254 = metadata !{i32 720918, null, metadata !"pthread_t", metadata !6, i32 60, i64 0, i64 0, i64 0, i32 0, metadata !255} ; [ DW_TAG_typedef ]
!255 = metadata !{i32 720932, null, metadata !"long unsigned int", null, i32 0, i64 32, i64 32, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ]
!256 = metadata !{i32 61, i32 15, metadata !253, null}
!257 = metadata !{i32 147}
!258 = metadata !{i32 721152, metadata !253, metadata !"t2", metadata !6, i32 61, metadata !254, i32 0, i32 0} ; [ DW_TAG_auto_variable ]
!259 = metadata !{i32 61, i32 19, metadata !253, null}
!260 = metadata !{i32 148}
!261 = metadata !{i32 62, i32 5, metadata !253, null}
!262 = metadata !{i32 149}
!263 = metadata !{i32 63, i32 5, metadata !253, null}
!264 = metadata !{i32 150}
!265 = metadata !{i32 64, i32 5, metadata !253, null}
!266 = metadata !{i32 151}
!267 = metadata !{i32 152}
!268 = metadata !{i32 65, i32 5, metadata !253, null}
!269 = metadata !{i32 153}
!270 = metadata !{i32 154}
!271 = metadata !{i32 66, i32 5, metadata !253, null}
!272 = metadata !{i32 155}
