@.str0 = private unnamed_addr constant [21 x i8]  c"Inicio del programa\n", align 1
@.str1 = private unnamed_addr constant [1 x i8]  c"a", align 1
@.str2 = private unnamed_addr constant [2 x i8]  c"\n", align 1
@.str3 = private unnamed_addr constant [10 x i8]  c"No a y b\n", align 1
@.str4 = private unnamed_addr constant [4 x i8]  c"c = ", align 1
@.str5 = private unnamed_addr constant [2 x i8]  c"\n", align 1
@.str6 = private unnamed_addr constant [5 x i8]  c"Final", align 1
@.str7 = private unnamed_addr constant [2 x i8]  c"\n", align 1

define dso_local i32 @main() #0{

	%1 = alloca i32, align 4
	store i32 0, ptr %1, align 4
	%a = alloca i32, align 4
	store ptr %1, ptr %a, align 4
	%2 = alloca i32, align 4
	store i32 0, ptr %2, align 4
	%b = alloca i32, align 4
	store ptr %2, ptr %b, align 4
	%3 = alloca i32, align 4
	store i32 5, ptr %3, align 4
	%4 = alloca i32, align 4
	store i32 2, ptr %4, align 4
	%5 = add %3, %4
	%6 = alloca i32, align 4
	store i32 2, ptr %6, align 4
	%7 = sub %5, %6
	%c = alloca i32, align 4
	store i32 %7, ptr %c, align 4
	%8 = call i32 (ptr, ...) @printf (ptr noundef @.str.0)
	%34 = icmp eq i32 %9, %33
	br i1 %34, label %35, label %36

35:
	%10 = call i32 (ptr, ...) @printf (ptr noundef @.str.1)
	%11 = call i32 (ptr, ...) @printf (ptr noundef @.str.2)

36:
	%30 = icmp eq i32 %12, %29
	br i1 %30, label %31, label %32

31:
	%13 = call i32 (ptr, ...) @printf (ptr noundef @.str.3)

32:

26:
	%25 = icmp eq i32 %14, %24
	br i1 %25, label %27, label %28

27:
	%15 = call i32 (ptr, ...) @printf (ptr noundef @.str.4)
	%17 = call i32 (ptr, ...) @printf (ptr noundef %16)
	%18 = call i32 (ptr, ...) @printf (ptr noundef @.str.2)
	%19 = alloca i32, align 4
	store i32 %c, ptr %19, align 4
	%20 = alloca i32, align 4
	store i32 2, ptr %20, align 4
	%21 = sub %19, %20
	%22 = alloca i32, align 4
	store i32 1, ptr %22, align 4
	%23 = add %21, %22
	store4 i32 %c, ptr %23, align 4
	br label %26

28:
	%37 = call i32 (ptr, ...) @printf (ptr noundef @.str.6)
	%38 = call i32 (ptr, ...) @printf (ptr noundef @.str.2)
}
declare i32 @printf(ptr noundef, ...) #1
