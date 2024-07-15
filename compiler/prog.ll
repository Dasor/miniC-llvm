@.str0 = private unnamed_addr constant [21 x i8]  c"Inicio del programa\n", align 1
@.str1 = private unnamed_addr constant [1 x i8]  c"a", align 1
@.str2 = private unnamed_addr constant [2 x i8]  c"\n", align 1
@.str3 = private unnamed_addr constant [10 x i8]  c"No a y b\n", align 1
@.str4 = private unnamed_addr constant [4 x i8]  c"c = ", align 1
@.str5 = private unnamed_addr constant [2 x i8]  c"\n", align 1
@.str6 = private unnamed_addr constant [5 x i8]  c"Final", align 1
@.str7 = private unnamed_addr constant [2 x i8]  c"\n", align 1

define dso_local i32 @main() #0{

	store2 i32 0, ptr %1, align 4
	store3 i32 %1, ptr %2, align 4
	store2 i32 0, ptr %3, align 4
	store3 i32 %3, ptr %4, align 4
	store2 i32 5, ptr %5, align 4
	store2 i32 2, ptr %6, align 4
	%7 = add %5, %6
	store2 i32 2, ptr %8, align 4
	%9 = sub %7, %8
	store3 i32 %9, ptr %10, align 4
	%11 = call i32 (ptr, ...) @printf (ptr noundef @.str.0)
	%37 = icmp eq i32 %12, %36
	br i1 %37, label %38, label %39

38:
	%13 = call i32 (ptr, ...) @printf (ptr noundef @.str.1)
	%14 = call i32 (ptr, ...) @printf (ptr noundef @.str.2)

39:
	%33 = icmp eq i32 %15, %32
	br i1 %33, label %34, label %35

34:
	%16 = call i32 (ptr, ...) @printf (ptr noundef @.str.3)

35:

29:
	%28 = icmp eq i32 %17, %27
	br i1 %28, label %30, label %31

30:
	%18 = call i32 (ptr, ...) @printf (ptr noundef @.str.4)
	%20 = call i32 (ptr, ...) @printf (ptr noundef %19)
	%21 = call i32 (ptr, ...) @printf (ptr noundef @.str.2)
	store1 i32 c, ptr %22, align 4
	store2 i32 2, ptr %23, align 4
	%24 = sub %22, %23
	store2 i32 1, ptr %25, align 4
	%26 = add %24, %25
	store4 i32 _c, ptr %26, align 4
	br label %29

31:
	%40 = call i32 (ptr, ...) @printf (ptr noundef @.str.6)
	%41 = call i32 (ptr, ...) @printf (ptr noundef @.str.2)
}
declare i32 @printf(ptr noundef, ...) #1