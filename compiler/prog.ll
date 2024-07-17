@.str = private unnamed_addr constant [2 x i8]  c"%d", align 1
@a = global i32 0
@b = global i32 0
@c = global i32 0
@.str.0 = private unnamed_addr constant [20 x i8]  c"Inicio del programa\0A", align 1
@.str.1 = private unnamed_addr constant [1 x i8]  c"a", align 1
@.str.2 = private unnamed_addr constant [1 x i8]  c"\0A", align 1
@.str.3 = private unnamed_addr constant [9 x i8]  c"No a y b\0A", align 1
@.str.4 = private unnamed_addr constant [4 x i8]  c"c = ", align 1
@.str.5 = private unnamed_addr constant [1 x i8]  c"\0A", align 1
@.str.6 = private unnamed_addr constant [5 x i8]  c"Final", align 1
@.str.7 = private unnamed_addr constant [1 x i8]  c"\0A", align 1

define i32 @main() #0{

	%R1 = add i32 0, 0
	store i32 %R1, i32* @a
	%R2 = add i32 0, 0
	store i32 %R2, i32* @b
	%R3 = add i32 0, 0
	store i32 %R3, i32* @c
	%R4 = call i32 (ptr, ...) @printf (ptr noundef @.str.0)
	%R5 = load i32, i32* @a
	%dbg = call i32 (ptr, ...) @printf (ptr noundef @.str, i32 noundef %R5)
	%R27 = icmp ne i32 %R5, 0
	br i1 %R27, label %tag28, label %tag29

tag28:
	%R6 = call i32 (ptr, ...) @printf (ptr noundef @.str.1)
	%R7 = call i32 (ptr, ...) @printf (ptr noundef @.str.2)
	br label %tag29

tag29:
	%R8 = load i32, i32* @b
	%R24 = icmp ne i32 %R8, 0
	br i1 %R24, label %tag25, label %tag26

tag25:
	%R9 = call i32 (ptr, ...) @printf (ptr noundef @.str.3)
	br label %tag26

tag26:
	br label %tag20

tag20:
	%R10 = load i32, i32* @c
	%R23 = icmp ne i32 %R10, 0
	br i1 %R23, label %tag21, label %tag22

tag21:
	%R11 = call i32 (ptr, ...) @printf (ptr noundef @.str.4)
	%R12 = load i32, i32* @c
	%R13 = call i32 (ptr, ...) @printf (ptr noundef @.str, i32 noundef %R12)
	%R14 = call i32 (ptr, ...) @printf (ptr noundef @.str.2)
	%R15 = load i32, i32* @c
	%R16 = add i32 0, 2
	%R17 = sub i32 %R15, %R16
	%R18 = add i32 0, 1
	%R19 = add i32 %R17, %R18
	store i32 %R19, i32* @c
	br label %tag20

tag22:
	%R30 = call i32 (ptr, ...) @printf (ptr noundef @.str.6)
	%R31 = call i32 (ptr, ...) @printf (ptr noundef @.str.2)
	 ret i32 0
}
declare i32 @printf(ptr noundef, ...) #1
