; ModuleID = '<stdin>'
source_filename = "<stdin>"

@glob = global i8 1

define void @test() !dbg !5 {
  tail call void @llvm.dbg.value(metadata i32 1, metadata !9, metadata !DIExpression(DW_OP_plus_uconst, 2, DW_OP_stack_value)), !dbg !12
  tail call void @llvm.dbg.value(metadata i32 1, metadata !11, metadata !DIExpression(DW_OP_plus_uconst, 2, DW_OP_constu, 1, DW_OP_minus, DW_OP_stack_value)), !dbg !13
  ret void, !dbg !14
}

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #0

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #0

define i32 @test_lifetime_alloca() !dbg !15 {
  tail call void @llvm.dbg.value(metadata ptr poison, metadata !17, metadata !DIExpression()), !dbg !19
  ret i32 0, !dbg !20
}

define i32 @test_lifetime_arg(ptr %0) !dbg !21 {
  tail call void @llvm.dbg.value(metadata i32 0, metadata !23, metadata !DIExpression()), !dbg !24
  ret i32 0, !dbg !24
}

define i32 @test_lifetime_global() !dbg !25 {
  tail call void @llvm.dbg.value(metadata i32 0, metadata !27, metadata !DIExpression()), !dbg !28
  ret i32 0, !dbg !28
}

define i32 @test_lifetime_bitcast(ptr %arg) !dbg !29 {
  %cast = bitcast ptr %arg to ptr, !dbg !32
  tail call void @llvm.dbg.value(metadata ptr %cast, metadata !31, metadata !DIExpression()), !dbg !32
  call void @llvm.lifetime.start.p0(i64 -1, ptr %cast), !dbg !33
  call void @llvm.lifetime.end.p0(i64 -1, ptr %cast), !dbg !34
  ret i32 0, !dbg !35
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.value(metadata, metadata, metadata) #1

attributes #0 = { nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }

!llvm.dbg.cu = !{!0}
!llvm.debugify = !{!2, !3}
!llvm.module.flags = !{!4}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "debugify", isOptimized: true, runtimeVersion: 0, emissionKind: FullDebug)
!1 = !DIFile(filename: "<stdin>", directory: "/")
!2 = !{i32 17}
!3 = !{i32 6}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = distinct !DISubprogram(name: "test", linkageName: "test", scope: null, file: !1, line: 1, type: !6, scopeLine: 1, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !8)
!6 = !DISubroutineType(types: !7)
!7 = !{}
!8 = !{!9, !11}
!9 = !DILocalVariable(name: "1", scope: !5, file: !1, line: 1, type: !10)
!10 = !DIBasicType(name: "ty32", size: 32, encoding: DW_ATE_unsigned)
!11 = !DILocalVariable(name: "2", scope: !5, file: !1, line: 2, type: !10)
!12 = !DILocation(line: 1, column: 1, scope: !5)
!13 = !DILocation(line: 2, column: 1, scope: !5)
!14 = !DILocation(line: 3, column: 1, scope: !5)
!15 = distinct !DISubprogram(name: "test_lifetime_alloca", linkageName: "test_lifetime_alloca", scope: null, file: !1, line: 4, type: !6, scopeLine: 4, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !16)
!16 = !{!17}
!17 = !DILocalVariable(name: "3", scope: !15, file: !1, line: 4, type: !18)
!18 = !DIBasicType(name: "ty64", size: 64, encoding: DW_ATE_unsigned)
!19 = !DILocation(line: 4, column: 1, scope: !15)
!20 = !DILocation(line: 7, column: 1, scope: !15)
!21 = distinct !DISubprogram(name: "test_lifetime_arg", linkageName: "test_lifetime_arg", scope: null, file: !1, line: 8, type: !6, scopeLine: 8, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !22)
!22 = !{!23}
!23 = !DILocalVariable(name: "4", scope: !21, file: !1, line: 10, type: !10)
!24 = !DILocation(line: 10, column: 1, scope: !21)
!25 = distinct !DISubprogram(name: "test_lifetime_global", linkageName: "test_lifetime_global", scope: null, file: !1, line: 11, type: !6, scopeLine: 11, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !26)
!26 = !{!27}
!27 = !DILocalVariable(name: "5", scope: !25, file: !1, line: 13, type: !10)
!28 = !DILocation(line: 13, column: 1, scope: !25)
!29 = distinct !DISubprogram(name: "test_lifetime_bitcast", linkageName: "test_lifetime_bitcast", scope: null, file: !1, line: 14, type: !6, scopeLine: 14, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !30)
!30 = !{!31}
!31 = !DILocalVariable(name: "6", scope: !29, file: !1, line: 14, type: !18)
!32 = !DILocation(line: 14, column: 1, scope: !29)
!33 = !DILocation(line: 15, column: 1, scope: !29)
!34 = !DILocation(line: 16, column: 1, scope: !29)
!35 = !DILocation(line: 17, column: 1, scope: !29)
