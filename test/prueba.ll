; ModuleID = 'prueba.c'
source_filename = "prueba.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [21 x i8] c"Inicio del programa\0A\00", align 1
@.str.1 = private unnamed_addr constant [3 x i8] c"a\0A\00", align 1
@.str.2 = private unnamed_addr constant [10 x i8] c"No a y b\0A\00", align 1
@.str.3 = private unnamed_addr constant [8 x i8] c"c = %d\0A\00", align 1
@.str.4 = private unnamed_addr constant [7 x i8] c"Final\0A\00", align 1
@.str.5 = private unnamed_addr constant [2 x i8] c"%d", align 1

; Function Attrs: noinline nounwind optnone sspstrong uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 0, ptr %2, align 4
  store i32 0, ptr %3, align 4
  store i32 5, ptr %4, align 4
  %5 = call i32 (ptr, ...) @printf(ptr noundef @.str)
  %6 = load i32, ptr %2, align 4
  %7 = icmp slt i32 %6, 88
  br i1 %7, label %8, label %10
; hola
8:                                                ; preds = %0
  %9 = call i32 (ptr, ...) @printf(ptr noundef @.str.1)
  br label %27

10:                                               ; preds = %0
  %11 = load i32, ptr %3, align 4
  %12 = icmp ne i32 %11, 0
  br i1 %12, label %13, label %15

13:                                               ; preds = %10
  %14 = call i32 (ptr, ...) @printf(ptr noundef @.str.2)
  br label %26

15:                                               ; preds = %10
  br label %16

16:                                               ; preds = %19, %15
  %17 = load i32, ptr %4, align 4
  %18 = icmp ne i32 %17, 0
  br i1 %18, label %19, label %25

19:                                               ; preds = %16
  %20 = load i32, ptr %4, align 4
  %21 = call i32 (ptr, ...) @printf(ptr noundef @.str.3, i32 noundef %20)
  %22 = load i32, ptr %4, align 4
  %23 = sub nsw i32 %22, 2
  %24 = add nsw i32 %23, 1
  store i32 %24, ptr %4, align 4
  br label %16, !llvm.loop !6

25:                                               ; preds = %16
  br label %26

26:                                               ; preds = %25, %13
  br label %27

27:                                               ; preds = %26, %8
  %28 = call i32 (ptr, ...) @printf(ptr noundef @.str.4)
  %31 = load i32, ptr %1, align 4
  ret i32 %31
}

declare i32 @printf(ptr noundef, ...) #1

attributes #0 = { noinline nounwind optnone sspstrong uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 18.1.8"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
